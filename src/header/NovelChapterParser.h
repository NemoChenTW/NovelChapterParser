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
#include <vector>

using namespace std;

class NovelChapterParser {
public:
	NovelChapterParser();
	virtual ~NovelChapterParser();

	///		Parse the novel chapter.
	void parseChapter();

private:
	fstream 		_fileInStream;		///< The file input stream.
	fstream 		_fileOutStream;		///< The file out stream.

	string			_tempDir;			///< The temp folder directory path.
	string			_resultDir;			///< The result folder directory path.

	list<regex> 	_regexList;			///< Regular expression list.
	vector<string> 	_inputNovel;		///< The input file name.

	///		Set default regular expression.
	void setDefaultRegExp();

	///		Set regular expression.
	void setRegularExp(string regularExpression);

	///		Check the work directory.
	void checkWorkingDirectory();

	///		Open in and out file.
	int fileOpen(string novelName);

	///		Close in and out files.
	void fileClosed();

	///		Analysis the temp folder.
	void analysisFile();

	///		Parse the novel contents.
	void parseContents();

	void outputContents(string contents);		///< Output contents to the new file.

};

#endif /* NOVELCHAPTERPARSER_H_ */
