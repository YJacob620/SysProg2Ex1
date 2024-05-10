// ID: 322281536
// EMAIL: yairjacob620@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace ex1;

/* TEMPLATES
        {0,INF,INF,INF,INF},
        {INF,0,INF,INF,INF},
        {INF,INF,0,INF,INF},
        {INF,INF,INF,0,INF},
        {INF,INF,INF,INF,0}

        {0,INF,INF,INF},
        {INF,0,INF,INF},
        {INF,INF,0,INF},
        {INF,INF,INF,0}
*/

TEST_CASE("loadGraph") {
    Graph g;
    /* Proper graphs */
    vector<vector<G>> v0_1 = {
        {0,1,2},
        {3,0,5},
        {6,-7,0}
    };
    CHECK(!g.isLoaded());
    vector<vector<G>> v0_2 = { {1} };
    CHECK_NOTHROW(g.loadGraph(v0_1));
    CHECK(g.isLoaded());

    /* Invalid sizes */
    vector<vector<G>> v1_1 = { {0,1,2},{3,0,5},{6,7,0},{10,11,-12} };
    CHECK_THROWS(g.loadGraph(v1_1));
    vector<vector<G>> v1_2 = { {0,1,-2},{3,0,-5,99},{6,7,0} };
    CHECK_THROWS(g.loadGraph(v1_2));
    vector<vector<G>> v1_3 = { {0,1,2},{3,0,5},{6,7,0,9} };
    CHECK_THROWS(g.loadGraph(v1_3));
    vector<vector<G>> v1_4 = { {0,1},{3,0,5},{6,-7,0} };
    CHECK_THROWS(g.loadGraph(v1_4));
    vector<vector<G>> v1_5 = { };
    CHECK_THROWS(g.loadGraph(v1_5));
    vector<vector<G>> v1_6 = { {} };
    CHECK_THROWS(g.loadGraph(v1_6));
    vector<vector<G>> v1_7 = { {1} };
    CHECK_THROWS(g.loadGraph(v1_7));

    /* Invalid weights */
    vector<vector<G>> v2_1 = { {1,2,3},{-4,0,6},{7,8,0} };
    CHECK_THROWS(g.loadGraph(v2_1));
    vector<vector<G>> v2_2 = { {0,-2,-3},{4,5,6},{7,-8,0} };
    CHECK_THROWS(g.loadGraph(v2_2));
    vector<vector<G>> v2_3 = { {0,2,3},{4,0,-6},{7,8,9} };
    CHECK_THROWS(g.loadGraph(v2_3));
}

TEST_CASE("printGraph") {
    Graph g;

    /* Directed graphs */
    vector<vector<G>> v1_1 = {
        {0,1,-2},
        {3,0,5},
        {6,-7,0}
    };
    g.loadGraph(v1_1);
    CHECK(g.printGraph() == "Directed graph with 3 vertices and 6 edges.");
    vector<vector<G>> v1_2 = {
        {0,1,2},
        {1,0,-5},
        {2,7,0}
    };
    g.loadGraph(v1_2);
    CHECK(g.printGraph() == "Directed graph with 3 vertices and 6 edges.");
    vector<vector<G>> v1_3 = {
        {0,1,2},
        {1,0,5},
        {INF,5,0}
    };
    g.loadGraph(v1_3);
    CHECK(g.printGraph() == "Directed graph with 3 vertices and 5 edges.");
    vector<vector<G>> v1_4 = {
        {0,1,2},
        {-1,0,5},
        {2,5,0}
    };
    g.loadGraph(v1_4);
    CHECK(g.printGraph() == "Directed graph with 3 vertices and 6 edges.");
    vector<vector<G>> v1_5 = {
        {0,INF,INF},
        {INF,0,INF},
        {INF,-5,0}
    };
    g.loadGraph(v1_5);
    CHECK(g.printGraph() == "Directed graph with 3 vertices and 1 edges.");

    /* Undirected graphs */
    vector<vector<G>> v2_1 = { {0} };
    vector<vector<G>> v2_2 = {
        {0,1,2},
        {1,0,5},
        {2,5,0}
    };
    vector<vector<G>> v2_3 = {
        {0,INF,INF},
        {INF,0,INF},
        {INF,INF,0}
    };
    vector<vector<G>> v2_4 = {
        {0,INF,INF},
        {INF,0,3},
        {INF,3,0}
    };
    g.loadGraph(v2_1);
    CHECK(g.printGraph() == "Undirected graph with 1 vertices and 0 edges.");
    g.loadGraph(v2_2);
    CHECK(g.printGraph() == "Undirected graph with 3 vertices and 3 edges.");
    g.loadGraph(v2_3);
    CHECK(g.printGraph() == "Undirected graph with 3 vertices and 0 edges.");
    g.loadGraph(v2_4);
    CHECK(g.printGraph() == "Undirected graph with 3 vertices and 1 edges.");
}

using namespace Algorithms;

TEST_CASE("isConnected") {
    Graph g;
    CHECK_THROWS(isConnected(g));
    vector<vector<G>> v1_1 = {
        {0,1,INF},
        {INF,0,1},
        {1,INF,0}
    };
    g.loadGraph(v1_1);
    CHECK(isConnected(g));
    vector<vector<G>> v1_2 = {
        {0,1,INF},
        {INF,0,1},
        {INF,INF,0}
    };
    g.loadGraph(v1_2);
    CHECK(!isConnected(g));
    vector<vector<G>> v1_3 = { {0} };
    g.loadGraph(v1_3);
    CHECK(isConnected(g));
    vector<vector<G>> v1_4 = {
        {0,-1,INF,INF},
        {INF,0,INF,-1},
        {-1,INF,0,INF},
        {INF,INF,-1,0}
    };
    g.loadGraph(v1_4);
    CHECK(isConnected(g));
    vector<vector<G>> v1_5 = {
        {0,-1,2,3},
        {1,0,INF,-1},
        {-1,INF,0,INF},
        {INF,INF,INF,0}
    };
    g.loadGraph(v1_5);
    CHECK(!isConnected(g));
}

TEST_CASE("shortestPath") {
    Graph g;
    CHECK_THROWS(shortestPath(g, 0, 0));
    vector<vector<G>> v1_1 = {
        {0,INF,1},
        {9,0,INF},
        {INF,-8,0}
    };
    g.loadGraph(v1_1);
    CHECK_THROWS(shortestPath(g, 0, 3));
    CHECK(shortestPath(g, 0, 0) == "0");
    CHECK(shortestPath(g, 0, 1) == "0 -> 2 -> 1");
    vector<vector<G>> v1_2 = {
        {0, -1, 9},
        {1, 0, -1},
        {-9, 1, 0}
    };
    g.loadGraph(v1_2);
    CHECK(shortestPath(g, 2, 0) == "2 -> 0");
    CHECK(shortestPath(g, 0, 2) == "0 -> 1 -> 2");
    CHECK(shortestPath(g, 2, 1) == "2 -> 0 -> 1");
}

TEST_CASE("isBipartite") {
    Graph g;
    CHECK_THROWS(isBipartite(g));
    vector<vector<G>> v1_1 = {
        {0, -1, 3},
        {INF, 0, INF},
        {INF, INF, 0}
    };
    g.loadGraph(v1_1);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_2 = {
        {0, -1, 3},
        {1, 0, INF},
        {5, INF, 0}
    };
    g.loadGraph(v1_2);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_3 = {
        {0, -1, INF}, // 0 <-> 1 , 2
        {1, 0, INF},
        {INF, INF, 0}
    };
    g.loadGraph(v1_3);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_4 = {
        {0, -1, 4},
        {1, 0, INF},
        {-9, INF, 0}
    };
    g.loadGraph(v1_4);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_5 = {
        {0,INF,INF,INF,1}, // 2 -> 0 -> 4 -> 3 -> 1
        {INF,0,INF,INF,INF},
        {1,INF,0,INF,INF},
        {INF,1,INF,0,INF},
        {INF,INF,INF,1,0}
    };
    g.loadGraph(v1_5);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_6 = {
        {0,INF,INF,INF,1}, // 2 -> 0 -> 4 -> 3 -> 1 -> 4
        {INF,0,INF,INF,-1},
        {1,INF,0,INF,INF},
        {INF,1,INF,0,INF},
        {INF,INF,INF,1,0}
    };
    g.loadGraph(v1_6);
    CHECK(!isBipartite(g));
    vector<vector<G>> v1_7 = {
        {0,INF,INF,INF,1}, // 2 -> 0 -> 4 -> 3 -> 1 -> 0,3
        {-1,0,INF,-1,INF},
        {1,INF,0,INF,INF},
        {INF,1,INF,0,INF},
        {INF,INF,INF,1,0}
    };
    g.loadGraph(v1_7);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_8 = {
        {0,INF,1,INF}, // 0 <-> 2 , 1 <-> 3
        {INF,0,INF,1},
        {1,INF,0,INF},
        {INF,1,INF,0}
    };
    g.loadGraph(v1_8);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_9 = {
        {0,INF,1,INF}, // 0 <-> 2 <- 1 <-> 3
        {INF,0,1,1},
        {1,INF,0,INF},
        {INF,1,INF,0}
    };
    g.loadGraph(v1_9);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_10 = {
        {0,INF,1,1}, // 0 <-> 2 <- 1 <-> 3 , 0 -> 3
        {INF,0,1,1},
        {1,INF,0,INF},
        {INF,1,INF,0}
    };
    g.loadGraph(v1_10);
    CHECK(isBipartite(g));
    vector<vector<G>> v1_11 = {
        {0,1,1,INF}, // 0 <-> 2 <- 1 <-> 3 , 0 -> 1
        {INF,0,1,1},
        {1,INF,0,INF},
        {INF,1,INF,0}
    };
    g.loadGraph(v1_11);
    CHECK(!isBipartite(g));
    vector<vector<G>> v1_12 = {
        {0,INF,INF,INF,INF},
        {INF,0,INF,INF,INF},
        {INF,INF,0,INF,INF},
        {INF,INF,INF,0,INF},
        {INF,INF,INF,INF,0}
    };
    g.loadGraph(v1_12);
    CHECK(isBipartite(g));



}

TEST_CASE("negativeCycle") {
    Graph g;
    vector<vector<G>> v1_1 = {
          {0,INF,INF,INF,INF}, // 4 -> 3 -> 1 , 2 -> 0
          {INF,0,INF,INF,INF},
          {3,INF,0,INF,INF},
          {INF,-1,INF,0,INF},
          {INF,INF,INF,-1,0}
    };
    CHECK_THROWS(negativeCycle(g));
    g.loadGraph(v1_1);
    CHECK(!negativeCycle(g));
    vector<vector<G>> v1_2 = {
          {0,INF,INF,INF,INF}, // 4 -> 3 -> 1 -> 4 , 2 -> 0
          {INF,0,INF,INF,-3},
          {3,INF,0,INF,INF},
          {INF,1,INF,0,INF},
          {INF,INF,INF,1,0}
    };
    g.loadGraph(v1_2);
    CHECK(negativeCycle(g));
    vector<vector<G>> v1_3 = {
          {0,INF,INF,INF,INF}, // 4 -> 3 -> 1 -> 4 , 2 -> 0
          {INF,0,INF,INF,-2},
          {3,INF,0,INF,INF},
          {INF,1,INF,0,INF},
          {INF,INF,INF,1,0}
    };
    g.loadGraph(v1_3);
    CHECK(!negativeCycle(g));
    vector<vector<G>> v1_4 = {
        {0,2,2,INF,INF}, // 4 -> 3 -> 1  , 2 <-> 0
        {INF,0,INF,INF,INF},
        {-3,INF,0,INF,INF},
        {INF,-1,INF,0,INF},
        {INF,INF,INF,-1,0}
    };
    g.loadGraph(v1_4);
    CHECK(negativeCycle(g));
    vector<vector<G>> v1_5 = {
        {0}
    };
    g.loadGraph(v1_5);
    CHECK(!negativeCycle(g));
    vector<vector<G>> v1_6 = {
        {0,INF,INF,INF,1}, // 2 -> 4 <-> 3 <-> 1 , 0 -> 4
        {INF,0,INF,-5,INF},
        {INF,INF,0,INF,1},
        {INF,-1,INF,0,-9},
        {INF,INF,INF,-1,0}
    };
    g.loadGraph(v1_6);
    CHECK(negativeCycle(g));
    vector<vector<G>> v1_7 = {
        {0,INF,INF,INF,1}, // 2 -> 4 <-> 3 -> 1 , 0 -> 4
        {INF,0,INF,INF,INF},
        {INF,INF,0,INF,1},
        {INF,-1,INF,0,-9},
        {INF,INF,INF,-1,0}
    };
    g.loadGraph(v1_7);
    CHECK(negativeCycle(g));
    vector<vector<G>> v1_8 = {
        {0,INF,INF,7,INF}, // 4 -> 3 -> 1 -> 2 -> 4 , 2 -> 0 , 0 -> 3 , 4 -> 0
        {INF,0,5,INF,INF},
        {3,INF,0,INF,6},
        {INF,-1,INF,0,INF},
        {8,INF,INF,-1,0}
    };
    g.loadGraph(v1_8);
    CHECK(!negativeCycle(g));
}

TEST_CASE("isContainsCycle") {
    Graph g;
    vector<vector<G>> v1_1 = {
          {0,INF,INF,INF,INF}, // 4 -> 3 -> 1 , 2 -> 0
          {INF,0,INF,INF,INF},
          {3,INF,0,INF,INF},
          {INF,-1,INF,0,INF},
          {INF,INF,INF,-1,0}
    };
    CHECK_THROWS(isContainsCycle(g));
    g.loadGraph(v1_1);
    CHECK(!isContainsCycle(g));
    vector<vector<G>> v1_2 = {
          {0,INF,INF,INF,INF}, // 4 -> 3 -> 1 -> 4 , 2 -> 0
          {INF,0,INF,INF,5},
          {3,INF,0,INF,INF},
          {INF,-1,INF,0,INF},
          {INF,INF,INF,-1,0}
    };
    g.loadGraph(v1_2);
    CHECK(isContainsCycle(g));
    vector<vector<G>> v1_3 = {
        {0,2,INF,INF,INF}, // 4 -> 3 -> 1  , 2 -> 0
        {INF,0,INF,INF,INF},
        {3,INF,0,INF,INF},
        {INF,-1,INF,0,INF},
        {INF,INF,INF,-1,0}
    };
    g.loadGraph(v1_3);
    CHECK(!isContainsCycle(g));
    vector<vector<G>> v1_4 = {
        {0,2,2,INF,INF}, // 4 -> 3 -> 1  , 2 <-> 0
        {INF,0,INF,INF,INF},
        {3,INF,0,INF,INF},
        {INF,-1,INF,0,INF},
        {INF,INF,INF,-1,0}
    };
    g.loadGraph(v1_4);
    CHECK(isContainsCycle(g));
    vector<vector<G>> v1_5 = {
        {0}
    };
    g.loadGraph(v1_5);
    CHECK(!isContainsCycle(g));
    vector<vector<G>> v1_6 = {
        {0,INF,INF,INF,1}, // 2 -> 4 <-> 3 <-> 1 , 0 -> 4
        {INF,0,INF,-5,INF},
        {INF,INF,0,INF,1},
        {INF,-1,INF,0,-9},
        {INF,INF,INF,-1,0}
    };
    g.loadGraph(v1_6);
    CHECK(isContainsCycle(g));
    vector<vector<G>> v1_7 = {
        {0,INF,INF,INF,1}, // 2 -> 4 <-> 3 -> 1 , 0 -> 4
        {INF,0,INF,INF,INF},
        {INF,INF,0,INF,1},
        {INF,-1,INF,0,-9},
        {INF,INF,INF,-1,0}
    };
    g.loadGraph(v1_7);
    CHECK(isContainsCycle(g));
    vector<vector<G>> v1_8 = {
        {0,INF,INF,7,INF}, // 4 -> 3 -> 1 -> 2 -> 4 , 2 -> 0 , 0 -> 3 , 4 -> 0
        {INF,0,5,INF,INF},
        {3,INF,0,INF,6},
        {INF,-1,INF,0,INF},
        {8,INF,INF,-1,0}
    };
    g.loadGraph(v1_8);
    CHECK(isContainsCycle(g));
}
