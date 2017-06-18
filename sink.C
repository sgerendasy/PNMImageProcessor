#include "sink.h"

void Sink::SetInput(Image *img1)
{
    imgInput1 = img1;
    assignedImg1 = true;
}

void Sink::SetInput2(Image *img2)
{
    imgInput2 = img2;
    assignedImg2 = true;
}

const Image* Sink::GetInput1()
{
    return imgInput1;
}
const Image* Sink::GetInput2()
{
    return imgInput2;
}