// A heap is a way to organize the elements of a range that allows for fast retrieval of the element
// with the highest value at any moment (with pop_heap), even repeatedly, while allowing for fast insertion
// of new elements (with push_heap).
// The element with the highest value is always pointed by first.
// The elements are compared using operator< (for the first version), or comp (for the second)
// The standard container adaptor priority_queue calls make_heap, push_heap and pop_heap automatically to
// maintain heap properties for a container.
// API:
// make_heap Make heap from range
// push_heap Push element into heap range
// pop_heap Pop element from heap range
// sort_heap Sort element of heap
// reverse Reverse range

// g++ -g -O0 heap_stl_impl.cpp -o heap_stl_impl.out -std=c++11
// ./heap_stl.out
// vector front: 10
// vector back: 15
// after make_heap
// vector front: 30
// vector back: 15
// after insert 90 and push_heap
// vector front: 90
// vector back: 10
// after pop_heap and remove 90
// vector front: 30
// vector back: 15
// after sort_heap
// 5 10 15 20 30
// vector front: 5
// vector back: 30

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(5);
    v.push_back(15);

    std::cout << "vector front: " << v.front() << std::endl;
    std::cout << "vector back: " << v.back() << std::endl;

    // make_heap sort with default order
    std::make_heap(v.begin(), v.end());
    std::cout << "after make_heap" << std::endl;
    // The element with the highest value is always pointed by first.
    std::cout << "vector front: " << v.front() << std::endl;
    // The order of the other elements depends on the particular implementation
    std::cout << "vector back: " << v.back() << std::endl;
    // so only consider the front which is the heighest priority
    
    // push_heap
    // Given a heap in the range [first,last-1), this function extends the range considered a heap to [first,last)
    // by placing the value in (last-1) into its corresponding location within it.
    // the initial and final positions of the new heap range, including the pushed element
    std::cout << "after insert 90 and push_heap" << std::endl;
    v.push_back(90);
    std::push_heap(v.begin(), v.end());
    std::cout << "vector front: " << v.front() << std::endl;
    std::cout << "vector back: " << v.back() << std::endl;
    // the highest priority now is 90

    // pop heap
    // Rearranges the elements in the heap range [first,last) in such a way that the part considered a heap is shortened by one:
    // The element with the highest value is moved to (last-1)
    // highest priority is reversed
    std::cout << "after pop_heap" << std::endl;
    std::pop_heap(v.begin(), v.end());
    // the highest priority is now at v.back() for remove (pop)
    v.pop_back();
    // after remove, the highest priority now is at v.front()
    std::cout << "vector front: " << v.front() << std::endl;
    std::cout << "vector back: " << v.back() << std::endl;


    // sort heap with default ascending order
    // sort all elements in the heap with defined orders, not only the higest priority
    std::sort_heap (v.begin(),v.end());
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "vector front: " << v.front() << std::endl;
    std::cout << "vector back: " << v.back() << std::endl;

    return 0;
}

