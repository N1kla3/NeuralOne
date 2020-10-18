//
// Created by nicolas on 03/10/2020.
//

#ifndef NEURALONE_PIXELRGB_H
#define NEURALONE_PIXELRGB_H


#include <cstdint>

class PixelRGB
{
public:
    PixelRGB() = default;

    PixelRGB(uint8_t Red, uint8_t Green, uint8_t Blue);

    static const int MAX_COLOR = 255;
    static const int MIN_COLOR = 0;
private:
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;

    friend class PictureStream;
    friend class PixelMatrix;
};


#endif //NEURALONE_PIXELRGB_H
