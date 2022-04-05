#include <iostream>
#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;

#include <string>
#include <algorithm>
using namespace std;

TEST_CASE("bad constructor") {
    //tries to give it zero or negative rows and columns or incompatble size
    vector<double> default_vector = vector<double>(10, 0);
    CHECK_THROWS(Matrix negative_rows_columns_matrix(default_vector, -1, -1));
    CHECK_THROWS(Matrix one_negative_rows_columns_matrix(default_vector, 1, -1));
    CHECK_THROWS(Matrix one_zero_rows_columns_matrix(default_vector, 1, 0));
    CHECK_THROWS(Matrix zero_rows_columns_matrix(default_vector, 0, 0));
    CHECK_THROWS(Matrix negative_rows_columns_matrix(default_vector, -1, 0));
}

TEST_CASE("bad constructor 2") {
    //tries to give it zero or negative rows and columns or incompatble size
    vector<double> default_vector = vector<double>(10, 0);
    //checking if rows*cols is vector size and if not throws exception
    CHECK_THROWS(Matrix matrix_with_incompatble_size(default_vector, 1, 2));
    CHECK_THROWS(Matrix matrix_with_incompatble_size(default_vector, 2, 1));
    CHECK_THROWS(Matrix matrix_with_incompatble_size(default_vector, 2, 3));
    CHECK_THROWS(Matrix matrix_with_incompatble_size(default_vector, 3, 2));
    //checking compability of rows and columns and if not throws exception when its valid row*cols = vector size
    CHECK_NOTHROW(Matrix matrix_with_compatble_size(default_vector, 2, 5));
    CHECK_NOTHROW(Matrix matrix_with_compatble_size(default_vector, 5, 2));
    CHECK_NOTHROW(Matrix matrix_with_compatble_size(default_vector, 1, 10));
    CHECK_NOTHROW(Matrix matrix_with_compatble_size(default_vector, 10, 1));


}

TEST_CASE("check plus is working"){
    vector<double> default_vector1 = vector<double>(10, 0);
    vector<double> default_vector2 = vector<double>(10, 1);
    Matrix metrix2by5(default_vector1, 5, 2);
    Matrix matrix1by10(default_vector2, 1, 10);
    //checking throws exception when trying to add matrices with different sizes
    CHECK_THROWS(metrix2by5 + matrix1by10);
    CHECK_THROWS(matrix1by10 + metrix2by5);
    //chekc not throws when same size
    CHECK_NOTHROW(metrix2by5+metrix2by5);
    CHECK_NOTHROW(matrix1by10 + matrix1by10);
    //checking if the result is correct
    Matrix result = matrix1by10 + matrix1by10;
    vector<double> excpected_vecotr = vector<double>(10, 2);
    Matrix expected_matrix(excpected_vecotr, 1, 10);
    CHECK((result == expected_matrix));
    matrix1by10 += matrix1by10;
    CHECK((matrix1by10 == expected_matrix));
    cout << result << endl;
    cout << expected_matrix << endl;
    //check ++ is working correctly
    Matrix matrix_plus_plus(default_vector1, 5, 2);
    Matrix matrix_plus_plus_expected(default_vector2, 5, 2);
    CHECK((++matrix_plus_plus == matrix_plus_plus_expected));
    

}
TEST_CASE("check minus is working"){
    vector<double> default_vector1 = vector<double>(10, 0);
    vector<double> default_vector2 = vector<double>(10, 1);
    Matrix metrix2by5(default_vector1, 5, 2);
    Matrix matrix1by10(default_vector2, 1, 10);
    //checking throws exception when trying to add matrices with different sizes
    CHECK_THROWS(metrix2by5 - matrix1by10);
    CHECK_THROWS(matrix1by10 - metrix2by5);
    //chekc not throws when same size
    CHECK_NOTHROW(metrix2by5-metrix2by5);
    CHECK_NOTHROW(matrix1by10 - matrix1by10);
    //checking if the result is correct
    Matrix result = matrix1by10 - matrix1by10;
    vector<double> excpected_vecotr = vector<double>(10, 0);
    Matrix expected_matrix(excpected_vecotr, 1, 10);
    CHECK((result == expected_matrix));
    matrix1by10 -= matrix1by10;
    CHECK((matrix1by10 == expected_matrix));
    cout << result << endl;
    cout << expected_matrix << endl;
    //checl -- is working correctly
    Matrix matrix_minus_minus(default_vector2, 5, 2);
    Matrix matrix_minus_minus_expected(default_vector1, 5, 2);
    CHECK(((--matrix_minus_minus) == matrix_minus_minus_expected));

}

TEST_CASE("unary stuff check"){
    vector<double> default_vector1 = vector<double>(10, 0);
    vector<double> default_vector2 = vector<double>(10, 1);
    Matrix metrix2by5(default_vector1, 5, 2);
    Matrix matrix1by10(default_vector2, 1, 10);
    //chekc not throws 
    CHECK_NOTHROW(-(metrix2by5));
    CHECK_NOTHROW(-(matrix1by10));
    //checking if the result is correct
    Matrix result = -(matrix1by10);
    vector<double> excpected_vecotr = vector<double>(10, -1);
    Matrix expected_matrix(excpected_vecotr, 1, 10);
    CHECK((result == expected_matrix));
    matrix1by10 = -matrix1by10;
    CHECK((matrix1by10 == expected_matrix));
    cout << result << endl;
    cout << expected_matrix << endl;

    //check if unary plus does nothing
    Matrix result2 = +(matrix1by10);
    CHECK((result2 == matrix1by10));
    cout << result2 << endl;
    cout << expected_matrix << endl;
}

TEST_CASE("mult test"){
    //create two matrices
    vector<double> default_vector1 = vector<double>(10, 0);
    vector<double> default_vector2 = vector<double>(10, 1);
    Matrix metrix2by5(default_vector1, 5, 2);
    Matrix metrix5by2(default_vector2, 2, 5);
    //create one matrix with different size
    vector<double> default_vector3 = vector<double>(10, 1);
    Matrix matrix1by10_different_size(default_vector3, 10, 1);
    //check throws exception when trying to mult matrices with different sizes
    CHECK_THROWS(metrix2by5 * matrix1by10_different_size);
    CHECK_THROWS(matrix1by10_different_size * metrix2by5);
    CHECK_THROWS(matrix1by10_different_size * metrix5by2);
    CHECK_THROWS(metrix5by2 * matrix1by10_different_size);
    //check not throws when same size
    CHECK_NOTHROW(metrix2by5 * metrix5by2);
    CHECK_NOTHROW(metrix5by2 * metrix2by5);
    //check if the result is correct
    Matrix result = metrix2by5 * metrix5by2;
    vector<double> excpected_vecotr = vector<double>(25, 0);
    Matrix expected_matrix(excpected_vecotr, 5, 5);
    CHECK((result == expected_matrix));
    cout << result << endl;
    cout << expected_matrix << endl;

    //now checking mult with a double
    Matrix result2 = (2 * metrix5by2);
    vector<double> excpected_vecotr2 = vector<double>(10, 2);
    Matrix expected_matrix2(excpected_vecotr2, 2, 5);
    CHECK((result2 == expected_matrix2));
    cout << result2 << endl;
    cout << expected_matrix2 << endl;
    CHECK_NOTHROW(matrix1by10_different_size*10.6);
    CHECK_NOTHROW(10.6*matrix1by10_different_size);
    // check *= is working correctly
    Matrix matrix_mult_mult(default_vector3, 10, 1);
    Matrix matrix_mult_mult_expected(default_vector3, 10, 1);
    CHECK(((matrix_mult_mult *= 1) == matrix_mult_mult_expected));
}

TEST_CASE("equal and not equal"){
    //create two different matrices with same size
    vector<double> default_vector1 = vector<double>(10, 0);
    vector<double> default_vector2 = vector<double>(10, 1);
    Matrix metrix2by5(default_vector1, 5, 2);
    Matrix metrix5by2(default_vector2, 5, 2);
    //check if they are equal
    CHECK_FALSE((metrix2by5 == metrix5by2));
    CHECK_FALSE((metrix5by2 == metrix2by5));
    //check if they are not equal
    CHECK((metrix2by5 != metrix5by2));
    CHECK((metrix5by2 != metrix2by5));
    //create two matrices that are the same
    vector<double> default_vector3 = vector<double>(10, 1);
    Matrix matrix1by10(default_vector3, 1, 10);
    Matrix matrix1by10_same(default_vector3, 1, 10);
    //check if they are equal
    CHECK((matrix1by10 == matrix1by10_same));
    CHECK((matrix1by10_same == matrix1by10));
    //check if they are not equal
    CHECK_FALSE((matrix1by10 != matrix1by10_same));
    CHECK_FALSE((matrix1by10_same != matrix1by10));
    //not a good coding but simple way raised an error in doctest - relational comparison result unused
    CHECK_THROWS(int x = (matrix1by10 == metrix2by5));
    CHECK_THROWS(int x = (matrix1by10 == metrix2by5));

}

TEST_CASE("bigger and less"){
    //create two diffrent matrices with same size
    vector<double> default_vector1 = vector<double>(10, 0);
    vector<double> default_vector2 = vector<double>(10, 1);
    Matrix metrix2by5(default_vector1, 5, 2);
    Matrix metrix5by2(default_vector2, 5, 2);
    //check if 52 is bigger than 25
    CHECK((metrix5by2 > metrix2by5));
    //create a vector with neg values
    vector<double> default_vector3 = vector<double>(10, -1);
    //create a matrix with neg values
    Matrix matrix1by10(default_vector3, 5, 2);
    //check if 110 is smaller the the both of the previous
    CHECK((matrix1by10 < metrix5by2));
    CHECK((matrix1by10 < metrix2by5));
    //check if 25 is smaller than 52    
    CHECK((metrix2by5 < metrix5by2));
    //check if 52 and 25 are bigger than 110
    CHECK((metrix5by2 > matrix1by10));
    CHECK((metrix2by5 > matrix1by10));

}
TEST_CASE("Equla big and equal small"){
    //create two diffrent matrices with same size
    vector<double> default_vector1 = vector<double>(10, 0);
    vector<double> default_vector2 = vector<double>(10, 1);
    Matrix metrix2by5(default_vector1, 5, 2);
    Matrix metrix5by2(default_vector2, 5, 2);
    //check if 52 is bigger than 25
    CHECK((metrix5by2 >= metrix2by5));
    //create a vector with neg values
    vector<double> default_vector3 = vector<double>(10, -1);
    //create a matrix with neg values
    Matrix matrix1by10(default_vector3, 5, 2);
    //check if 110 is smaller the the both of the previous
    CHECK((matrix1by10 <= metrix5by2));
    CHECK((matrix1by10 <= metrix2by5));
    //check if 25 is smaller than 52    
    CHECK((metrix2by5 <= metrix5by2));
    //check if 52 and 25 are bigger than 110
    CHECK((metrix5by2 >= matrix1by10));
    CHECK((metrix2by5 >= matrix1by10));

    //now checking if the matrix is (big Orless) or big )or equal to itself
    CHECK((matrix1by10 <= matrix1by10));
    CHECK((matrix1by10 >= matrix1by10));
    //creata a 1 by 10 matrix
    vector<double> default_vector4 = vector<double>(10, 1);
    Matrix matrix10by1(default_vector4, 1, 10);

    //not a good coding but simple way raised an error in doctest - relational comparison result unused
    CHECK_THROWS(int x = (matrix10by1 <= matrix1by10));
    CHECK_THROWS(int x = (matrix10by1 <= metrix5by2));
    CHECK_THROWS(int x = (matrix10by1 >= matrix1by10));
    CHECK_THROWS(int x = (matrix10by1 >= metrix5by2));


}