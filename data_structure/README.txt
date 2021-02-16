list -> linked list -> ordered linked list -> double linked list -> double circle linked list
stack
queue -> priority queue -> heap
tree

list by default is not ordered and sequence is insert sequence.
if want to have an order container, can list::order or use std::set, std::multiset, std::map, and std::multimap. They are all sorted using std::less as the default comparison operation.
The underlying data-structure used is typically a balanced binary search tree such as a red-black tree. So if you add an element to these data-structures and then iterate over the contained elements, the output will be in sorted order.
