/**
 * @file kumar-project-5.cpp
 * @author Kartik Kumar
 * @brief Project 5 - Use Depth First Search to find the number of connected
 components and at least a cycle (the graph must contain at least a cycle) of
 the graphs shown below. Display the edges of the cycles, for example in graph
 one below, the following edges should be displayed “Cycle: (0,1), (1,2), (2,3),
 (3,0)”.
 */

#include <iostream>
using namespace std;

// Define a simple structure to represent a node in the graph
struct Node {
  int value;
  Node *next;
};

// Define a class to represent a graph
class Graph {
private:
  int vertices; // Number of vertices in the graph
  int edges;    // Number of edges in the graph
  Node *roots;  // Array of roots (heads) of the linked lists
public:
  // Constructor to initialize the graph
  Graph(int vertices) {
    // Initialize the number of vertices and edges
    this->edges = 0;
    this->vertices = vertices;

    // Initialize the array of roots with incrementing values
    this->roots = new Node[vertices];
    for (int i = 0; i < vertices; i++) {
      this->roots[i].next = 0;
      this->roots[i].value = i;
    }
  }

  // This method will create a graph from user input
  // Required by project directions from professor
  void Creates() {
    // Retrieve number of edges from user input
    cout << "Enter the number of edges: ";
    cin >> this->edges;

    // Retrieve the edges from user input number of edges times
    for (int i = 0; i < this->edges; i++) {
      // Retrieve the number of vertices from the from-to range
      int from, to;
      cout << "Enter the number of vertices connecting 0 to " << (i + 1)
           << ": ";
      cin >> from >> to;

      // Add the two nodes to the internal linked lists of the graph
      this->Add(from, to);
      this->Add(to, from);
    }
  }

  // This method will add a node to the linked list of the graph
  void Add(int from, int to) {
    // Create a new node to be added to the linked list
    Node *node = new Node;
    node->value = to;
    node->next = this->roots[from].next;

    // Set the head of the linked list to the new node
    this->roots[from].next = node;
  }

  // This method will print the graph
  // Follows directions from professor in format "Cycle: (0,1), (1,2), (2,3),
  // (3,0)"
  void Print() {
    // Print the beginning of the cycle
    cout << "Cycle:";

    // Loop through the linked lists
    int cursor = 0;
    for (int i = 0; i < this->vertices; i++) {
      // Retrieve the head of the linked list
      Node *node = this->roots[i].next;

      // Loop through the linked list
      while (node != 0) {
        // Print a comma if the node is not the last in the list
        if (cursor > 0) {
          cout << ",";
        }

        // Print the edge
        cout << " (" << i << ", " << node->value << ")";

        // Increment the cursor
        cursor++;
      }
    }
  }
};

int main() {
  // Retrieve the number of vertices from user input
  int vertices;
  cout << "Enter the number of vertices: ";
  cin >> vertices;

  // Create a graph with the number of vertices
  Graph *graph = new Graph(vertices);

  // Create and print the graph back to the user
  graph->Creates();
  graph->Print();

  return 0;
}