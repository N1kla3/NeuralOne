//
// Created by nicolas on 11/10/2020.
//

#ifndef NEURALONE_MATHMATRIX_H
#define NEURALONE_MATHMATRIX_H


#include <utility>
#include <vector>

class MathMatrix
{
public:
    MathMatrix(size_t height, size_t width)
    {
        matrix_data = std::move(std::vector<std::vector<float>>(height, std::vector<float>(width, 0)));
    }
    explicit MathMatrix(std::vector<std::vector<float>>  create_from):
            matrix_data(std::move(create_from))
    {

    }
    static MathMatrix MatrixTransposition(const MathMatrix& matrix);

    size_t getHeight()const;
    size_t getWidth()const;

    float at(size_t x, size_t y)const;

    MathMatrix operator*(const MathMatrix& one);
private:
    std::vector<std::vector<float>> matrix_data;
};


#endif //NEURALONE_MATHMATRIX_H
