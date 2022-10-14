//
// Created by noor dar yahya on 15/05/2022.
//
#include "Matrix.h"
#include "Activation.h"
#include <iostream>
#include <cmath>


Matrix activation::relu(const Matrix &x)
{
    int rows = x.get_rows();
    int cols = x.get_cols();
    Matrix a(rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        if (x[i] < 0)
        {
            a[i] = 0;
        } else
        {
            a[i] = x[i];
        }

    }
    return a;
}

Matrix activation::softmax(const Matrix &m){
    float sum = 0;
    Matrix x(m.get_rows(),m.get_cols());

    for (int i = 0; i < m.get_rows()*m.get_cols(); i++) {
        x[i]= exp(m[i]);
        sum += x[i];
    }

    x=x*(1/sum);
    return x;
}


