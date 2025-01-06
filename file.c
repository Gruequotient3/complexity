#ifndef FILE_C
#define FILE_C

#include <assert.h>

#include <file.h>


FILE* openFile(const char* path, const char* mode){
    return fopen(path, mode);
}


void closeFile(FILE* file){
    fclose(file);
}


void writeData2(FILE* file, double x, double y){
    assert(file);
    fprintf(file, "%f\t%f\n", x, y);
}

void writeData3(FILE* file, double x, double y, double z){
    assert(file);
    fprintf(file, "%f\t%f\t%f\n", x, y, z);
}


#endif
