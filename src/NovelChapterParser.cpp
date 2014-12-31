/*
 * NovelChapterParser.cpp
 *
 *  Created on: 2014年11月28日
 *      Author: nemo
 */

#include "header/NovelChapterParser.h"
#include <iostream>

NovelChapterParser::NovelChapterParser(string filePath)
{
	_novelPath.clear();
	_novelPath = filePath;
}

NovelChapterParser::~NovelChapterParser()
{
	fileClosed();
}

/**
 * @brief	Open file
 *
 * @param 	filePath	Input file path.
 *
 * @retval	 0	File open success.
 * @retval	-1	File open fail.
 * @retval	-2	File path is empty.
 * @retval	-3	Output file open failed.
 */
int NovelChapterParser::fileOpen()
{
	if(!_novelPath.empty())
	{
		_fileInStream.open(_novelPath.c_str(), ios::in);

		if (!_fileInStream)
			return -1;
		else
		{
			string outputNovelPath = _novelPath + ".chaptered";
			_fileOutStream.open(outputNovelPath.c_str(), ios::out);
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
 * @brief	Close file.
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
			cout << "File closed." << endl;
			break;
		}
	}

	fileClosed();
}

/**
 * @brief	Output contents to the new file.
 */
void NovelChapterParser::outputContents(string contents)
{
	_fileOutStream << contents;
}
