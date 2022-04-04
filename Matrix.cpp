#include <iostream>
#include <stdexcept>
#include "Matrix.hpp"
using namespace std;
#include <string>
#include <array>
#include <algorithm>

bool T = true;
bool F = false;

//row and column constructor
zich::Matrix::Matrix(int row, int col)
{   //check if row and col are valid not zero and not negative
    if (row <= 0 || col <= 0)
    {
        throw invalid_argument("row and col must be positive");
    }
    rows = row;
    columns = col;
    matrix = vector<double>((unsigned long)row*(unsigned long)col, 0);
}
//vector constructor
zich::Matrix::Matrix(const vector<double>& mat, int row, int col)
{   
    //check if row and col are valid not zero and not negative
    if (row <= 0 || col <= 0)
    {
        throw invalid_argument("row and col must be positive");
    }
    //check if the size of the vector is equal to the row and col meening yoy can create a matrix
    if (mat.size() != (unsigned long)row*(unsigned long)col)
    {
        throw invalid_argument("vector size must be equal to row*col");
    }
    rows = row;
    columns = col;
    matrix = mat;
    
}
//deep copy constructor
zich::Matrix::Matrix(const Matrix& matrix_to_copy)
{
    rows = matrix_to_copy.rows;
    columns = matrix_to_copy.columns;
    matrix = vector<double>(matrix_to_copy.matrix);
}
//destructor - not realy needed but good doing it anyway
zich::Matrix::~Matrix()
{
    rows = 0;
    columns = 0;
    matrix.clear();
}
//plus and minus operator overload
//simple plus operator
zich::Matrix zich::Matrix::operator+(zich::Matrix matrix_to_add)
{
    if(rows != matrix_to_add.rows || columns != matrix_to_add.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    zich::Matrix result(rows, columns);
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        result.matrix.at(i) = matrix.at(i) + matrix_to_add.matrix.at(i);
    }
    return result;
}
//plus equals operator
zich::Matrix zich::Matrix::operator+=(zich::Matrix matrix_to_add)
{
    if(rows != matrix_to_add.rows || columns != matrix_to_add.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i) += matrix_to_add.matrix.at(i);
    }
    return *this;
}
//unary plus operator
zich::Matrix zich::Matrix::operator+()
{
    zich::Matrix result(rows, columns);
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        result.matrix.at(i) = matrix.at(i);
    }
    return result;
}
//simple minus operator
zich::Matrix zich::Matrix::operator-(zich::Matrix matrix_to_subtract)
{
    if(rows != matrix_to_subtract.rows || columns != matrix_to_subtract.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    zich::Matrix result(rows, columns);
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        result.matrix.at(i) = matrix.at(i) - matrix_to_subtract.matrix.at(i);
    }
    return result;
}
//minus equals operator
zich::Matrix zich::Matrix::operator-=(zich::Matrix matrix_to_subtract)
{
    if(rows != matrix_to_subtract.rows || columns != matrix_to_subtract.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i) -= matrix_to_subtract.matrix.at(i);
    }
    return *this;
}
//unary minus operator
zich::Matrix zich::Matrix::operator-()
{
    zich::Matrix result(rows, columns);
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        result.matrix.at(i) = -matrix.at(i);
    }
    return result;
}

//mult operator overload
//multiplication with double
zich::Matrix zich::operator*(double scalar, zich::Matrix matrix_to_mult){
    zich::Matrix result(matrix_to_mult.rows, matrix_to_mult.columns);
    for(unsigned long i = 0; i < matrix_to_mult.rows*matrix_to_mult.columns; i++)
    {
        result.matrix.at(i) = scalar * matrix_to_mult.matrix.at(i);
    }
    return result;
}

zich::Matrix zich::operator*(zich::Matrix matrix_to_mult, double scalar){
    zich::Matrix result(matrix_to_mult.rows, matrix_to_mult.columns);
    for(unsigned long i = 0; i < matrix_to_mult.rows*matrix_to_mult.columns; i++)
    {
        result.matrix.at(i) = scalar * matrix_to_mult.matrix.at(i);
    }
    return result;
}

//multiplication with matrix
zich::Matrix zich::Matrix::operator*(zich::Matrix matrix_to_multiply)
{
    if(columns != matrix_to_multiply.rows)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    zich::Matrix result(rows, matrix_to_multiply.columns);
    for(unsigned long i = 0; i < rows; i++)
    {
        for(unsigned long j = 0; j < matrix_to_multiply.columns; j++)
        {
            for(unsigned long k = 0; k < columns; k++)
            {
                result.matrix.at(i*(unsigned long)matrix_to_multiply.columns + j) += matrix.at(i*(unsigned long)columns + k) * matrix_to_multiply.matrix.at(k*(unsigned long)matrix_to_multiply.columns + j);
            }
        }
    }
    return result;
}
//mult equals operator with double
zich::Matrix zich::Matrix::operator*=(double scalar)
{
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i) *= scalar;
    }
    return *this;
}
//mult equals operator with metrix
zich::Matrix zich::Matrix::operator*=(const zich::Matrix& matrix_to_multiply){
    zich::Matrix result(rows, columns);
    result = *this * matrix_to_multiply;
    // copy result to this
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i) = result.matrix.at(i);
    }
    return *this;
}
//++ and -- operator overload
//increment operator
zich::Matrix zich::Matrix::operator++()
{
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i)++;
    }
    return *this;
}
//decrement operator
zich::Matrix zich::Matrix::operator--()
{
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        matrix.at(i)--;
    }
    return *this;
}

//comp operator overload
//equality operator
bool zich::Matrix::operator==(zich::Matrix matrix_to_compare)
{
    if(rows != matrix_to_compare.rows || columns != matrix_to_compare.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        if(matrix.at(i) != matrix_to_compare.matrix.at(i))
        {
            return F;
        }
    }
    return T;
}
//inequality operator
bool zich::Matrix::operator!=(zich::Matrix matrix_to_compare)
{
    if(rows != matrix_to_compare.rows || columns != matrix_to_compare.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        if(matrix.at(i) != matrix_to_compare.matrix.at(i))
        {
            return T;
        }
    }
    return F;
}
//more than operator - if the sum of all elements is greater than the other matrix
bool zich::Matrix::operator>(zich::Matrix matrix_to_compare)
{
    if(rows != matrix_to_compare.rows || columns != matrix_to_compare.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    double sum = 0;
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        sum += matrix.at(i);
    }
    double sum_to_compare = 0;
    for(unsigned long i = 0; i < matrix_to_compare.rows*matrix_to_compare.columns; i++)
    {
        sum_to_compare += matrix_to_compare.matrix.at(i);
    }
    if(sum > sum_to_compare)
    {
        return T;
    }
    return F;
}
//less than operator - if the sum of all elements is greater than the other matrix
bool zich::Matrix::operator<(zich::Matrix matrix_to_compare)
{
    if(rows != matrix_to_compare.rows || columns != matrix_to_compare.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    double sum = 0;
    for(unsigned long i = 0; i < rows*columns; i++)
    {
        sum += matrix.at(i);
    }
    double sum_to_compare = 0;
    for(unsigned long i = 0; i < matrix_to_compare.rows*matrix_to_compare.columns; i++)
    {
        sum_to_compare += matrix_to_compare.matrix.at(i);
    }
    if(sum < sum_to_compare)
    {
        return T;
    }
    return F;
}
//more than or equal operator - using the opreator > and == from above 
bool zich::Matrix::operator>=(const zich::Matrix& matrix_to_compare){
    if(rows != matrix_to_compare.rows || columns != matrix_to_compare.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    if(*this == matrix_to_compare)
    {
        return T;
    }
    if(*this > matrix_to_compare)
    {
        return T;
    }
    return F;
}

bool zich::Matrix::operator<=(const zich::Matrix& matrix_to_compare){
    if(rows != matrix_to_compare.rows || columns != matrix_to_compare.columns)
    {
        throw invalid_argument("Matrix dimensions do not match");
    }
    if(*this == matrix_to_compare)
    {
        return T;
    }
    if(*this < matrix_to_compare)
    {
        return T;
    }
    return F;
}
//output operator
ostream& zich::operator<<(ostream& out, zich::Matrix matrix_to_print)
{
    for(unsigned long i = 0; i < matrix_to_print.rows; i++)
    {
        out << '[';
        for(unsigned long j = 0; j < matrix_to_print.columns; j++)
        {
            if(j<matrix_to_print.columns-1)
            {
                out << matrix_to_print.matrix.at(i*(unsigned long)matrix_to_print.columns + j) << " ";
            }
            else
            {
                out << matrix_to_print.matrix.at(i*(unsigned long)matrix_to_print.columns + j);
            }
        }
        
        out << ']' << endl; 
    }
    return out;
}
//input operator
istream& zich::operator>>(istream& input, zich::Matrix& matrix_to_input)
{
    char dummy = ' ';
    for(unsigned long i = 0; i < matrix_to_input.rows; i++)
    {
        input >> dummy;
        //check if dummy is [
        
        if(dummy != '[')
        {
            throw invalid_argument("Matrix not opend error");
        }

        for(unsigned long j = 0; j < matrix_to_input.columns; j++)
        {   
            
            cout << "Enter element " << i << "," << j << ": ";
            input >> matrix_to_input.matrix.at(i*(unsigned long)matrix_to_input.columns + j);
            //print the elemnt 
            cout << matrix_to_input.matrix.at(i*(unsigned long)matrix_to_input.columns + j) << endl;
            
        }
        input >> dummy;
        //check if dummy is ]
        if(dummy != ']')
        {
            throw invalid_argument("Matrix not closed properly");
        }
        if(i<matrix_to_input.rows-1)
        {
            input >> dummy;
            //check if dummy is , (seperator)
            if(dummy != ',')
            {
                throw invalid_argument("Matrix not spaced properly");
            }
        }
        

    }
    return input;
}
