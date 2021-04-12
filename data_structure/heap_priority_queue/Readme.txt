heap (priority queue)

Pre-required knowledge: tree and binary tree

https://www.fluentcpp.com/2018/03/13/heaps-priority-queues-stl-part-1/
https://www.fluentcpp.com/2018/03/16/heaps-cpp-stl/

A heap is a data structure that has the form of a tree and that respects the heap property, namely: every node must be lower than each of its children - this is ordered.
(here heap is not the same as heap memory allocation, same for stack)

In a heap, each node can theoretically have any number of children.
But in the STL, heaps’ nodes have two children, so by heap we will designate binary tree in this article.

This is how the STL represents heaps: a heap can be stored in an std::vector for example, with the elements laid out next to each other like above.

Priority queues find applications in an operating system that maintains a waiting list for system tasks (process) that is based on their urgency (priority). - CPU Scheduling
Graph algorithms like Dijkstra’s shortest path algorithm, Prim’s Minimum Spanning Tree, etc
All queue applications where priority is involved.

https://www.geeksforgeeks.org/priority-queue-set-1-introduction/
https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
https://www.geeksforgeeks.org/binary-heap/
https://www.geeksforgeeks.org/priority-queue-using-binary-heap/

Priority Queue is an extension of queue with following properties.
    Every item has a priority associated with it.
    An element with high priority is dequeued before an element with low priority.
    If two elements have the same priority, they are served according to their order in the queue.
A typical priority queue supports following operations.
    insert(item, priority): Inserts an item with given priority.
    getHighestPriority(): Returns the highest priority item.
    deleteHighestPriority(): Removes the highest priority item.
How to implement priority queue?
    Using Array
    Using Heaps
        Heap is generally preferred for priority queue implementation because heaps provide better performance compared arrays or linked list.
        using binary heap
