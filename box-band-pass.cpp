#include "Image.h"
#include "convolution.h"

int main()
{
    GrayscaleImage image;

    image.Load("input.png");

    std::vector<std::vector<double>> kernel = {
        {-1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1},
        {-1, -1, 24, -1, -1},
        {-1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1},
    };

    normalizeKernel(kernel);

    GrayscaleImage output = applyConvolution(image, kernel);

    output.Save("BoxBandPass.png");

    return 0;
}