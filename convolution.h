#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Image.h"
#include <numeric>

GrayscaleImage applyConvolution(const GrayscaleImage &image, const std::vector<std::vector<double>> &kernel)
{
    int width = image.GetWidth();
    int height = image.GetHeight();
    int dimension = kernel.size();
    int kernelCenter = dimension / 2;
    GrayscaleImage output(width, height);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            if (x < kernelCenter || x >= width - kernelCenter || y < kernelCenter || y >= height - kernelCenter)
            {
                output(x, y) = image(x, y);
                continue;
            }

            double value = 0;

            for (int row = dimension - 1; row > -1; row--)
            {
                for (int col = dimension - 1; col > -1; col--)
                {
                    int imageX = x + col - kernelCenter;
                    int imageY = y + row - kernelCenter;

                    value += image(imageX, imageY) * kernel[row][col];
                }
            }

            output(x, y) = car(value, 255);
        }
    }

    return output;
}

void normalizeKernel(std::vector<std::vector<double>> &kernel)
{
    double sum = 0;

    for (const auto &row : kernel)
    {
        sum += std::accumulate(row.begin(), row.end(), 0.0);
    }

    if (sum == 0)
    {
        return;
    }

    for (auto &row : kernel)
    {
        for (auto &value : row)
        {
            value /= sum;
        }
    }
}

#endif // CONVOLUTION_H
