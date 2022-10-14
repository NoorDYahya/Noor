#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
// Insert Dense class here...
class Dense
{
private:
    ActivationFunction _activate_func;
    Matrix _bias;
    Matrix _weight;
public:
    Dense(const Matrix& w, const Matrix& bias, ActivationFunction func);
    Matrix get_weights();
    Matrix get_bias();
    ActivationFunction  get_activation();
    Matrix operator()(const Matrix& m);

};
#endif //DENSE_H


