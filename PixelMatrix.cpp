//
// Created by nicolas on 04/10/2020.
//

#include <cstring>
#include <iostream>
#include "PixelMatrix.h"
#include "PixelRGB.h"

using matrix = std::vector<std::vector<PixelRGB>>;

PixelMatrix::PixelMatrix(PixelMatrix &&moveMatrix) noexcept:
        HEIGHT(moveMatrix.HEIGHT),
        WIDTH(moveMatrix.WIDTH)
{
    pixels = std::move(moveMatrix.pixels);
    header = std::move(moveMatrix.header);
    offset = std::move(moveMatrix.offset);
    if (moveMatrix.isCompletlyCreated())
    {
        isComplete = true;
    } else
    {
        isComplete = false;
        curHeight = moveMatrix.curHeight;
        curWidth = moveMatrix.curWidth;
    }
}

void PixelMatrix::addPixel(const PixelRGB &pixel)
{
    if (curWidth >= WIDTH)
    {
        curWidth = 0;
        curHeight++;
    }
    if (curHeight >= HEIGHT)
    {
        isComplete = true;
        return;
    }
    pixels[curHeight][curWidth] = pixel;
    curWidth++;
}

bool PixelMatrix::isCompletlyCreated() const noexcept
{
    return isComplete;
}

std::vector<PartPixelMatrix> PixelMatrix::matrixDecomposition(const int sub_width, const int sub_height)
{
    std::vector<PartPixelMatrix> result;
    if (sub_width > WIDTH || sub_height > HEIGHT)return result;

    size_t y_number = 0;
    for (size_t y = 0; y < HEIGHT; y += sub_height)
    {
        y_number++;
        auto y_free_space = HEIGHT - y;
        auto y_loc = y;
        if (y_free_space < sub_height)
        {
            y_loc -= (sub_height - y_free_space);
        }
        size_t x_number = 0;
        for (size_t x = 0; x < WIDTH; x += sub_width)
        {
            x_number++;
            auto x_free_space = WIDTH - x;
            auto x_loc = x;
            if (x_free_space < sub_width)
            {
                x_loc -= (sub_width - x_free_space);
            }
            PartPixelMatrix temp(x_number, y_number, x_free_space, y_free_space);
            temp.mx = std::move(CreateMatrixAtLocation(x_loc, y_loc, sub_width, sub_height));
            result.push_back(temp);
        }
    }
    return result;
}

matrix PixelMatrix::CreateMatrixAtLocation(const int xLocation, const int yLocation, const int width, const int height)
{
    matrix part_matrix(height, std::vector<PixelRGB>(width));
    for (size_t y_pixel_location = 0; y_pixel_location < height; y_pixel_location++)
    {
        for (size_t x_pixel_location = 0; x_pixel_location < width; x_pixel_location++)
        {
            part_matrix[y_pixel_location][x_pixel_location] = pixels[y_pixel_location + yLocation][x_pixel_location + xLocation];
        }
    }
    return part_matrix;
}

void PixelMatrix::createFromParts(std::vector<PartPixelMatrix> &parts)
{
    std::sort(parts.begin(), parts.end(), [](PartPixelMatrix& one, PartPixelMatrix& two){
        if (one.y_number < two.y_number)
        {
            return true;

        } else if(one.y_number == two.y_number && one.x_number < two.x_number)
        {
            return true;
        }
        return false;
    });
    size_t parts_width = parts[0].mx[0].size();
    size_t parts_height = parts[0].mx.size();
    uint32_t new_width = parts[parts.size()-1].x_number * parts_width;
    uint32_t new_height = parts[parts.size()-1].y_number * parts_height;

    changeSize(new_height, new_width);

    size_t part_counter = 0;
    for (size_t start_y = 0; start_y < HEIGHT; start_y += parts_height)
    {
        for (size_t start_x = 0; start_x < WIDTH; start_x += parts_width)
        {
            writeMatrixAtLocation(start_x, start_y, parts[part_counter]);
            part_counter++;
        }
    }
}

void PixelMatrix::writeMatrixAtLocation(const int xLocation, const int yLocation, PartPixelMatrix& part)
{
    for (size_t y = 0; y < part.mx.size(); y++)
    {
        for (size_t x = 0; x < part.mx[0].size(); ++x)
        {
            pixels[y+yLocation][x+xLocation] = part.mx[y][x];
        }
    }
}

void PixelMatrix::changeSize(uint32_t height, uint32_t width)
{
    HEIGHT = height;
    WIDTH = width;
    pixels = matrix(height, std::vector<PixelRGB>(width));
    int32_t h = height * (-1);
    std::memcpy(&header[18], (char*)&WIDTH, sizeof(WIDTH));
    std::memcpy(&header[22], (char*)&h, sizeof(h));
    std::cout << *reinterpret_cast<uint32_t *>(&header[18]) <<
    *reinterpret_cast<int32_t *>(&header[22]);
}

std::vector<std::vector<float>> PixelMatrix::MathMatrixFromPart(const PartPixelMatrix& matr)
{
    std::vector<float> res_vector;
    for (const auto& row : matr.mx)
    {
        for (auto column : row)
        {
            res_vector.push_back(((float)(2*column.Red)/PixelRGB::MAX_COLOR)-1);
            res_vector.push_back(((float)(2*column.Green)/PixelRGB::MAX_COLOR)-1);
            res_vector.push_back(((float)(2*column.Blue)/PixelRGB::MAX_COLOR)-1);
        }
    }
    return std::vector<std::vector<float>>(1, res_vector);
}

uint8_t constructColor(float color)
{
    auto raw_res = PixelRGB::MAX_COLOR * (color + 1) / 2;
    raw_res = raw_res > PixelRGB::MAX_COLOR ? PixelRGB::MAX_COLOR : raw_res;
    raw_res = raw_res < PixelRGB::MIN_COLOR ? PixelRGB::MIN_COLOR : raw_res;
    return static_cast<uint8_t>(raw_res);
}

void PixelMatrix::ChangePartFromMathM(PartPixelMatrix &matr, const MathMatrix &math)
{
    //TODO: generate back
    int counter = 0;
    for (int y = 0; y < matr.mx.size(); y++)
    {
        for (int x = 0; x < matr.mx[0].size(); ++x)
        {
            auto red = math.at(counter++, 0);
            auto green = math.at(counter++, 0);
            auto blue = math.at(counter++, 0);
            matr.mx[y][x] = PixelRGB(constructColor(red), constructColor(green), constructColor(blue));
        }
    }
}
