/*
 * NovelChapterParser.cpp
 *
 *  Created on: 2014年11月28日
 *      Author: nemo
 */

#include "header/NovelChapterParser.h"
#include "Utility/FileUtils.h"

#include <iostream>

NovelChapterParser::NovelChapterParser()
{
	checkWorkingDirectory();

	setDefaultRegExp();
}

NovelChapterParser::~NovelChapterParser()
{
	fileClosed();
}

/**
 * @brief	Set default regular expression.
 */
void NovelChapterParser::setDefaultRegExp()
{
	setRegularExp("第[0-9]+章.{0,15}\\s+");
	setRegularExp("第[零一二三四五六七八九十百千零壹貳參肆伍陸柒捌玖拾佰仟]+章.{0,15}\\s+");
	setRegularExp("楔.{0,5}子.{0,15}\\s+");
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
 * @brief	Parse the novel contents.
 */
void NovelChapterParser::parseContents()
{

	unsigned int maxReadSize = 204800;
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
					break;
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
