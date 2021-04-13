// g++ -g -O0 dijkstra_impl.cpp -o dijkstra_impl.out -std=c++11

// ./dijkstra_impl.out
// vertex name: A
// B:4 C:11 E:4
// vertex name: B
// A:2 C:6 D:8
// vertex name: C
// B:6 D:14
// vertex name: D
// A:12 E:4
// vertex name: E
// D:10
// vertex name: F
// D:20 E:6
// minmum path weight from VERTEX F to VERTEX C -1
// path vertex sequence

#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <list>

class VERTEX
{
 public:
    enum COLOUR
    {
        WHITE, // not visited
        BLACK  // processed
    };

    VERTEX() {}

    VERTEX(std::string name, int idx) :
        m_name(name), m_idx(idx), m_colour(VERTEX::COLOUR::WHITE)
    {
    }

    virtual ~VERTEX() {}

    std::string get_name() { return m_name; }

    int get_idx() { return m_idx; }

    VERTEX::COLOUR get_color() { return m_colour; }

    void set_colour(VERTEX::COLOUR colour) { m_colour = colour; }

 private:
    std::string m_name;
    int m_idx;
    VERTEX::COLOUR m_colour;
};

class GRAPH
{
 public:
    GRAPH();

    virtual ~GRAPH();

    // add vertex to the set of vertices
    void insert_vertex(VERTEX* v);

    // add edge (v(i), v(j)) with weight
    void insert_edge(VERTEX* v_i, VERTEX* v_j, int weight);

    // get neighour set
    std::set<VERTEX*> get_neighbors(VERTEX* v);

    // dump the graph
    void dump();

    // mimimum path
    // return the weight of minimum path and the list of vertex
    int minimum_path(VERTEX* v_start, VERTEX* v_end, std::list<VERTEX*>& path);

 private:
    // <label, VERTEX*>
    std::map<std::string, VERTEX*> m_label_map;

    // <idx, VERTEX*>
    std::map<int, VERTEX*> m_idx_map;

    // adjacent map
    // <idx, weight>
    typedef std::map<int, int> ADJCENT_MAP;
    std::map<int, ADJCENT_MAP> m_adjcent_map;
};

GRAPH::GRAPH()
{
}

GRAPH::~GRAPH()
{
}

void GRAPH::insert_vertex(VERTEX* v)
{
    m_label_map[v->get_name()] = v;
    m_idx_map[v->get_idx()] = v;
    ADJCENT_MAP adj_map;
    m_adjcent_map[v->get_idx()] = adj_map;

    return;
}

void GRAPH::insert_edge(VERTEX* v_i, VERTEX* v_j, int weight)
{
    int v_i_idx = v_i->get_idx();
    int v_j_idx = v_j->get_idx();

    auto it = m_adjcent_map.find(v_i_idx);
    it->second[v_j_idx] = weight;

    return;
}

std::set<VERTEX*> GRAPH::get_neighbors(VERTEX* v)
{
    std::set<VERTEX*> s;

    int v_i_idx = v->get_idx();

    {
        // search destination neighbor
        auto it = m_adjcent_map.find(v_i_idx);
        for (auto itt = it->second.begin(); itt != it->second.end(); ++itt)
        {
            int v_j_idx = itt->first;
            auto ittt = m_idx_map.find(v_j_idx);
            s.insert(ittt->second);
        }
    }

    {
        // search source neighbor
        for (auto it = m_adjcent_map.begin(); it != m_adjcent_map.end(); ++it)
        {
            if (it->first != v_i_idx)
            {
                auto itt = it->second.find(v_i_idx);
                if (itt != it->second.end())
                {
                    int v_j_idx = itt->first;
                    auto ittt = m_idx_map.find(v_j_idx);
                    s.insert(ittt->second);
                }
            }
        }
    }

    return s;
}

void GRAPH::dump()
{
    for (auto it = m_label_map.begin(); it != m_label_map.end(); it++)
    {
        std::string name = it->first;
        VERTEX* v = it->second;
        int id = v->get_idx();

        std::cout << "vertex name: " << name << std::endl;
        auto itt = m_adjcent_map.find(id);
        for (auto ittt = itt->second.begin(); ittt != itt->second.end(); ittt++)
        {
            int id = ittt->first;
            int weight = ittt->second;

            auto itttt = m_idx_map.find(id);
            VERTEX* v = itttt->second;
            std::string n = v->get_name();

            std::cout << n << ":" << weight << " ";
        }
        std::cout << std::endl;
    }

    return;
}

int GRAPH::minimum_path(VERTEX* v_start, VERTEX* v_end, std::list<VERTEX*>& path)
{
    int ret = -1;
    return ret;
}

int main()
{
    VERTEX* v_a = new VERTEX("A", 0);
    VERTEX* v_b = new VERTEX("B", 1);
    VERTEX* v_c = new VERTEX("C", 2);
    VERTEX* v_d = new VERTEX("D", 3);
    VERTEX* v_e = new VERTEX("E", 4);
    VERTEX* v_f = new VERTEX("F", 5);

    GRAPH graph;

    graph.insert_vertex(v_a);
    graph.insert_vertex(v_b);
    graph.insert_vertex(v_c);
    graph.insert_vertex(v_d);
    graph.insert_vertex(v_e);
    graph.insert_vertex(v_f);

    graph.insert_edge(v_a, v_b, 4);
    graph.insert_edge(v_a, v_c, 11);
    graph.insert_edge(v_a, v_e, 4);
    graph.insert_edge(v_b, v_a, 2);
    graph.insert_edge(v_b, v_c, 6);
    graph.insert_edge(v_b, v_d, 8);
    graph.insert_edge(v_c, v_b, 6);
    graph.insert_edge(v_c, v_d, 14);
    graph.insert_edge(v_d, v_a, 12);
    graph.insert_edge(v_d, v_e, 4);
    graph.insert_edge(v_e, v_d, 10);
    graph.insert_edge(v_f, v_d, 20);
    graph.insert_edge(v_f, v_e, 6);

    graph.dump();

    int min_weight = -1;
    std::list<VERTEX*> path_list;
    min_weight = graph.minimum_path(v_f, v_c, path_list);
    std::cout << "minmum path weight from VERTEX F to VERTEX C " << min_weight << std::endl;
    std::cout << "path vertex sequence ";
    for (std::list<VERTEX*>::iterator it = path_list.begin(); it != path_list.end(); it++)
    {
        VERTEX* v = *it;
        std::cout << v->get_name() << " ";
    }
    std::cout << std::endl;

    return 0;
}
