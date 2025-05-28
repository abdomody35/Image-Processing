#include "Image.h"
#include "morphology.h"

int main()
{
    GrayscaleImage image;

    image.Load("binary.png");

    GrayscaleImage output = applyNegation(image);

    output.Save("negated.png");

    return 0;
}
