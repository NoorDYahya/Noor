
#include "Matrix.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>

#define ZERO_PIONT_ONE 0.1


using std::cin;
using std::cout;
using std::cerr;
using std::endl;

Matrix::Matrix() : rows_(1), cols_(1)
{
    size = 1;
    vals_ = new float[1]{0};
}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols), size(
        rows * cols)
{
    if (rows <= 0 || cols <= 0)
    {
        throw std::length_error("entered matrix's size is invalid ");
    } else
    {
        vals_ = new float[size];
        for (int i = 0; i < size; i++)
        {
            vals_[i] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &m) : rows_(m.rows_), cols_(m.cols_), size(m.size)
{
    if (m.rows_ <= 0 || m.cols_ <= 0)
    {
        throw std::length_error("entered matrix's size is invalid ");
    } else
    {
        vals_ = new float[size];
        for (int i = 0; i < size; i++)
        {
            vals_[i] = m.vals_[i];
        }
    }
}


Matrix::~Matrix()
{
    if (vals_)
    {
        delete[] vals_;
        vals_ = nullptr;
    }
}

int Matrix::get_cols() const
{
    return cols_;
}

int Matrix::get_rows() const
{
    return rows_;
}

Matrix &Matrix::transpose()
{

    Matrix new_m(cols_, rows_);
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            new_m(j, i) = (*this)(i, j);
        }
    }
    *this = new_m;
    return *this;
}

Matrix &Matrix::vectorize()
{
    rows_ = size;
    cols_ = 1;
    return *this;
}

void Matrix::plain_print() const
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            cout << (*this)(i, j) << " ";
        }
        // Newline for new row
        cout << endl;
    }
}

Matrix Matrix::dot(const Matrix &m)
{
    if (rows_ != m.rows_ || cols_ != m.cols_)
    {

        throw std::length_error("rows and cols are not mach ,this product "
                                "can't be done!");
    }
    Matrix m_dot(rows_, cols_);
    for (int i = 0; i < size; i++)
    {
        m_dot.vals_[i] = vals_[i] * m.vals_[i];
    }
    return m_dot;
}

float Matrix::norm()
{
    float sum = 0;
    float norm;
    for (int i = 0; i < size; i++)
    {
        sum += pow(vals_[i], 2);
    }
    norm = sqrt(sum);
    return norm;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    {
        throw std::length_error("rows and cols are not match ,"
                                "this addition can't be done!");

    }
    Matrix result(rows_, cols_);
    for (int i = 0; i < size; i++)
    {
        result.vals_[i] = vals_[i] + other.vals_[i];
    }
    return result;
}

float &Matrix::operator()(int row, int column) const
{
    if (row >= rows_ || column >= cols_ || row < 0 || column < 0)
    {
        throw std::out_of_range("Index out of bounds");

    }
    return vals_[(row * cols_) + column];
}


Matrix &Matrix::operator=(const Matrix &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    size = rhs.size;
    rows_ = rhs.rows_;
    cols_ = rhs.cols_;
    float *tmp = new float[rhs.size];
    for (int i = 0; i < size; i++)
    {
        tmp[i] = rhs.vals_[i];
    }
    delete[] vals_;
    vals_ = tmp;
    return *this;
}

Matrix Matrix::operator*(float scalar)
{
    Matrix result(rows_, cols_);
    for (int i = 0; i < size; i++)
    {
        result.vals_[i] = scalar * vals_[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (cols_ != other.rows_)
    {
        throw std::length_error("Error: Matrices shapes mismatch");
    }
    Matrix result(rows_, other.cols_);
    for (int i = 0; i < this->rows_; i++)
    {
        for (int j = 0; j < other.cols_; j++)
        {
            for (int k = 0; k < cols_; k++)
            {
                result(i, j) += this->operator()(i, k) * other(k, j);
            }
        }
    }
    return result;
}

Matrix operator*(float scalar, const Matrix &m)
{
    Matrix result(m.rows_, m.cols_);
    for (int i = 0; i < m.size; i++)
    {
        result.vals_[i] = m.vals_[i] * scalar;
    }
    return result;
}

float &Matrix::operator[](int index) const
{
    if (index >= size || index < 0)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return vals_[index];
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    Matrix result = (*this) + other;
    (*this) = result;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Matrix &m)
{
    for (int i = 1; i < m.rows_; i++)
    {
        for (int j = 1; j < m.cols_; j++)
        {
            if (m(i, j) <= ZERO_PIONT_ONE)
            {
                out << "  ";
            } else
            {
                out << "**";
            }
        }
        out << endl;
    }
    return out;
}

void operator>>(std::ifstream &is, Matrix &m)
{
//     get length of file:
    is.seekg(0, std::ios_base::end);
    long unsigned int length = is.tellg();
    is.seekg(0, std::ios_base::beg);

    if (length != (m.size * sizeof(float)))
    {
        throw std::length_error("matrix size are mot equal to file "
                                "size");

    }
//     read data as a block:
    is.read((char *) m.vals_, length);
}
