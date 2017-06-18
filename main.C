#include "PNMreader.h"
#include "PNMwriter.h"
#include "filters.h"
#include "logging.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{

    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);


    PNMreader reader((char*) "deschutes.pnm"); // read an .pnm image

    /* Use the following filters as desired:
     * Rotate (rotate image 90 degrees)
     * LRConcat (concatenate two image left-to-right)
     * TBConcat (concatenate two image top-to-bottom)
     * Mirror (Flip image along y-axis)
     * Grayscale (Make a black-and-white version of an image)
     * Subtract (subtract rgb values of pixels from images of the same dimensions
     * Shrinker (half the size of an image)
     * Blur (blur an image)
     * Blender (blend pixel values of two images. Can set a factor between 0-1)
     * Color (create an image of a given size that is one solid color)
     */

    Image *finalImage = reader.GetOutput();

    try
    {
        finalImage->Update();
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
            cerr << "Something is wrong ... can't open my_exception"
                 << " for opening" << endl;
            exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum((char*) "my_checksum");


    PNMwriter writer;
    writer.SetInput(finalImage);
    writer.Write((char*) "output.pnm");

    Logger::Finalize();
}
