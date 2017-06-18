#include <stdlib.h>
#include "image.h"
#include "source.h"

#include <iostream>

Image::Image(void)
{
    width = 0;
    height= 0;
    updated = false;
    myFilter = NULL;
}

Image::Image(int w, int h)
{
    width = w;
    height = h;
    pixel = (Pixel*) malloc(w * h * sizeof(Pixel));
}

Image::Image(Image &img)
{
    width = img.width;
    height = img.height;
    pixel = (Pixel*) malloc(sizeof(Pixel) * height * width);
    *pixel = *img.pixel;
}

int Image::getHeight() const
{
    return height;
}

int Image::getWidth() const
{
    return width;
}

Pixel* Image::getPixel() const
{
    return pixel;
}

void Image::setHeight(int h)
{
    height = h;
}

void Image::setWidth(int w)
{
    width = w;
}

void Image::setPixel()
{
    pixel = (Pixel*) malloc(width * height * sizeof(Pixel));
}

void Image::Update() const
{

    if(!updated)
    {
        updated = true;
        myFilter->Execute();
    }

}
