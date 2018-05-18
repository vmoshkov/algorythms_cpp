#include "adjacencyList.h"

adjacencyList::adjacencyList()
{
    //ctor
}

adjacencyList::~adjacencyList()
{
    cout << "deleting adjacency list" << endl;
    //dtor
}

/*
* adds a vertex to the graph
*/
void adjacencyList::addVertex(const Vertex& V)
{
    // we have to chaeck if this element already exists
    if(adjList.count(V)==0)
    {
        unordered_set<Vertex> adjVertices;
        pair<Vertex, unordered_set<Vertex>> element = {V, adjVertices};
        adjList.insert(element);
        cout << "size of adjacency list is " << adjList.size() << endl;
    }

}

/*
*  adds an adjacency node to a vertex
*/
void adjacencyList::addaddjacentNode(const Vertex& V, const Vertex& adjV)
{
    unordered_set<Vertex> &adjVertices = adjList[V];

    adjVertices.insert(adjV);

    cout << "Vertex" << V.name << ": size of adjacent vertices list is " << adjVertices.size() << endl;
}

/*
* prints a graph
*/
void adjacencyList::dumpGraph()
{
    for (pair<Vertex, unordered_set<Vertex>> element : adjList)
    {
        Vertex& v = element.first;
        unordered_set<Vertex> &adjVertices = element.second;

        cout << v.name << " :: ";

        for(Vertex adjVertex: adjVertices)
        {
            cout << adjVertex.name << "  ";
        }

        cout << "\n";

    }

}


void adjacencyList::testMe()
{

    cout<< "Start test of adjacency list representation of a graph.\n";

    Vertex v1 = {"A"};
    Vertex v2 = {"B"};
    Vertex v3 = {"C"};
    Vertex v4 = {"D"};
    Vertex v5 = {"E"};
    Vertex v6 = {"F"};

    this->addVertex(v1);
    this->addVertex(v2);
    this->addVertex(v3);
    this->addVertex(v4);
    this->addVertex(v5);
    this->addVertex(v6);

    // adjacent vertices for A
    this->addaddjacentNode(v1, v3);
    this->addaddjacentNode(v1, v4);

    // adjacent vertices for B
    this->addaddjacentNode(v2, v3);
    this->addaddjacentNode(v2, v5);

    // adjacent vertices for C
    this->addaddjacentNode(v3, v4);

    // adjacent vertices for D
    this->addaddjacentNode(v4, v5);
    this->addaddjacentNode(v4, v6);

    // adjacent vertices for E
    this->addaddjacentNode(v5, v1);

    // adjacent vertices for F
    this->addaddjacentNode(v6, v3);
    this->addaddjacentNode(v6, v5);


    this->dumpGraph();


}
