/* Adapted from: https://eigen.tuxfamily.org/dox/classEigen_1_1JacobiSVD.html */

#include <iostream>
using std::cout;
using std::endl;

#include <Eigen/Core>
#include <Eigen/SVD>
using Eigen::ComputeFullU;
using Eigen::ComputeFullV;
using Eigen::DiagonalMatrix;
using Eigen::JacobiSVD;
using Eigen::MatrixXf;
using Eigen::Vector3f;

int main() {
    MatrixXf m(3,2);
    m <<
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
    ;
    JacobiSVD<MatrixXf> svd(m, ComputeFullU | ComputeFullV);
    auto e = svd.singularValues();
    // TODO. e needs to be 3x2, what is the nicest way? Almost there, but this changes value positions.
    //MatrixXf e(svd.singularValues().asDiagonal());
    //e.resize(m.rows(), m.cols());
    cout << "E" << endl << e << endl << endl;
    auto u = svd.matrixU();
    cout << "U" << endl << u << endl << endl;
    cout << "UU'" << endl << u.adjoint() * u << endl << endl;
    auto v = svd.matrixV();
    cout << "V" << endl << v << endl << endl;
    cout << "VV'" << endl << v * v.adjoint() << endl << endl;
    //cout << "UEV" << endl << u * e * v << endl << endl;
    cout << "least squares" << endl << svd.solve(Vector3f(1, 0, 0)) << endl << endl;
}
