// stl list implementation
// Lists are sequence containers that allow constant time insert and erase operations anywhere within the sequence,
// and iteration in both directions.
// List containers are implemented as doubly-linked lists
// Compared to other base standard sequence containers (array, vector and deque):
//    lists perform generally better in inserting, extracting and moving elements in any position within the container
//    in algorithms that make intensive use of these, like sorting algorithms
// The main drawback of lists and forward_lists compared to these other sequence containers is that they lack direct
// access to the elements by their position
// common used public api:
//    iterators:
//        begin - return iterator to beginning
//        end - return iterator to end
//    capacity
//        empty - test whether container is empty
//        size/max_size return size/max size
//    access
//        front - access first element
//        back - access last element
//    modifier
//        push_front - Insert element at beginning
//        pop_front - Delete first element
//        push_back - Add element at the end
//        pop_back - Delete last element
//        insert - inserting new elements before the element at the specified position
//        erase - remove from the list container either a single element (at specificed position) or a range of elements ([first,last))
//        clear - clear content
//    operations
//        remove - remove elements with specificed value
//        remove_if
//        unique - remove duplicate values
//        sort - sort elements in container
//        reverse - reverse the order of elements

// g++ list_stl.cpp -o list_stl.out
// ./list_stl.out
// front 200
// back 400
// front 100
// back 300
// size 2

#include <iostream>
#include <list>

using namespace std;

int main()
{
    std::list<int> my_list;

    my_list.push_front(100);
    my_list.push_front(200);

    my_list.push_back(300);
    my_list.push_back(400);

    cout << "front " << my_list.front() << endl;
    cout << "back " << my_list.back() << endl;

    // pop front
    my_list.pop_front();
    cout << "front " << my_list.front() << endl;

    // pop back
    my_list.pop_back();
    cout << "back " << my_list.back() << endl;

    // size
    cout << "size " << my_list.size() << endl;

    return 0;
}
