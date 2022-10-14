#include "Matrix.h"
#ifndef ACTIVATION_H
#define ACTIVATION_H

typedef Matrix (*ActivationFunction)(const Matrix & x);

// Insert Activation class here...
namespace activation
{

    Matrix relu(const Matrix & x);
    Matrix softmax(const Matrix & x);

};
#endif //ACTIVATION_H


