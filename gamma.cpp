#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image;

    image.Load("input.png");

    GrayscaleImage output(image.GetWidth(), image.GetHeight());

    double gamma = 1.1;

    for (int y = 0; y < output.GetHeight(); y++)
    {
        for (int x = 0; x < output.GetWidth(); x++)
        {
            output(x, y) = car(255 * pow((image(x, y) / 255.0), gamma), 255);
        }
    }

    output.Save("output.png");

    return 0;
}