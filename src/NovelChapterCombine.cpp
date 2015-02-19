/*
 * NovelChapterCombine.cpp
 *
 *  Created on: 2015年2月19日
 *      Author: nemo
 */

#include "header/NovelChapterCombine.h"
#include <iostream>

using namespace std;

NovelChapterCombine::NovelChapterCombine()
{
	checkWorkingDirectory();

}

NovelChapterCombine::~NovelChapterCombine()
{
	// TODO Auto-generated destructor stub
}

void NovelChapterCombine::combineChapter()
{
	analysisFile();
	if(_inputNovel.size() == 0)
	{
		cout << "No input file." << endl;
		exit(0);
	}

	for(auto iter = _inputNovel.begin(); iter != _inputNovel.end(); iter++)
	{
		int err = fileOpen(*iter, false, "nOutout");

		if(err != 0)
		{
			cout << "File open Error(" << err << ")." << endl;
			fileClosed();
			continue;
		}

		parseContents();
		fileClosed();
	}
	fileClosed();
}

///		Parse novel contents and combine to one file.
void NovelChapterCombine::parseContents()
{
	unsigned int maxReadSize = 204800;
	char readBuf[maxReadSize];

	while (true)
	{
		if(_fileInStream)
		{
			_fileInStream.getline(readBuf, maxReadSize);
			string readString = readBuf;

			outputContents(readString);
		}
		else
		{
			cout << "File end." << endl << endl;
			break;
		}
	}
}
