// use deque to implement stack
// public api:
// empty() - test stack is empty
// size() - return size
// top() - access next element
// push() - insert element
// pop() - remove top element

// advantage of deque to array is that it can dynamically change

// g++ stack_deque.cpp -o stack_deque.out
// ./stack_deque.out
// 8 1 3 2 6 7 1 2 7 3
// stack size 10
// 3 7 2 1 7 6 2 3 1 8
// stack empty 1

#include <cstdlib>
#include <iostream>
#include <deque>

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
    std::deque<int> m_deque;
};

STACK::STACK()
{
}

STACK::~STACK()
{
}

bool STACK::empty()
{
    return m_deque.empty();
}

size_t STACK::size()
{
    return m_deque.size();
}

int STACK::top()
{
    return m_deque.front();
}

void STACK::push(int val)
{
    m_deque.push_front(val);

    return;
}

void STACK::pop()
{
    m_deque.pop_front();

    return;
}

int main()
{
    // generate 10 random numbers
    int a[10];

    // initialize the random generator
    srand (time(NULL));

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
