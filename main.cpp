#include "PictureStream.h"
#include "NeuralNet.h"

int main() {
    PixelMatrix a(std::move(PictureStream::ReadFromBMP("../neuron.bmp")));
    auto parts = a.matrixDecomposition(11, 11);

    NeuralNet net(5, 0.1f);
    net.start(parts);

    a.createFromParts(parts);
    PictureStream::WriteToBMP(a);

    return 0;
}
