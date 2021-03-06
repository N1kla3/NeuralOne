//
// Created by nicolas on 11/10/2020.
//

#include "MathMatrix.h"

MathMatrix MathMatrix::MatrixTransposition(const MathMatrix &matrix)
{
    if (matrix.getWidth() == 0 || matrix.getHeight() == 0)throw std::exception();
    MathMatrix result(matrix.getWidth(), matrix.getHeight(), 0);
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
    return matrix_data[y][x];
}

MathMatrix operator*(const MathMatrix &one, const MathMatrix& two)
{
    if (one.getWidth() != two.getHeight())throw std::exception();
    MathMatrix result(one.getHeight(), two.getWidth(), 0);
    for (int i = 0; i < one.getHeight(); i++)
    {
        for (int j = 0; j < two.getWidth(); j++)
        {
            for (int k = 0; k < one.getWidth(); k++)
            {
                result.matrix_data[i][j] += one.matrix_data[i][k] * two.matrix_data[k][j];
            }
        }
    }
    return result;
}

MathMatrix operator-(const MathMatrix &one, const MathMatrix &two)
{
    if (two.matrix_data.empty() || one.matrix_data.empty())throw std::exception();
    int height = one.matrix_data.size(), width = one.matrix_data[0].size();
    if (height != two.matrix_data.size()
        || width != two.matrix_data[0].size())throw std::exception();
    MathMatrix result = one;
    for (int _height = 0; _height < height; ++_height)
    {
        for (int _width = 0; _width < width; ++_width)
        {
            result.matrix_data[_height][_width] -= two.at(_width, _height);
        }
    }
    return result;
}

MathMatrix operator*(float one, const MathMatrix &two)
{
    MathMatrix res = two;
    for (auto& line : res.matrix_data)
    {
        for (auto& item : line)
        {
            item *= one;
        }
    }
    return res;
}

void MathMatrix::print() const
{
    for (const auto& y : matrix_data)
    {
        for (auto x : y)
        {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}

float MathMatrix::vectorModule(int vectorIndex) const
{
    if (matrix_data.size() <= vectorIndex)
    {
        return 1.f;
    }
    float answer = 0.f;
    for (auto num : matrix_data[vectorIndex])
    {
        answer += num*num;
    }
    return std::sqrt(answer);
}

void MathMatrix::doNormal()
{
    auto tr = MathMatrix::MatrixTransposition(*this);
    for (auto & i : matrix_data)
    {
        for (int j = 0; j < matrix_data[0].size(); ++j)
        {
            i[j] /= tr.vectorModule(j);
        }
    }
}
