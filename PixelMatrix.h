//
// Created by nicolas on 04/10/2020.
//

#ifndef NEURALONE_PIXELMATRIX_H
#define NEURALONE_PIXELMATRIX_H


#include <cstdint>
#include <vector>
#include "PixelRGB.h"



struct PartPixelMatrix
{
    using matrix = std::vector<std::vector<PixelRGB>>;
    PartPixelMatrix(size_t x, size_t y, size_t x_shift = 0, size_t y_shift = 0):
            x_number(x),
            y_number(y),
            x_shift(x_shift),
            y_shift(y_shift)
    {
    }

    size_t x_number;
    size_t y_number;
    size_t x_shift;
    size_t y_shift;
    matrix mx;
};

class PixelMatrix
{
    using matrix = std::vector<std::vector<PixelRGB>>;
public:
    PixelMatrix(PixelMatrix &&moveMatrix) noexcept;

    std::vector<PartPixelMatrix> matrixDecomposition(int sub_width, int sub_height);

    void createFromParts(std::vector<PartPixelMatrix> &parts);

private:

    PixelMatrix(const uint32_t height, const uint32_t width) :
            HEIGHT(height),
            WIDTH(width)
    {
        pixels.resize(HEIGHT, std::vector<PixelRGB>(WIDTH));
    }
    bool isCompletlyCreated() const noexcept;

    matrix CreateMatrixAtLocation(int xLocation, int yLocation, int width, int height);
    void writeMatrixAtLocation(int xLocation, int yLocation, PartPixelMatrix &part);

    void addPixel(const PixelRGB &pixel);
    void changeSize(uint32_t height, uint32_t width);

    std::vector<char> header;
    std::vector<char> offset;
    matrix pixels;
    uint32_t HEIGHT;
    uint32_t WIDTH;
    uint32_t curHeight = 0;
    uint32_t curWidth = 0;
    bool isComplete = false;

    friend class PictureStream;
};
#endif //NEURALONE_PIXELMATRIX_H
