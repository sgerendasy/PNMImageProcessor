#ifndef SINK_H
#define SINK_H
#include "image.h"
struct Image;
class Sink{
public:
    virtual void SetInput(Image* img1);
    virtual void SetInput2(Image* img2);
    virtual const Image* GetInput1();
    virtual const Image* GetInput2();
    virtual const char* SinkName() = 0;
    bool assignedImg1;
    bool assignedImg2;

protected:
    const Image* imgInput1; // make const
    const Image* imgInput2; // make const

};
#endif //SINK_H
