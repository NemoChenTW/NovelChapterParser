/*
 * NovelChapterCombine.h
 *
 *  Created on: 2015年2月19日
 *      Author: nemo
 */

#ifndef SRC_NOVELCHAPTERCOMBINE_H_
#define SRC_NOVELCHAPTERCOMBINE_H_

#include "header/NovelProcessTool.h"

class NovelChapterCombine: public NovelProcessTool {
public:
	NovelChapterCombine();
	virtual ~NovelChapterCombine();

	void combineChapter();

private:

	///		Parse novel contents and combine to one file.
	void parseContents();
};

#endif /* SRC_NOVELCHAPTERCOMBINE_H_ */
