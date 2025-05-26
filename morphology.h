#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include "Image.h"

GrayscaleImage applyErosion(const GrayscaleImage &image, const std::vector<std::vector<bool>> &kernel)
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
            bool truePixel = true;

            for (int row = 0; row < dimension; row++)
            {
                for (int col = 0; col < dimension; col++)
                {
                    int imageX = x + col - kernelCenter, imageY = y + row - kernelCenter;

                    if (imageX < 0 || imageX > width - 1 || imageY < 0 || imageY > height - 1)
                    {
                        if (kernel[row][col])
                        {
                            truePixel = false;
                            break;
                        }

                        continue;
                    }

                    if (kernel[row][col] && image(imageX, imageY) != 255)
                    {
                        truePixel = false;
                        break;
                    }
                }

                if (!truePixel)
                {
                    break;
                }
            }

            output(x, y) = truePixel ? 255 : 0;
        }
    }

    return output;
}

GrayscaleImage applyDilation(const GrayscaleImage &image, const std::vector<std::vector<bool>> &kernel)
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
            bool truePixel = false;

            for (int row = 0; row < dimension; row++)
            {
                for (int col = 0; col < dimension; col++)
                {
                    int imageX = x + col - kernelCenter, imageY = y + row - kernelCenter;

                    if (imageX < 0 || imageX > width - 1 || imageY < 0 || imageY > height - 1)
                    {
                        continue;
                    }

                    if (kernel[row][col] && image(imageX, imageY) == 255)
                    {
                        truePixel = true;
                        break;
                    }
                }

                if (truePixel)
                {
                    break;
                }
            }

            output(x, y) = truePixel ? 255 : 0;
        }
    }

    return output;
}

GrayscaleImage applyNegation(const GrayscaleImage &image)
{
    int width = image.GetWidth();
    int height = image.GetHeight();
    GrayscaleImage output(width, height);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            output(x, y) = image(x, y) ? 0 : 255;
        }
    }

    return output;
}

GrayscaleImage applyOR(const GrayscaleImage &image1, const GrayscaleImage &image2)
{
    if (image1.GetHeight() != image2.GetHeight() || image1.GetWidth() != image2.GetWidth())
    {
        std::cout << "Dimensions do not match" << std::endl;
        exit(1);
    }

    int width = image1.GetWidth();
    int height = image1.GetHeight();
    GrayscaleImage output(width, height);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            output(x, y) = image1(x, y) || image2(x, y) ? 255 : 0;
        }
    }

    return output;
}

GrayscaleImage applyXOR(const GrayscaleImage &image1, const GrayscaleImage &image2)
{
    if (image1.GetHeight() != image2.GetHeight() || image1.GetWidth() != image2.GetWidth())
    {
        std::cout << "Dimensions do not match" << std::endl;
        exit(1);
    }

    int width = image1.GetWidth();
    int height = image1.GetHeight();
    GrayscaleImage output(width, height);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            output(x, y) = (image1(x, y) || image2(x, y)) && !(image1(x, y) && image2(x, y)) ? 255 : 0;
        }
    }

    return output;
}

#endif // MORPHOLOGY_H
