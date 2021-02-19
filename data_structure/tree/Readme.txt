C/C++ tree

https://www.softwaretestinghelp.com/trees-in-cpp/

https://www.geeksforgeeks.org/c-programs-gq/tree-programs-gq/

tree
binary tree

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
    
