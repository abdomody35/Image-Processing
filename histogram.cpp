#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image, hist(256, 256);

    image.Load("input.png");

    std::vector<int> counts(256);

    double scale = 0.05;

    for (int y = 0; y < image.GetHeight(); y++)
    {
        for (int x = 0; x < image.GetWidth(); x++)
        {
            counts[image(x, y)]++;
        }
    }

    for (int x = 0; x < 256; x++)
    {
        // std::cout << "there are " << counts[x] << " pixels with the value " << x << std::endl;

        for (int y = 0; y < std::min<int>(256, counts[x] * scale); y++)
        {
            hist(x, 255 - y) = 255;
        }
    }

    hist.Save("histogram.png");

    return 0;
}