array
list -> linked list -> ordered linked list -> double linked list -> double circle linked list
stack
queue -> priority queue -> heap
tree

stl organizes its classes into three categories: sequence containers, adapters and associative containers.
stack is an adapter implementing LIFO access.
queue is an adapter implementing FIFO access.
a priority queue is an adapter for which deletion returns the largest (or smallest) value.

sequence container: store data by position in linear order: first element, second element, ... - vector, deque, list
associative container: stores elements by key and access elements by key - set, multiset, map, multimap
adapter contains another container as its underlying storge structure - stack, queue, priority_queue

std::array: store in the stack and its size has to be known at compile time
std::vector: store in the heap and is dynamical std::array. Recommend to use.

list by default is not ordered and sequence is insert sequence.
if want to have an order container, can list::order or use std::set, std::multiset, std::map, and std::multimap. They are all sorted using std::less as the default comparison operation.
The underlying data-structure used (std::multiset, std::map, and std::multimap) is typically a balanced binary search tree such as a red-black tree. So if you add an element
to these data-structures and then iterate over the contained elements, the output will be in sorted order.

std::queue and std:deque
https://www.geeksforgeeks.org/difference-between-queue-and-deque-in-c/
deque is an ADT (abstract data structure) and the implementation can be array or double linked list.
queue is an container type and the underlying container may be one of the standard container class template or some other specifically designed container class.
stl queue is using deque as standard container
https://www.cplusplus.com/reference/queue/queue/

deque can push/pop from front/end and also allow linear access, is the best candidate to implement circualr buffer/list
can use std::queue/std::deque to implement circular buffer/list
