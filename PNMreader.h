#ifndef PNMREADER_H
#define PNMREADER_H

#include "source.h"
#include "logging.h"

class PNMreader : public Source{
public:
    PNMreader();
    PNMreader(char*);
    ~PNMreader();
    virtual const char* SourceName(){return FilterName();};
    virtual const char* FilterName();
    char* filterName;
    char* fileName;
    void Execute();

};

#endif //PNMREADER_H
