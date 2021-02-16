// implement the double-linked list
//          -> A2 -> A1 -> nullptr
// nullptr <-    <-

// g++ -g -O0 list_impl.cpp -o list_impl.out -std=c++11
// valgrind --leak-check=full ./list_impl.out
// ./list_impl.out
// expected front 200 front 200
// expected back 400 back 400
// expected front 100 front 100
// expected back 300 back 300
// size 2
// size 0
// expected empty 1 empty 1

#include <iostream>

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
    virtual ~List();

    bool    empty();
    int     front();
    void    push_front(int val);
    void    pop_front();
    int     back();
    void    push_back(int val);
    void    pop_back();

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

void List::push_front(int val)
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
}

void List::pop_front()
{
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

void List::push_back(int val)
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
}

void List::pop_back()
{
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
}

size_t List::size()
{
    return m_size;
}

int main()
{
    List my_list;

    my_list.push_front(100);
    my_list.push_front(200);

    my_list.push_back(300);
    my_list.push_back(400);

    cout << "expected front 200 front " << my_list.front() << endl;
    cout << "expected back 400 back " << my_list.back() << endl;

    // pop front
    my_list.pop_front();
    cout << "expected front 100 front " << my_list.front() << endl;

    // pop back
    my_list.pop_back();
    cout << "expected back 300 back " << my_list.back() << endl;

    // size
    cout << "size " << my_list.size() << endl;

    // test empty list
    my_list.pop_front();
    my_list.pop_back();
    cout << "size " << my_list.size() << endl;
    cout << "expected empty 1 empty " << my_list.empty() << endl;

    // test de-constructor
    my_list.push_front(500);
    my_list.push_front(600);

    return 0;
}
