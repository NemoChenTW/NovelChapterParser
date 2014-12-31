/*
 * main.cpp
 *
 *  Created on: 2014年11月28日
 *      Author: nemo
 */


#include <iostream>
#include <string>
#include <regex>
#include <sstream>

#include "src/libNovelChapterParser.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Start" << endl;

	if(argc != 2)
	{
		cout << "Wrong argument." << endl;
		exit(-1);
	}
	string filePath = argv[1];

	filePath = "劍噬虛空乾坤逆亂.txt";
	NovelChapterParser novelParser(filePath);
	int err = novelParser.fileOpen();
	if(err != 0)
	{
		cout << "File open error (" << err << ")" << endl;
		exit(-1);
	}

	//TODO Load from file.
	novelParser.setRegularExp("第[0-9]+章.*");
	novelParser.setRegularExp("第[零一二三四五六七八九十百千零壹貳參肆伍陸柒捌玖拾佰仟]+章.*");

	cout << "Prepare parse chapter." << endl;
	novelParser.parseChapter();

//	try
//	{
//		stringstream tmpSS;
//
//		regex reg("第[0-9]+章.*");
//		std::string s = "第1365章 神魔遮天 QQ 第1366章 GG \n第1367章 GG惹";
//
//		smatch mat;
//		std::cout << "Matched: " << regex_search(s, mat, reg) << std::endl;
//
//		cout << *(mat.begin()) << endl;
//
//
//		ssub_match prefix = mat.prefix();
//		std::string str_prefix(prefix.first, prefix.second);
//		std::cout << "Prefix: " << str_prefix << std::endl;
//		std::cout << "Length: " << prefix.length() << std::endl;
//
//	}
//	catch (const regex_error& e)
//	{
//		std::cout << "Error: " << e.what() << std::endl;
//	}

	return 0;
}
