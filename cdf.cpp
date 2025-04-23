#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image, cdf(256, 256);

    image.Load("input.png");

    std::vector<int> counts(256), cdfs(256);

    double scale = 0.05;

    for (int y = 0; y < image.GetHeight(); y++)
    {
        for (int x = 0; x < image.GetWidth(); x++)
        {
            counts[image(x, y)]++;
        }
    }

    long long numPixels = image.GetHeight() * image.GetWidth();

    double sum = 0;

    for (int x = 0; x < 256; x++)
    {
        double propability = counts[x] / (double)numPixels;

        sum += propability;

        cdfs[x] = sum;

        for (int y = 0; y < std::min<int>(256, sum * 256); y++)
        {
            cdf(x, 255 - y) = 255;
        }

        // std::cout << "the cumulative probability of value " << x << " is " << sum << std::endl;
    }

    // std::cout << "the sum of the propabilities is " << sum << std::endl;

    cdf.Save("cdf.png");

    return 0;
}