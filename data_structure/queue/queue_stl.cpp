// stl queue (FIFO) implementation
// queues are a type of container adaptor, specifically designed to operate in a FIFO context (first-in first-out)
// elements are inserted into one end of the container and extracted from the other
// public API
//     empty
//     size - return the number of elements
//     front - access next element
//     back - access last element
//     push - insert element at the end of queue
//     pop - remove next element

// g++ queue_stl.cpp -o queue_stl.out
// ./queue_stl.out
// expected front 100, front 100
// expected back 300, back 300
// expected front 200, front 200

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    std::queue<int> my_queue;

    my_queue.push(100);
    my_queue.push(200);
    my_queue.push(300);

    cout << "expected front 100, front " << my_queue.front() << endl;
    cout << "expected back 300, back " << my_queue.back() << endl;

    my_queue.pop();
    cout << "expected front 200, front " << my_queue.front() << endl;

    return 0;
}
