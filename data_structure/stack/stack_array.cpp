// use array to implement stack
// public api:
// empty() - test stack is empty
// size() - return size
// top() - access next element
// push() - insert element
// pop() - remove top element

// g++ stack_array.cpp -o stack_array.out
// ./stack_array.out
// 3 6 7 5 3 5 6 2 9 1
// stack size 10
// 1 9 2 6 5 3 5 7 6 3
// stack empty 1

#include <cstdlib>
#include <iostream>

using namespace std;

class STACK
{
public:
    STACK(int size);
    virtual ~STACK();

    bool    empty();
    size_t  size();
    int     top();
    void    push(int val);
    void    pop();
private:
    int*    m_base;
    int     m_top;
    int     m_size;
};

STACK::STACK(int size)
{
    m_size = size;
    m_base = (int*)malloc(size * sizeof(int));
    m_top = -1;
}

STACK::~STACK()
{
    delete []m_base;
}

bool STACK::empty()
{
    return (m_top == -1);
}

size_t STACK::size()
{
    if (m_top == -1)
    {
        return 0;
    }

    return (size_t)(m_top + 1);
}

int STACK::top()
{
    return *(m_base + m_top);
}

void STACK::push(int val)
{
    if ((int)size() == m_size)
        return;

    m_top ++;

    *(m_base + m_top) = val;

    return;
}

void STACK::pop()
{
    if (m_top == -1)
    {
        // do nothing
    }
    else
    {
        m_top --;
    }

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
    STACK my_stack(10);

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

