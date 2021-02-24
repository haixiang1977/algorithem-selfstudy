C/C++ tree

https://www.softwaretestinghelp.com/trees-in-cpp/

https://www.geeksforgeeks.org/c-programs-gq/tree-programs-gq/

tree
binary tree (insert is faster than array, search is slower than binary search). it commonly used when insert/delete a record and search. And it cannot random access.
insert/delete: linkedlist < tree < array
search:  array < tree < linkedlist

tree definition:
    root - distinguished node
    each node connected by a directed edge
    child/parent/grand parent/grand children
    node without children - leaves
    node with same parent - siblings
    a path from node n(1) to n(k) is a defined as a sequence n(1), n(2), ... n(k). The lengh of this path is k - 1
    the depth of n(i) is the length of the unique path from the root to n(i)
    the height of n(i) is the length of the longest path from n(i) to leaf. the height of tree == the height of the root
    if there is a path from n(1) to n(2), then n(1) is ancestor of n(2) and n(2) is a descendant of n(1)

node declaration from tree
    struct TreeNode
    {
        Object      element
        TreeNode*   *firstChild;
        TreeNode*   *nextSilbing;
    }
    
2 types of tree traversal
    preorder traversal - work at a node is performed before (pre) its children are processed
    postorder traversal - the work at a node is performed after (post) its children are processed

binary tree - a tree which no node can have more than two children

binary search tree (BST) - The binary tree that is ordered. In a binary search tree, the nodes to the left are less than the root node while the nodes to the right are greater than or equal to the root node.

expression tree - A binary tree that is used to evaluate simple arithmetic expressions is called an expression tree.

binary tree is an example of associative container

node declaration from binary tree
    struct BinaryTreeNode
    {
        Object              element
        BinaryTreeNode*     parent;
        BinaryTreeNode*     left;
        BinaryTreeNode*     right;
    }

balanced tree - The left and right subtrees' heights differ by at most one, The left subtree is balanced, The right subtree is balanced

balanced binary tree (B-BST) - Red-Black tree as example

Red-Black tree - a special balanced binary tree
    can finish insert/delete/search in O(log(n))
