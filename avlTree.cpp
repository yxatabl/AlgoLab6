#include <iostream>

using namespace std;

class avlTree{
    struct Node{
        long long key;
        int height;
        Node* left;
        Node* right;

        Node(long long data){
            key = data;
            left = right = nullptr;
            height = 1;
        }
    };

    Node* root;

    avlTree(){
        root = nullptr;
    }

    int height(Node* p){
        return p ? p->height : 0;
    }

    int balanceFactor(Node* p){
        return height(p->right)-height(p->left);
    }

    void fixHeight(Node* p){
        int hl = height(p->left);
        int hr = height(p->right);
        p->height = hl > hr ? hl : hr;
    }

    Node* rotateRight(Node* p){
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }

    Node* rotateLeft(Node* q){
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixHeight(q);
        fixHeight(p);
        return p;
    }

    Node* balance(Node* p){
        fixHeight(p);
        if (balanceFactor(p) == 2){
            if (balanceFactor(p->right) < 0){
                p->right = rotateRight(p->right);
            }
            return rotateLeft(p);
        }

        if (balanceFactor(p) == -2){
            if (balanceFactor(p->left) > 0){
                p->left = rotateLeft(p->left);
            }
            return rotateRight(p);
        }
        return p;
    }

    Node* insert(Node* p, long long k){
        if (!p) return new Node(k);

        if (k < p->key){
            p->left = insert(p->left, k);
        } else {
            p->right = insert(p->right, k);
        }

        return balance(p);
    }

    Node* findMin(Node* p){
        return p->left ? findMin(p->left) : p;
    }

    Node* removeMin(Node* p){
        if (p->left == nullptr) return p->right;
        p->left = removeMin(p->left);
        return balance(p);
    }

    Node* remove(Node* p, long long k){
        if (!p) return nullptr;

        if (k < p->key) p->left = remove(p->left, k);
        else if (k > p->key) p->right = remove(p->right, k);
        else {
            Node* q = p->left;
            Node* r = p->right;
            delete p;
            if (!r) return q;
            Node* min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }

        return balance(p);
    }
};