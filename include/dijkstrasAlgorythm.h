#ifndef DIJKSTRASALGORYTHM_H
#define DIJKSTRASALGORYTHM_H

#include "adjacencyList.h"
#include <limits>

using namespace std;

// http://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B



class dijkstrasAlgorythm
{
    public:
        dijkstrasAlgorythm();
        virtual ~dijkstrasAlgorythm();
        void addVertex(const Vertex& V);
        void addaddjacentNode(const Vertex& V, const Vertex& adjV, const int& weight);
        void dumpGraph();
        void dijkstra(const Vertex& from, const Vertex& to);
        void testMe();

    protected:

    private:

        // whole graph as an adjacency list with distances between nodes
        unordered_map<Vertex, unordered_set<pair<Vertex, int>>> adjListWithweights;
};


#endif // DIJKSTRASALGORYTHM_H
