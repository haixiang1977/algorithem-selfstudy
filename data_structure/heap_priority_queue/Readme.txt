heap (priority queue)

Pre-required knowledge: tree and binary tree

https://www.fluentcpp.com/2018/03/13/heaps-priority-queues-stl-part-1/
https://www.fluentcpp.com/2018/03/16/heaps-cpp-stl/

A heap is a data structure that has the form of a tree and that respects the heap property, namely: every node must be lower than each of its children.

In a heap, each node can theoretically have any number of children.
But in the STL, heaps’ nodes have two children, so by heap we will designate binary heaps in this article.

This is how the STL represents heaps: a heap can be stored in an std::vector for example, with the elements laid out next to each other like above.
