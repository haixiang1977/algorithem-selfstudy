// use c++ stl stack data structure
// public api:
// empty() - test stack is empty
// size() - return size
// top() - access next element
// push() - insert element
// pop() - remove top element

// g++ stack_stl.cpp -o stack_stl.out
// ./stack_stl.out
// 3 6 7 5 3 5 6 2 9 1
// stack size 10
// 1 9 2 6 5 3 5 7 6 3
// stack empty 1

#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

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
    std::stack<int> my_stack;

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
