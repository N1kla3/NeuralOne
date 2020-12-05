//
// Created by nicolas on 12/10/2020.
//

#include "NeuralNet.h"

void NeuralNet::start(std::vector<PartPixelMatrix> &parts)
{
    W = MathMatrix(PixelMatrix::MathMatrixFromPart(parts[0])[0].size(), neuron_count);
    hatchW = MathMatrix(std::move(MathMatrix::MatrixTransposition(W)));
    W.doNormal();
    hatchW.doNormal();
    //W.print();
    //std::cout << "\n";
    //hatchW.print();
    auto test = W * hatchW;
    std::vector<MathMatrix> Q(parts.size());
    int epoch = 0;
    float result = e;
    while (result >= e)
    {
        float E = 0;
        for (size_t parts_index = 0; parts_index < parts.size(); parts_index++)
        {
            MathMatrix q(PixelMatrix::MathMatrixFromPart(parts[parts_index]));
            E += trainNeuron(q);
            Q[parts_index] = q;
        }
        std::cout << "\n"<< E ;
        epoch++;
        result = E;
    }

    for (int i = 0; i < Q.size(); ++i)
    {
        auto Y = Q[i] * W;
        auto hatchX = Y * hatchW;
        PixelMatrix::ChangePartFromMathM(parts[i], hatchX);
    }
    auto minipart = PixelMatrix::MathMatrixFromPart(parts[0]);
    float N = minipart[0].size();
    float Z = (parts.size() * N)/((N + parts.size())*(float)neuron_count+2);
    std::cout << "\n" << Z << "\n";
    std::cout << "epoch = " << epoch << "\n";
}

float NeuralNet::trainNeuron(const MathMatrix &X)
{
    auto Y = X * W;
    auto hatchX = Y * hatchW;
    auto deltaX = hatchX - X;
    //auto alpha = 0.0003f;
    //auto alphaHatch = alpha;
    auto alphaHatch = 1 / (Y * MathMatrix::MatrixTransposition(Y)).at(0,0)/44;
    auto alpha = 1 / (X * MathMatrix::MatrixTransposition(X)).at(0,0)/44;
    trainW(alpha, X, deltaX);
    trainHatchW(alphaHatch, Y, deltaX);
    return calculateE(deltaX);
}

void NeuralNet::trainW(float alpha, const MathMatrix &X, const MathMatrix &deltaX)
{
    auto w_plus = (alpha * MathMatrix::MatrixTransposition(X) * deltaX * MathMatrix::MatrixTransposition(hatchW));
    W = W - w_plus;
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
