#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <set>
#include <functional>
using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;
    Node* path;
    Node(int x) : val(x), left(NULL), right(NULL), path(NULL) {}
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
            q.push(node->left);
            node->right = new Node(v[i++]);
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

bool BFS(Node* root,int value){
    queue<Node*> q;
    set<Node*> visited;
    q.push(root);
    while(!q.empty()){
        Node* node = q.front();
        if(visited.find(node)!=visited.end()){
            q.pop();
            continue;
        }
        if(node->val == value){
            return true;
        }
        if(node->left){
            q.push(node->left);
        }
        if(node->right){
            q.push(node->right);
        }
        if(node->path){
            q.push(node->path);
        }
        q.pop();
        visited.insert(node);
    }
    return false;
}

int main()
{
    int num_tree;
    cin >> num_tree;

    vector<Btree> trees(num_tree);
    for (int i = 0; i < num_tree; ++i) {
        int k;
        cin >> k;
        vector<int> values((1<<k)- 1);
        for (int j = 0; j < (1 << k) - 1; ++j) {
            cin >> values[j];
        }
        trees[i].root = new Node(values[0]);
        trees[i].create_tree(trees[i].root, values);
    }

    int num_paths;
    cin >> num_paths;
    vector<int> head(num_paths);
    vector<int> tail(num_paths);
    for (int i = 0; i < num_paths; ++i) {
        cin >> head[i] >> tail[i];
    }

    vector<Node*> head_nodes(num_paths);
    vector<Node*> tail_nodes(num_paths);

    for(int i = 0; i < num_tree; i++){
        vector<int> tree_values = trees[i].get_values(trees[i].root);
        unordered_map<int, Node*> tree_nodes = trees[i].get_nodes(trees[i].root);
        for (int j = 0; j < tree_values.size(); j++){
            for(int k = 0; k < num_paths; k++){
                if(tree_values[j] == head[k]){
                    head_nodes[k] = tree_nodes[head[k]];
                }
                if(tree_values[j] == tail[k]){
                    tail_nodes[k] = tree_nodes[tail[k]];
                }
            }
        }
    }

    for(int i = 0; i < num_paths; i++){
        Node* head_node = head_nodes[i];
        Node* tail_node = tail_nodes[i];
        head_node->path = tail_node;
    }

    int num_queries;
    cin >> num_queries;
    vector<int> queries(num_queries);
    for (int i = 0; i < num_queries; ++i) {
        cin >> queries[i];
    }

    for(int i = 0;i<num_queries;i++){
        bool flag = BFS(trees[0].root,queries[i]);
        if (flag)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
        
    }
    return 0;
}
    
