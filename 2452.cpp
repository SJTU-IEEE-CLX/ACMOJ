#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int x) : val(x), left(NULL), right(NULL) {}
};

class Btree
{
private:
    Node *insert(Node *node, int val)
    {
        if (node == NULL)
        {
            return new Node(val);
        }
        if (val < node->val)
        {
            node->left = insert(node->left, val);
        }
        else
        {
            node->right = insert(node->right, val);
        }
        return node;
    }

public:
    Node *root;
    Btree() : root(NULL) {}

    void insert(int val)
    {
        root = insert(root, val);
    }

    int findKthLargest(Node *node, int k, int &count)
    {
        if (node == NULL)
        {
            return -1; // or throw an exception
        }
        int right = findKthLargest(node->right, k, count);
        if (right != -1)
        {
            return right;
        }
        count++;
        if (count == k)
        {
            return node->val;
        }
        return findKthLargest(node->left, k, count);
    }
    void destroy(Node *node)
    {
        if (node != NULL)
        {
            destroy(node->right);
            destroy(node->left);
            delete node;
        }
    }

    ~Btree()
    {
        destroy(root);
    }
};

int main()
{
    Btree Btree;
    int val;
    for (int i = 0; i < 7; ++i)
    {
        std::cin >> val;
        Btree.insert(val);
    }
    int k;
    std::cin >> k;
    int count = 0;
    std::cout << Btree.findKthLargest(Btree.root, k, count) << std::endl;
    return 0;
}