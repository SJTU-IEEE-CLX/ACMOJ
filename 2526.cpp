#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

struct TreeNode;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* buildTree(const vector<string>& nodes) {
    //树为空
    if (nodes.empty() || nodes[0] == "null") return nullptr;
    
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    
    while (!q.empty() && i < nodes.size()) {
        TreeNode* current = q.front();
        q.pop();
        
        if (nodes[i] != "null") {
            current->left = new TreeNode(stoi(nodes[i]));
            q.push(current->left);
        }
        i++;
        if (i < nodes.size() && nodes[i] != "null") {
            current->right = new TreeNode(stoi(nodes[i]));
            q.push(current->right);
        }
        i++;
    }
    
    return root;
}

int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

void destroy(TreeNode *node)
    {
        if (node != NULL)
        {
            destroy(node->right);
            destroy(node->left);
            delete node;
        }
    }

int main() {
    int n;
    cin >> n;
    vector<string> nodes(n);
    for (int i = 0; i < n; ++i) {
        cin >> nodes[i];
    }
    
    TreeNode* root = buildTree(nodes);
    cout << maxDepth(root) << endl;
    
    destroy(root);
    return 0;
}