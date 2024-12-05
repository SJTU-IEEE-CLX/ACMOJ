#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;
    Node* parent;
    Node(int x) : val(x), left(NULL), right(NULL),parent(NULL) {}
};

class Btree
{
public:
    Node *root;
    Btree() : root(NULL) {}

    void create_tree(Node *root, vector<int> v)
    {
        int i = 1;
        root->val = v[0];
        int size = v.size();
        queue<Node *> q;
        q.push(root);
        while (!q.empty() && i < size)
        {
            Node *node = q.front();
            node->left = new Node(v[i++]);
            node->left->parent = node;
            q.push(node->left);
            node->right = new Node(v[i++]);
            node->right->parent = node;
            q.push(node->right);
            q.pop();
        }
    }

    vector<int> get_values(Node *root)
    {
        vector<int> res;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *node = q.front();
            res.push_back(node->val);
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
            q.pop();
        }
        return res;
    }

    unordered_map<int, Node*> get_nodes(Node *root)
    {
        unordered_map<int, Node*> res;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *node = q.front();
            res[node->val] = node;
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
            q.pop();
        }
        return res;
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


int minstep(Btree& tree, Node* root, int a, int b) {
    unordered_map<int, Node*> nodes = tree.get_nodes(root);
    if (a == b) {
        return 0;
    }
    Node* node_a = nodes[a];
    Node* node_b = nodes[b];

    queue<pair<Node*, int>> q;
    set<int> visited;
    q.push({node_a, 0});
    visited.insert(node_a->val);

    while (!q.empty()) {
        Node* node = q.front().first;
        int steps = q.front().second;
        q.pop();

        if (node == node_b) {
            return steps;
        }

        if (node->left && visited.find(node->left->val) == visited.end()) {
            q.push({node->left, steps + 1});
            visited.insert(node->left->val);
        }
        if (node->right && visited.find(node->right->val) == visited.end()) {
            q.push({node->right, steps + 1});
            visited.insert(node->right->val);
        }
        if (node->parent && visited.find(node->parent->val) == visited.end()) {
            q.push({node->parent, steps + 1});
            visited.insert(node->parent->val);
        }
    }

    return -1; 
}
    

int main(){
    int size;
    cin>>size;
    vector<int> values(size);
    for(int i = 0; i < size; i++){
        cin>>values[i];
    }
    Node* root = new Node(values[0]);
    Btree tree;
    tree.create_tree(root, values);
    int a,b;
    cin>>a>>b;
    cout<<minstep(tree,root, a, b)<<endl;
    return 0;
}