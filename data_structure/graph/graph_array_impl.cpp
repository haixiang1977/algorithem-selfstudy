// representing graph
// a simple technique stores the vertices as a list: v(0), v(1), v(2), ... v(n-1).
// An m-by-m matrix, called an adjacency matrix, identifies the edges. An entry in
// row i and column j coresponds to the edge e = (v(i), v(j)). It's value is the
// weight of the edge, or -1 if the edge doesn't exist
// for example
// A -----x B x --- E
// |        x
// |        |
// x        |
// C x-------
// |
// x
// D
// resprent as non-weighted array
//    A  B  C  D  E
// A  -1 1  1  -1 -1
// B  -1 -1 1  -1 -1
// C  -1 1  -1 1  -1
// D  -1 -1 -1 -1 -1
// E  -1 1  -1 -1 -1

// represent as weighted array
//    A  B  C  D  E
// A  -1 4  7  -1 -1
// B  -1 -1 2  -1 -1
// C  -1 3  -1 2  -1
// D  -1 -1 -1 -1 -1
// E  -1 1  -1 -1 -1

// g++ -g -O0 graph_array_impl.cpp -o graph_array_impl.out -std=c++11

#include <iostream>
#include <string>
#include <set>
#include <map>

class GRAPH {
 public:
    // create an empty graph
    GRAPH();

    // create graph with maximum number of vertices, in this example, it is 5.
    GRAPH(int n);

    virtual ~GRAPH();

    // remove all vertices and edges in the graph
    void clear();

    // return true if the graph has no vertices
    bool empty();

    // delete the edge (v(i), v(j)) from the graph
    void erase_edge(int v_i, int v_j);

    // delete the vertex
    void erase_vertex(int v_i);

    // return the weight of edge (v(i), v(j)) if the edge doesn't exit, return -1
    int get_weight(int v_i, int v_j);

    // return the set of vertices adjacent to v(i)
    std::set<int> get_neighbors(int v_i);

    // return the number of edges that terminate in v_i
    int get_in_degree(int v_i);

    // return the number of edges that originate from v_i
    int get_out_degree(int v_i);

    // add edge (v(i), v(j)) with the specific weight
    void insert_edge(int v_i, int v_j, int w);

    // add vertex to the set of vertices
    void insert_vertex(std::string label, int v_i);

    // return the number of edges in graph
    int get_num_edges();

    // return the number of vertex in graph
    int get_num_vertices();

    // update the weight of edge (v(i), v(j))
    void set_weight(int v_i, int v_j, int w);

    // dump the graph
    void dump();

 private:
    std::map<std::string, int> graph_lable_map;

    int**   m_array;        // point to 2D array
    int     m_size;         // size of the array
};

GRAPH::GRAPH()
{
    m_array = nullptr;
}

GRAPH::GRAPH(int n)
{
    m_array = new int*[n];
    m_size = n;

    for (int i = 0; i < m_size; i++)
    {
        int* p = m_array[i];

        p = new int[m_size];
    }

    // fill initialize value -1
    for (int i = 0; i < m_size; i++)
    {
        int* p = m_array[i];

        for (int j = 0; j < m_size; j++)
        {
            p[j] = -1;
        }
    }

    dump();
}

GRAPH::~GRAPH()
{
    clear();

    for (int i = 0; i < m_size; i++)
    {
        int* p = m_array[i];

        delete[] p;
    }

    delete[] m_array;
}

void GRAPH::clear()
{
    // fill initialize value -1
    for (int i = 0; i < m_size; i++)
    {
        int* p = m_array[i];

        for (int j = 0; j < m_size; j++)
        {
            p[j] = -1;
        }
    }

    graph_lable_map.clear();
}

bool GRAPH::empty()
{
    return graph_lable_map.empty();
}

void GRAPH::erase_edge(int v_i, int v_j)
{
    return;
}

void GRAPH::erase_vertex(int v_i)
{
    return;
}

int GRAPH::get_weight(int v_i, int v_j)
{
    return -1;
}

std::set<int> GRAPH::get_neighbors(int v_i)
{
    std::set<int> s;

    return s;
}

int GRAPH::get_in_degree(int v_i)
{
    return 0;
}

int GRAPH::get_out_degree(int v_i)
{
    return 0;
}

void GRAPH::insert_edge(int v_i, int v_j, int w)
{
    return;
}

void GRAPH::insert_vertex(std::string label, int v_i)
{
    return;
}

int GRAPH::get_num_edges()
{
    return 0;
}

int GRAPH::get_num_vertices()
{
    return 0;
}

void GRAPH::set_weight(int v_i, int v_j, int w)
{
    return;
}

void GRAPH::dump()
{
    for (auto it = graph_lable_map.begin(); it != graph_lable_map.end(); ++it)
    {
        std::cout << "label: " << it->first << " id: " << it->second << std::endl;
    }

    for (int i = 0; i < m_size; i++)
    {
        int* p = m_array[i];

        for (int j = 0; j < m_size; j++)
        {
            std::cout << p[j] << " ";
        }
        std::cout << std::endl;
    }

    return;
}

int main()
{
    return 0;
}
