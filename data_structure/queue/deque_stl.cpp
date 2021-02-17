// stl deque (double ended queue) implementation
// Double-ended queues are sequence containers with dynamic sizes that can be expanded or contracted on both ends
// (either its front or its back).
// difference compared to vector
//    deque - are not guaranteed to store all its elements in contiguous storage locations
//            the elements of a deque can be scattered in different chunks of storage
//    vectors - use a single array that needs to be occasionally reallocated for growth
// Generally implemented as a dynamic array, it allows direct access to any element in the sequence and provides relatively fast
// addition/removal of elements at the beginning or the end of the sequence.
// Common public API:
//    iterators:
//          begin - return iterator of beginning
//          end - return iterator to end
//    capacity:
//          size/max_size - return size and max size
//          empty - test whether container is empty
//    access:
//          at,[], front/back
//    modifiers:
//          push_back/push_front
//          pop_back/pop_front
//          insert - inserting new elements before the element at the specified position
//          erase - Removes from the deque container either a single element (position) or a range of elements ([first,last))

// g++ deque_stl.cpp -o deque_stl.out
// ./deque_stl.out
// expected front 100, front 100
// expected front 200, front 200
// expected queue size 2, size 2
// expected front 300, front 300
// max size 4611686018427387903

#include <iostream>
#include <deque>

using namespace std;

int main()
{
    std::deque<int> my_queue;

    my_queue.push_back(100);
    my_queue.push_back(200);
    my_queue.push_back(300);

    cout << "expected front 100, front " << my_queue.front() << endl;
    my_queue.pop_front();
    cout << "expected front 200, front " << my_queue.front() << endl;
    my_queue.pop_front();

    my_queue.push_back(400);
    cout << "expected queue size 2, size " << my_queue.size() << endl;

    cout << "expected front 300, front " << my_queue.front() << endl;
    cout << "max size " << my_queue.max_size() << endl;
}
