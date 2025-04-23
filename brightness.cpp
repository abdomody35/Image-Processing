#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image;

    image.Load("input.png");

    GrayscaleImage output(image.GetWidth(), image.GetHeight());

    int b = 15;

    for (int y = 0; y < output.GetHeight(); y++)
    {
        for (int x = 0; x < output.GetWidth(); x++)
        {
            output(x, y) = std::clamp(image(x, y) + b, 0, 255);
        }
    }

    output.Save("output.png");

    return 0;
}