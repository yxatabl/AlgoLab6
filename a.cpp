#include <iostream>

using namespace std;

struct Node{
    long long key;
    Node* left;
    Node* right;

    Node(long long num){
        key = num;
        left = right = nullptr;
    }
};

int height(Node* nd){
    if (nd == nullptr) return 0;
    else {
        int hl = 0;
        int hr = 0;
        if (nd->left != nullptr) hl = height(nd->left);
        if (nd->right != nullptr) hr = height(nd->right);
        return hl > hr ? hl+1 : hr+1;
    }
};

int main(){
    int n;
    cin >> n;

    Node* list[n];
    for (int i = 0; i < n; i++) list[i] = new Node(0);

    long long k, l, r;
    for (int i = 0; i < n; i++){
        cin >> k >> l >> r;
        list[i]->key = k;
        if (l > 0) list[i]->left = list[l-1];
        if (r > 0) list[i]->right = list[r-1];
    }

    for (int i = 0; i < n; i++){
        int balance = height(list[i]->right) - height(list[i]->left);
        cout << balance << "\n";
    }
}