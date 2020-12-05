#include "PictureStream.h"
#include "NeuralNet.h"

int main() {
    PixelMatrix a(std::move(PictureStream::ReadFromBMP("../dd.bmp")));
    auto parts = a.matrixDecomposition(9, 8);

    NeuralNet net(22, 1111.f);
    net.start(parts);

    a.createFromParts(parts);
    PictureStream::WriteToBMP(a);

    return 0;
}
