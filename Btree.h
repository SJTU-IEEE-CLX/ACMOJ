#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include <iostream>
#include "seqStack.h"
#include "seqQueue.h"
using namespace std;
// BTree类的前向说明
template <class elemType>
class BTree;

template <class elemType>
class Node
{
    friend class BTree<elemType>;

private:
    elemType data;
    Node *left, *right;

public:
    Node()
    {
        left = NULL;
        right = NULL;
    };
    Node(const elemType &e, Node *L = NULL, Node *R = NULL)
    {
        data = e;
        left = L;
        right = R;
    };
};

template <class elemType>
class BTree
{
private:
    Node<elemType> *root;

    int Size(Node<elemType> *t);     // 求以t为根的二叉树的结点个数。
    int Height(Node<elemType> *t);   // 求以t为根的二叉树的高度。
    void DelTree(Node<elemType> *t); // 删除以t为根的二叉树
    // 按前序遍历输出以t为根的二叉树的结点的数据值
    void PreOrder(Node<elemType> *t);
    // 按中序遍历输出以t为根的二叉树的结点的数据值
    void InOrder(Node<elemType> *t);
    // 按后序遍历输出以t为根的二叉树的结点的数据值
    void PostOrder(Node<elemType> *t);

public:
    BTree() { root = NULL; }
    void createTree(const elemType &stopFlag); // 创建一棵二叉树
    bool isEmpty() { return (root == NULL); }  // 二叉树为空返回true，否则返回false
    Node<elemType> *GetRoot() { return root; }
    int Size();        // 求二叉树的结点个数。
    int Height();      // 求二叉树的高度。
    void DelTree();    // 删除二叉树
    void PreOrder();   // 按前序遍历输出二叉树的结点的数据值
    void InOrder();    // 按中序遍历输出二叉树的结点的数据值
    void PostOrder();  // 按后序遍历输出二叉树的结点的数据值
    void LevelOrder(); // 按中序遍历输出二叉树的结点的数据值
};

template <class elemType>
void BTree<elemType>::createTree(const elemType &stopFlag)
{
    seqQueue<Node<elemType> *> que;
    elemType e, el, er;
    Node<elemType> *p, *pl, *pr;

    cout << "Please input the value of the root: ";
    cin >> e;
    if (e == stopFlag)
        return;
    p = new Node<elemType>(e);
    root = p; // 根结点为该新创建结点
    que.enQueue(p);
    while (!que.isEmpty())
    {
        p = que.front(); // 获得队首元素并出队
        que.deQueue();
        cout << "Please input the value of the left child and the right child of " << p->data
             << " using " << stopFlag << " as no child: ";
        cin >> el >> er;
        if (el != stopFlag) // 该结点有左孩子
        {
            pl = new Node<elemType>(el);
            p->left = pl;
            que.enQueue(pl);
        }
        if (er != stopFlag) // 该结点有右孩子
        {
            pr = new Node<elemType>(er);
            p->right = pr;
            que.enQueue(pr);
        }
    }
}

template <class elemType> // 公有
int BTree<elemType>::Size()
{
    return Size(root);
}

// 得到以t为根二叉树结点个数，递归算法实现。
template <class elemType> // 私有
int BTree<elemType>::Size(Node<elemType> *t)
{
    if (!t)
        return 0;
    return 1 + Size(t->left) + Size(t->right);
}

template <class elemType>
int BTree<elemType>::Height()
{
    return Height(root);
}

// 得到以t为根二叉树的高度，递归算法实现。
template <class elemType>
int BTree<elemType>::Height(Node<elemType> *t)
{
    int hl, hr;
    if (!t)
        return 0;
    hl = Height(t->left);
    hr = Height(t->right);
    if (hl >= hr)
        return 1 + hl;
    return 1 + hr;
}

template <class elemType>
void BTree<elemType>::DelTree()
{
    DelTree(root);
    root = NULL;
}

// 删除以t为根的二叉树，递归算法实现 
template <class elemType>
void BTree<elemType>::DelTree(Node<elemType> *t)
{
    if (!t)
        return;
    DelTree(t->left);
    DelTree(t->right);
    delete t;
}

template <class elemType>
void BTree<elemType>::LevelOrder()
{
    seqQueue<Node<elemType> *> que;
    Node<elemType> *p;

    if (!root)
        return; // 二叉树为空
    que.enQueue(root);
    while (!que.isEmpty())
    {
        p = que.front();
        que.deQueue();
        cout << p->data;

        if (p->left)
            que.enQueue(p->left);
        if (p->right)
            que.enQueue(p->right);
    }
    cout << endl;
}

template <class elemType> // 公有
void BTree<elemType>::PreOrder()
{
    return PreOrder(root);
}

template <class elemType> // 公有
void BTree<elemType>::InOrder()
{
    return InOrder(root);
}

template <class elemType> // 公有
void BTree<elemType>::PostOrder()
{
    return PostOrder(root);
}

template <class elemType>
void BTree<elemType>::PreOrder(Node<elemType> *t)
{
    if (!t)
        return;
    cout << t->data;
    PreOrder(t->left);
    PreOrder(t->right);
}

template <class elemType>
void BTree<elemType>::InOrder(Node<elemType> *t)
{
    if (!t)
        return;
    InOrder(t->left);
    cout << t->data;
    InOrder(t->right);
}

template <class elemType>
void BTree<elemType>::PostOrder(Node<elemType> *t)
{
    if (!t)
        return;
    PostOrder(t->left);
    PostOrder(t->right);
    cout << t->data;
}



#endif // BTREE_H_INCLUDED