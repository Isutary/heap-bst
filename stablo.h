#ifndef STABLO_H_INCLUDED
#define STABLO_H_INCLUDED
#include<iostream>
#include<utility>
using namespace std;

template <typename T>
class Stablo {
private:
    // MEMBERS
    struct Node {
        T element;
        int priority;
        Node *leftChild, *rightChild, *parent;
    };
    int length;
    Node *root;
    // CONSTRUCTOR
    Stablo(Node *n1, int length = 100) : length(length), root(n1) { if (root) root->parent = nullptr;  }
    // ADDITIONS
    void myAdd(T x, Node *currentRoot);
    void myDivide(T x, Node *currentRoot);
    // REMOVE
    void myRemove(T x, Node *&currentRoot);
    // PROPERTY CHECKS
    void checkProperty(Node *currentRoot);
    void checkUnite(Node *currentRoot);
    // ROTATIONS
    void rotateRight(Node *currentRoot);
    void rotateLeft(Node *currentRoot);
    // SEARCHES
    T findMin(Node *currentRoot) const;
    T findMax(Node *currentRoot) const;
    bool myFind(T x, const Node *const& currentRoot) const;
    // OUTPUT
    void preOrder(Node *currentRoot, int d = 0) const;
public:
    // CONSTRUCTOR
    Stablo(int length=100) : length(length), root(nullptr) {}
    // ADDITIONS
    void myAdd(T x) { myAdd(x, root); }
    // REMOVE
    void myRemove(T x) { myRemove(x,root); }
    // SEARCHES
    T findMin() const { return findMin(root); }
    T findMax() const { return findMax(root); }
    bool myFind(T x) const { return myFind(x, root); }
    // OUTPUT
    void preOrder() const { preOrder(root); }
    // DIVIDE, UNITE AND UNION
    pair<Stablo, Stablo> myDivide(T x);
    template <typename T1>
    friend Stablo<T1> myUnite(Stablo<T1> s1, Stablo<T1> s2);
    template <typename T1>
    friend Stablo<T1> myUnion(Stablo<T1> s1, Stablo<T1> s2);
};

//#include "stablo.cpp"
#endif // STABLO_H_INCLUDED
