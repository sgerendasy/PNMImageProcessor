#ifndef FILTERS_H
#define FILTERS_H

#include "image.h"
#include "sink.h"
#include "source.h"
#include "logging.h"


/* ============= Filter ============= */
class Filter : public Source, public Sink
{
public:
    virtual const char* FilterName();
    char* filterName;
    const char* SourceName(){return FilterName();};
    const char* SinkName(){return FilterName();};

};

/* ============= Color (Source) ============= */
class Color : public Source
{
public:
    Color(int, int, unsigned char, unsigned char, unsigned char);
    virtual void Execute();
    const char* SourceName(){return filterName;};
    char* filterName;

protected:
    int colorWidth;
    int colorHeight;
    unsigned char colorRed;
    unsigned char colorBlue;
    unsigned char colorGreen;
};


/* ============= Checksum (Sink) ============= */
class CheckSum : public Sink
{
public:
    CheckSum();
    const char* SinkName(){return filterName;};
    char* filterName;
    void OutputCheckSum(char*);

protected:
    unsigned char redTotal;
    unsigned char greenTotal;
    unsigned char blueTotal;
};


/* ============= Mirror ============= */
class Mirror : public Filter
{
public:
    Mirror();
    virtual void Execute();
    virtual const char* FilterName(){return filterName;};
};


/* ============= Rotate ============= */
class Rotate : public Filter
{
public:
    Rotate();
    virtual void Execute();
    virtual const char* FilterName(){return filterName;};
};


/* ============= Subtract ============= */
class Subtract : public Filter
{
public:
    Subtract();
    virtual void Execute();
    virtual const char* FilterName(){return filterName;};
};


/* ============= Grayscale ============= */
class Grayscale : public Filter
{
public:
    Grayscale();
    virtual void Execute();
    virtual const char* FilterName(){ return filterName;};
};


/* ============= Blur ============= */
class Blur : public Filter
{
public:
    Blur();
    virtual void Execute();
    virtual const char* FilterName(){ return filterName;};
};



/* ============= Shrinker ============= */

class Shrinker : public Filter{
public:
    Shrinker();
    virtual void Execute();
    virtual const char* FilterName(){return filterName;};
};

/* ============= LRConcat ============= */

class LRConcat : public Filter{
public:
    LRConcat();
    virtual void Execute();
    virtual const char* FilterName(){return filterName;};

};

/* ============= TBConcat ============= */

class TBConcat : public Filter{
public:
    TBConcat();
    void Execute();
    virtual const char* FilterName(){return filterName;};

};

/* ============= Blender ============= */

class Blender : public Filter{
public:
    Blender();
    void SetFactor(float);
    void Execute();
    virtual const char* FilterName(){return filterName;};

private:
    float factor;
    Pixel blender(Pixel, Pixel, float);

};

#endif //FILTERS_H
