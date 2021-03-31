// depth first search
// https://www.youtube.com/watch?v=9AEFRkI2SHA&list=PLWU74p77JcPbVrGkyJz8ouCb2TsbloCy6
// better performance when vertex is deep
// the algorithm assumes a graph g and starting vertex called startVertex
// the search first visits the startVertex (path length 0), follows paths of adjacent vertices
// until it reaches a vertex that has no neighbors or only neighbors that have already been visited
// visits to the vertex occur via backtracing.
// the step takes the color of gray when this vertex is first visited
// continue to look at the neighbor undiscovered whose color is white
// the color will ultimately reach the end of path where the vertex has no white
// as part of each visit the vertex is colored as black
// the color of vertex in the depth first visit allows us to recogonize the presence of a cycle
// if we are currently at vertex v and a neighbor vertex w has color grey, we say that (v, w) is
// a back edge. A back edge indicates a cycle

// g++ -g -O0 depth_first_search_impl.cpp -o depth_first_search_impl.out -std=c++11
// A --- x B --- x D
// |       x       |
// x       |       x
// C       |------ E
// x               |
// |               |
// F x ------------|

// ./depth_first_search_impl.out
// vertex name: A
// B:1 C:1
// vertex name: B
// D:1
// vertex name: C
// 
// vertex name: D
// E:1
// vertex name: E
// B:1 F:1
// vertex name: F
// C:1
// is cyclic

// comment edge E->B to make acyclic 
// is acyclic

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <queue>

class VERTEX
{
 public:
    enum COLOUR
    {
        WHITE, // not visited
        GREY,  // to process
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

    // add edge (v(i), v(j)) and assume weight = 1
    void insert_edge(VERTEX* v_i, VERTEX* v_j);

    // get neighour set
    std::set<VERTEX*> get_neighbors(VERTEX* v);

    // dump the graph
    void dump();

    // dfs search (traverse)
    // return traversed set
    void dfs(VERTEX* start_v, bool* is_cyclic);

    // dfs search all vertexes
    void dfs_visit();

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

void GRAPH::insert_edge(VERTEX* v_i, VERTEX* v_j)
{
    int v_i_idx = v_i->get_idx();
    int v_j_idx = v_j->get_idx();

    auto it = m_adjcent_map.find(v_i_idx);
    it->second[v_j_idx] = 1;

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

void GRAPH::dfs(VERTEX* start_v, bool* is_cyclic)
{
    std::set<VERTEX*> visited_set;

    // set start vertex to color grey
    start_v->set_colour(VERTEX::COLOUR::GREY);

    // check adjacent neigbor
    auto it = m_adjcent_map.find(start_v->get_idx());
    for (auto itt = it->second.begin(); itt != it->second.end(); itt++)
    {
        int v_j_idx = itt->first;
        auto ittt = m_idx_map.find(v_j_idx);
        VERTEX* v = ittt->second;

        if (v->get_color() == VERTEX::COLOUR::WHITE)
        {
            dfs(v, is_cyclic);
        }
        else if (v->get_color() == VERTEX::COLOUR::GREY)
        {
            *is_cyclic = true;
            return;
        }
        else
        {
            // black which already visited, then skip and do nothing
        }
    }

    // all neighbors have been processed
    // set color to black and push into set
    start_v->set_colour(VERTEX::COLOUR::BLACK);

    return;
}

void GRAPH::dfs_visit()
{
    bool is_cyclic = false;

    // initialize all color to WHITE
    for (auto it = m_label_map.begin(); it != m_label_map.end(); it++)
    {
        VERTEX* v = it->second;
        v->set_colour(VERTEX::COLOUR::WHITE);
    }

    for (auto it = m_label_map.begin(); it != m_label_map.end(); it++)
    {
        VERTEX* v = it->second;
        if (v->get_color() == VERTEX::COLOUR::WHITE)
        {
            dfs(v, &is_cyclic);
            if (is_cyclic)
            {
                break;
            }
        }
    }

    if (is_cyclic)
    {
        std::cout << "is cyclic" << std::endl;
    }
    else
    {
        std::cout << "is acyclic" << std::endl;
    }
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

    graph.insert_edge(v_a, v_b);
    graph.insert_edge(v_a, v_c);
    graph.insert_edge(v_b, v_d);
    graph.insert_edge(v_d, v_e);
    graph.insert_edge(v_e, v_f);
    graph.insert_edge(v_e, v_b);
    graph.insert_edge(v_f, v_c);

    graph.dump();

    graph.dfs_visit();

    return 0;
}
