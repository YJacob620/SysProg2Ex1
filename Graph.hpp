#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <limits>

#define T int // Type of the elements in the matrix/sub-vectors.
#define INF std::numeric_limits<T>::max() // Maximum value of type T.
#define NOPATH -1 // Value which indicates "no path" between 2 in shortest paths tree.

namespace ex1 {
  using namespace std;

  class Graph {
    private:
    vector<vector<T>> matrix; // Adjacency matrix representing the graph.
    bool directed; // Whether the graph is directed or not.
    vector<vector<T>> SP_weights; // Shortest paths weights.
    vector<vector<T>> SP_tree; // Shortest paths tree.

    /// @brief Runs Floyd Warshall algorithm on the graph to find all-pairs-shortest-paths and
    ///        to set the appropriate shortest-paths-tree to the graph.
    void run_FloydWarshall();

    public:
    /// @brief Loads an adjacency matrix (as a graph) to this Graph - as long as it's valid. 
    ///        Throws runtime_error if matrix is invalid.
    /// @param matrix Adjacency matrix to load as a graph.
    void loadGraph(const vector<vector<T>>& matrix);

    /// @brief Prints information about the graph.
    /// @return Some information about the graph as a string type.
    string printGraph() const;

    /// @return The adjacency matrix representing this graph.
    vector<vector<T>> get_matrix() const;

    /// @brief Get Shortest Paths Tree.
    /// @return The all-pairs-shortest-paths shortest-paths-tree of the graph.
    vector<vector<T>> get_SPT() const;

    /// @brief Get Shortest Paths Weights.
    /// @return The all-pairs-shortest-paths weights-matrix of the graph.
    vector<vector<T>> get_SPW() const;

    /// @brief Checks whether the graph is currently loaded (not empty).
    /// @return True if he graph is loaded, False otherwise.
    bool isLoaded() const;

    /// @brief Checks whether the graph is directed.
    /// @return True if he graph is directed, False otherwise.
    bool isDirected() const;

    ~Graph();
  };
};