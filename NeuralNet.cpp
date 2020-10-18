//
// Created by nicolas on 12/10/2020.
//

#include "NeuralNet.h"

void NeuralNet::start(std::vector<PartPixelMatrix>& parts)
{
    W = MathMatrix(PixelMatrix::MathMatrixFromPart(parts[0])[0].size(), neuron_count);
    hatchW = MathMatrix(std::move(MathMatrix::MatrixTransposition(W)));
    std::vector<MathMatrix> Q;
    for (const auto& part : parts)
    {
        MathMatrix q(PixelMatrix::MathMatrixFromPart(part));
        Q.push_back(q);
        trainNeuron(q);
    }
    for (int i = 0; i < Q.size(); ++i)
    {
        auto Y = Q[i] * W;
        auto hatchX = Y * hatchW;
        PixelMatrix::ChangePartFromMathM(parts[i], Q[i]);
    }
}

void NeuralNet::trainNeuron(const MathMatrix &X)
{
    auto Y = X * W;
    auto hatchX = Y * hatchW;
    auto deltaX = hatchX - X;
    auto E = calculateE(deltaX);
    while (E > e)
    {
        Y = X * W;
        hatchX = Y * hatchW;
        deltaX = hatchX - X;
        auto alphaHatch = 1 / ((Y * MathMatrix::MatrixTransposition(Y)).at(0,0));
        auto alpha = 1 / ((X * MathMatrix::MatrixTransposition(X)).at(0,0));
        trainW(alpha, X, deltaX);
        trainHatchW(alphaHatch, Y, deltaX);
    }

}

void NeuralNet::trainW(float alpha, const MathMatrix &X, const MathMatrix &deltaX)
{
    W = W - (alpha * MathMatrix::MatrixTransposition(X) * deltaX * MathMatrix::MatrixTransposition(hatchW));
}

void NeuralNet::trainHatchW(float alphaHatch, const MathMatrix &Y, const MathMatrix &deltaX)
{
    hatchW = hatchW - (alphaHatch * MathMatrix::MatrixTransposition(Y) * deltaX);
}

float NeuralNet::calculateE(const MathMatrix &deltaX)
{
    float result = 0;
    for (int y = 0; y < deltaX.getHeight(); ++y)
    {
        for (int x = 0; x < deltaX.getWidth(); ++x)
        {
            auto temp = deltaX.at(x, y);
            result += temp * temp;
        }
    }
    return result;
}
