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
// min 5
// max 80
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
    // parameter: root of tree
    // return:    root of tree
    int SearchMaximum(BinarySearchTree_Node* root);

    // delete node
    // parameter: root of tree and value
    //            is_left, is parent left child
    // return: 0 - found and deleted -1 - not found
    int Delete(BinarySearchTree_Node* root, bool is_left, int val);

    int m_val;
    BinarySearchTree_Node* m_parent;
    BinarySearchTree_Node* m_left;
    BinarySearchTree_Node* m_right;
};

BinarySearchTree_Node::BinarySearchTree_Node() :
    m_val(0),
    m_parent(nullptr),
    m_left(nullptr),
    m_right(nullptr)
{
}

BinarySearchTree_Node::BinarySearchTree_Node(int val) :
    m_val(val),
    m_parent(nullptr),
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
        return Search(root->m_right, val);
    }
    else
    {
        return Search(root->m_left, val);
    }
}

BinarySearchTree_Node* BinarySearchTree_Node::Insert(BinarySearchTree_Node* root, int val)
{
    if (root == nullptr)
    {
        // this is root node
        return new BinarySearchTree_Node(val);
    }

    BinarySearchTree_Node* node = root;
    while (node)
    {
        if (val > node->m_val)
        {
            if (node->m_right)
            {
                node = node->m_right;
            }
            else
            {
                BinarySearchTree_Node* n = new BinarySearchTree_Node(val);
                node->m_right = n;
                n->m_parent = node;
                break;
            }
        }
        else
        {
            if (node->m_left)
            {
                node = node->m_left;
            }
            else
            {
                BinarySearchTree_Node* n = new BinarySearchTree_Node(val);
                node->m_left = n;
                n->m_parent = node;
                break;
            }
        }
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
        return SearchMaximum(root->m_right);
    }
}

int BinarySearchTree_Node::Delete(BinarySearchTree_Node* root, bool is_left, int val)
{
    BinarySearchTree_Node* node = nullptr;

    if (root == nullptr)
    {
        return -1;
    }

    if ((val > root->m_val) && (root->m_right))
    {
        return Delete(root->m_right, false, val);
    }

    if ((val < root->m_val) && (root->m_left))
    {
        return Delete(root->m_left, true, val);
    }

    if ((val > root->m_val) && (root->m_right == nullptr))
    {
        return -1;
    }

    if ((val < root->m_val) && (root->m_left == nullptr))
    {
        return -1;
    }

    // val == root->m_val
    // 1. root has no child and just delete
    if ((root->m_left == nullptr) && (root->m_right == nullptr))
    {
        delete root;
        return 0;
    }

    // 2. root has 1 child and need to move this child to has the same parent
    if ((root->m_left == nullptr) && (root->m_right))
    {
        BinarySearchTree_Node* n = root->m_right;
        BinarySearchTree_Node* p = root->m_parent;
        n->m_parent = p;
        if (is_left)
        {
            p->m_left = n;
        }
        else
        {
            p->m_right = n;
        }
        delete root;
        return 0;
    }

    if ((root->m_right == nullptr) && (root->m_left))
    {
        BinarySearchTree_Node* n = root->m_left;
        BinarySearchTree_Node* p = root->m_parent;
        n->m_parent = p;
        if (is_left)
        {
            p->m_left = n;
        }
        else
        {
            p->m_right = n;
        }
        delete root;
        return 0;
    }

    // 2. root has 2 children and need to move the right to has the same parent
    //    move the left to be the child of right
    {
        BinarySearchTree_Node* n_left = root->m_left;
        BinarySearchTree_Node* n_right = root->m_right;
        BinarySearchTree_Node* p = root->m_parent;
        n_right->m_parent = p;
        n_left->m_parent = n_right;
        if (is_left)
        {
            p->m_left = n_right;
        }
        else
        {
            p->m_right = n_right;
        }
        delete root;
        return 0;
    }
}

int main()
{
    BinarySearchTree_Node tmp;
    BinarySearchTree_Node* root = nullptr;
    BinarySearchTree_Node* node = nullptr;

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
    node = tmp.Search(root, 5);
    if (node)
    {
        cout << "node " << node->m_val << " found" << endl;
    }
    else
    {
        cout << "node 5 not found" << endl;
    }

    node = tmp.Search(root, 100);
    if (node)
    {
        cout << "node " << node->m_val << " found" << endl;
    }
    else
    {
        cout << "node 100 not found" << endl;
    }

    cout << "min " << tmp.SearchMinimum(root) << endl;

    cout << "max " << tmp.SearchMaximum(root) << endl;

    return 0;
}
