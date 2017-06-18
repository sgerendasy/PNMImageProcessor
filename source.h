#ifndef SOURCE_H
#define SOURCE_H
#include "image.h"
struct Image;
class Source
{
    public:
    virtual void SetSize(int w, int h);
    virtual Image* GetOutput();
    virtual const char* SourceName() = 0;
    virtual void Update();
    friend struct Image;

protected:
    virtual void Execute() = 0;
    Image imgOutput;
};
#endif //SOURCE_H