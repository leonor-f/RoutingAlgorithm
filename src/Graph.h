#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <float.h>
#include "NetworkPoint.h"
#include <unordered_set>

template <class T>
class Edge;

/************************* Vertex  **************************/

template <class T>
class Vertex {
public:
    Vertex(T in);

    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    double getDist() const;
    Edge<T> *getPath() const;
    std::vector<Edge<T> *> getIncoming() const;

    void setInfo(T info);
    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Edge<T> *path);
    Edge<T> * addEdge(Vertex<T> *dest, double w);
    bool removeEdge(T in);
    void removeOutgoingEdges();

    const Edge<T> *getEdge(const Vertex<T> *dest) const;

protected:
    T info;                // info node
    std::vector<Edge<T> *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    double dist = 0;
    Edge<T> *path = nullptr;

    std::vector<Edge<T> *> incoming; // incoming edges

    void deleteEdge(Edge<T> *edge);

};

/********************** Edge  ****************************/

template <class T>
class Edge {
public:
    Edge(Vertex<T> *orig, Vertex<T> *dest, double w);

    Vertex<T> * getDest() const;
    double getWeight() const;
    Vertex<T> * getOrig() const;
    Edge<T> *getReverse() const;
    void setReverse(Edge<T> *reverse);
protected:
    Vertex<T> * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // used for bidirectional edges
    Vertex<T> *orig;
    Edge<T> *reverse = nullptr;
};

/********************** Graph  ****************************/

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex<NetworkPoint> *findVertex(const NetworkPoint &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const NetworkPoint &in);
    bool removeVertex(const NetworkPoint &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const NetworkPoint &sourc, const NetworkPoint &dest, double w);
    bool removeEdge(const NetworkPoint &source, const NetworkPoint &dest);
    bool addBidirectionalEdge(const NetworkPoint &sourc, const NetworkPoint &dest, double w);

    int getNumVertex() const;
    std::unordered_map<unsigned, Vertex<NetworkPoint> *> getVertexSet() const;

    std:: vector<NetworkPoint> dfs() const;
    std:: vector<NetworkPoint> dfs(const NetworkPoint & source) const;
    void dfsVisit(Vertex<NetworkPoint> *v,  std::vector<NetworkPoint> & res) const;
    std::vector<NetworkPoint> bfs(const NetworkPoint & source) const;

    bool isDAG() const;
    bool dfsIsDAG(Vertex<NetworkPoint> *v) const;

    /**
     * @brief Calculates the Haversine distance between two points specified by latitude and longitude.
     *
     * @param lat1 Latitude of the first point in degrees.
     * @param lon1 Longitude of the first point in degrees.
     * @param lat2 Latitude of the second point in degrees.
     * @param lon2 Longitude of the second point in degrees.
     * @return The Haversine distance between the two points in meters.
     * @complexity O(1)
     */
    double haversine(double lat1, double lon1, double lat2, double lon2) const;

    /**
     * @brief Computes an approximate solution to the TSP using MST and preorder traversal.
     *
     * @return A vector of NetworkPoint objects representing the approximate TSP tour.
     * @complexity O(V + E), where V is the number of vertices and E is the number of edges.
     */
    std::vector<NetworkPoint> aproxTSP();

    /**
     * @brief Computes the Minimum Spanning Tree of the graph starting from a given root vertex using Prim's algorithm.
     *
     * @param root A pointer to the root vertex from which to start the MST computation.
     * @return A Graph representing the MST.
     * @complexity O((V + E) log V), where V is the number of vertices and E is the number of edges.
     */
    Graph computeMST(Vertex<NetworkPoint> *root);

    /**
     * @brief Calculates the total weight of a triangular tour through the given points.
     *
     * @param g A vector of NetworkPoint objects representing the points in the tour.
     * @return The total weight of the triangular tour.
     * @complexity O(N), where N is the number of points in the vector.
     */
    double calculateTriangular(std::vector<NetworkPoint> g);

    double getEdgeWeight(const NetworkPoint &a, const NetworkPoint &b) const;

    /**
     * @brief Recursive helper function for solving the Traveling Salesman Problem using backtracking. Complexity: O(V!)
     *
     * This function attempts to find the shortest path that visits all vertices in the graph exactly once
     * and returns to the starting vertex. It explores all possible paths using backtracking and updates
     * the minimum distance and corresponding path whenever a shorter path is found.
     *
     * @param curIndex The current index in the path being constructed.
     * @param curDist The current total distance of the path being constructed.
     * @param curPath The current path being constructed.
     * @param minDist Reference to the minimum distance found so far.
     * @param path Reference to the path corresponding to the minimum distance found so far.
     *
     */
    void tspBTRec(unsigned int curIndex, double curDist, std::vector<unsigned int> &curPath, double &minDist,
                  std::vector<unsigned int> &path) const;

    /**
     * @brief Solves the Traveling Salesman Problem using backtracking. Complexity: O(V!)
     *
     * This function initializes the necessary variables and calls the recursive helper function `tspBTRec`
     * to compute the shortest possible route that visits each vertex exactly once and returns to the starting point.
     * It returns the minimum distance of such a path and stores the corresponding path in the provided vector.
     *
     * @param path Reference to a vector where the path of the minimum distance will be stored.
     * @return The minimum distance of the Traveling Salesman Problem solution.
     *
     */
    double tspBT(std::vector<unsigned int> &path) const;

    /**
     * @brief Solves the TSP using a heuristic approach based on clustering and greedy traversal. Complexity: O(N^2), where N is the number of vertices in the graph.
     *
     * @param path A reference to a vector of unsigned integers to store the resulting TSP path.
     * @return The total distance of the TSP tour.
     *
     */
    double tspHeuristic(std::vector<unsigned int> &path) const;

    /**
     * @brief Finds the nearest vertex from a specified vertex among a set of candidates. Complexity: O(C), where C is the number of candidates.
     *
     * @param from The index of the vertex from which distances are measured.
     * @param candidates A reference to an unordered set of unsigned integers representing
     *        the indices of candidate vertices.
     * @return The index of the nearest vertex from the specified vertex.
     *
     */
    unsigned int getNearestVertex(unsigned int from, const std::unordered_set<unsigned int> &candidates) const;

    /**
     * @brief Calculates the total distance of a tour within a cluster using a greedy algorithm. Complexity: O(N^2), where N is the number of vertices in the cluster.
     *
     * @param cluster A reference to a vector of unsigned integers representing the indices of vertices in the cluster.
     * @param clusterPath A reference to a vector of unsigned integers to store the tour path within the cluster.
     * @return The total distance of the tour within the cluster.
     *
     */
    double solveClusterTSP(const std::vector<unsigned int> &cluster, std::vector<unsigned int> &clusterPath) const;

    /**
     *
     *
     * @brief Perform k-means clustering on the vertices of the graph. Complexity: O(V * k * T), where V is the number of vertices, k is the number of clusters, and T is the number of iterations until convergence.
     *
     * @param clusters A reference to a vector of vectors of unsigned integers.
     * @param k The number of clusters to create.
     * @return void
     * Complexity: O(V * k * T), where V is the number of vertices, k is the
     *             number of clusters, and T is the number of iterations until
     *             convergence.
     */
    void clustering(std::vector<std::vector<unsigned int>> &clusters, unsigned int k) const;

protected:
    std::unordered_map<unsigned, Vertex<NetworkPoint> *> vertexSet;    // vertex set
};


#endif //GRAPH_H