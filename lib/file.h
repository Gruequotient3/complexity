#ifndef FILE_H
#define FILE_H

#include <stdio.h>

FILE* openFile(const char* path, const char* mode);
void closeFile(FILE* file);

void writeData2(FILE* file, double x, double y);
void writeData3(FILE* file, double x, double y, double z);




#endif
