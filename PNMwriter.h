#ifndef PNMWRITER_H
#define PNMWRITER_H

#include "image.h"
#include "sink.h"

class PNMwriter : public Sink{
public:
    PNMwriter();
    void Write(char*);
    virtual const char* SinkName(){return FilterName();};
    virtual const char* FilterName();
    char* filterName;
};

#endif //PNMWRITER_H
