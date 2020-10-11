//
// Created by nicolas on 03/10/2020.
//

#ifndef NEURALONE_PICTURESTREAM_H
#define NEURALONE_PICTURESTREAM_H


#include <string>

class PixelMatrix;

class PictureStream
{
public:
    PictureStream() = delete;

    ~PictureStream() = delete;

    PictureStream &operator=(PictureStream &stream) = delete;

    static PixelMatrix ReadFromBMP(const std::string &Path);

    static void WriteToBMP(const PixelMatrix &pixelMatrix);

private:


};


#endif //NEURALONE_PICTURESTREAM_H
