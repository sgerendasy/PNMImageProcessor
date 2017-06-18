#include <stdio.h>
#include <iostream>
#include "PNMwriter.h"

PNMwriter::PNMwriter() {}

void PNMwriter::Write(char* outputFileName)
{
    FILE* fp = fopen(outputFileName, "w");
    std::cerr << "output file" << fp << std::endl;
    if(!fp)
    {
        std::cerr << "No output file" << std::endl;
    }
    int imgWidth = GetInput1()->getWidth();
    int imgHeight = GetInput1()->getHeight();
    int bytes = imgWidth * imgHeight;

    fprintf(fp, "%s\n%d %d\n%d\n", "P6", imgWidth, imgHeight, 255);
    fwrite(GetInput1()->getPixel(), sizeof(Pixel) * bytes, 1, fp);
    fclose(fp);
}

const char* PNMwriter::FilterName()
{
    return filterName;
}