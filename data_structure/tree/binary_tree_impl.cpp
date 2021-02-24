// binary tree is a tree in which no node can have more than 2 children
// a complete binary tree with n nodes has a depth of int(log2(n))

// build binary tree manually
// g++ -g -O0 -std=c++11 binary_tree_impl.cpp -o binary_tree_impl.out
// in_order_scan
// name: node3 value: 3
// name: node1 value: 1
// name: node4 value: 4
// name: node0 value: 0
// name: node5 value: 5
// name: node2 value: 2
// post_order_scan
// name: node3 value: 3
// name: node4 value: 4
// name: node1 value: 1
// name: node5 value: 5
// name: node2 value: 2
// name: node0 value: 0
// level_order_scan
// name: node0 value: 0
// name: node1 value: 1
// name: node2 value: 2
// name: node3 value: 3
// name: node4 value: 4
// name: node5 value: 5

#include <iostream>
#include <queue>

using namespace std;

class TreeNode
{
public:
    TreeNode();
    TreeNode(std::string name, int val, TreeNode* left, TreeNode* right);
    virtual ~TreeNode();

    std::string m_name;
    int 	m_val;
    TreeNode*	m_left;
    TreeNode*	m_right;
};

TreeNode::TreeNode() :
    m_name(),
    m_val(0),
    m_left(nullptr),
    m_right(nullptr)
{
}

TreeNode::TreeNode(std::string name, int val, TreeNode* left, TreeNode* right) :
    m_name(name),
    m_val(val),
    m_left(left),
    m_right(right)
{
}

TreeNode::~TreeNode()
{
}

// in order scan - recursive
// traverse the left tree until the leaf
// access the current node
// traverse the right tree until the leaf
void in_order_scan(TreeNode* node)
{
    if (node->m_left)
    {
        in_order_scan(node->m_left);
    }

    cout << "name: " << node->m_name << " value: " << node->m_val << endl;

    if (node->m_right)
    {
        in_order_scan(node->m_right);
    }
}

// post order scan - recursive
// traverse the left tree until the leaf
// traverse the right tree until the leaf
// access the current node
void post_order_scan(TreeNode* node)
{
    if (node->m_left)
    {
        post_order_scan(node->m_left);
    }

    if (node->m_right)
    {
        post_order_scan(node->m_right);
    }

    cout << "name: " << node->m_name << " value: " << node->m_val << endl;
}

void level_order_scan(TreeNode* node)
{
    queue<TreeNode*> q;
    TreeNode* p;

    // initialize the queue
    q.push(node);

    while(!q.empty())
    {
        p = q.front();
	q.pop();

        cout << "name: " << p->m_name << " value: " << p->m_val << endl;

        if (p->m_left)
        {
	    q.push(p->m_left);
	}
	if (p->m_right)
        {
            q.push(p->m_right);
	}
    }
}

int main()
{
    // build 4 nodes binary tree
    //           node0
    //    node1         node2
    // node3 node4   node5

    // start from leaf first
    TreeNode node3("node3", 3, nullptr, nullptr);
    TreeNode node4("node4", 4, nullptr, nullptr);
    TreeNode node5("node5", 5, nullptr, nullptr);

    TreeNode node1("node1", 1, &node3, &node4);
    TreeNode node2("node2", 2, &node5, nullptr);

    TreeNode node0("node0", 0, &node1, &node2);

    // scan the tree
    cout << "in_order_scan" << endl;
    in_order_scan(&node0);

    // scan the tree
    cout << "post_order_scan" << endl;
    post_order_scan(&node0);

    // scan the tree
    cout << "level_order_scan" << endl;
    level_order_scan(&node0);

    return 0;
}


