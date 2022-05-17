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
  Node *roots;  // Array of roots
  int vertices; // Number of vertices in the graph
  int edges;    // Number of edges in the graph
public:
  bool cycles = false; // Flag to indicate if the graph contains a cycle
  bool *tracking;      // Array to keep track of visited nodes

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

    // Initialize the tracking array
    tracking = new bool[vertices];
    for (int i = 0; i < vertices; i++) {
      tracking[i] = false;
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

  // Prints any cycles in the graph in the format "Cycle: (0, 1), (1, 2), (2,
  // 3), (3, 0)"
  void PrintCycles() {
    // Iterate through the roots
    for (int i = 0; i < this->vertices; i++) {
      // Iterate through the linked list of the root
      Node current = this->roots[i];
      Node *node = current.next;
      while (node) {
        // If the node is the same as the root, then a cycle has been found
        if (node->value == current.value) {
          // Set the flag to indicate a cycle has been found
          this->cycles = true;

          // Print the cycle
          cout << "Cycle: ";
          Node *temp = node;
          while (temp != 0) {
            cout << "(" << temp->value << ", ";
            temp = temp->next;
          }
          cout << i << ")" << endl;
        }
        node = node->next;
      }
    }
  }

  // This method will perform a depth first search on the graph
  void DFS(int root) {
    // Set the node as visited
    this->tracking[root] = true;

    // Iterate through the linked list of the root
    Node current = this->roots[root];
    Node *node = current.next;
    while (node) {
      // If the node has not been visited, then perform a depth first search
      if (!this->tracking[node->value]) {
        // Perform a depth first search on the node
        this->DFS(node->value);
      }
      node = node->next;
    }
  }

  // This methods will return the number of connected components in the graph
  int GetConnections() {
    // Initialize the number of connected components
    int connections = 0;

    // Iterate through the roots
    for (int i = 0; i < this->vertices; i++) {
      // If the root has not been visited, then increment the number of
      // connected components
      if (!this->tracking[i]) {
        connections++;
        this->DFS(i);
      }
    }

    // Return the number of connected components
    return connections;
  }
};

int main() {
  // Retrieve the number of vertices from user input
  int vertices;
  cout << "Enter the number of vertices: ";
  cin >> vertices;

  // Create a graph with the number of vertices
  Graph *graph = new Graph(vertices);

  // Create, Print and Generate Insights for the graph
  graph->Creates();
  graph->PrintCycles();

  // Print the number of connected components
  cout << "Number of connected components: " << graph->GetConnections() << endl;

  // Print whether this graph contains a cycle
  if (graph->cycles) {
    cout << "This Graph Contains A Cycle!" << endl;
  } else {
    cout << "This Graph Does NOT Contain A Cycle." << endl;
  }

  return 0;
}