// Binary Search Tree is a node-based binary tree data structure which has the following properties:
//     The left subtree of a node contains only nodes with keys lesser than the node’s key
//     The right subtree of a node contains only nodes with keys greater than the node’s key
//     The left and right subtree each must also be a binary search tree
// insertion (setup):
//     A new key is always inserted at the leaf. start searching a key from the root until we hit a leaf node.
//     Once a leaf node is found, the new node is added as a child of the leaf node. If greater, then right. If less, then left
// g++ -g -O0 -std=c++11 binary_search_tree_impl.cpp -o binary_search_tree_impl.out
// ./binary_search_tree_impl.out
//  --50
//      |-30
//          |-20
//              |-10
//                  |-5
//          --40
//      --60
//          --80
// node 5 found
// node 100 not found
// we can see when the new node is inserted, the tree is not balanced
#include <iostream>

using namespace std;

class BinarySearchTree_Node
{
 public:
    BinarySearchTree_Node();
    BinarySearchTree_Node(int val);
    virtual ~BinarySearchTree_Node();

    // search
    // parameter: root of tree and value
    // return: the node of matched value
    BinarySearchTree_Node* Search(BinarySearchTree_Node* root, int val);

    // insert
    // parameter: root of tree and value
    // return:    root of tree
    BinarySearchTree_Node* Insert(BinarySearchTree_Node* root, int val);

    // dump binary search tree
    void Dump(BinarySearchTree_Node* node, int level, bool is_left);

    // search minimum value
    int SearchMinimum(BinarySearchTree_Node* root);

    // search maximum value
    int SearchMaximum(BinarySearchTree_Node* root);

    int m_val;
    BinarySearchTree_Node* m_left;
    BinarySearchTree_Node* m_right;
};

BinarySearchTree_Node::BinarySearchTree_Node() :
    m_val(0),
    m_left(nullptr),
    m_right(nullptr)
{
}

BinarySearchTree_Node::BinarySearchTree_Node(int val) :
    m_val(val),
    m_left(nullptr),
    m_right(nullptr)
{
}

BinarySearchTree_Node::~BinarySearchTree_Node()
{
}

BinarySearchTree_Node* BinarySearchTree_Node::Search(BinarySearchTree_Node* root, int val)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->m_val == val)
    {
        return root;
    }

    if (val > root->m_val)
    {
        Search(root->m_right, val);
    }
    else
    {
        Search(root->m_left, val);
    }
}

BinarySearchTree_Node* BinarySearchTree_Node::Insert(BinarySearchTree_Node* root, int val)
{
    if (root == nullptr)
    {
        // this is leaf node
        return new BinarySearchTree_Node(val);
    }

    if (val > root->m_val)
    {
        root->m_right = Insert(root->m_right, val);
    }
    else
    {
        root->m_left = Insert(root->m_left, val);
    }

    return root;
}

void BinarySearchTree_Node::Dump(BinarySearchTree_Node* node, int level, bool is_left)
{
    if (node == nullptr)
    {
        return;
    }

    for (int i = 0; i < level; i++)
    {
        printf(" ");
    }

    if (is_left)
    {
        printf("|-");
    }
    else
    {
        printf("--");
    }
    printf("%d\n", node->m_val);

    level += 4;
    if (node->m_left)
    {
        Dump(node->m_left, level, true);
    }

    if (node->m_right)
    {
        Dump(node->m_right, level, false);
    }
    
    return;
}

int BinarySearchTree_Node::SearchMinimum(BinarySearchTree_Node* root)
{
    if (root == nullptr)
    {
        // invalid value
        return -1;
    }

    if (root->m_left == nullptr)
    {
        return root->m_val;
    }
    else
    {
        return SearchMinimum(root->m_left);
    }
}

int BinarySearchTree_Node::SearchMaximum(BinarySearchTree_Node* root)
{
    if (root == nullptr)
    {
        // invalid value
        return -1;
    }

    if (root->m_right == nullptr)
    {
        return root->m_val;
    }
    else
    {
        return SearchMinimum(root->m_right);
    }
}

int main()
{
    BinarySearchTree_Node tmp;
    BinarySearchTree_Node* root = nullptr;

    // insert tree
    root = tmp.Insert(root, 50);
    tmp.Insert(root, 30);
    tmp.Insert(root, 20);
    tmp.Insert(root, 40);
    tmp.Insert(root, 60);
    tmp.Insert(root, 80);
    tmp.Insert(root, 10);
    tmp.Insert(root, 5);

    // dump tree
    tmp.Dump(root, 0, false);

    // search tree
    if (tmp.Search(root, 5))
    {
        cout << "node 5 found" << endl;
    }

    if (!tmp.Search(root, 100))
    {
        cout << "node 100 not found" << endl;
    }

    cout << "min " << tmp.SearchMinimum(root) << endl;

    cout << "max " << tmp.SearchMaximum(root) << endl;

    return 0;
}
