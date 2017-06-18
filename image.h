#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

class Source;

struct Pixel
{
    unsigned char r,g,b;
};

struct Image{
public:
    Image(void);
    Image(int w, int h);
    Image(Image&);

    int getWidth() const;
    int getHeight() const;
    Pixel* getPixel() const;

    void setWidth(int);
    void setHeight(int);
    void setPixel();
    virtual void Update() const;
    //void setUpdate(bool);

    Source* myFilter;
    mutable bool updated;

private:
    int width;
    int height;
    Pixel* pixel;

};

#endif //IMAGE_H
