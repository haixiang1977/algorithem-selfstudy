// representing graph
// array is not dynamic also waste space if the space is loose
// use map to implement dynamic graph
// map<label, id>
// map<id, adjcent_list>
// adjcent_list map<dest_id, weight>
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

// g++ -g -O0 graph_map_impl.cpp -o graph_map_impl.out -std=c++11
// ./graph_vector_impl.out
// vertex label: A
// B:4 C:7
// vertex label: B
// C:2
// vertex label: C
// B:3 D:2
// vertex label: D
// 
// vertex label: E
// B:1
#include <iostream>
#include <string>
#include <map>
#include <set>

class GRAPH {
 public:
    // create an empty graph
    GRAPH();

    GRAPH(int max_num);

    virtual ~GRAPH();

    // remove all vertices and edges in the graph
    void clear();

    // return true if the graph has no vertices
    bool empty();

    // delete the edge (v(i), v(j)) from the graph
    void erase_edge(std::string v_i, std::string v_j);

    // delete the vertex
    void erase_vertex(std::string v_i);

    // return the weight of edge (v(i), v(j)) if the edge doesn't exit, return -1
    int get_weight(std::string v_i, std::string v_j);

    // return the set of vertices adjacent to v(i)
    std::set<std::string> get_neighbors(std::string v_i);

    // return the number of edges that terminate in v_i
    int get_in_degree(std::string v_i);

    // return the number of edges that originate from v_i
    int get_out_degree(std::string v_i);

    // add edge (v(i), v(j)) with the specific weight
    void insert_edge(std::string v_i, std::string v_j, int w);

    // add vertex to the set of vertices
    void insert_vertex(std::string label, int id);

    // return the number of edges in graph
    int get_num_edges();

    // return the number of vertex in graph
    int get_num_vertices();

    // update the weight of edge (v(i), v(j))
    void set_weight(std::string v_i, std::string v_j, int w);

    // dump the graph
    void dump();

 private:
    // <label, id>
    std::map<std::string, int> m_label_map;
    // <id, label>
    std::map<int, std::string> m_id_map;
    // <id, weight>>
    typedef std::map<int, int> NEIGHBOR_MAP;
    std::map<int, NEIGHBOR_MAP> m_adjcent_map;
};

GRAPH::GRAPH()
{
    ;
}

GRAPH::~GRAPH()
{
    ;
}

void GRAPH::clear()
{
    m_label_map.clear();
    m_id_map.clear();
    m_adjcent_map.clear();
    return;
}

bool GRAPH::empty()
{
    return m_label_map.empty();
}

void GRAPH::erase_edge(std::string v_i, std::string v_j)
{
    return;
}

void GRAPH::erase_vertex(std::string v_i)
{
    return;
}

int GRAPH::get_weight(std::string v_i, std::string v_j)
{
    return -1;
}

std::set<std::string> GRAPH::get_neighbors(std::string v_i)
{
    std::set<std::string> s;

    return s;
}

int GRAPH::get_in_degree(std::string v_i)
{
    return 0;
}

int GRAPH::get_out_degree(std::string v_i)
{
    return 0;
}

void GRAPH::insert_edge(std::string v_i, std::string v_j, int w)
{
    auto it = m_label_map.find(v_i);
    int v_i_id = it->second;

    it = m_label_map.find(v_j);
    int v_j_id = it->second;

    auto itt = m_adjcent_map.find(v_i_id);
    itt->second[v_j_id] = w;

    return;
}

void GRAPH::insert_vertex(std::string label, int id)
{
    m_label_map[label] = id;
    m_id_map[id] = label;
    NEIGHBOR_MAP neighbor_map;
    m_adjcent_map[id] = neighbor_map;
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

void GRAPH::set_weight(std::string v_i, std::string v_j, int w)
{
    return;
}

void GRAPH::dump()
{
    for (auto it = m_label_map.begin(); it != m_label_map.end(); it++)
    {
        std::string label = it->first;
        int id = it->second;

        std::cout << "vertex label: " << label << std::endl;
        auto itt = m_adjcent_map.find(id);
        for (auto ittt = itt->second.begin(); ittt != itt->second.end(); ittt++)
        {
            int id = ittt->first;
            int weight = ittt->second;

            auto itttt = m_id_map.find(id);
            std::string l = itttt->second;

            std::cout << l << ":" << weight << " ";
        }
        std::cout << std::endl;
    }

    return;
}

int main()
{
    GRAPH graph;
    // to be simple application will be sure the unique id for each vertex
    // insert vertex
    graph.insert_vertex("A", 0);
    graph.insert_vertex("B", 1);
    graph.insert_vertex("C", 2);
    graph.insert_vertex("D", 3);
    graph.insert_vertex("E", 4);

    // insert edge
    // A -> B
    graph.insert_edge("A", "B", 4);
    // A -> C
    graph.insert_edge("A", "C", 7);
    // B -> C
    graph.insert_edge("B", "C", 2);
    // C -> B
    graph.insert_edge("C", "B", 3);
    // C -> D
    graph.insert_edge("C", "D", 2);
    // E -> B
    graph.insert_edge("E", "B", 1);

    graph.dump();

    return 0;
}
