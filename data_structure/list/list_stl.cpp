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
