#include "Image.h"
#include <set>
#include <queue>

int main()
{
    GrayscaleImage image;

    image.Load("binary.png");

    // von Neumann neighborhood
    std::vector<std::vector<int>> kernel = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}};

    int width = image.GetWidth();
    int height = image.GetHeight();
    int dimension = kernel.size();
    int kernelCenter = dimension / 2;

    std::set<std::pair<int, int>> checked;
    std::queue<std::pair<int, int>> locations;
    std::vector<std::vector<std::pair<int, int>>> objects;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (image(x, y) == 255 && checked.find({x, y}) == checked.end())
            {
                std::vector<std::pair<int, int>> object;

                locations.push({x, y});
                checked.insert({x, y});

                while (locations.size())
                {
                    int X = locations.front().first;
                    int Y = locations.front().second;

                    locations.pop();
                    checked.insert({X, Y});
                    object.push_back({X, Y});

                    for (int row = 0; row < dimension; row++)
                    {
                        for (int col = 0; col < dimension; col++)
                        {
                            if (kernel[row][col] == 0)
                            {
                                continue;
                            }

                            int imageX = X + col - kernelCenter;
                            int imageY = Y + row - kernelCenter;

                            if (imageX < 0 || imageX >= width || imageY < 0 || imageY >= height)
                            {
                                continue;
                            }

                            if (image(imageX, imageY) == 255 && checked.find({imageX, imageY}) == checked.end())
                            {
                                locations.push({imageX, imageY});
                                checked.insert({imageX, imageY});
                            }
                        }
                    }
                }

                objects.push_back(object);
            }
        }
    }

    GrayscaleImage output(width, height);

    for (const auto &object : objects)
    {
        for (const auto &pair : object)
        {
            output(pair.first, pair.second) = 255;
        }
    }

    output.Save("white-objects.png");

    return 0;
}