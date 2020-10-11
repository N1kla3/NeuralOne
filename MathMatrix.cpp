//
// Created by nicolas on 11/10/2020.
//

#include "MathMatrix.h"

MathMatrix MathMatrix::MatrixTransposition(const MathMatrix &matrix)
{
    if (matrix.getWidth() == 0 || matrix.getHeight() == 0)throw std::exception();
    MathMatrix result(matrix.getWidth(), matrix.getHeight());
    for (int y = 0; y < matrix.getHeight(); ++y)
    {
        for (int x = 0; x < matrix.getWidth(); ++x)
        {
            result.matrix_data[x][y] = matrix.matrix_data[y][x];
        }
    }
    return result;
}

size_t MathMatrix::getWidth() const
{
    return matrix_data[0].size();
}

size_t MathMatrix::getHeight() const
{
    return matrix_data.size();
}

float MathMatrix::at(size_t x, size_t y) const
{
    return matrix_data[x][y];
}
