/**
 * @file kumar-project-2.cpp
 * @author Kartik Kumar
 * @brief Project 2 - This project will try to match the Average Case of
 * algorithm A5 as calculated in class and the "Real Average Case" of the
 * algorithm.
 */

#include <climits>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using namespace std;

// Algorithm taken from project direction sheet
// Linear Search Algorithm
int A5_Find(int x, int A[], int n) {
  int j;
  for (j = 0; j < n; j++) {
    if (x == A[j]) {
      return j + 1; // The steps are 1 more than index
    }
  }
  return 0; // x is not an element of the array
}

const int n = 50; // 1.a) Let n = 50
const int iterations = 10000;

void perform_average_scenarios(int bound) {
  // 1.c) Let x be an integer between 0 and bound.
  int x = rand() % bound;

  // 1.d) Let hits = 0.
  int hits = 0;
  int total_steps = 0;
  for (int i = 0; i < iterations; i++) {
    int Sequence[n];

    // 1.e) Generate a sequence of n integers using a random number generator
    // where the numbers of the sequence are between 0 and bound.
    for (int j = 0; j < n; j++) {
      Sequence[j] = rand() % bound;
    }

    // 1.f) If x is equal to any of the numbers generated in the sequence
    // increment hits by one (if x appears more than once do not increment hits
    // every time).
    int steps_taken = A5_Find(x, Sequence, n);
    if (steps_taken > 0) {
      // Count the number of steps this successul search took
      total_steps += steps_taken;
      hits++;
    } else {
      // Count the number of steps this unsuccessful search took
      total_steps += n;
    }
  }

  // 1.h) Let q = hits / 10,000.
  // This is the quality ratio of the of random arrays to the ideal scenario
  // where all 10k arrays have x somewhere in them
  double q = hits / (double)iterations;

  // 1.i) Let calculated_average -> A(n) = (n + 1) / 2 -> Real[A(n)] = A(n) * q
  // where q is the quality of the random We only want to add one term if it is
  // less then the max integer value possible to prevent overflow
  double calculated_average = static_cast<double>(n + (q / 2) - (q * n) / 2);

  // Calculate the real average by taking the total steps and dividing by the
  // number of iterations
  double real_average = static_cast<double>(total_steps) / iterations;

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

  // Run steps 1-2 for the following bound values
  int bounds[] = {30, 50, 80, 100, 1000, 10000, INT_MAX};
  for (int i = 0; i < *(&bounds + 1) - bounds; i++) {
    perform_average_scenarios(bounds[i]);
  }

  return 0;
}