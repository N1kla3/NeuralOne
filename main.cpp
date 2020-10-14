#include "PictureStream.h"
#include "PixelMatrix.h"

int main() {
    PixelMatrix a(std::move(PictureStream::ReadFromBMP("../output-onlinepngtools.bmp")));
    auto parts = a.matrixDecomposition(444, 500);
    a.createFromParts(parts);
    auto b = PixelMatrix::MathMatrixFromPart(parts[0]);
    PictureStream::WriteToBMP(a);
    return 0;
}
