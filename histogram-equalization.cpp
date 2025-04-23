#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image;

    image.Load("input.png");

    GrayscaleImage output(image.GetWidth(), image.GetHeight());

    std::vector<int> counts(256);
    std::vector<double> cdfs(256);

    for (int y = 0; y < image.GetHeight(); y++)
    {
        for (int x = 0; x < image.GetWidth(); x++)
        {
            counts[image(x, y)]++;
        }
    }

    long long numPixels = image.GetHeight() * image.GetWidth();

    for (int x = 0; x < 256; x++)
    {
        double propability = counts[x] / (double)numPixels;
        cdfs[x] = x > 0 ? cdfs[x - 1] + propability : propability;
    }

    for (int y = 0; y < image.GetHeight(); y++)
    {
        for (int x = 0; x < image.GetWidth(); x++)
        {
            output(x, y) = car(cdfs[image(x, y)] * 255, 255);
        }
    }

    output.Save("output.png");

    return 0;
}