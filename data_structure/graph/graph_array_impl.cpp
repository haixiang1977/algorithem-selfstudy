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

// ./graph_array_impl.out
// GRAPH::dump ====
// -1 -1 -1 -1 -1
// -1 -1 -1 -1 -1
// -1 -1 -1 -1 -1
// -1 -1 -1 -1 -1
// -1 -1 -1 -1 -1
// GRAPH::dump ====
// label: A id: 0
// label: B id: 1
// label: C id: 2
// label: D id: 3
// label: E id: 4
// -1 4 7 -1 -1
// -1 -1 2 -1 -1
// -1 3 -1 2 -1
// -1 -1 -1 -1 -1
// -1 1 -1 -1 -1
// number of vertex 5
// number of edges 6
// vertex B's neighbor:
//  A C E
// vertex C's neighbor:
//  A B D
// number of C vertex in degree 2
// number of C vertex out degree 2
// weight from B to C 2
// weight from B to C 10

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

    // get the label
    std::string get_label(int v_i);

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
        m_array[i] = new int[m_size];
    }

    // fill initialize value -1
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            m_array[i][j] = -1;
        }
    }

    dump();
}

GRAPH::~GRAPH()
{
    clear();

    for (int i = 0; i < m_size; i++)
    {
        delete[] m_array[i];
    }

    delete[] m_array;
}

void GRAPH::clear()
{
    // fill initialize value -1
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            m_array[i][j] = -1;
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
    m_array[v_i][v_j] = -1;
    return;
}

void GRAPH::erase_vertex(int v_i)
{
    for (int i = 0; i < m_size; i++)
    {
        m_array[i][v_i] = -1;
        m_array[v_i][i] = -1;
    }

    for (auto it = graph_lable_map.begin(); it != graph_lable_map.end(); ++it)
    {
        if (it->second == v_i)
        {
            graph_lable_map.erase(it);
            break;
        }
    }

    return;
}

int GRAPH::get_weight(int v_i, int v_j)
{
    return m_array[v_i][v_j];
}

std::set<int> GRAPH::get_neighbors(int v_i)
{
    std::set<int> s;

    for (int i = 0; i < m_size; i++)
    {
        // check the source
        if (m_array[i][v_i] != -1)
        {
            s.insert(i);
        }
        // check the destination
        if (m_array[v_i][i] != -1)
        {
            s.insert(i);
        }
    }

    return s;
}

int GRAPH::get_in_degree(int v_i)
{
    int cnt = 0;
    for (int i = 0; i < m_size; i++)
    {
        // check the source
        if (m_array[i][v_i] != -1)
        {
            cnt++;
        }
    }
    return cnt;
}

int GRAPH::get_out_degree(int v_i)
{
    int cnt = 0;
    for (int i = 0; i < m_size; i++)
    {
        // check the source
        if (m_array[v_i][i] != -1)
        {
            cnt++;
        }
    }
    return cnt;
}

void GRAPH::insert_edge(int v_i, int v_j, int w)
{
    m_array[v_i][v_j] = w;

    return;
}

void GRAPH::insert_vertex(std::string label, int v_i)
{
    graph_lable_map[label] = v_i;

    return;
}

int GRAPH::get_num_edges()
{
    int cnt = 0;
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            if (m_array[i][j] != -1)
            {
                cnt ++;
            }
        }
    }

    return cnt;
}

int GRAPH::get_num_vertices()
{   
    return graph_lable_map.size();
}

void GRAPH::set_weight(int v_i, int v_j, int w)
{
    m_array[v_i][v_j] = w;
    return;
}

std::string GRAPH::get_label(int v_i)
{
    for (auto it = graph_lable_map.begin(); it != graph_lable_map.end(); ++it)
    {
        if (it->second == v_i)
        {
            return it->first;
        }
    }

    return std::string("Unknown");
}

void GRAPH::dump()
{
    std::cout << "GRAPH::dump ====" << std::endl;

    for (auto it = graph_lable_map.begin(); it != graph_lable_map.end(); ++it)
    {
        std::cout << "label: " << it->first << " id: " << it->second << std::endl;
    }

    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            std::cout << m_array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return;
}

int main()
{
    GRAPH graph(5);

    // insert vertex
    graph.insert_vertex("A", 0);
    graph.insert_vertex("B", 1);
    graph.insert_vertex("C", 2);
    graph.insert_vertex("D", 3);
    graph.insert_vertex("E", 4);

    // insert edge
    // A -> B
    graph.insert_edge(0, 1, 4);
    // A -> C
    graph.insert_edge(0, 2, 7);
    // B -> C
    graph.insert_edge(1, 2, 2);
    // C -> B
    graph.insert_edge(2, 1, 3);
    // C -> D
    graph.insert_edge(2, 3, 2);
    // E -> B
    graph.insert_edge(4, 1, 1);

    graph.dump();

    // get number of vertex
    std::cout << "number of vertex " << graph.get_num_vertices() << std::endl;
    // get number of edges
    std::cout << "number of edges " << graph.get_num_edges() << std::endl;

    // get B's neigbor
    // neighbor is the vertices which has edge connected regardless in or out
    std::set<int> s = graph.get_neighbors(1);
    std::cout << "vertex B's neighbor: " << std::endl;
    for (auto it = s.begin(); it != s.end(); it++)
    {
        std::cout << " " << graph.get_label(*it);
    }
    std::cout << std::endl;

    // get C's neigbhor
    s = graph.get_neighbors(2);
    std::cout << "vertex C's neighbor: " << std::endl;
    for (auto it = s.begin(); it != s.end(); it++)
    {
        std::cout << " " << graph.get_label(*it);
    }
    std::cout << std::endl;

    // get number of C's in degree
    std::cout << "number of C vertex in degree " << graph.get_in_degree(2) << std::endl;
    
    // get number of C's out degree
    std::cout << "number of C vertex out degree " << graph.get_out_degree(2) << std::endl;

    // get weight from B to C
    std::cout << "weight from B to C " << graph.get_weight(1, 2) << std::endl;
    // set weight from B to C
    graph.set_weight(1, 2, 10);
    std::cout << "weight from B to C " << graph.get_weight(1, 2) << std::endl;

    return 0;
}
