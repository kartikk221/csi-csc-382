/**
 * @file kumar-project-3.cpp
 * @author Kartik Kumar
 * @brief Project 3 - In this project we will try to match the Average Case of
 * algorithm A10 (Insertion Sort) as we derived in class and the “Real Average”
 * of the algorithm using Monte Carlo approach.
 */

#include <climits>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using namespace std;

int InsertionMod(int A[], int n) {
  int steps = 0;
  int i, j, temp;
  A[0] =
      -32768; // smallest possible integer using 2 bytes integer representation
  for (i = 1; i <= n; i++) {
    j = i;
    while (A[j] < A[j - 1]) { // swap
      temp = A[j];
      A[j] = A[j - 1];
      A[j - 1] = temp;
      j--;
      steps++;
    }
    steps++;
  }
  return steps;
}

const int n = 100; // 1.a) Let n = 100
const int iterations = 100000;

void perform_average_scenarios(int bound) {
  int total_num_steps = 0;
  for (int i = 0; i < iterations; i++) {
    int Sequence[n];
    for (int j = 0; j < n; j++) {
      Sequence[j] = rand() % bound;
      Sequence[j] *= rand() > RAND_MAX / 2 ? 1 : -1;
    }

    // Count the number of steps this insertion sort took
    total_num_steps += InsertionMod(Sequence, n);
  }

  // Calculate the expected number of steps for insertion sort
  double calculated_average = (pow(n, 2) / 4) + (3 * n / 4);

  // Calculate the real average number of steps by dividing the total number of
  // steps by the number of iterations
  double real_average = (double)total_num_steps / iterations;

  // Set the print number decimal precision to 2 decimal places
  cout << setprecision(2) << fixed;

  // Print the results for this bound
  cout << (bound == INT_MAX ? "Infinity" : to_string(bound)) << setw(30)
       << calculated_average << setw(30) << real_average << endl;
}

int main() {
  // Log the information columns with a border line
  cout << "Bound" << setw(30) << "Calculated Average" << setw(30)
       << "Real Average" << endl;

  // Print the border line
  cout << "-----------------------------------------------------------------"
       << endl;

  // Seed the random number generator
  srand(time(NULL));

  // Run steps 1-2 for the following bounds
  int bounds[] = {100, 500, 1000, 2500, 3000, 3500};
  for (int i = 0; i < *(&bounds + 1) - bounds; i++) {
    perform_average_scenarios(bounds[i]);
  }

  return 0;
}

/**
 * @brief The output of the program displays that the calculated average remains
 * the same at 2575 steps for all bounds. With this in mind, the real average
 * tends to follow very close to the 2575 steps while increasing in accuracy as
 * the bounds increase. This proves that the mod insertion's average case is
 * validated through both the calculated and real average over 100,000
 * iterations with increasing range of numbers in both negative and positive
 * domains.
 *
 */