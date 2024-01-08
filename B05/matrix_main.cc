
# include <iostream>
# include <array>
# include <vector>
# include "matrix.hh"

int main() {
    std::cout << "Matrix no 0.: a zero matrix" << std::endl;
    Matrix<int, 2, 3> mat;
    mat.print();
    std::cout << "mat.get(0, 1) : " << mat.get(0, 1) << std::endl;
    mat.get(0, 1) = 42;
    std::cout << "After mat.get(0, 1) = 42 :" << std::endl;
    mat.print();

    std::cout << std::endl;
    
    std::cout << "Matrix no. 1: out of an array" << std::endl;
    std::array<std::array<int, 2>, 3> arr = {{{1, 2, 3}, {4, 5, 6}}};
    Matrix<int, 2, 3> matArr(arr);
    matArr.print();
    
    std::cout << std::endl;

    std::cout << "Matrix no. 2: out of a vector" << std::endl;
    std::vector<std::vector<int>> vec = {{1, 2}, {3, 4}, {5, 6}}; 
    Matrix<int, 3, 2> matVec(vec);
    matArr.print();

    std::cout << std::endl;

    std::cout << "Sum : (no. 1) + (no 0.)" << std::endl;
    matArr.add(mat).print();
    std::cout << "Subtract : (no. 1) - (no 0.)" << std::endl;
    matArr.subtract(mat).print();
    std::cout << "Multiply : (no. 1) o (no 2.)" << std::endl;
    matArr.multiply<2>(matVec).print();        
}