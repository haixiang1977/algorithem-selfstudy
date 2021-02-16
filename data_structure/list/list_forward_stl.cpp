// Forward lists are sequence containers that allow constant time insert and erase operations anywhere within the sequence.
// Forward lists are implemented as singly-linked lists
// The main design difference between a forward_list container and a list container is that the first keeps internally only a link to the next element,
// while the latter keeps two links per element: one pointing to the next element and one to the preceding one, allowing efficient iteration in both directions,
// but consuming additional storage per element and with a slight higher time overhead inserting and removing elements.
// common used public api:
//    iterators:
//        begin - return iterator to beginning
//        end - return iterator to end
//    capacity
//        empty - test whether container is empty
//        max_size - return max size
//    access
//        front - access first element
//    modifier
//        push_front - Insert element at beginning
//        pop_front - Delete first element
//        insert_after - inserting new elements before the element at the specified position
//        erase_after - remove from the list container either a single element (at specificed position) or a range of elements ([first,last))
//        clear - clear content
//    operations
//        remove - remove elements with specificed value
//        remove_if
//        unique - remove duplicate values
//        sort - sort elements in container
//        reverse - reverse the order of elements

// g++ list_forward_stl.cpp -o list_forward_stl.out -std=c++11
// ./list_forward_stl.out
// front 200
// front 100

#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
    std::forward_list<int> my_forward_list;

    my_forward_list.push_front(100);
    my_forward_list.push_front(200);


    cout << "front " << my_forward_list.front() << endl;

    // pop front
    my_forward_list.pop_front();
    cout << "front " << my_forward_list.front() << endl;

    return 0;
}
