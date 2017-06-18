#include "image.h"
#include "source.h"
#include "logging.h"
#include <stdio.h>
#include <iostream>
void Source::SetSize(int w, int h)
{
    imgOutput.setWidth(w);
    imgOutput.setHeight(h);
    imgOutput.setPixel();
}
Image* Source::GetOutput()
{
    return &imgOutput;
}

void Source::Update()
{
    std::cerr << "hereUpdate" << SourceName() <<  std::endl;
    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}
