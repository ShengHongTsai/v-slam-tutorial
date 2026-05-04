#include <iostream>
#include <ctime>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Dense>

#define MATRIX_SIZE 50

int main(int argc, char **argv) {
    // 2*3 float matrix
    Eigen::Matrix<float, 2, 3> matrix_23;
    // 3d vector of double
    Eigen::Vector3d v_3d;
    // 3*3 double matrix, type determined by the right side
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();
    // unknown size matrix
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
    // dynamic matrix with fixed size
    Eigen::MatrixXd matrix_x;

    matrix_23 << 1, 2, 3, 4, 5, 6;
    cout << "matrix 2x3: " << endl << matrix_23 << endl;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            matrix_23(i, j) = i + j;
        }
    }
    cout << "refined matrix 2x3: " << endl << matrix_23 << endl;

    v_3d << 3, 2, 1;
    cout << "vector 3d: " << endl << v_3d.transpose() << endl;

    Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << "result: " << endl << result.transpose() << endl;

    

    return 0;
}