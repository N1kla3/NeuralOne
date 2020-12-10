#include "PictureStream.h"
#include "NeuralNet.h"

int main() {
    PixelMatrix a(std::move(PictureStream::ReadFromBMP("../neuron8.bmp")));
    auto parts = a.matrixDecomposition(9, 8);

    NeuralNet net(54, 1000.f);
    net.start(parts);

    a.createFromParts(parts);
    PictureStream::WriteToBMP(a);

    return 0;
}
