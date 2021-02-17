// Double-ended queues are designed to be efficient performing insertions (and removals) from either the end or the beginning
// of the sequence.
// Insertions on other positions are usually less efficient than in list or forward_list containers.
// customize linked list (efficient insert/del) + std::vector (random access)

// g++ -g -O0 deque_list_vector.cpp -o deque_list_vector.out -std=c++11
// ./deque_list_vector.out
// expected front 300, front 300
// expected front 100, front 100
// expected back 400 back 400
// expected back 200 back 200
// expected front 200, front 200
// expected at [0] 200 [0] 200
// expected at [1] 500 [1] 500

#include <iostream>
#include <vector>

using namespace std;

class ListNode
{
 public:
    int         m_val;
    ListNode*   m_next;
    ListNode*   m_pre;
};

class List
{
 public:
    List();
    virtual     ~List();

    bool        empty();
    int         front();
    ListNode*   push_front(int val);
    ListNode*   pop_front();
    int         back();
    ListNode*   push_back(int val);
    ListNode*   pop_back();

    size_t  size();

 private:
    ListNode*   m_header;
    ListNode*   m_tail;

    size_t      m_size;
};

List::List() :
    m_header(nullptr),
    m_tail(nullptr),
    m_size(0)
{
    ;
}

List::~List()
{
    ListNode* tmp = m_header;
    while (tmp)
    {
        ListNode* tmpp = tmp->m_next;
        delete tmp;
        tmp = tmpp;
    }

    m_header = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

bool List::empty()
{
    return ((m_header == nullptr) && (m_tail == nullptr));
}

int List::front()
{
    if (m_header)
    {
        return m_header->m_val;
    }
    else
    {
        cout << "empty list" << endl;
        return -1;
    }
}

ListNode* List::push_front(int val)
{
    ListNode* tmp = new ListNode();
    tmp->m_val = val;
    tmp->m_next = nullptr;
    tmp->m_pre = nullptr;

    if (m_header)
    {
        // header -> A1 -> nullptr
        // tmpp -> A1 -> nullptr
        // header -> A2
        //           -> A2 -> A1 -> nullptr
        //  nullptr <-    <-
        ListNode* tmpp = m_header;
        m_header = tmp;
        m_header->m_next = tmpp;
        tmpp->m_pre = m_header;
    }
    else
    {
        m_header = tmp;
        m_tail = tmp;
    }

    m_size++;
    return tmp;
}

ListNode* List::pop_front()
{
    ListNode* tmpp = m_header;
    if (m_header)
    {
        // header -> A2 -> A1 -> nullptr
        // tmp -> A1 -> nullptr
        // header -> A1 -> nullptr
        ListNode* tmp = m_header->m_next;
        delete m_header;
        m_header = tmp;
        if (m_header)
        {
            m_header->m_pre = nullptr;
        }
        else
        {
            m_tail = nullptr;
        }
        m_size --;
    }
    return tmpp;
}

int List::back()
{
    if (m_tail)
    {
        return m_tail->m_val;
    }
    else
    {
        cout << "empty list" << endl;
        return -1;
    }
}

ListNode* List::push_back(int val)
{
    ListNode* tmp = new ListNode();
    tmp->m_val = val;
    tmp->m_next = nullptr;
    tmp->m_pre = nullptr;

    if (m_tail)
    {
        // tail -> A1 -> nullptr
        // tmpp -> A1 -> nullptr
        // tail -> A2
        //           -> A1 -> A2 -> nullptr
        //  nullptr <-    <-
        ListNode* tmpp = m_tail;
        m_tail = tmp;
        m_tail->m_pre = tmpp;
        tmpp->m_next = m_tail;
    }
    else
    {
        m_header = tmp;
        m_tail = tmp;
    }

    m_size ++;
    return tmp;
}

ListNode* List::pop_back()
{
    ListNode* tmpp = m_header;
    if (m_tail)
    {
        // tail -> A2 -> A1 -> nullptr
        // tmp -> A1 -> nullptr
        // header -> A1 -> nullptr
        ListNode* tmp = m_tail->m_pre;
        delete m_tail;
        m_tail = tmp;
        if (m_tail)
        {
            m_tail->m_next = nullptr;
        }
        else
        {
            m_header = nullptr;
        }
    }

    m_size --;
    return tmpp;
}

class Deque
{
 public:
    Deque();
    virtual ~Deque();

    void    push_front(int val);
    void    pop_front();
    void    push_back(int val);
    void    pop_back();
    int     front();
    int     back();
    int     at(int idx);

 private:
    std::vector<ListNode*>  m_vector; // to store the list node address
    List                    m_list;   // to store the list node
};

Deque::Deque()
{
}

Deque::~Deque()
{
}

void Deque::push_front(int val)
{
    ListNode* node = m_list.push_front(val);

    // insert the list node address at vector[0]
    std::vector<ListNode*>::iterator it = m_vector.begin();
    m_vector.insert(it, node);

    return;
}

void Deque::pop_front()
{
    ListNode* node = m_list.pop_front();

    // erase the list node address at vector[0]
    std::vector<ListNode*>::iterator it = m_vector.begin();
    m_vector.erase(it);

    return;
}

void Deque::push_back(int val)
{
    ListNode* node = m_list.push_back(val);

    // push the list node address at the end
    m_vector.push_back(node);

    return;
}

void Deque::pop_back()
{
    ListNode* node = m_list.pop_back();

    // remove the last list node address at vector
    m_vector.pop_back();

    return;
}

int Deque::front()
{
    return m_list.front();
}

int Deque::back()
{
    return m_list.back();
}

int Deque::at(int idx)
{
    ListNode* node = m_vector[idx];

    return node->m_val;
}

int main()
{
    Deque my_queue;

    my_queue.push_back(100);
    my_queue.push_back(200);
    my_queue.push_front(300); // 300 100 200

    cout << "expected front 300, front " << my_queue.front() << endl;
    my_queue.pop_front(); // 100 200
    cout << "expected front 100, front " << my_queue.front() << endl;
    my_queue.pop_front(); // 200

    my_queue.push_back(400); // 200 400
    cout << "expected back 400 back " << my_queue.back() << endl;

    my_queue.pop_back(); // 200
    cout << "expected back 200 back " << my_queue.back() << endl;
    cout << "expected front 200, front " << my_queue.front() << endl;

    my_queue.push_back(500); // 200 500
    cout << "expected at [0] 200 [0] " << my_queue.at(0) << endl;
    cout << "expected at [1] 500 [1] " << my_queue.at(1) << endl;
}

