//
// Created by nicolas on 12/10/2020.
//

#ifndef NEURALONE_NEURALNET_H
#define NEURALONE_NEURALNET_H


class NeuralNet
{
public:
    NeuralNet() = delete;
    ~NeuralNet() = delete;
    NeuralNet operator=(const NeuralNet& one) = delete;
    static void init(int neuronCount);
    static void start();
private:
    static int neuron_count;
};


#endif //NEURALONE_NEURALNET_H
