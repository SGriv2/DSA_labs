#pragma once
#include <vector>
#include <list>
#include <cmath>


typedef long long int lli;
#define GOLDEN_RATIO_ROUND_DOWN 1.618

template<typename T, typename V> class FibonacciHeap;

template<typename T, typename V>
class Node {
protected:
    Node<T, V> *left = this;
    Node<T, V> *right = this;
    Node<T, V> *parent = nullptr;
    Node<T, V> *child = nullptr;

	T key;
	V value;
    lli degree = 0;
    bool mark = false;

public:
    Node(T key, V value) : key(key), value(value) {};
    Node(Node<T, V> *other) : key(other->key), value(other->value), degree(other->degree), mark(other->mark) {
        this->left = other->left;
        this->right = other->right;
        this->parent = other->parent;
        this->child = other->child;
    }

    T getKey() { return this->key; }
	V getValue() { return this->value; }
    Node<T, V> *getLeft() { return this->left; }
    Node<T, V> *getRight() { return this->right; }
    Node<T, V> *getChild() { return this->child; }
    Node<T, V> *getParent() { return this->parent; }
    bool isMarked() { return this->mark; }
    lli getDegree() { return this->degree; }

    friend class FibonacciHeap<T, V>;
};

template<typename T, typename V>
class FibonacciHeap
{
	protected:
	    Node<T, V> *minNode;
		int nodeCount;

		void FibHeapLinkLists(FibonacciHeap<T, V> *other) {
			if (other == nullptr) {
				return;
			}

			auto left1 = minNode->left;
			auto left2 = other->minNode->left;
			left1->right = other->minNode;
			other->minNode->left = left1;
			minNode->left = left2;
			left2->right = minNode;
		}

		void FibHeapAddNodeToRootList(Node<T, V> *node) {
			if (minNode == nullptr) {
				return;
			}
			if (minNode->left == minNode) {
				minNode->left = node;
                minNode->right = node;
                node->left = minNode;
                node->right = minNode;
			} else {
				Node<T, V> *temp = minNode->left; // operator =
                minNode->left = node;
                node->right = minNode;
                node->left = temp;
                temp->right = node;
			}
		}

		int D() {
			return (int) std::log2(nodeCount) + 1;
		}

	public:
	    void FibHeapInsert(T key, V value) {
			Node<T, V> *newNode = new Node<T, V>(key, value);

			FibHeapAddNodeToRootList(newNode);
			if (minNode == nullptr || newNode->key < minNode->key) {
				minNode = newNode;
			}
			nodeCount++;
		}

		Node<T, V> *FibHeapMin() {
			return minNode;
		}

		void FibHeapUnion(FibonacciHeap<T, V> *other) {
			Node<T, V> *newmin = minNode;
			FibHeapLinkLists(other);
			if ((minNode == nullptr) || (other->minNode != nullptr && other->minNode->key < newmin->key)) {
				newmin = other->minNode;
			}

			nodeCount += other->nodeCount;
			minNode = newmin;
		}

		void FibHeapDeleteMin() {
			Node<T, V> *z = minNode;
			if(z == nullptr) {
				return;
			}
			Node<T, V>* x;
			for(int i = 0; i < z->child->degree; i++) {
				x = &z->child[i];
				FibHeapAddNodeToRootList(x);
				x->parent = nullptr;
			}
			z->left->right = z->right;
        	z->right->left = z->left;
			if( z == z->right) {
				minNode = nullptr;
			} else {
				minNode = z->right;
				FibHeapConsolidate();
			}
			
			nodeCount--;
		}

		void FibHeapConsolidate() {
			int D_ = D();
			Node<T, V>* A[D_] = {nullptr};
			Node<T, V>* x;
			int d;
			Node<T, V>* y;

			for(int i = 0; i < minNode->degree; i++) {
				*x = minNode[i];
                d = x->degree;
                while(A[d]!= nullptr) {
                    y = A[d];
                    if(x->key > y->key) {
                        FibHeapSwap(x, y);
                    }
                    FibHeapLink(y, x);
                    A[d] = nullptr;
                    d++;
                }
                A[d] = x;
			}

			minNode = nullptr;
			for(int i = 0; i < D_; i++) {
				if (A[i] != nullptr) {
					FibHeapAddNodeToRootList(A[i]);
					if(minNode == nullptr || A[i]->key < minNode->key) {
                        minNode = A[i];
                    }
				}
			}
		}

		void FibHeapSwap(Node<T, V>* &x, Node<T, V>* &y) {
            Node<T, V>* temp = x;
            x = y;
            y = temp;
        }

		void FibHeapLink(Node<T, V>* &y, Node<T, V>* &x) {
			y->left->right = y->right;
        	y->right->left = y->left;

        	if (x->child == nullptr) {
            	x->child = y;
            	y->right = y;
            	y->left = y;
        	} else {
            	Node<T, V> *child = x->child;
            	y->right = child;
            	y->left = child->left;
            	child->left->right = y;
            	child->left = y;
        	}

        	y->parent = x;
        	x->degree++;
        	y->mark = false;
		}

		void FibHeapDecreaseKey(Node<T, V>* x, T newkey) {
			if (newkey > x.key) {
				return;
			}
			x.key = newkey;
			auto y = x->parent;
			if(y != nullptr && x.key < y.key) {
				FibHeapCut(x, y);
				FibHeapCascadingCut(y);
			}
			if(x.key < minNode.key) {
				minNode = x;
			}
		}

		void FibHeapCut(Node<T, V> *x, Node<T, V> *y) {
			FibHeapRemoveNodeFromRootList(x, y);
			y.degree--;
			FibHeapAddNodeToRootList(x);
			x.parent = nullptr;
			x.mark = false;
		}

		void FibHeapRemoveNodeFromRootList(Node<T, V> *x, Node<T, V> *y) {
			x->left->right = x->right;
        	x->right->left = x->left;

        	if (y->child == x) {
            	if (x->right == x) {
                	y->child = nullptr;
            	} else {
                	y->child = x->right;
            	}
        	}
		}


		void FibHeapCascadingCut(Node<T, V> *y) {
			auto z = y->parent;
			if(z != nullptr) {
				return;
			}
			if(y->mark == false) {
				y->mark = true;
			} else {
				FibHeapCut(y, z);
                FibHeapCascadingCut(z);
			}
		}

		void FibHeapDelete(Node<T, V>* x) {
			FibHeapDecreaseKey(x, std::numeric_limits<T>::min());
            FibHeapDeleteMin();
		}
};