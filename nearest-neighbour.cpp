#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage original;

    original.Load("input.png");

    int targetWidth = original.GetWidth() / 2.0, targetHeight = original.GetHeight() / 2.0;

    GrayscaleImage output(targetWidth, targetHeight);

    double sx = double(original.GetWidth()) / targetWidth, sy = double(original.GetHeight()) / targetHeight;

    for (int x = 0; x < targetWidth; x++)
    {
        for (int y = 0; y < targetHeight; y++)
        {
            output(x, y) = original(std::round(x * sx), std::round(y * sy));
        }
    }

    output.Save("output.png");

    return 0;
}
