#include "Image.h"
#include <math.h>

int main()
{
    GrayscaleImage original;

    original.Load("input.png");

    int targetWidth = original.GetWidth() / 2.0, targetHeight = original.GetHeight() / 2.0;

    GrayscaleImage output(targetWidth, targetHeight);

    float sx = float(original.GetWidth()) / targetWidth, sy = float(original.GetHeight()) / targetHeight;

    for (int x = 0; x < targetWidth; x++)
    {
        float tx = x * sx;
        
        for (int y = 0; y < targetHeight; y++)
        {
            float ty = y * sy;
            float ax = std::floor(tx), ay = std::floor(ty);
            float bx = ax + 1, by = ay + 1;
            float fx = tx - ax, fy = ty - ay;

            float value =
                original(ax, ay) * fx * fy +
                original(ax, by) * fx * (1 - fy) +
                original(bx, ay) * (1 - fx) * fy +
                original(bx, by) * (1 - fx) * (1 - fy);

            output(x, y) = car(value, 255);
        }
    }

    output.Save("output.png");

    return 0;
}
