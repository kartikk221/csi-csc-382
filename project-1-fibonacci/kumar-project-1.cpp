/**
 * @file kumar-project-1.cpp
 * @author Kartik Kumar
 * @brief Project 1 - This project tests three types of fibonacci algorithms:
 * Recursive, Modified-Recursive (Cached), and Non-Recursive (Iterative).
 */

#include <ctime>
#include <iostream>
#include <map>
#include <string>

using namespace std;

long fibo_recursive(int n) {
  // Return the "n" value for the base cases 0/1 to end recursion tail
  if (n == 0 || n == 1)
    return n;

  // Recursively call the function to get the nth fibonacci number
  return fibo_recursive(n - 1) + fibo_recursive(n - 2);
}

long fibo_non_recursive(int n) {
  // Declare the variables to store the fibonacci numbers
  long fibo_0 = 0;
  long fibo_1 = 1;
  long fibo_n = 0;

  // Handle special base case of 0/1 n fibonacci parameter
  if (n == 0 || n == 1)
    return n;

  // Loop through the fibonacci numbers
  for (int i = 2; i <= n; i++) {
    // Store the next fibonacci number
    fibo_n = fibo_0 + fibo_1;

    // Update the storage fibonacci numbers
    fibo_0 = fibo_1;
    fibo_1 = fibo_n;
  }

  // Return the last fibonacci number
  return fibo_n;
}

// We will use this dictionary as a cache for previously calculated values to
// speed things up
map<int, long> fibo_cache = {};
long fibo_modified_recursive(int n) {
  // Return the "n" value for the base cases 0/1 to end recursion tail
  if (n == 0 || n == 1)
    return n;

  // Resolve value from cache if it exists from a previous calculation
  if (fibo_cache[n])
    return fibo_cache[n];

  // Calculate the value for this iteration and cache it
  fibo_cache[n] =
      fibo_modified_recursive(n - 1) + fibo_modified_recursive(n - 2);

  // Resolve the value from cache
  return fibo_cache[n];
}

float seconds_since(clock_t start) {
  return (clock() - start) / (float)CLOCKS_PER_SEC;
}

void test_algorithms(int i, bool test_recursive, bool test_modified,
                     bool test_non_recursive) {
  // Clamp the minimum possible i value to 1
  int number = i;
  if (number < 1)
    number = 1;

  // Initialize an empty long to store last calculated fibonacci number
  long last_fibonacci_value = -1;
  cout << "Fibonacci[" << to_string(number) << "] | ";

  // Test the recursive algorithm if specified
  if (test_recursive) {
    // Calculate execution time for recursive algorithm
    clock_t recursive_start = clock();
    last_fibonacci_value = fibo_recursive(number);
    float recursive_end = seconds_since(recursive_start);
    cout << "Recursive Took " << to_string(recursive_end) << " Second(s) | ";
  }

  // Test the modified recursive algorithm if specified
  if (test_modified) {
    clock_t modified_start = clock();
    if (last_fibonacci_value == -1) {
      last_fibonacci_value = fibo_modified_recursive(number);
    } else if (last_fibonacci_value != fibo_modified_recursive(number)) {
      cout << "Modified Recursive Failed | ";
    }
    float modified_end = seconds_since(modified_start);
    cout << "Modified-Recursive Took " << to_string(modified_end)
         << " Second(s) | ";
  }

  // Calculate execution time for non_recursive algorithm
  if (test_non_recursive) {
    clock_t non_recursive_start = clock();
    if (last_fibonacci_value == -1) {
      last_fibonacci_value = fibo_non_recursive(number);
    } else if (last_fibonacci_value != fibo_non_recursive(number)) {
      cout << "Non-Recursive Failed | ";
    }
    float non_recursive_end = seconds_since(non_recursive_start);
    cout << "Non-Recursive Took " << to_string(non_recursive_end)
         << " Second(s) | ";
  }

  // Print the final value and end line
  cout << "Fibonacci Value: " << to_string(last_fibonacci_value) << endl;
}

int main() {
  // Customize which algorithms you want to test from here
  bool test_recursive = true;
  bool test_modified_recursive = true;
  bool test_non_recursive = true;

  // Log a descriptor statement
  cout << "Fibonacci Time Analysis (recursive vs non recursive vs "
          "modified-recursive)"
       << endl;

  // Run routines from 1 - 60 with intervals += 5
  for (int i = 0; i < 100; i += 5)
    test_algorithms(i, test_recursive, test_modified_recursive,
                    test_non_recursive);

  return 0;
}