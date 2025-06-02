#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image;

    image.Load("input.png");

    std::vector<int> counts(256);

    for (int y = 0; y < image.GetHeight(); y++)
    {
        for (int x = 0; x < image.GetWidth(); x++)
        {
            counts[image(x, y)]++;
        }
    }

    long long numPixels = image.GetHeight() * image.GetWidth();

    double entropy = 0;

    for (int x = 0; x < 256; x++)
    {
        double pdf = counts[x] / (double)numPixels;

        if (pdf > 0)
        {
            entropy -= pdf * std::log2(pdf);
        }
    }

    std::cout << "Entropy: " << entropy << std::endl;

    return 0;
}
