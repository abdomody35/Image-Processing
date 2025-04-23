#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Image.h"
#include <numeric>

GrayscaleImage applyConvolution(GrayscaleImage &image, std::vector<std::vector<double>> kernel)
{
    GrayscaleImage output(image.GetWidth(), image.GetHeight());

    int dimension = kernel.size();

    for (int y = 0; y < output.GetHeight(); y++)
    {
        for (int x = 0; x < output.GetWidth(); x++)
        {
            if (x - dimension + 2 < 0 || y - dimension + 2 < 0)
            {
                output(x, y) == image(x, y);
                continue;
            }

            double value = 0;

            for (int row = dimension - 1; row > -1; row--)
            {
                for (int col = dimension - 1; col > -1; col--)
                {
                    value += image(x - row + 1, y - col + 1) * kernel[row][col];
                }
            }

            output(x, y) = car(value, 255);
        }
    }

    return output;
}

void normalizeKernel(std::vector<std::vector<double>> kernel)
{
    double sum = 0;
    for (const auto &row : kernel)
    {
        sum += std::accumulate(row.begin(), row.end(), 0.0);
    }
    for (auto &row : kernel)
    {
        for (auto &value : row)
        {
            value /= sum;
        }
    }
}

#endif