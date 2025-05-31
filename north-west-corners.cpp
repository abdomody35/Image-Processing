#include "Image.h"
#include "morphology.h"

int main()
{
    GrayscaleImage image;

    image.Load("binary.png");

    std::vector<std::vector<int>> kernel = {
        {0, 1, 0},
        {1, 1, -1},
        {0, -1, -1}};

    GrayscaleImage output = performHitAndMissTransform(image, kernel);

    output.Save("NorthWestCorners.png");

    return 0;
}
