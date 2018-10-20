
#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include <chrono>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>

#include  "./lib/newmat.h"
#include "./lib/newmatio.h"

using namespace std;

Matrix brute_force(Matrix B, int exponent, int no_rows) {
    Matrix C(no_rows, no_rows);
    C = B;
    for (int i = 1; i < exponent; i++)
    {
        C = B * C;
    }
    return C;
};

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

unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);

// U.I.I.D. RV generator
double get_uniform()
{
    std::uniform_real_distribution <double> distribution(-5.0, 5.0);
    double number = distribution(generator);
    return (number);
}

Matrix generate_random_matrix(int no_row) {
    Matrix A(no_row, no_row);

   for (int i=1; i < no_row; i++)
   {
       for (int j = 1; j < no_row; j++)
       {
         A(i, j) = get_uniform();
       }
   }
   return A;
}

int main() {
    // int n = 5;
    // IdentityMatrix I(n);
    // cout << setw(10) << setprecision(5) << I; 
   //int rows = 2, expo = 2;
   int rows, expo;
   Matrix A(rows, rows);
   double time_before, time_after, diff;

   // read input
   cout << "Enter the exponent : ";
   cin >> expo;
   cout << "Enter the number of rows/cols : ";
   cin >> rows;
   //Real a[] = { 1, 2, 3, 4 };
   Matrix B(rows, rows);
   Matrix C(rows, rows);
   Matrix D(rows, rows);

   //initialize
   A = generate_random_matrix(rows);

  // compute matrix exponentiation
  cout << "Result of repeated squaring \n";
  time_before = clock();
   B = repeated_squaring(A, expo, rows);
  time_after = clock();
  diff = ((float) time_after - (float)time_before);
  cout << "it took " << diff/CLOCKS_PER_SEC << " seconds to complete" << endl;
   C = brute_force(A, expo, rows);
  
  cout << "Result of direct multiplication \n";
  time_before = clock();
   B = brute_force(A, expo, rows);
  time_after = clock();
  diff = ((float) time_after - (float)time_before);
  cout << "it took " << diff/CLOCKS_PER_SEC << " seconds to complete" << endl;

   // run times
   int data_points = 250;
   int var_exp;
   ofstream bfruntime ("bfruntime.txt");   // brute force runtimes
   ofstream rsruntime ("rsruntime.txt");   // repeated squaring 
   
   A = generate_random_matrix(5);

  cout << "Runtime experiments \n";

   for (int i = 1; i < data_points; i++)
   {
      time_before = clock();
      var_exp = i * 1000;
      B = brute_force(A, var_exp, 5);
      time_after = clock();
      diff = ((float) time_after - (float)time_before);
      if (bfruntime.is_open())
      {
          bfruntime << diff << endl;
      }
   }
   bfruntime.close();


   for (int i = 1; i < data_points; i++)
   {
      time_before = clock();
      var_exp = i * 1000;
      B = repeated_squaring(A, var_exp, 5);
      time_after = clock();
      diff = ((float) time_after - (float)time_before);
      if (rsruntime.is_open())
      {
          rsruntime << diff << endl;
      }
   }
   rsruntime.close();

   return 0;
}