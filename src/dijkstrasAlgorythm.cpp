#include "dijkstrasAlgorythm.h"
#include <set>
#include <map>


dijkstrasAlgorythm::dijkstrasAlgorythm()
{
    //ctor
}

dijkstrasAlgorythm::~dijkstrasAlgorythm()
{
    //dtor
}

/*
* adds a vertex to the graph
*/
void dijkstrasAlgorythm::addVertex(const Vertex& V)
{
    // we have to chaeck if this element already exists
    if(adjListWithweights.count(V)==0)
    {
        unordered_set<pair<Vertex, int>> adjVerticesWithDistances;
        pair<Vertex, unordered_set<pair<Vertex, int>>> element = {V, adjVerticesWithDistances};
        adjListWithweights.insert(element);
        cout << "size of adjacency list is " << adjListWithweights.size() << endl;
    }

}

/*
*  adds an adjacency node to a vertex with the weight of distance
*/
void dijkstrasAlgorythm::addaddjacentNode(const Vertex& V, const Vertex& adjV, const int& weight)
{
    unordered_set<pair<Vertex, int>>& adjVerticesWithDistances = adjListWithweights[V];

    pair<Vertex, int> element = {adjV, weight};

    adjVerticesWithDistances.insert(element);

    cout << "Vertex" << V.name << ": size of adjacent vertices list is " << adjVerticesWithDistances.size() << endl;
}

/*
* prints a graph
*/
void dijkstrasAlgorythm::dumpGraph()
{
    for (pair<Vertex, unordered_set<pair<Vertex, int>>> element : adjListWithweights)
    {
        Vertex& v = element.first;
        unordered_set<pair<Vertex, int>> &adjVerticesWithDistances = element.second;

        cout << v.name <<" :: ";

        for(pair<Vertex, int> adjVertex: adjVerticesWithDistances)
        {
            cout << adjVertex.first.name << " [weight:" << adjVertex.second << "] ";
        }

        cout << "\n";
    }

}

/*
* Вычисление кратчайшего пути от точки до точки
*/
void dijkstrasAlgorythm::dijkstra(const Vertex& from, const Vertex& to)
{


    /*

    берем начальную ноду
    - находим все её связанные ноыы, если связанной ноды нет, переходим к следующей ноде в массиве
    - для каждой ноды высчитываем расстояние от неё до начальной ноды
    - для каждой ноды помещаем её в отсортированный сет(нода, дистанция)
    - фиксируем начальную ноду: обновляем во втором массиве данные <нода, дистанция, предыдущая, посещенна>
    - удаляем из сета фиксированную ноду

    берем из сета ноду с мин дистанцией (мин нода)
    - находим все её связанные ноыы,
    - если связанных нод нет, а эта нода не искомая, удаляем её из сета, переходим к следующей ноде в сете
    - для каждой связанной ноды высчитываем расстояние от неё до начальной ноды
    - для каждой связанной ноды помещаем её в отсортированный сет(нода, дистанция)
    - если нашли искомую ноду, фиксируем её: обновляем во втором массиве данные <нода, дистанция, предыдущая, посещен>
    - текущую мин ноду "фиксируем": обновляем во втором массиве данные <нода, дистанция, предыдущая, посещенна>
    - удаляем из сета фиксированную ноду


    */

    // структура для поддержанич отсортированным по дистанциям от начальной ноды
    //  массив остальных нод
    multiset<pair<int, Vertex>> vertex_minheap;

    // соотношение нода - мин путь для этой ноды
    map<Vertex, int> min_distance_for_a_vertex;
    // Родительская нода в пути
    map<Vertex, Vertex> parent_node_in_path;

    // финализирую начальную ноду
    // мин расстояние на текущий момент
    int mindistance = 0;
    min_distance_for_a_vertex[from] = 0;
    parent_node_in_path[from] = from;

    cout << "finilize " <<from.name<< " with distance " << mindistance <<endl;

    // все связанные ноды начальной ноды
    unordered_set<pair<Vertex, int>> adjVertices = adjListWithweights[from];

    // для каждой связанной ноды надо вычислить расстояние
    unordered_set<pair<Vertex, int>>::iterator it;
    for (it = adjVertices.begin(); it != adjVertices.end(); it++) {
        pair<Vertex, int> adjacentNode =  *it;

        cout<<adjacentNode.first.name<< " " <<adjacentNode.second<<endl;

        min_distance_for_a_vertex[adjacentNode.first] = adjacentNode.second + mindistance;
        // устанавливаем пред ноду для этой ноды в этом пути
        parent_node_in_path[adjacentNode.first] = from;

        // добавляем в мин хип ноду с её текущей дистанцией:
        // аргумент №1 - мин дист для этой ноды
        // аргумент №2 - нода
        vertex_minheap.insert(
            make_pair(min_distance_for_a_vertex[adjacentNode.first],
            adjacentNode.first));
    }


    while(!vertex_minheap.empty())
    {
       // получаю ноду с мин дистанцие (и удаляю её из списка рассматриваемых)
       pair<int, Vertex> nextNode = *vertex_minheap.begin();
       vertex_minheap.erase(nextNode);
       // финализирую ноду:
       // мин расстояние теперь принимается расстоянию этой ноды
       mindistance = nextNode.first;

       cout << "finilize " <<nextNode.second.name<<
                    " with distance " << nextNode.first <<
                    " with parent node" << parent_node_in_path[nextNode.second].name << endl;

       // для каждой связанной ноды для мин ноды надо вычислить расстояние
       // и добавить в мин хип для последующего последовательного рассмотрения
        unordered_set<pair<Vertex, int>> adjVertices = adjListWithweights[nextNode.second];
        unordered_set<pair<Vertex, int>>::iterator it;
        for (it = adjVertices.begin(); it != adjVertices.end(); it++) {
            pair<Vertex, int> adjacentNode =  *it;

            cout<<adjacentNode.first.name<< " " <<adjacentNode.second<<endl;

            // сохраняем для ноды её мин расстояние
            int mindist = adjacentNode.second + mindistance;

            // если в кеше дистанций для ноды уже есть расстояние и оно меньше текущего,
            // просто продолжаем
            if (min_distance_for_a_vertex.count(adjacentNode.first)>0 &&
                        min_distance_for_a_vertex[adjacentNode.first] < mindist)
                        continue;

            // иначе удаляем из мин хипа значение больше чем только что получили, т.к.
            // этот путь рассматривать уже не имеет смысла
            vertex_minheap.erase(make_pair(min_distance_for_a_vertex[adjacentNode.first],
                    adjacentNode.first));

            // устанавливаем мин значение для ноды в кеше мин значени
            min_distance_for_a_vertex[adjacentNode.first] = mindist;
            // устанавливаем предыдущую ноду для этой ноды в этом пути
            parent_node_in_path.erase(adjacentNode.first);
            parent_node_in_path.insert(make_pair(adjacentNode.first, nextNode.second));

            // добавляем в мин хип ноду с её текущей дистанцией
            // для последующего рассматрения
            vertex_minheap.insert(make_pair(min_distance_for_a_vertex[adjacentNode.first],
                    adjacentNode.first));
        }
    }

    //DUMP
    cout<<" path is " << to.name << " <- ";

    Vertex prev = parent_node_in_path[to];

    while(prev!=from)
    {
        cout<<prev.name << " <- ";
        prev = parent_node_in_path[prev];
    }

    cout << from.name << endl;

    cout<< " distance between " << from.name << " and " << to.name
                << " is " << min_distance_for_a_vertex[to] << endl;

}

void dijkstrasAlgorythm::testMe()
{

    cout<< "Start test of dijkstras algorythm.\n";

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
    this->addaddjacentNode(v1, v2, 9); //B
    this->addaddjacentNode(v1, v3, 3); //C

    // adjacent vertices for B
    this->addaddjacentNode(v2, v4, 2); //D

    // adjacent vertices for C
    this->addaddjacentNode(v3, v2, 4); //B
    this->addaddjacentNode(v3, v4, 6); //D
    this->addaddjacentNode(v3, v5, 5); //E
    //this->addaddjacentNode(v3, v6, 6); //F

    // adjacent vertices for D
    this->addaddjacentNode(v4, v6, 3); //F

    // adjacent vertices for E
    this->addaddjacentNode(v5, v6, 7); //F


    this->dumpGraph();

    this->dijkstra(v1, v6);

}
