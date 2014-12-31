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
	// TODO Auto-generated destructor stub
}

/**
 * @brief	Open file
 *
 * @param 	filePath	Input file path.
 *
 * @retval	 0	File open success.
 * @retval	-1	File open fail.
 * @retval	-2	File path is empty.
 */
int NovelChapterParser::fileOpen()
{
	if(!_novelPath.empty())
	{
		_fileStream.open(_novelPath.c_str(), ios::in|ios::out);

		if (!_fileStream)
			return -1;
		else
		{
			return 0;
		}
	}
	else
	{
		return -2;
	}
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
		if(_fileStream)
		{
			_fileStream.getline(readBuf, maxReadSize);
			string readString = readBuf;
			if(readString.empty())
				continue;

			for(auto iter = _regexList.begin(); iter != _regexList.end(); iter++)
			{
				smatch mat;
				regex_search(readString, mat, *iter);

				string matchResult = *(mat.begin());
				if (!matchResult.empty())
				{
					cout << matchResult << endl;
				}
			}

		}
		else
		{
			cout << "File closed." << endl;
			break;
		}
	}

}
