#include "PictureStream.h"
#include "NeuralNet.h"

int main() {
    PixelMatrix a(std::move(PictureStream::ReadFromBMP("../neuron.bmp")));
    auto parts = a.matrixDecomposition(7, 6);

    NeuralNet net(15, 0.1f);
    net.start(parts);

    a.createFromParts(parts);
    PictureStream::WriteToBMP(a);

    return 0;
}
