/*
 * NovelProcessTool.cpp
 *
 *  Created on: 2015年2月19日
 *      Author: nemo
 */

#include "header/NovelProcessTool.h"
#include "Utility/FileUtils.h"

#include <iostream>
#include <dirent.h>

NovelProcessTool::NovelProcessTool()
{
	// TODO Auto-generated constructor stub

}

NovelProcessTool::~NovelProcessTool()
{
	// TODO Auto-generated destructor stub
}

/**
 * @brief	Check the work directory.
 *
 * Create working directories if they are not exist.
 */
void NovelProcessTool::checkWorkingDirectory()
{
	_tempDir = "temp";
	_resultDir = "result";

	FileUtils::createDir(_tempDir.c_str());
	FileUtils::createDir(_resultDir.c_str());
}

/**
 * @brief	Open in and out file.
 *
 * @param 	novelName	Input file name.
 *
 * @retval	 0	File open success.
 * @retval	-1	File open fail.
 * @retval	-2	File path is empty.
 * @retval	-3	Output file open failed.
 */
int NovelProcessTool::fileOpen(string novelName, bool sameAsInputName, string oNovelName)
{
	if(!novelName.empty())
	{
		string inFilePath = _tempDir + "/" + novelName;
		string outFilePath = _resultDir + "/" + novelName;

		_fileInStream.open(inFilePath.c_str(), ios::in);

		if (!_fileInStream)
			return -1;
		else
		{
			cout << novelName << endl;
			_fileOutStream.open(outFilePath.c_str(), ios::out);
			if(!_fileOutStream)
				return -3;

			return 0;
		}
	}
	else
	{
		return -2;
	}
}

/**
 * @brief	Close in and out files.
 */
void NovelProcessTool::fileClosed()
{
	_fileInStream.close();
	_fileOutStream.close();
}

/**
 * @brief	Analysis the temp folder.
 *
 * Analysis the temp folder, and save the file name.
 */
void NovelProcessTool::analysisFile()
{
	struct dirent **namelist;
	int fileCount = scandir(_tempDir.c_str(), &namelist, 0, alphasort);
	if(fileCount < 0)
	{
		perror("scandir");
	}
	else
	{
		for(int i = 0; i < fileCount; i++)
		{
			string fileName = namelist[i]->d_name;
			if(fileName == "." || fileName == "..")
				continue;
			else if(fileName[fileName.length()-1] == '~')
				continue;
			else
				_inputNovel.push_back(namelist[i]->d_name);
		}
	}
	free(namelist);
}
