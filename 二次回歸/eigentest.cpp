#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
int main()
{
    int day = 10;
    int funding[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Matrix2d X;
    X << 1, 2,
        3, 4;
    cout << "X" << endl;
    cout << X << endl;
    Matrix2d inv_X;
    inv_X = X.inverse().eval();
    cout << "inverse(X)" << endl;
    cout << inv_X << endl;
    Matrix2d XX;
    XX = X * X;
    cout << "X*X" << endl;
    cout << XX << endl;

    Matrix2d Y;
    Y = (((X.transpose() * X).inverse()) * X.transpose() * X).eval();
    cout << Y << endl;

    //Matrix<double, 3, 3> A;
    //Matrix<double, 3, Dynamic> B;
}
