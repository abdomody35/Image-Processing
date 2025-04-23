#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image;

    image.Load("input.png");

    GrayscaleImage output(image.GetWidth(), image.GetHeight());

    int min = 255, max = 0;

    for (int y = 0; y < output.GetHeight(); y++)
    {
        for (int x = 0; x < output.GetWidth(); x++)
        {
            min = std::min((int)image(x, y), min);
            max = std::max((int)image(x, y), max);
        }
    }

    for (int y = 0; y < output.GetHeight(); y++)
    {
        for (int x = 0; x < output.GetWidth(); x++)
        {
            output(x, y) = car((image(x, y) - min) * 255 / (double)(max - min), 255);
        }
    }

    output.Save("output.png");

    return 0;
}