// stl vector
// Vectors are sequence containers representing arrays that can change in size.
// Just like arrays, vectors use contiguous storage locations for their elements
// Internally, vectors use a dynamically allocated array to store their elements. This array may need to be reallocated in order to
// grow in size when new elements are inserted, which implies allocating a new array and moving all elements to it.
// vector containers may allocate some extra storage to accommodate for possible growth, and thus the container may have an actual
// capacity greater than the storage strictly needed to contain its elements
// Therefore, compared to arrays, vectors consume more memory in exchange for the ability to manage storage and grow dynamically in
// an efficient way.
// Vector insert/erase will causes the container to relocate all the elements beause vectors use an array as their underlying storage
// and are all inefficient operations
// public API:
//      iterators
//          begin/end
//      capacity
//          size/max_size/empty/shrink_to_fit
//      access
//          [], at, front, end, data
//      modifiers
//          push_back, pop_back, insert, erase

// g++ vector_stl.cpp -o vector_stl.out -std=c++11
// ./vector_stl.out
// expected front 100, front 100
// expect [0] 100, [0] 100
// expect [1] 200, [1] 200

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> my_vector;

    my_vector.push_back(100);
    my_vector.push_back(200);
    my_vector.push_back(300);

    cout << "expected front 100, front " << my_vector.front() << endl;

    my_vector.pop_back(); // pop the last element
    cout << "expect [0] 100, [0] " << my_vector.at(0) << endl;
    cout << "expect [1] 200, [1] " << my_vector.at(1) << endl;
}
