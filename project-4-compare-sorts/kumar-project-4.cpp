/**
 * @file kumar-project-4.cpp
 * @author Kartik Kumar
 * @brief Project 4 - Write a C++ program that compares the execution times of
Heap, Insertion Sort and Merge Sorts for inputs of different sizes.
 */

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

bool is_array_sorted(int arr[]) {
  // Iterate over all of array
  for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])) - 1; i++) {
    // If any element is greater than next element, return false
    if (arr[i] > arr[i + 1]) {
      cout << arr[i] << " is greater than " << arr[i + 1] << endl;
      return false;
    }
  }

  return true;
}

// Algorithm for Heap Sort with a max heap
void heapSort(int arr[]) {
  // Declare the variables to store the heap size and the current index
  int heap_size = sizeof(arr) / sizeof(arr[0]);
  int current_index = heap_size - 1;

  // Build the max heap
  while (current_index > 0) {
    // Declare the variables to store the parent and child indices
    int parent_index = (current_index - 1) / 2;
    int child_index = current_index;

    // While the child index is greater than the parent index
    while (child_index > parent_index) {
      // Declare the variables to store the parent and child values
      int parent_value = arr[parent_index];
      int child_value = arr[child_index];

      // If the parent value is greater than the child value
      if (parent_value > child_value) {
        // Swap the parent and child values
        arr[parent_index] = child_value;
        arr[child_index] = parent_value;

        // Update the parent and child indices
        parent_index = (child_index - 1) / 2;
        child_index = parent_index;
      } else {
        // Break out of the loop
        break;
      }
    }

    // Update the current index
    current_index--;
  }

  // Declare the variables to store the heap size and the current index
  heap_size = sizeof(arr) / sizeof(arr[0]);
  current_index = heap_size - 1;

  // While the current index is greater than 0
  while (current_index > 0) {
    // Declare the variables to store the parent and child indices
    int parent_index = 0;
    int child_index = current_index;

    // While the child index is greater than the parent index
    while (child_index > parent_index) {
      // Declare the variables to store the parent and child values
      int parent_value = arr[parent_index];
      int child_value = arr[child_index];

      // If the parent value is greater than the child value
      if (parent_value > child_value) {
        // Swap the parent and child values
        arr[parent_index] = child_value;
        arr[child_index] = parent_value;

        // Update the parent and child indices
        parent_index = (child_index - 1) / 2;
        child_index = parent_index;
      } else {
        // Break out of the loop
        break;
      }
    }

    // Update the current index
    current_index--;
  }
}

// Algoirhtm for Insertion Sort
void insertionSort(int arr[], int n) {
  // Traverse through 1 to length of the array
  for (int i = 1; i < n; i++) {
    // Get element to be inserted
    int key = arr[i];

    // Find location to insert the element
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }

    // Insert the element
    arr[j + 1] = key;
  }
}

// Algorithm for Merge Sort
void merge(int array[], int const left, int const mid, int const right) {
  auto const subArrayOne = mid - left + 1;
  auto const subArrayTwo = right - mid;

  // Create temp arrays
  auto *leftArray = new int[subArrayOne], *rightArray = new int[subArrayTwo];

  // Copy data to temp arrays leftArray[] and rightArray[]
  for (auto i = 0; i < subArrayOne; i++)
    leftArray[i] = array[left + i];
  for (auto j = 0; j < subArrayTwo; j++)
    rightArray[j] = array[mid + 1 + j];

  auto indexOfSubArrayOne = 0,   // Initial index of first sub-array
      indexOfSubArrayTwo = 0;    // Initial index of second sub-array
  int indexOfMergedArray = left; // Initial index of merged array

  // Merge the temp arrays back into array[left..right]
  while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
    if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
      array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
      indexOfSubArrayOne++;
    } else {
      array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
      indexOfSubArrayTwo++;
    }
    indexOfMergedArray++;
  }
  // Copy the remaining elements of
  // left[], if there are any
  while (indexOfSubArrayOne < subArrayOne) {
    array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
    indexOfSubArrayOne++;
    indexOfMergedArray++;
  }
  // Copy the remaining elements of
  // right[], if there are any
  while (indexOfSubArrayTwo < subArrayTwo) {
    array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
    indexOfSubArrayTwo++;
    indexOfMergedArray++;
  }
}

void mergeSort(int array[], int const begin, int const end) {
  if (begin >= end)
    return; // Returns recursively

  auto mid = begin + (end - begin) / 2;
  mergeSort(array, begin, mid);
  mergeSort(array, mid + 1, end);
  merge(array, begin, mid, end);
}

const int LOG_TABLE_SPACING = 30;

// Calculate and return the duration between two time points in microseconds
float duration_microseconds(
    const chrono::time_point<chrono::high_resolution_clock> &start,
    const chrono::time_point<chrono::high_resolution_clock> &end) {
  return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

// Calculate and return the duration between two time points in seconds
float duration_seconds(
    const chrono::time_point<chrono::high_resolution_clock> &start,
    const chrono::time_point<chrono::high_resolution_clock> &end) {
  return chrono::duration_cast<chrono::seconds>(end - start).count();
}

void testSorts(int input_length) {
  // Generate a random array of size input_length
  int *arr_copy_1 = new int[input_length];
  for (int i = 0; i < input_length; i++) {
    // Generate a random number between 0 and input_length
    arr_copy_1[i] = rand() % input_length;
  }

  // Create two more copies of the array
  int *arr_copy_2 = new int[input_length];
  int *arr_copy_3 = new int[input_length];
  for (int i = 0; i < input_length; i++) {
    arr_copy_2[i] = arr_copy_1[i];
    arr_copy_3[i] = arr_copy_1[i];
  }

  // Retrieve the execution time for Heap Sort with the first copy array
  auto start = chrono::high_resolution_clock::now();
  heapSort(arr_copy_1);
  auto heap_sort_stop = chrono::high_resolution_clock::now();
  float heap_sort_microseconds = duration_microseconds(start, heap_sort_stop);
  float heap_sort_seconds = duration_seconds(start, heap_sort_stop);
  if (!is_array_sorted(arr_copy_1)) {
    cout << "Heap Sort failed to sort the array!" << endl;
  }

  // Retrieve the execution time for Insertion Sort with the second copy array
  start = chrono::high_resolution_clock::now();
  insertionSort(arr_copy_2, input_length);
  auto insertion_sort_stop = chrono::high_resolution_clock::now();
  float insertion_sort_microseconds =
      duration_microseconds(start, insertion_sort_stop);
  float insertion_sort_seconds = duration_seconds(start, insertion_sort_stop);
  if (!is_array_sorted(arr_copy_2)) {
    cout << "Insertion Sort failed to sort the array!" << endl;
  }

  // Retrieve the execution time for Merge Sort with the third copy array
  start = chrono::high_resolution_clock::now();
  mergeSort(arr_copy_3, 0, input_length - 1);
  auto merge_sort_stop = chrono::high_resolution_clock::now();
  float merge_sort_microseconds = duration_microseconds(start, merge_sort_stop);
  float merge_sort_seconds = duration_seconds(start, merge_sort_stop);
  if (!is_array_sorted(arr_copy_3)) {
    cout << "Merge Sort failed to sort the array!" << endl;
  }

  // Determine the best sort based on the microseconds
  string best_sort = "";
  if (heap_sort_microseconds < insertion_sort_microseconds &&
      heap_sort_microseconds < merge_sort_microseconds) {
    best_sort = "Heap";
  } else if (insertion_sort_microseconds < heap_sort_microseconds &&
             insertion_sort_microseconds < merge_sort_microseconds) {
    best_sort = "Insertion";
  } else {
    best_sort = "Merge";
  }

  // Print the results to the console in the pretty table format
  cout << fixed;
  cout << setprecision(6);
  cout << left << setw(LOG_TABLE_SPACING) << to_string(input_length) << left
       << setw(LOG_TABLE_SPACING) << heap_sort_seconds << left
       << setw(LOG_TABLE_SPACING) << insertion_sort_seconds << left
       << setw(LOG_TABLE_SPACING) << merge_sort_seconds << left
       << setw(LOG_TABLE_SPACING) << best_sort << endl;
}

int main() {
  // Print the table header with the following columns: "Input Length", "Heap
  // Sort (s)", "Insertion Sort (s)", "Merge Sort (s)", "Best Time"
  cout << left << setw(LOG_TABLE_SPACING) << "Input Length" << left
       << setw(LOG_TABLE_SPACING) << "Heap Sort (seconds)" << left
       << setw(LOG_TABLE_SPACING) << "Insertion Sort (seconds)" << left
       << setw(LOG_TABLE_SPACING) << "Merge Sort (seconds)" << left
       << setw(LOG_TABLE_SPACING) << "Best Time" << endl;

  // Test the sorts with various input lengths
  int input_lengths[] = {1000, 10000, 25000, 50000, 150000, 250000};
  for (int i = 0; i < sizeof(input_lengths) / sizeof(int); i++) {
    testSorts(input_lengths[i]);
  }

  return 0;
}