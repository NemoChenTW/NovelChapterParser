/*
 * NovelChapterParser.h
 *
 *  Created on: 2014年11月28日
 *      Author: nemo
 */

#ifndef NOVELCHAPTERPARSER_H_
#define NOVELCHAPTERPARSER_H_

#include <string>
#include <fstream>
#include <regex>
#include <list>

#include "NovelProcessTool.h"

using namespace std;

class NovelChapterParser: public NovelProcessTool {
public:
	NovelChapterParser();
	virtual ~NovelChapterParser();

	///		Parse the novel chapter.
	void parseChapter();

private:

	list<regex> 	_regexList;			///< Regular expression list.

	///		Set default regular expression.
	void setDefaultRegExp();

	///		Set regular expression.
	void setRegularExp(string regularExpression);

	///		Parse the novel contents.
	void parseContents();

};

#endif /* NOVELCHAPTERPARSER_H_ */
