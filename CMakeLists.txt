cmake_minimum_required(VERSION 3.17)
project(neuralOne)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE PictureStream.cpp PictureStream.h PixelRGB.cpp PixelRGB.h PixelMatrix.cpp PixelMatrix.h MathMatrix.cpp MathMatrix.h NeuralNet.cpp NeuralNet.h)

add_executable(neuralOne main.cpp ${SOURCE})
add_executable(neuralTwo elman.cpp ${SOURCE} ElmanNeural.cpp ElmanNeural.h)