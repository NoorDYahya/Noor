//
// Created by noor dar yahya on 15/05/2022.
//

#include "Dense.h"
#include "Activation.h"

Dense::Dense( const Matrix& w, const Matrix& bias, ActivationFunction func)
{
    _activate_func = func;
    _bias = bias;
    _weight= w;
}
Matrix Dense::get_weights(){
    return this->_weight;
}

Matrix Dense::get_bias(){
    return this->_bias;
}


ActivationFunction Dense::get_activation(){
    return _activate_func;

}

Matrix Dense::operator()(const Matrix &x) {

    return  _activate_func((this->_weight * x) + this->_bias);

}





