#include "Image.h"
#include "morphology.h"

int main()
{
    GrayscaleImage image;

    image.Load("binary.png");

    std::vector<std::vector<bool>> kernel = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}};

    GrayscaleImage output = applyDilation(image, kernel);
    output = applyErosion(output, kernel);

    output.Save("dilated.png");

    return 0;
}
