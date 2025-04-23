#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage image, pdf(256, 256);

    image.Load("input.png");

    std::vector<int> counts(256);

    std::vector<double> pdfs(256);

    for (int y = 0; y < image.GetHeight(); y++)
    {
        for (int x = 0; x < image.GetWidth(); x++)
        {
            counts[image(x, y)]++;
        }
    }

    long long numPixels = image.GetHeight() * image.GetWidth();

    double sum = 0, max;

    for (int x = 0; x < 256; x++)
    {
        pdfs[x] = counts[x] / (double)numPixels;

        max = std::max(max, pdfs[x]);

        // std::cout << "the propability of finding " << x << " is " << propability << std::endl;

        // sum += propability;
    }

    for (int x = 0; x < 256; x++)
    {
        for (int y = 0; y < std::min<int>(256, (pdfs[x] / max) * 128); y++)
        {
            pdf(x, 255 - y) = 255;
        }
    }

    // std::cout << "the sum of the propabilities is " << sum << std::endl;

    pdf.Save("pdf.png");

    return 0;
}