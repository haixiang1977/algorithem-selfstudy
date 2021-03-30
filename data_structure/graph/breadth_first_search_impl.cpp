// bread first search
// https://www.youtube.com/watch?v=9AEFRkI2SHA&list=PLWU74p77JcPbVrGkyJz8ouCb2TsbloCy6
// better performance when vertex is close to the starting vertice
// the algorithm assumes a graph g and starting vertex called startVertex
// the search first visits the startVertex (path length 0), then its adjacent vertices (path lenght 1)
// continues visit vertices with path starting from startVertex from 2, then 3 and so forth
// running time for queue handling is O(V), V is the number of vertices
// running time for search the neighbor is o(E), E is the number of edges
// totol running time = O(V) + O(E)

// g++ -g -O0 breadth_first_search_impl.cpp -o breadth_first_search_impl.out -std=c++11

// A ----x B ----x D ----x E
// |               |
// |               x
// ------x C       F
// |       |       |
// |       x       |
// ------x G x-----|

// ./breadth_first_search_impl.out
// vertex name: A
// B:1 C:1 G:1
// vertex name: B
// D:1
// vertex name: C
// G:1
// vertex name: D
// E:1 F:1
// vertex name: E
// 
// vertex name: F
// E:1 G:1
// vertex name: G
// traverse from vertex A: A B C D E F G
// traverse from vertex D: D E F G
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

    // bfs search (traverse)
    // return traversed set
    std::set<VERTEX*> bfs(VERTEX* start_v);

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

std::set<VERTEX*> GRAPH::bfs(VERTEX* start_v)
{
    std::set<VERTEX*> visited_set;
    std::queue<VERTEX*> visit_queue;

    // initialize all vertex's color to WHITE
    for (auto it = m_idx_map.begin(); it != m_idx_map.end(); it++)
    {
        VERTEX* v = it->second;
        v->set_colour(VERTEX::COLOUR::WHITE);
    }

    // initialize the queue
    visit_queue.push(start_v);

    while (!visit_queue.empty())
    {
        // pop queue
        VERTEX* v = visit_queue.front();
        visit_queue.pop();

        // this vertex has been processed
        v->set_colour(VERTEX::COLOUR::BLACK);

        // put the vertex in the visited list
        visited_set.insert(v);

        // get the neighbors
        std::set<VERTEX*> neighbor = get_neighbors(v);
        // if the neighbor not visited, push into queue
        for (auto it = neighbor.begin(); it != neighbor.end(); ++it)
        {
            VERTEX* vv = *it;
            if (vv->get_color() == VERTEX::COLOUR::WHITE)
            {
                vv->set_colour(VERTEX::COLOUR::GREY);
                visit_queue.push(vv);
            }
        }
    }

    return visited_set;
}

int main()
{
    VERTEX* v_a = new VERTEX("A", 0);
    VERTEX* v_b = new VERTEX("B", 1);
    VERTEX* v_c = new VERTEX("C", 2);
    VERTEX* v_d = new VERTEX("D", 3);
    VERTEX* v_e = new VERTEX("E", 4);
    VERTEX* v_f = new VERTEX("F", 5);
    VERTEX* v_g = new VERTEX("G", 6);

    GRAPH graph;

    graph.insert_vertex(v_a);
    graph.insert_vertex(v_b);
    graph.insert_vertex(v_c);
    graph.insert_vertex(v_d);
    graph.insert_vertex(v_e);
    graph.insert_vertex(v_f);
    graph.insert_vertex(v_g);

    graph.insert_edge(v_a, v_b);
    graph.insert_edge(v_a, v_c);
    graph.insert_edge(v_a, v_g);
    graph.insert_edge(v_b, v_d);
    graph.insert_edge(v_c, v_g);
    graph.insert_edge(v_d, v_e);
    graph.insert_edge(v_d, v_f);
    graph.insert_edge(v_f, v_e);
    graph.insert_edge(v_f, v_g);

    graph.dump();

    {
        // traverse from vertex A
        std::set<VERTEX*> s = graph.bfs(v_a);
        std::cout << "traverse from vertex A: ";
        for (auto it = s.begin(); it != s.end(); it++)
        {
            VERTEX* v = *it;
            std::cout << v->get_name() << " ";
        }
        std::cout << std::endl;
    }

    {
        // traverse from vertex D
        std::set<VERTEX*> s = graph.bfs(v_d);
        std::cout << "traverse from vertex D: ";
        for (auto it = s.begin(); it != s.end(); it++)
        {
            VERTEX* v = *it;
            std::cout << v->get_name() << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
