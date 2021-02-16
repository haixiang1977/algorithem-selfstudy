// header -> nullptr
// header -> A1 -> nullptr push_front(A1)
// header -> A2 -> A1 -> nullptr push_front(A2)
// header -> A3 -> A2 -> A1 -> nullptr push_front(A3)

// g++ -g -O0 list_forward_impl.cpp -o list_forward_impl.out -std=c++11
// valgrind --leak-check=full ./list_forward_impl.out
// ./list_forward_impl.out
// expected front 200, front 200
// expected front 100, front 100
// expected front 300, front 300
// expected 100 front 100
// expected empty 1 empty 

#include <iostream>

using namespace std;

class ListNode
{
 public:
    int         m_val;
    ListNode*   m_next;
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

 private:
    ListNode*   m_header;
};

List::List() :
    m_header(nullptr)
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
}

bool List::empty()
{
    return (m_header == nullptr);
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

    if (m_header)
    {
        // header -> A1 -> nullptr
        // tmpp -> A1 -> nullptr
        // header -> A2
        // header -> A2 -> A1 -> nullptr
        ListNode* tmpp = m_header;
        m_header = tmp;
        m_header->m_next = tmpp;
    }
    else
    {
        // header -> nullptr
        // header -> A1 -> nullptr
        m_header = tmp;
    }
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
    }
}

int main()
{
    List my_list;

    my_list.push_front(100);
    my_list.push_front(200);

    cout << "expected front 200, front " << my_list.front() << endl;

    my_list.pop_front();
    cout << "expected front 100, front " << my_list.front() << endl;

    my_list.push_front(300);
    cout << "expected front 300, front " << my_list.front() << endl;

    my_list.pop_front();
    cout << "expected 100 front " << my_list.front() << endl;

    my_list.pop_front();
    cout << "expected empty 1 empty " << my_list.empty() << endl;

    // test destructor
    my_list.push_front(400);
    my_list.push_front(500);

    return 0;
}
