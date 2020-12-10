//
// Created by nicolas on 10/12/2020.
//
#pragma once

#ifndef NEURALONE_ELMANNEURAL_H
#define NEURALONE_ELMANNEURAL_H

#include "MathMatrix.h"

class ElmanNeural{
public:
    ElmanNeural(float e, float a, int p, int L) :
        e(e),
        a(a),
        p(p),
        L(L)
    {

    }
private:
    MathMatrix W{};
    MathMatrix hatchW{};
    float e;
    float a;
    int p;
    int L;
};


#endif //NEURALONE_ELMANNEURAL_H
