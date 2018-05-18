#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>      // std::pair, std::make_pair

using namespace std;

// single vertex of a graph
typedef struct Vertex_ {
        string name;
} Vertex;


// custom specialization of std::hash can be injected in namespace std
namespace std
{
    // it is needed to use Vertex as a key in unordered_map
    template<> struct hash<Vertex>
    {
        typedef Vertex argument_type;
        typedef size_t result_type;
        result_type operator()(argument_type const& v) const
        {
            result_type const h1 ( std::hash<string>{}(v.name) );
            return (h1 << 1); // or use boost::hash_combine (see Discussion)
        }
    };


    // it is needed to use pair<Vertex, int> as value in unordered_set
    template<> struct hash<pair<Vertex, int>>
    {
        typedef pair<Vertex, int> argument_type;
        typedef size_t result_type;
        result_type operator()(const pair<Vertex, int>& v) const
        {
            auto h1 = std::hash<Vertex>{}(v.first);
            auto h2 = std::hash<int>{}(v.second);

            return h1 ^ h2;
        }
    };

    // inline definition for == operator for Vertex struct (needed for unordered_map)
    inline bool operator==(const Vertex& first,const Vertex& second)
    {
        return  first.name == second.name;
    }

    // inline definition for != operator for Vertex struct
    inline bool operator!=(const Vertex& first,const Vertex& second)
    {
        return  first.name != second.name;
    }

    // inline definition for < operator for Vertex struct (needed for map)
    inline bool operator < (const Vertex& first,const Vertex& second)
    {
        return  first.name < second.name;
    }
}

/*

adjacency list represention of a graph

*/
class adjacencyList
{
    public:
        adjacencyList();
        virtual ~adjacencyList();
        void addVertex(const Vertex& V);
        void addaddjacentNode(const Vertex& V, const Vertex&adjV);
        void dumpGraph();
        void testMe();

    protected:
    // adjacency list without distances between nodes
        unordered_map<Vertex, unordered_set<Vertex>> adjList;


    private:


};

#endif // ADJACENCYLIST_H
