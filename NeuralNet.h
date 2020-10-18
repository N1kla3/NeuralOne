//
// Created by nicolas on 12/10/2020.
//

#ifndef NEURALONE_NEURALNET_H
#define NEURALONE_NEURALNET_H

#include "MathMatrix.h"
#include "PixelMatrix.h"

class NeuralNet
{
public:
    NeuralNet(int neuronCount, float e):
            neuron_count(neuronCount),
            e(e)
    {

    }
    NeuralNet operator=(const NeuralNet& one) = delete;
    void start(std::vector<PartPixelMatrix> &parts);
    void trainNeuron(const MathMatrix& X);
private:
    void trainW(float alpha, const MathMatrix &X, const MathMatrix &deltaX);
    void trainHatchW(float alphaHatch, const MathMatrix &Y, const MathMatrix &deltaX);
    float calculateE(const MathMatrix& deltaX);
    int neuron_count;
    float e;
    MathMatrix W;
    MathMatrix hatchW;
};


#endif //NEURALONE_NEURALNET_H
