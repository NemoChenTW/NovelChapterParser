/*
 * NovelProcessTool.h
 *
 *  Created on: 2015年2月19日
 *      Author: nemo
 */

#ifndef SRC_NOVELPROCESSTOOL_H_
#define SRC_NOVELPROCESSTOOL_H_

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class NovelProcessTool {
public:
	NovelProcessTool();
	virtual ~NovelProcessTool();

protected:

	///		Check the work directory.
	void checkWorkingDirectory();

	///		Open in and out file.
	int fileOpen(string novelName, bool sameAsInputName = true, string oNovelName = "");

	///		Close in and out files.
	void fileClosed(int closeOption = 2);

	///		Analysis the temp folder.
	void analysisFile();

	///		Novel tool action, implement in sub class.
	virtual void parseContents() = 0;

	fstream 		_fileInStream;		///< The file input stream.
	fstream 		_fileOutStream;		///< The file out stream.

	string			_tempDir;			///< The temp folder directory path.
	string			_resultDir;			///< The result folder directory path.

	vector<string> 	_inputNovel;		///< The input file name.
};

#endif /* SRC_NOVELPROCESSTOOL_H_ */
