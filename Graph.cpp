// ID: 322281536
// EMAIL: yairjacob620@gmail.com

#include "Graph.hpp"

namespace ex1 {
    /// @brief Checks if an adjacency matrix is valid. A valid one is a square matrix 
    ///        where the elements in the main diagonal are zeros.
    /// @param matrix Matrix to check.
    /// @return True if the matrix is valid, False otherwise.
    bool isValid(const vector<vector<T>>& matrix) {
        if (matrix.empty()) {
            return false;
        }
        auto rows = matrix.size();
        for (int i = 0;i < rows;i++) {
            vector<T> vec = matrix[i];
            if (vec.size() != rows || vec[i] != 0) {
                return false;
            }
        }
        return true;
    }

    /// @brief Checks if an adjacency matrix is a directed graph. Assumes the matrix is valid.
    /// @param matrix Matrix to check.
    /// @return True if the matrix is directed, False otherwise.
    bool checkIfDirected(const vector<vector<T>>& matrix) {
        auto rows = matrix.size();
        for (int i = 0;i < rows;i++) {
            for (int j = i;j < rows;j++) {
                if (matrix[i][j] != matrix[j][i]) {
                    return true;
                }
            }
        }
        return false;
    }

    /// @brief Prints a matrix.
    /// @param mat Matrix to print.
    void printMatrix(const vector<vector<T>>& mat) {
        for (const vector<T>& vec : mat) {
            for (T element : vec) {
                if (element == INF) {
                    cout << "inf";
                }
                else {
                    cout << element;
                }
                cout << "   ";
            }
            cout << endl;
        }
    }

    void Graph::run_FloydWarshall() {
        auto rows = this->matrix.size();
        this->SP_weights.resize(rows, vector<T>(rows));
        this->SP_tree.resize(rows, vector<T>(rows));

        /* Shortest paths matrix and SP-tree initialization */
        for (int i = 0;i < rows;i++) {
            for (int j = 0;j < rows;j++) {
                T val = this->matrix[i][j];
                SP_weights[i][j] = val;
                if (val == INF) {
                    SP_tree[i][j] = NOPATH;
                }
                else {
                    SP_tree[i][j] = i;
                }
            }
        }
        for (int i = 0; i < rows; ++i) {
            SP_tree[i][i] = i;
        }

        /* The "meat" of the algorithm */
        for (int k = 0;k < rows;k++) {
            for (int i = 0;i < rows;i++) {
                for (int j = 0;j < rows;j++) {
                    if (SP_weights[i][k] != INF && SP_weights[k][j] != INF) {
                        int new_path_weight = SP_weights[i][k] + SP_weights[k][j];
                        if (SP_weights[i][j] > new_path_weight) {
                            SP_weights[i][j] = new_path_weight;
                            SP_tree[i][j] = SP_tree[k][j];
                        }
                    }
                }
            }
        }
    }

    void Graph::loadGraph(const vector<vector<T>>& matrix) {
        if (!isValid(matrix)) {
            throw runtime_error("Invalid graph. A graph should be a square matrix where the "
                "elements in the main diagonal are zeros.");
            return;
        }
        this->matrix = matrix;
        this->directed = checkIfDirected(matrix);
        run_FloydWarshall();
    }

    string Graph::printGraph() const {
        string ans;
        if (this->matrix.empty()) {
            cout << "Empty graph." << endl;
            return ans;
        }
        unsigned vertices = this->matrix[0].size();
        unsigned edges = 0;
        for (const vector<T>& vec : this->matrix) {
            for (T element : vec) {
                if (element != INF) {
                    edges++;
                }
            }
        }
        edges -= vertices; // No such thing as an edge between a vertex and itself.
        if (this->directed) {
            ans.append("Directed ");
        }
        else {
            ans.append("Undirected ");
            edges /= 2;
        }
        ans.append("graph with " + to_string(vertices) + " vertices and " + to_string(edges) + " edges.");
        cout << ans << endl;
        printMatrix(this->matrix); //REMOVE MAYBE
        return ans;
    }

    vector<vector<T>> Graph::get_matrix() const {
        return this->matrix;
    }

    vector<vector<T>> Graph::get_SPT() const {
        return this->SP_tree;
    }

    vector<vector<T>> Graph::get_SPW() const {
        return this->SP_weights;
    }

    bool Graph::isLoaded() const {
        return !(this->matrix.empty()); // asd
    }

    bool Graph::isDirected() const {
        if (!isLoaded()) {
            throw runtime_error("Invalid action - graph is not loaded. (1)");
        }
        return directed;
    }

    Graph::~Graph() {
        cout << "DISTRUCTOR" << endl;
    }
}
