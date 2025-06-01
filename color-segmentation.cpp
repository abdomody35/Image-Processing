#include "Image.h"
#include "color.h"
#include "morphology.h"
#include <math.h>

int main()
{
    ColorImage image;

    image.Load("green-screen.png");

    int width = image.GetWidth();
    int height = image.GetHeight();

    GrayscaleImage mask(width, height), mask2(width, height);
    ColorImage output(width, height);

    float hueTolerance = 10.0f;   // ±10 degrees
    float satTolerance = 0.25f;   // ±25%
    float lightTolerance = 0.25f; // ±25%

    // Target background (green)
    float targetHue = 120;
    float targetSaturation = 0.5f;
    float targetLightness = 0.5f;

    // Create binary mask
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            HSL hsl = RGBtoHSL(image(x, y));
            float hueDiff = std::abs(hsl.hue - targetHue);
            if (hueDiff > 180.0f)
                hueDiff = 360.0f - hueDiff; // Handle hue wraparound
            bool isForeground =
                hueDiff <= hueTolerance &&
                std::abs(hsl.saturation - targetSaturation) <= satTolerance &&
                std::abs(hsl.lightness - targetLightness) <= lightTolerance;
            mask(x, y) = isForeground ? 255 : 0;
        }
    }

    // Refine mask with morphological operations
    std::vector<std::vector<bool>> kernel = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}};

    // Opening: remove small noise
    mask = applyErosion(mask, kernel);
    mask = applyDilation(mask, kernel);

    // Closing: fill small holes
    mask = applyDilation(mask, kernel);
    mask = applyErosion(mask, kernel);

    // Apply mask to create output image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            output(x, y) = mask(x, y) != 255 ? image(x, y) : RGBA(0, 0, 0, 0); // Transparent background
        }
    }

    // Save results
    output.Save("output.png");

    return 0;
}