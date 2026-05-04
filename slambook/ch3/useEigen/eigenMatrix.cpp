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

    matrix_33 = Eigen::Matrix3d::Random();
    cout << "random matrix 3x3: " << endl << matrix_33 << '\n' <<endl;

    cout << matrix_33.transpose() << '\n' << endl;
    cout << matrix_33.sum() << '\n' << endl;
    cout << matrix_33.trace() << '\n' << endl;
    cout << 10 * matrix_33 << '\n' << endl;
    cout << matrix_33.inverse() << '\n' << endl;
    cout << matrix_33.determinant() << '\n' << endl;

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    cout << "eigen values = " << eigen_solver.eigenvalues().transpose() << endl;
    cout << "eigen vectors = " << endl << eigen_solver.eigenvectors() << endl;

    // Solve matrix_NN * x = v_Nd
    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);
    clock_t time_stt = clock(); // start time
    // direct inverse
    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    cout << "time of normal inverse is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;   

    time_stt = clock(); // start time
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd); // QR decomposition
    cout << "time of Qr decomposition is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl; 

    return 0;
}