/*
 * NovelChapterParser.cpp
 *
 *  Created on: 2014年11月28日
 *      Author: nemo
 */

#include "header/NovelChapterParser.h"
#include "Utility/FileUtils.h"

#include <iostream>
#include <dirent.h>

NovelChapterParser::NovelChapterParser()
{
	_tempDir = "temp";
	_resultDir = "result";

	FileUtils::createDir(_tempDir.c_str());
	FileUtils::createDir(_resultDir.c_str());
}

NovelChapterParser::~NovelChapterParser()
{
	fileClosed();
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
int NovelChapterParser::fileOpen(string novelName)
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
void NovelChapterParser::fileClosed()
{
	_fileInStream.close();
	_fileOutStream.close();
}

/**
 * @brief	Set regular expression.
 *
 * @param regularExpression		Input regular expression.
 */
void NovelChapterParser::setRegularExp(string regularExpression)
{
	_regexList.push_back(regex(regularExpression));
}

/**
 * @brief	Parse the novel chapter.
 *
 * Parse the novel chapter according to the setting regular expression.
 */
void NovelChapterParser::parseChapter()
{
	analysisFile();
	if(_inputNovel.size() == 0)
	{
		cout << "No input file." << endl;
		exit(0);
	}

	for(auto iter = _inputNovel.begin(); iter != _inputNovel.end(); iter++)
	{
		int err = fileOpen(*iter);

		if(err != 0)
		{
			cout << "File open Error(" << err << ")." << endl;
			fileClosed();
			continue;
		}

		parseContents();
		fileClosed();
	}

}

/**
 * @brief	Analysis the temp folder.
 *
 * Analysis the temp folder, and save the file name.
 */
void NovelChapterParser::analysisFile()
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

/**
 * @brief	Parse the novel contents.
 */
void NovelChapterParser::parseContents()
{

	unsigned int maxReadSize = 1024;
	char readBuf[maxReadSize];

	while (true)
	{
		if(_fileInStream)
		{
			_fileInStream.getline(readBuf, maxReadSize);
			string readString = readBuf;
			if(readString.empty())
			{
				outputContents(readString);
				continue;
			}

			bool isChapter = false;
			for(auto iter = _regexList.begin(); iter != _regexList.end(); iter++)
			{
				smatch mat;
				regex_search(readString, mat, *iter);

				string matchResult = *(mat.begin());
				if (!matchResult.empty())
				{
					cout << matchResult << endl;

					string chapterString;
					chapterString = "<chapter> " + readString;
					outputContents(chapterString);
					isChapter = true;
				}
			}
			if( !isChapter )
				outputContents(readString);

		}
		else
		{
			cout << "File closed." << endl << endl;
			break;
		}
	}
}

/**
 * @brief	Output contents to the new file.
 */
void NovelChapterParser::outputContents(string contents)
{
	_fileOutStream << contents;
}
