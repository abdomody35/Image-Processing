#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image;

    image.Load("input.png");

    GrayscaleImage output(image.GetWidth(), image.GetHeight());

    double c = 1.5;

    for (int y = 0; y < output.GetHeight(); y++)
    {
        for (int x = 0; x < output.GetWidth(); x++)
        {
            output(x, y) = car(c * (image(x, y) - 128) + 128, 255);
        }
    }

    output.Save("output.png");

    return 0;
}