#include "PictureStream.h"
#include "PixelMatrix.h"

int main() {
    PixelMatrix a(std::move(PictureStream::ReadFromBMP("../output-onlinepngtools.bmp")));
    auto parts = a.matrixDecomposition(100, 100);
    a.createFromParts(parts);
    PictureStream::WriteToBMP(a);
    return 0;
}
