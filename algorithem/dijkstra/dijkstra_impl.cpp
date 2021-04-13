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
#include <functional>

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

class VERTEXINFO
{
 public:
    VERTEXINFO() :
        m_parent_id(-1), m_min_weight(0)
        {}
    VERTEXINFO(int id, int val) :
        m_parent_id(id), m_min_weight(val)
        {}
    virtual ~VERTEXINFO() {}

    int get_parent_id() const { return m_parent_id; }
    int get_min_weight() const { return m_min_weight; }

    void set_min_weight(int weight) { m_min_weight = weight; }
    void set_parent_id(int id) { m_parent_id = id; }

 private:
    int m_parent_id;
    int m_min_weight;
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

    int get_edge_weight(VERTEX* v_i, VERTEX* v_j);

    // dump the graph
    void dump();

    // mimimum path
    // return the weight of minimum path and the list of vertex
    int minimum_path(VERTEX* v_start, VERTEX* v_end, std::vector<VERTEXINFO>& path);

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

int GRAPH::get_edge_weight(VERTEX* v_i, VERTEX* v_j)
{
    int v_i_idx = v_i->get_idx();
    int v_j_idx = v_j->get_idx();

    auto it = m_adjcent_map.find(v_i_idx);

    return it->second[v_j_idx];
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

class MINPATH
{
 public:
    MINPATH() {}
    MINPATH (int v_end, int weight) :
        m_end_idx(v_end), m_weight(weight)
    {}
    virtual ~MINPATH() {}

    int get_end_idx() const { return m_end_idx; }
    int get_weight() const { return m_weight; }

    void set_end_idx(int v_end) { m_end_idx = v_end; }
    void set_weight (int weight) { m_weight = weight; }

    friend bool operator < (const MINPATH& lhs, const MINPATH& rhs)
    {
        return lhs.get_weight() < rhs.get_weight();
    }

    friend bool operator > (const MINPATH& lhs, const MINPATH& rhs)
    {
        return lhs.get_weight() > rhs.get_weight();
    }

 private:
    int m_end_idx;
    int m_weight;
};

int GRAPH::minimum_path(VERTEX* v_start, VERTEX* v_end, std::vector<VERTEXINFO>& path)
{
    int ret = -1;
    bool is_found = false;

    std::priority_queue<MINPATH,std::vector<MINPATH>> min_path_queue;

    for (auto it = m_label_map.begin(); it != m_label_map.end(); it++)
    {
        // initialize all the vertex is white color
        VERTEX* v = it->second;
        v->set_colour(VERTEX::COLOUR::WHITE);
        // initialize the path list
        VERTEXINFO v_info;
        path.push_back(v_info);
    }

    // push start vertex into priority queue and weight = 0 since self
    int v_start_idx = v_start->get_idx();
    MINPATH min_path(v_start_idx, 0);
    min_path_queue.push(min_path);

    int v_end_idx = v_end->get_idx();

    while (!min_path_queue.empty())
    {
        min_path = min_path_queue.top();
        min_path_queue.pop();

        int v_cur_idx = min_path.get_end_idx();
        if (v_cur_idx == v_end_idx)
        {
            is_found = true;
            break;
        }

        auto it = m_idx_map.find(v_cur_idx);
        VERTEX* v = it->second;
        if (v->get_color() != VERTEX::COLOUR::BLACK)
        {
            v->set_colour(VERTEX::COLOUR::BLACK);
            // get adjcent neighbors
            std::set<VERTEX*> neigbor = get_neighbors(v);
            for (auto it = neigbor.begin(); it != neigbor.end(); it++)
            {
                VERTEX* n = *it;
                int n_idx = n->get_idx();
                if (n->get_color() == VERTEX::COLOUR::WHITE)
                {
                    int new_weight = path[v_cur_idx].get_min_weight() + get_edge_weight(v, n);
                    if (new_weight < path[n_idx].get_min_weight())
                    {
                        path[n_idx].set_min_weight(new_weight);
                        path[n_idx].set_parent_id(v_cur_idx);
                        MINPATH m_path(n_idx, new_weight);
                        min_path_queue.push(m_path);
                    }
                }
                else
                {
                    // already visited and can not be less
                    // so skip here
                }
            }
        }
    }

    if (is_found)
    {
        ret = path[v_end_idx].get_min_weight();
    }
    else
    {
        std::cout << "path not found" << std::endl;
    }

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
    std::vector<VERTEXINFO> path_vector;
    min_weight = graph.minimum_path(v_f, v_c, path_vector);
    std::cout << "minmum path weight from VERTEX F to VERTEX C " << min_weight << std::endl;
    std::cout << "path vertex sequence ";
    for (int i = 0; i < path_vector.size(); i++)
    {
        std::cout << path_vector[i].get_parent_id() << " ";
    }
    std::cout << std::endl;

    return 0;
}
