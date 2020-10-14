cmake_minimum_required(VERSION 3.17)
project(neuralOne)

set(CMAKE_CXX_STANDARD 20)

add_executable(neuralOne main.cpp PictureStream.cpp PictureStream.h PixelRGB.cpp PixelRGB.h PixelMatrix.cpp PixelMatrix.h MathMatrix.cpp MathMatrix.h NeuralNet.cpp NeuralNet.h)