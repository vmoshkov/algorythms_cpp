#include <iostream>
#include "adjacencyList.h"
#include "vmHeap.h"
#include "dijkstrasAlgorythm.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    adjacencyList adjList;
    vmHeap myheap;
    dijkstrasAlgorythm dijkstra;

    adjList.testMe();
    myheap.testMe();
    dijkstra.testMe();

    return 0;
}
