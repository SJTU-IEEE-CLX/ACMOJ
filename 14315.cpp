#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(NULL), right(NULL) {}
};

void mirrorTree(Node* root) {
    if (root == NULL) return;
    swap(root->left, root->right);
    mirrorTree(root->left);
    mirrorTree(root->right);
}

void postOrderTraversal(Node* root) {
    if (root == NULL) return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout<<root->val<<" ";
}

int main() {
    int n;
    cin >> n;
    unordered_map<int, Node*> nodes;
    int a, b, c;
    Node* root = NULL;

    for (int i = 0; i < n; ++i) {
        cin >> a >> b >> c;
        if (nodes.find(a) == nodes.end()) {
            nodes[a] = new Node(a);
            if (root == NULL) root = nodes[a];
        }
        if (b != -1) {
            nodes[b] = new Node(b);
            nodes[a]->left = nodes[b];
        }
        if (c != -1) {
            nodes[c] = new Node(c);
            nodes[a]->right = nodes[c];
        }
    }

    mirrorTree(root);

    vector<int> result;
    postOrderTraversal(root);


    return 0;
}