#include "stablo.h"
#include<random>
#include<iomanip>

///// ADDITIONS  /////

template <typename T>
void Stablo<T>::myAdd(T x, Node *currentRoot) {
	if (!currentRoot) {
		int priorityValue = rand() % length;
		root = new Node{ x, priorityValue, nullptr, nullptr, nullptr };
	}
	else if (x < currentRoot->element) {
		if (!currentRoot->leftChild) {
			int priorityValue = rand() % length;
			currentRoot->leftChild = new Node{ x, priorityValue, nullptr, nullptr, currentRoot };
			checkProperty(currentRoot);
		}
		else myAdd(x, currentRoot->leftChild);
	}
	else if (x > currentRoot->element) {
		if (!currentRoot->rightChild) {
			int priorityValue = rand() % length;
			currentRoot->rightChild = new Node{ x, priorityValue, nullptr, nullptr, currentRoot };
			checkProperty(currentRoot);
		}
		else myAdd(x, currentRoot->rightChild);
	}
}

template <typename T>
void Stablo<T>::myDivide(T x, Node *currentRoot) {
	if (!currentRoot) {
		root = new Node{ x, length+1, nullptr, nullptr, nullptr };
	}
	else if (x < currentRoot->element) {
		if (!currentRoot->leftChild) {
			currentRoot->leftChild = new Node{ x, length+1, nullptr, nullptr, currentRoot };
			checkProperty(currentRoot);
		}
		else myDivide(x, currentRoot->leftChild);
	}
	else if (x > currentRoot->element) {
		if (!currentRoot->rightChild) {
			currentRoot->rightChild = new Node{ x, length+1, nullptr, nullptr, currentRoot };
			checkProperty(currentRoot);
		}
		else myDivide(x, currentRoot->rightChild);
	}
}

///// REMOVE /////

template <typename T>
void Stablo<T>::myRemove(T x, Node *&currentRoot) {
    if (!currentRoot) return;
    else if (x == currentRoot->element) {
        if (!currentRoot->leftChild && !currentRoot->rightChild) {
            delete currentRoot;
            currentRoot = nullptr;
        }
        else if (!currentRoot->leftChild ^ !currentRoot->rightChild) {
            Node *oldNode = currentRoot;
            currentRoot = (currentRoot->leftChild)?currentRoot->leftChild:currentRoot->rightChild;
            currentRoot->parent = oldNode->parent;
            delete oldNode;
        }
        else {
            T temp = findMin(currentRoot->rightChild);
            currentRoot->element = temp;
            myRemove(temp, currentRoot->rightChild);
        }
    }
    else if (x < currentRoot->element) myRemove(x, currentRoot->leftChild);
    else if (x > currentRoot->element) myRemove(x, currentRoot->rightChild);
}

///// PROPERTY CHECKS /////

template <typename T>
void Stablo<T>::checkProperty(Node *currentRoot) {
	if (!currentRoot) return;
	else if (currentRoot->leftChild && currentRoot->leftChild->priority > currentRoot->priority) {
		rotateRight(currentRoot);
		checkProperty(currentRoot->parent->parent);
	}
	else if (currentRoot->rightChild && currentRoot->rightChild->priority > currentRoot->priority) {
		rotateLeft(currentRoot);
		checkProperty(currentRoot->parent->parent);
	}
}

template <typename T>
void Stablo<T>::checkUnite(Node *currentRoot) {
    if (!currentRoot) return;
    else if (!currentRoot->leftChild && !currentRoot->rightChild) {
        Node *oldNode = currentRoot;
        if (currentRoot->parent->leftChild == currentRoot) currentRoot->parent->leftChild = nullptr;
        else currentRoot->parent->rightChild = nullptr;
        delete oldNode;
    }
	else if (currentRoot->leftChild && currentRoot->rightChild) {
        if (currentRoot->leftChild->priority > currentRoot->rightChild->priority) rotateRight(currentRoot);
        else rotateLeft(currentRoot);
        checkUnite(currentRoot);
	}
	else if (currentRoot->leftChild) {
        rotateRight(currentRoot);
        checkUnite(currentRoot);
	}
	else {
        rotateLeft(currentRoot);
        checkUnite(currentRoot);
	}
}

///// ROTATIONS /////

template <typename T>
void Stablo<T>::rotateRight(Node *currentRoot) {
	if (!currentRoot->leftChild->rightChild) {
		Node *tempNode = currentRoot->leftChild;
		tempNode->rightChild = currentRoot;
		tempNode->parent = currentRoot->parent;
		currentRoot->leftChild = nullptr;
		currentRoot->parent = tempNode;
		if (!tempNode->parent) root = tempNode;
		else if (tempNode->parent->element < tempNode->element) tempNode->parent->rightChild = tempNode;
		else tempNode->parent->leftChild = tempNode;
	}
	else {
		Node *tempNode = currentRoot->leftChild;
		currentRoot->leftChild = tempNode->rightChild;
		tempNode->rightChild->parent = currentRoot;
		tempNode->parent = currentRoot->parent;
		tempNode->rightChild = currentRoot;
		currentRoot->parent = tempNode;
		if (!tempNode->parent) root = tempNode;
		else if (tempNode->parent->element < tempNode->element) tempNode->parent->rightChild = tempNode;
		else tempNode->parent->leftChild = tempNode;
	}
}

template <typename T>
void Stablo<T>::rotateLeft(Node *currentRoot) {
	if (!currentRoot->rightChild->leftChild) {
		Node *tempNode = currentRoot->rightChild;
		tempNode->leftChild = currentRoot;
		tempNode->parent = currentRoot->parent;
		currentRoot->rightChild = nullptr;
		currentRoot->parent = tempNode;
		if (!tempNode->parent) root = tempNode;
		else if (tempNode->parent->element < tempNode->element) tempNode->parent->rightChild = tempNode;
		else tempNode->parent->leftChild = tempNode;
	}
	else {
		Node *tempNode = currentRoot->rightChild;
		currentRoot->rightChild = tempNode->leftChild;
		tempNode->leftChild->parent = currentRoot;
		tempNode->parent = currentRoot->parent;
		tempNode->leftChild = currentRoot;
		currentRoot->parent = tempNode;
		if (!tempNode->parent) root = tempNode;
		else if (tempNode->parent->element < tempNode->element) tempNode->parent->rightChild = tempNode;
		else tempNode->parent->leftChild = tempNode;
	}
}

///// SEARCHES /////

template <typename T>
T Stablo<T>::findMin(Node *currentRoot) const {
    if (!currentRoot->leftChild) return currentRoot->element;
    else findMin(currentRoot->leftChild);
}

template <typename T>
T Stablo<T>::findMax(Node *currentRoot) const {
    if (!currentRoot->rightChild) return currentRoot->element;
    else findMax(currentRoot->rightChild);
}

template <typename T>
bool Stablo<T>::myFind(T x, const Node *const&currentRoot) const {
    if (!currentRoot) return false;
    else if (x == currentRoot->element) return true;
    else if (x < currentRoot->element) myFind(x, currentRoot->leftChild);
    else myFind(x, currentRoot->rightChild);
}

///// OUTPUT /////

template <typename T>
void Stablo<T>::preOrder(Node *currentRoot, int d) const {
    if (currentRoot) {
        cout << setw(++d) << currentRoot->element << "(" << currentRoot->priority << ")" << endl;
        preOrder(currentRoot->leftChild, d);
        preOrder(currentRoot->rightChild, d);
    }
}

///// DIVIDE, UNITE AND UNION /////

template <typename T>
pair<Stablo<T>, Stablo<T>> Stablo<T>::myDivide(T x) {
	myDivide(x, root);
	pair<Stablo<T>, Stablo<T>> tempPair{ root->leftChild, root->rightChild };
	delete root;
	root = nullptr;
	return tempPair;
}

template <typename T>
Stablo<T> myUnite(Stablo<T> leftStablo, Stablo<T> rightStablo) {
    if (!leftStablo.root || !rightStablo.root) return (leftStablo.root)?leftStablo:rightStablo;
    T leftMax = leftStablo.findMax();
    T rightMin = rightStablo.findMin();
    T x = (leftMax+rightMin)/2;
    Stablo<T> newStablo(new typename Stablo<T>::Node{ x, -1, leftStablo.root, rightStablo.root, nullptr });
    newStablo.checkUnite(newStablo.root);
    return newStablo;
}

template <typename T>
Stablo<T> myUnion(Stablo<T> s1, Stablo<T> s2) {
	if (!s1.root || !s2.root) return myUnite(s1, s2);
	else if (s1.root->priority > s2.root->priority) {
		pair<Stablo<T>, Stablo<T>> tempPair = s2.myDivide(s1.root->element);
		Stablo<T> a = myUnion(Stablo<T> {s1.root->leftChild}, tempPair.first);
		Stablo<T> b = myUnion(Stablo<T> {s1.root->rightChild}, tempPair.second);
		Stablo<T> c(new typename Stablo<T>::Node{ s1.root->element, s1.root->priority, a.root, b.root, nullptr });
		if (a.root) a.root->parent = c.root;
		if (b.root) b.root->parent = c.root;
		return c;
	}
	else if (s1.root->priority <= s2.root->priority) {
		pair<Stablo<T>, Stablo<T>> tempPair = s1.myDivide(s2.root->element);
		Stablo<T> a = myUnion(Stablo<T> {s2.root->leftChild}, tempPair.first);
		Stablo<T> b = myUnion(Stablo<T> {s2.root->rightChild}, tempPair.second);
		Stablo<T> c(new typename Stablo<T>::Node{ s2.root->element, s2.root->priority, a.root, b.root, nullptr });
		if (a.root) a.root->parent = c.root;
		if (b.root) b.root->parent = c.root;
		return c;
	}
}
