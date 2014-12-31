/*
 * FileUtils.h
 *
 *  Created on: 2014/8/4
 *      Author: leo
 */

#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>

namespace FileUtils {

    inline bool fileExist(const char* filePath) {
        struct stat buf;
        int result = stat(filePath, &buf);

        return (result == 0);
    }

    static bool createDir(const char* dirPath) {
        if (!fileExist(dirPath)) {
            if (mkdir(dirPath, 0700) == -1)
                return false;
        }
        return true;
    }

    static bool copyFile(const char* srcFilePath, const char* destFilePath) {
        if (!fileExist(srcFilePath))
            return false;

        std::ifstream src(srcFilePath,  std::ios::binary);
        std::ofstream dst(destFilePath, std::ios::binary);

        printf("CopyFile successfully from %s ... %s", srcFilePath, destFilePath);

        dst << src.rdbuf();
        return true;
    }

    static bool moveFile(const char* srcFilePath, const char* destFilePath) {
        if (rename(srcFilePath, destFilePath) == 0) {
        	printf("MoveFile successfully from %s ... %s", srcFilePath, destFilePath);
            return true;

        } else {
        	printf("Error renaming file from %s ... %s", srcFilePath, destFilePath);
            return false;
        }
    }

    static bool removeFile(const char* filePath) {
        if (fileExist(filePath) && remove(filePath) != 0) {
        	printf("Error deleting file %s", filePath);
            return false;

        } else {
        	printf("File successfully deleted %s", filePath);
            return true;
        }
    }
}

#endif /* FILEUTILS_H_ */
