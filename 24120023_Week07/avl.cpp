#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};
NODE* createNode(int data);
void Insert(NODE* &pRoot, int x);
void Remove(NODE* &pRoot, int x);
bool isAVL(NODE* pRoot);
/*
void test(NODE* root) {
    if (!root) return;
    test(root->p_left);
    cout << root->key << " ";
    test(root->p_right);
}
int main() {
    NODE* root = nullptr;

    // Insert nodes
    vector<int> values = {10, 20, 30, 10, 25, 50, 5};
    for (int x : values) {
        Insert(root, x);
        cout << "Inserted " << x << ". Is AVL: " << (isAVL(root) ? "Yes" : "No") << endl;
    }

    // Inorder Traversal (should be sorted if BST)
    cout << "\nInorder traversal of AVL tree: ";
    test(root);
    cout << endl;

    // Remove a node
    cout << "\nRemoving 20..." << endl;
    Remove(root, 20);
    cout << "After removing 20, inorder: ";
    test(root);
    cout << "\nIs AVL: " << (isAVL(root) ? "Yes" : "No") << endl;

    // Remove a leaf node
    cout << "\nRemoving 5..." << endl;
    Remove(root, 5);
    cout << "After removing 5, inorder: ";
    test(root);
    cout << "\nIs AVL: " << (isAVL(root) ? "Yes" : "No") << endl;

    return 0;
}
*/
NODE* createNode(int data) {
    NODE* node = new NODE;
    node->key = data;
    node->p_left = nullptr;
    node->p_right = nullptr;
    node->height = 1; 
    return node;
}

int getHeight(NODE* node) {
    if (node == NULL) return 0;
        return node->height;
}
int getBalance(NODE* node) {
    if (node == nullptr)
        return 0;

    int left , right ;

    if (node->p_left == nullptr)
        left = 0;
    else
        left = node->p_left->height;

    if (node->p_right == nullptr)
        right = 0;
    else
        right = node->p_right->height ;

    return left  - right ;
}

void updateHeight(NODE* node) {
    int left , right ;

    if (node->p_left == nullptr)
        left = 0;
    else
        left = node->p_left->height;

    if (node->p_right == nullptr)
        right = 0;
    else
        right = node->p_right->height;

    node->height = 1 + (left > right ? left : right);
}

NODE* rotateRight(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;

    x->p_right = y;
    y->p_left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

NODE* rotateLeft(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;

    y->p_left = x;
    x->p_right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}
void Insert(NODE* &pRoot, int x) {
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return; // check for duplicate

    updateHeight(pRoot);

    int balance = getBalance(pRoot);

    // LL
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rotateRight(pRoot);
    // RR
    else if (balance < -1 && x > pRoot->p_right->key)
        pRoot = rotateLeft(pRoot);
    // LR
    else if (balance > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    // RL
    else if (balance < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}
void removeTree(NODE* &pRoot){
    if (!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}
bool isAVL(NODE* root) {
    if (!root) return true;

    int balance = getBalance(root);
    if (balance < -1 || balance > 1)
        return false;

    return isAVL(root->p_left) && isAVL(root->p_right);
}
NODE* minValueNode(NODE* node) {
    NODE* cur = node;
    while (cur && cur->p_left)
        cur = cur->p_left;
    return cur;
}

void Remove(NODE* &pRoot, int x) {
    if (!pRoot) return;

    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            
            if (!temp) {
                temp = pRoot;
                pRoot = nullptr;
            } else *pRoot = *temp;
            delete temp;
        } else {
            NODE* temp = minValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }

    if (!pRoot) return;
    updateHeight(pRoot);
    int balance = getBalance(pRoot);

    // LL
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        pRoot = rotateRight(pRoot);
    // LR
    else if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    // RR
    else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        pRoot = rotateLeft(pRoot);
    // RL
    else if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}
