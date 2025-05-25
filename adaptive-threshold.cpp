#include "Image.h"

void applyAdaptiveThresholding(const GrayscaleImage &image, GrayscaleImage &output);

int main()
{
    GrayscaleImage image;

    image.Load("input.png");

    GrayscaleImage output(image.GetWidth(), image.GetHeight());

    applyAdaptiveThresholding(image, output);

    output.Save("output.png");

    return 0;
}

void applyAdaptiveThresholding(const GrayscaleImage &image, GrayscaleImage &output)
{
    long sum = 0;

    for (int y = 0; y < output.GetHeight(); y++)
    {
        for (int x = 0; x < output.GetWidth(); x++)
        {
            sum += image(x, y);
        }
    }

    float threshold = sum / (image.GetHeight() * image.GetWidth());
    float newThreshold = threshold;

    do
    {
        threshold = newThreshold;
        long sumFalse = 0, sumTrue = 0;
        int countFalse = 0, countTrue = 0;

        for (int y = 0; y < output.GetHeight(); y++)
        {
            for (int x = 0; x < output.GetWidth(); x++)
            {
                if (image(x, y) < threshold)
                {
                    sumFalse += image(x, y);
                    countFalse++;
                }
                else
                {
                    sumTrue += image(x, y);
                    countTrue++;
                }
            }
        }

        float avgFalse = sumFalse / (float)countFalse;
        float avgTrue = sumTrue / (float)countTrue;
        newThreshold = (avgFalse + avgTrue) / 2;

    } while (threshold != newThreshold);

    for (int y = 0; y < output.GetHeight(); y++)
    {
        for (int x = 0; x < output.GetWidth(); x++)
        {
            output(x, y) = image(x, y) < threshold ? 0 : 255;
        }
    }
}
