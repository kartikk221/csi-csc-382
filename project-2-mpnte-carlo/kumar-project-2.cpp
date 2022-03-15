/**
 * @file kumar-project-2.cpp
 * @author Kartik Kumar
 * @brief Project 2 - This project will try to match the Average Case of
 * algorithm A5 as calculated in class and the "Real Average Case" of the
 * algorithm.
 */

#include <iostream>
#include <random>
#include <time.h>
using namespace std;

// Generates a random integer between provided min and max values
int random_integer(int min, int max) {
  // Seed the random number generator
  srand(time(NULL));

  // Generate a random number between min and max
  return min + rand() % (max - min + 1);
}

// Algorithm taken from project direction sheet
int A5_Find(int x, int A[], int n) {
  int j;
  for (j = 0; j < n; j++) {
    if (x == A[j]) {
      return (j + 1); // The position is 1 more than index
    }
  }
  return 0; // x is not an element of the array
}

const int n = 50; // 1.a) Let n = 50
const int iterations = 10000;

void perform_average_scenarios(int bound) {
  // 1) Calculated Average
  // 1.c) Let x be an integer between 0 and bound.
  int x = random_integer(0, bound);

  // 1.d) Let hits = 0.
  int hits = 0;

  // 1.g) Repeat steps e and f 10,000 times (in other words create 10,000
  // sequences of 50 integers each. Clearly Sequences is a 50 x 10,000
  // two-dimensional array
  int Sequences[iterations][n];
  for (int i = 0; i < iterations; i++) {
    // 1.e) Generate a sequence of n integers using a random number generator
    // where the numbers of the sequence are between 0 and bound.
    for (int j = 0; j < n; j++) {
      Sequences[i][j] = random_integer(0, bound);
    }

    // 1.f) If x is equal to any of the numbers generated in the sequence
    // increment hits by one (if x appears more than once do not increment hits
    // every time).
    for (int j = 0; j < n; j++) {
      bool is_repeating = Sequences[i][j] == Sequences[i][j + 1];
      if (!is_repeating && x == Sequences[i][j]) {
        hits++;
      }
    }
  }

  // 1.h) Let q = hits / 10,000.
  int q = hits / iterations;

  // 1.i) Let calculated_average = A5_Find(x, Sequences, n).
  int calculated_average = A5_Find(x, *Sequences, n);

  // 2) Real Average
  // Let total-steps be a variable that tells you the total number of steps
  // executed so far, that is, initialize total-steps to zero
  int total_steps = 0;

  // Using the sequences created in the previous step (two-dimensional array
  // Sequences) run algorithm A5 10,000 times using each time an input of
  // Sequences
  for (int i = 0; i < iterations; i++) {
    // 2.a) Let x be an integer between 0 and bound.
    x = random_integer(0, bound);

    // 2.b) Let total-steps = total-steps + A5_Find(x, Sequences, n).
    total_steps += A5_Find(x, *Sequences, n);
  }
}

int main() {
  // Log the information columns with a border line
  cout << "Bound		Calculated Average		Real Average"
       << endl;
  cout << "--------------------------------------------------------------------"
          "----"
       << endl;
  return 0;

  // Run steps 1-2 for the following bound values
  int bounds[] = {30, 50, 80, 100, 1000, 10000};
  for (int i = 0; i < *(&bounds + 1) - bounds; i++) {
    perform_average_scenarios(bounds[i]);
  }

  return 0;
}