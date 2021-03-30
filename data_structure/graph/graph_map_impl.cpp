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
// ./graph_map_impl.out
// number of vertex 5
// number of edges 6
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
// neighbor of C: A B D
// erase edge from C to B
// vertex label: A
// B:4 C:7
// vertex label: B
// C:2
// vertex label: C
// D:2
// vertex label: D
// 
// vertex label: E
// B:1
// weight from A to C 7
// weight from A to C 9
// in degree of C 2
// out degree of C 1
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
    auto it = m_label_map.find(v_i);
    int v_i_id = it->second;

    it = m_label_map.find(v_j);
    int v_j_id = it->second;

    auto itt = m_adjcent_map.find(v_i_id);
    auto ittt = itt->second.find(v_j_id);
    itt->second.erase(ittt);

    return;
}

void GRAPH::erase_vertex(std::string v_i)
{
    auto it = m_label_map.find(v_i);
    int v_i_id = it->second;

    auto itt = m_adjcent_map.find(v_i_id);
    m_adjcent_map.erase(itt);

    for (auto ittt = m_adjcent_map.begin(); ittt != m_adjcent_map.end(); ++ittt)
    {
        auto itttt = ittt->second.find(v_i_id);
        if (itttt != ittt->second.end())
        {
            ittt->second.erase(itttt);
        }
    }
    return;
}

int GRAPH::get_weight(std::string v_i, std::string v_j)
{
    int w = -1;

    auto it = m_label_map.find(v_i);
    int v_i_id = it->second;

    it = m_label_map.find(v_j);
    int v_j_id = it->second;

    auto itt = m_adjcent_map.find(v_i_id);
    auto ittt = itt->second.find(v_j_id);

    w = ittt->second;

    return w;
}

std::set<std::string> GRAPH::get_neighbors(std::string v_i)
{
    std::set<std::string> s;

    auto it = m_label_map.find(v_i);
    int v_i_id = it->second;

    auto itt = m_adjcent_map.find(v_i_id);
    for (auto ittt = itt->second.begin(); ittt != itt->second.end(); ++ittt)
    {
        int v_j_d = ittt->first;
        auto itttt = m_id_map.find(v_j_d);
        s.insert(itttt->second);
    }

    for (auto ittt = m_adjcent_map.begin(); ittt != m_adjcent_map.end(); ++ittt)
    {
        if (ittt->first != v_i_id)
        {
            auto itttt = ittt->second.find(v_i_id);
            if (itttt != ittt->second.end())
            {
                int v_j_d = ittt->first;
                auto ittttt = m_id_map.find(v_j_d);
                s.insert(ittttt->second);
            }
        }
    }

    return s;
}

int GRAPH::get_in_degree(std::string v_i)
{
    int cnt = 0;
    auto it = m_label_map.find(v_i);
    int v_i_id = it->second;

    for (auto itt = m_adjcent_map.begin(); itt != m_adjcent_map.end(); ++itt)
    {
        if (itt->first != v_i_id)
        {
            auto ittt = itt->second.find(v_i_id);
            if (ittt != itt->second.end())
            {
                cnt ++;
            }
        }
    }

    return cnt;
}

int GRAPH::get_out_degree(std::string v_i)
{
    auto it = m_label_map.find(v_i);
    int v_i_id = it->second;

    auto itt = m_adjcent_map.find(v_i_id);
    return itt->second.size();
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
    int size = 0;
    for (auto it = m_adjcent_map.begin(); it != m_adjcent_map.end(); ++it)
    {
        size += it->second.size();
    }
    return size;
}

int GRAPH::get_num_vertices()
{
    return m_label_map.size();
}

void GRAPH::set_weight(std::string v_i, std::string v_j, int w)
{
    auto it = m_label_map.find(v_i);
    int v_i_id = it->second;

    it = m_label_map.find(v_j);
    int v_j_id = it->second;

    auto itt = m_adjcent_map.find(v_i_id);
    auto ittt = itt->second.find(v_j_id);

    ittt->second = w;

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
    // get number of edges and vertex
    std::cout << "number of vertex " << graph.get_num_vertices() << std::endl;
    std::cout << "number of edges " << graph.get_num_edges() << std::endl;
    graph.dump();

    // get neighbours of "C"
    std::set<std::string> s = graph.get_neighbors("C");
    std::cout << "neighbor of C: ";
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // erase edge from C -> B
    std::cout << "erase edge from C to B" << std::endl;
    graph.erase_edge("C", "B");
    graph.dump();

    // get weight A -> C
    std::cout << "weight from A to C " << graph.get_weight("A", "C") << std::endl;
    // set weight A -> C to 9
    graph.set_weight("A", "C", 9);
    std::cout << "weight from A to C " << graph.get_weight("A", "C") << std::endl;

    // get vertex C in degree and out degree
    std::cout << "in degree of C " << graph.get_in_degree("C") << std::endl;
    std::cout << "out degree of C " << graph.get_out_degree("C") << std::endl;

    return 0;
}
