#include <stdio.h>
#include <cstring>
#include "image.h"
#include "PNMreader.h"


PNMreader::PNMreader()
{
    fileName = NULL;
    GetOutput()->myFilter = this;
    filterName = (char*) "PNMreader";
}

PNMreader::~PNMreader()
{
    if(fileName != NULL){
        delete[](fileName);
    }
}

PNMreader::PNMreader(char* fName)
{
    fileName = new char[strlen(fName)+1];
    strcpy(fileName, fName);
    GetOutput()->myFilter = this;
    filterName = (char*) "PNMreader";
}

const char* PNMreader::FilterName()
{
    return filterName;
}

void PNMreader::Execute() {

    char msg[128];
    sprintf(msg, "%s: about to execute", FilterName());
    Logger::LogEvent(msg);

    FILE* f_in = fopen(fileName, "rb");
    if(!f_in){
        char errorMsg[1024];
        sprintf(errorMsg, "Exception found!");
        DataFlowException e(SourceName(), errorMsg);
        throw e;
    }
    char magicNum[128];
    int width, height, maxval;
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    SetSize(width, height);
    int bytesToRead = height * width;
    fread(GetOutput()->getPixel(), bytesToRead * sizeof(Pixel), 1, f_in);
    fclose(f_in);
    sprintf(msg, "%s: done executing", FilterName());
    Logger::LogEvent(msg);
}
