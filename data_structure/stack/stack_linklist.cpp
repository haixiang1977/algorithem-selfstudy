// use linklist to implement stack
// public api:
// empty() - test stack is empty
// size() - return size
// top() - access next element
// push() - insert element
// pop() - remove top element

// advantage of linklist to array is that it can dynamically change

// g++ stack_linklist.cpp -o stack_linklist.out
// ./stack_linklist.out
// 3 6 7 5 3 5 6 2 9 1
// stack size 10
// 1 9 2 6 5 3 5 7 6 3
// stack empty 1

#include <cstdlib>
#include <iostream>
#include <list>

using namespace std;

class STACK
{
public:
    STACK();
    virtual ~STACK();

    bool    empty();
    size_t  size();
    int     top();
    void    push(int val);
    void    pop();

private:
    std::list<int> m_list;
};

STACK::STACK()
{
}

STACK::~STACK()
{
}

bool STACK::empty()
{
    return m_list.empty();
}

size_t STACK::size()
{
    return m_list.size();
}

int STACK::top()
{
    return m_list.front();
}

void STACK::push(int val)
{
    m_list.push_front(val);

    return;
}

void STACK::pop()
{
    m_list.pop_front();

    return;
}

int main()
{
    // generate 10 random numbers
    int a[10];

    for (int i = 0; i < 10; i++)
    {
        a[i] = rand() % 10;
        cout << a[i] << " ";
    }
    cout << endl;

    // create empty stack
    STACK my_stack;

    // push data into stack
    for (int i = 0; i < 10; i++)
    {
        my_stack.push(a[i]);
    }

    // return stack size
    cout << "stack size " << my_stack.size() << endl;

    // print stack
    for (int i = 0; i < 10; i++)
    {
        cout << my_stack.top() << " ";
        my_stack.pop();
    }
    cout << endl;

    cout << "stack empty " << my_stack.empty() << endl;

    return 0;
}

