
#include <iostream>
#include "filters.h"

/* ============= Filter ============= */
const char* Filter::FilterName()
{
    return filterName;
}


/* ============= Color ============= */
Color::Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
    filterName = (char*) "Color";
    GetOutput()->myFilter = this;
    colorWidth = w;
    colorHeight = h;
    colorRed = r;
    colorGreen = g;
    colorBlue = b;
}

void Color::Execute()
{
    SetSize(colorWidth, colorHeight);
    for(int i = 0; i < colorHeight; i++)
    {
        for(int j = 0; j < colorWidth; j++)
        {
            GetOutput()->getPixel()[i*colorWidth + j].r = colorRed;
            GetOutput()->getPixel()[i*colorWidth + j].g = colorGreen;
            GetOutput()->getPixel()[i*colorWidth + j].b = colorBlue;
        }
    }
}


/* ============= CheckSum ============= */
CheckSum::CheckSum()
{
    filterName = (char*) "CheckSum";
}

void CheckSum::OutputCheckSum(char * outputFileName)
{
    // check if input assigned
    int width = GetInput1()->getWidth();
    int height = GetInput1()->getHeight();
    redTotal = 0;
    greenTotal = 0;
    blueTotal = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            redTotal += GetInput1()->getPixel()[i*width + j].r;
            greenTotal += GetInput1()->getPixel()[i*width + j].g;
            blueTotal += GetInput1()->getPixel()[i*width + j].b;
        }
    }
    FILE* checkSumOutput = fopen(outputFileName, "w");
    fprintf(checkSumOutput, "CHECKSUM: %d, %d, %d\n", redTotal, greenTotal, blueTotal);
    fclose(checkSumOutput);
}


/* ============= Mirror ============= */
Mirror::Mirror()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "Mirror";
    assignedImg1 = false;
    assignedImg2 = false;
}

void Mirror::Execute()
{
    char msg[128];
    if(!assignedImg1)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }

    int width = GetInput1()->getWidth();
    int height = GetInput1()->getHeight();
    SetSize(width, height);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            GetOutput()->getPixel()[(i*width) + j] = GetInput1()->getPixel()[(i*width)+(width - j - 1)];
        }
    }
}


/* ============= Rotate ============= */
Rotate::Rotate()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "Rotate";
    assignedImg1 = false;
    assignedImg2 = false;


}

void Rotate::Execute()
{

    char msg[128];
    if(!assignedImg1)
    {

        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }
    int width = GetInput1()->getWidth();
    int height = GetInput1()->getHeight();
    SetSize(height, width);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            GetOutput()->getPixel()[(j*height + (height - 1 - i))] = GetInput1()->getPixel()[(i*width)+j];
        }
    }
}


/* ============= Subtract ============= */
Subtract::Subtract()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "Subtract";
    assignedImg1 = false;
    assignedImg2 = false;
}

void Subtract::Execute()
{
    char msg[128];
    if(!assignedImg1)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }

    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);

    }

    if (!assignedImg2)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input2!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }

    if(!GetInput2()->updated)
    {
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        GetInput2()->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg);
    }
    int width = GetInput1()->getWidth();
    int height = GetInput1()->getHeight();

    if(width != GetInput2()->getWidth() || height != GetInput2()->getHeight())
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Exception found!");
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }

    SetSize(width, height);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            GetOutput()->getPixel()[(i*width) + j].r =
                    (GetInput1()->getPixel()[(i*width)+j].r - GetInput2()->getPixel()[(i*width)+j].r) > 0?
                    (GetInput1()->getPixel()[(i*width)+j].r - GetInput2()->getPixel()[(i*width)+j].r) : (unsigned char) 0;
            GetOutput()->getPixel()[(i*width) + j].g =
                    (GetInput1()->getPixel()[(i*width)+j].g - GetInput2()->getPixel()[(i*width)+j].g) > 0?
                    (GetInput1()->getPixel()[(i*width)+j].g - GetInput2()->getPixel()[(i*width)+j].g) : (unsigned char) 0;
            GetOutput()->getPixel()[(i*width) + j].b =
                    (GetInput1()->getPixel()[(i*width)+j].b - GetInput2()->getPixel()[(i*width)+j].b) > 0?
                    (GetInput1()->getPixel()[(i*width)+j].b - GetInput2()->getPixel()[(i*width)+j].b) : (unsigned char) 0;
        }
    }
}


/* ============= Grayscale ============= */
Grayscale::Grayscale()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "Grayscale";
    assignedImg1 = false;
    assignedImg2 = false;
}

void Grayscale::Execute()
{
    char msg[128];
    if(!assignedImg1)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }
    int width = GetInput1()->getWidth();
    int height = GetInput1()->getHeight();
    SetSize(width, height);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int grayColor = (GetInput1()->getPixel()[(i*width)+j].r / 5) +
                    (GetInput1()->getPixel()[(i*width)+j].g / 2) + (GetInput1()->getPixel()[(i*width)+j].b / 4);
            GetOutput()->getPixel()[i*width + j].r = (unsigned char) grayColor;
            GetOutput()->getPixel()[i*width + j].g = (unsigned char) grayColor;
            GetOutput()->getPixel()[i*width + j].b = (unsigned char) grayColor;
        }
    }
}


/* ============= Blur ============= */
Blur::Blur()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "Blur";
    assignedImg1 = false;
    assignedImg2 = false;
}

void Blur::Execute()
{
    char msg[128];
    if(!assignedImg1)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }
    int width = GetInput1()->getWidth();
    int height = GetInput1()->getHeight();
    SetSize(width, height);
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                GetOutput()->getPixel()[i*width + j] = GetInput1()->getPixel()[i*width+j];
            }
            else
            {
                GetOutput()->getPixel()[i*width + j].r = (unsigned char)(
                        GetInput1()->getPixel()[((i-1)*width) + (j-1)].r / 8 +
                        GetInput1()->getPixel()[(i*width) + (j-1)].r / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j-1)].r / 8 +
                        GetInput1()->getPixel()[((i-1)*width) + (j)].r / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j)].r / 8 +
                        GetInput1()->getPixel()[((i-1)*width) + (j+1)].r / 8 +
                        GetInput1()->getPixel()[((i)*width) + (j+1)].r / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j+1)].r / 8);

                GetOutput()->getPixel()[i*width + j].g = (unsigned char)(
                        GetInput1()->getPixel()[((i-1)*width) + (j-1)].g / 8 +
                        GetInput1()->getPixel()[(i*width) + (j-1)].g / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j-1)].g / 8 +
                        GetInput1()->getPixel()[((i-1)*width) + (j)].g / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j)].g / 8 +
                        GetInput1()->getPixel()[((i-1)*width) + (j+1)].g / 8 +
                        GetInput1()->getPixel()[((i)*width) + (j+1)].g / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j+1)].g / 8);

                GetOutput()->getPixel()[i*width + j].b = (unsigned char)(
                        GetInput1()->getPixel()[((i-1)*width) + (j-1)].b / 8 +
                        GetInput1()->getPixel()[(i*width) + (j-1)].b / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j-1)].b / 8 +
                        GetInput1()->getPixel()[((i-1)*width) + (j)].b / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j)].b / 8 +
                        GetInput1()->getPixel()[((i-1)*width) + (j+1)].b / 8 +
                        GetInput1()->getPixel()[((i)*width) + (j+1)].b / 8 +
                        GetInput1()->getPixel()[((i+1)*width) + (j+1)].b / 8);
            }

        }
    }
}


/* ============= Shrinker ============= */
Shrinker::Shrinker()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "Shrinker";
    assignedImg1 = false;
    assignedImg2 = false;
}

void Shrinker::Execute()
{
    char msg[128];
    if(!assignedImg1)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }

    int oldWidth = GetInput1()->getWidth();
    int newWidth = oldWidth / 2;
    int newHeight = GetInput1()->getHeight() / 2;
    SetSize(newWidth, newHeight);
    for (int i = 0; i < newHeight; i++)
    {
        for(int j = 0; j < newWidth; j++)
        {
            GetOutput()->getPixel()[(i*newWidth) + j] = GetInput1()->getPixel()[(i*2*oldWidth)+(j*2)];
        }
    }
}


/* ============= LRConcat ============= */

LRConcat::LRConcat()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "LRConcat";
    assignedImg1 = false;
    assignedImg2 = false;
}

void LRConcat::Execute()
{
    char msg[128];
    if(!assignedImg1)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);

    }
    if (!assignedImg2)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input2!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput2()->updated)
    {
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        GetInput2()->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg);
    }


    if (GetInput1()->getHeight() != GetInput2()->getHeight()) {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: heights must match: %d, %d", SinkName(),
                GetInput1()->getHeight(), GetInput2()->getHeight());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }


    else {
        int leftWidth = GetInput1()->getWidth();
        int rightWidth = GetInput2()->getWidth();
        int leftHeight = GetInput1()->getHeight();
        int rightHeight = GetInput2()->getHeight();

        int minWidth = (leftWidth < rightWidth)? leftWidth : rightWidth;
        int maxWidth = (leftWidth > rightWidth)? leftWidth : rightWidth;


        int newWidth = leftWidth + rightWidth;
        int newHeight = leftHeight;
        SetSize(newWidth, newHeight);

        //std::cerr << "new w: " << newWidth << " , new h: " << newHeight << " , pixel: " << GetOutput()->getPixel() << std::endl;
        //std::cerr << "minw: " << minWidth << " , maxw: " << maxWidth << std::endl;

        for(int i = 0; i < newHeight; i++)
        {
            for(int j = 0; j < minWidth; j++)
            {
                GetOutput()->getPixel()[(i*newWidth) + j] = GetInput1()->getPixel()[(i*leftWidth) + j];
                GetOutput()->getPixel()[(i*newWidth) + leftWidth + j] = GetInput2()->getPixel()[(i*rightWidth) + j];
            }
        }

        if(maxWidth == rightWidth){
            for (int i = 0; i < newHeight; i++){
                for (int j = minWidth; j < maxWidth; j++){
                    GetOutput()->getPixel()[(i*newWidth) + leftWidth + j] = GetInput2()->getPixel()[(i*rightWidth) + j];
                }

            }
        }
        else if(maxWidth == leftWidth) {
            for (int i = 0; i < newHeight; i++){
                for (int j = minWidth; j < maxWidth; j++){
                    GetOutput()->getPixel()[(i*newWidth) + j] = GetInput1()->getPixel()[(i*leftWidth) + j];
                }
            }
        }

        
    }
}


/* ============= TBConcat ============= */

TBConcat::TBConcat()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "TBConcat";
    assignedImg1 = false;
    assignedImg2 = false;
}

void TBConcat::Execute()
{
    char msg[128];
    if(!assignedImg1)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", FilterName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", FilterName());
        Logger::LogEvent(msg);
    }
    if (!assignedImg2)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input2!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput2()->updated)
    {
        sprintf(msg, "%s: about to update input2", FilterName());
        Logger::LogEvent(msg);
        GetInput2()->Update();
        sprintf(msg, "%s: done updating input2", FilterName());
        Logger::LogEvent(msg);
    }
    if (GetInput1()->getWidth() != GetInput2()->getWidth() )
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: widths must match: %d, %d", SinkName(),
                GetInput1()->getWidth(), GetInput2()->getWidth());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }

    else
    {
        int topHeight = GetInput1()->getHeight();
        int bottomHeight = GetInput2()->getHeight();
        int topWidth = GetInput1()->getWidth();

        int minHeight = (topHeight < bottomHeight)? topHeight : bottomHeight; // minHeight(input1, input2)
        int maxHeight = (topHeight > bottomHeight)? topHeight : bottomHeight; // maxHeight(input1, input2)

        int newWidth = topWidth;
        int newHeight = topHeight + bottomHeight;
        SetSize(newWidth, newHeight);
        for(int i = 0; i < minHeight; i++)
        {
            for(int j = 0; j < newWidth; j++)
            {
                GetOutput()->getPixel()[(i*newWidth) + j] = GetInput1()->getPixel()[(i*newWidth) + j];
                GetOutput()->getPixel()[((i+topHeight)*newWidth) + j] = GetInput2()->getPixel()[(i*newWidth) + j];
            }
        }
        if(maxHeight == topHeight) {
            for (int i = minHeight; i < maxHeight; i++) {
                for (int j = 0; j < newWidth; j++) {
                    GetOutput()->getPixel()[(i * newWidth) + j] = GetInput1()->getPixel()[(i * newWidth) + j];
                }

            }
        }
        else if(maxHeight == bottomHeight){
            for (int i = minHeight; i < maxHeight; i++) {
                for (int j = 0; j < newWidth; j++) {
                    GetOutput()->getPixel()[((i+topHeight) * newWidth) + j] = GetInput2()->getPixel()[(i * newWidth) + j];
                }

            }
        }
    }
}


/* ============= Blender ============= */

Blender::Blender()
{
    GetOutput()->myFilter = this;
    filterName = (char*) "Blender";
    assignedImg1 = false;
    assignedImg2 = false;
}

void Blender::SetFactor(float f)
{
    factor = f;
}

void Blender::Execute()
{
    char msg[128];
    if(!assignedImg1)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input1!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput1()->updated)
    {
        sprintf(msg, "%s: about to update input1", FilterName());
        Logger::LogEvent(msg);
        GetInput1()->Update();
        sprintf(msg, "%s: done updating input1", FilterName());
        Logger::LogEvent(msg);
    }
    if (!assignedImg2)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: no input2!", SinkName());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if(!GetInput2()->updated)
    {
        sprintf(msg, "%s: about to update input1", FilterName());
        Logger::LogEvent(msg);
        GetInput2()->Update();
        sprintf(msg, "%s: done updating input2", FilterName());
        Logger::LogEvent(msg);
    }

    if (GetInput1()->getWidth() != GetInput2()->getWidth())
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: widths must match: %d, %d", SinkName(),
                GetInput1()->getWidth(), GetInput2()->getWidth());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if (GetInput1()->getHeight() != GetInput2()->getHeight())
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: heights must match: %d, %d", SinkName(),
                GetInput1()->getHeight(), GetInput2()->getHeight());
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    if (factor > 1.0f)
    {
        char errorMsg[1024];
        sprintf(errorMsg, "Throwing exception: %s: Invalid factor for Blender: %f", SinkName(),
                factor);
        DataFlowException e(SinkName(), errorMsg);
        throw e;
    }
    // else no error, Execute()
    else
    {
        int newHeight = GetInput1()->getHeight();
        int newWidth = GetInput1()->getWidth();
        SetSize(newWidth, newHeight);
        for(int i = 0; i < newHeight; i++)
        {
            for(int j = 0; j < newWidth; j++)
            {
                GetOutput()->getPixel()[(i*newWidth) + j] = blender(GetInput1()->getPixel()[(i*newWidth) + j],
                                                                    GetInput2()->getPixel()[(i*newWidth) + j], factor);
            }
        }

    }
}

Pixel Blender::blender(Pixel p1, Pixel p2, float)
{
    Pixel tempPixel;
    double doubleTempR = (factor*p1.r) + ((1-factor)*p2.r);
    int intTempR = (int) doubleTempR;
    tempPixel.r = (unsigned char) intTempR;

    double doubleTempG = (factor*p1.g) + ((1-factor)*p2.g);
    int intTempG = (int) doubleTempG;
    tempPixel.g = (unsigned char) intTempG;

    double doubleTempB = (factor*p1.b) + ((1-factor)*p2.b);
    int intTempB = (int) doubleTempB;
    tempPixel.b = (unsigned char) intTempB;

    return tempPixel;
}
