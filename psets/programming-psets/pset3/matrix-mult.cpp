
#include  <iostream>
#include <iomanip>
#include <cmath>

#include  "./lib/newmat.h"
#include "./lib/newmatio.h"

using namespace std;

Matrix repeated_squaring(Matrix B, int exponent, int no_rows) {
        if (exponent == 0) 
        {
            IdentityMatrix I(no_rows);
            return I;
        }
        if (fmod(exponent, 2) != 0)
        {
            return B * repeated_squaring(B * B, (exponent -1) / 2, no_rows);
        }
        else 
        {
            return repeated_squaring(B * B, exponent / 2, no_rows);
        }
};

int main() {
    // int n = 5;
    // IdentityMatrix I(n);
    // cout << setw(10) << setprecision(5) << I; 
   int rows = 2;
   int expo = 5;
   Matrix A(rows, rows);
   Real a[] = { 1, 2, 3, 4 };
   Matrix B(rows, rows);
   Matrix C(rows, rows);

   //initialize
   A << a;

   B = repeated_squaring(A, expo, rows);

   C = A * A * A * A * A;

   cout << setw(10) << setprecision(5) << B;
   cout << setw(10) << setprecision(5) << C - B;
   return 0;
}