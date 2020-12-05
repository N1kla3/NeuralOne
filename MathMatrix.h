//
// Created by nicolas on 11/10/2020.
//

#ifndef NEURALONE_MATHMATRIX_H
#define NEURALONE_MATHMATRIX_H


#include <utility>
#include <vector>
#include <random>
#include <iostream>

class MathMatrix
{
public:
    MathMatrix() = default;
    MathMatrix(size_t height, size_t width)
    {
        matrix_data = std::move(std::vector<std::vector<float>>(height, std::vector<float>(width, 0)));
        std::random_device random_device;
        std::mt19937 random_engine(random_device());
        std::uniform_int_distribution<int> distribution(-1000, 1000);

        for (auto& h : matrix_data)
        {
            for (auto& w : h)
            {
                w = float(distribution(random_engine))/1000;
            }
        }
    }
    MathMatrix(size_t height, size_t width, int flag)
    {
        matrix_data = std::vector<std::vector<float>>(height, std::vector<float>(width, 0));
    }
    explicit MathMatrix(std::vector<std::vector<float>>  create_from):
            matrix_data(std::move(create_from))
    {

    }
    static MathMatrix MatrixTransposition(const MathMatrix& matrix);
    [[nodiscard]]float vectorModule(int vectorIndex)const;
    void doNormal();

    size_t getHeight()const;
    size_t getWidth()const;

    float at(size_t x, size_t y)const;

    void print()const;

    friend MathMatrix operator*(const MathMatrix& one, const MathMatrix& two);
    friend MathMatrix operator*(float one, const MathMatrix& two);
    friend MathMatrix operator-(const MathMatrix& one, const MathMatrix& two);
private:
    std::vector<std::vector<float>> matrix_data;
};


#endif //NEURALONE_MATHMATRIX_H
