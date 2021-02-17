// stl array
// Arrays are fixed-size sequence containers: they hold a specific number of elements ordered in a strict linear sequence.
// Unlike the other standard containers, arrays have a fixed size and do not manage the allocation of its elements through an allocator
// Therefore, they cannot be expanded or contracted dynamically
// (see vector for a similar container that can be expanded).
// public API:
//    itertators
//          begin/end
//    capacity
//          size/max_size, empty
//    access
//          [], at, front, back
// g++ array_stl.cpp -o array_stl.out -std=c++11
// ./array_stl.out
// expected front 100, front 100
// expected front 300, front 300
// expected [1] 200, [1] 200
// expected [1] 400, [1] 400

#include <iostream>
#include <array>

using namespace std;

int main()
{
    std::array<int, 3> my_array = {100, 200, 300};

    cout << "expected front 100, front " << my_array.front() << endl;
    cout << "expected front 300, front " << my_array.back() << endl;

    cout << "expected [1] 200, [1] " << my_array[1] << endl;
    my_array.at(1) = 400;
    cout << "expected [1] 400, [1] " << my_array[1] << endl;
}
