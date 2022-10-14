// Matrix.h
#include <iostream>
#ifndef MATRIX_H
#define MATRIX_H
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;



// Insert Matrix class here...
class Matrix
{
private:
    int rows_ ,cols_ , size;
    float* vals_;
public:
//ctrs :

    Matrix(int rows, int cols);
    Matrix();
    Matrix(const Matrix& m );
//detr :

    ~Matrix();
//getters:

    int get_rows() const ;
    int get_cols() const ;
// methods:

    Matrix& transpose();
    Matrix& vectorize();
    void plain_print()const;
    Matrix dot(const Matrix& m);
    float norm();
// operators :
    Matrix operator+(const Matrix& other)const;
    float& operator()(int row, int column) const;
    Matrix& operator= (const Matrix& rhs);
    Matrix operator*(float scalar);
    Matrix operator* (const Matrix& other) const;
    friend Matrix operator*(float scalar ,const Matrix& m);
    float& operator[](int index) const;
    Matrix& operator+=(const Matrix& other);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
    friend void operator>> (std::ifstream &is, Matrix& m);

};
#endif //MATRIX_H