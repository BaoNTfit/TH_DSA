#include<iostream>
#include<stack>
using namespace std;
struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};
//Reuse 

NODE* findNode(NODE* root, int value);
NODE* createNode(int data);

//Exercise
NODE* Search(NODE* pRoot, int x);
void Insert(NODE* &pRoot, int x);
void Remove(NODE* &pRoot, int x);
NODE* createTree(int a[], int n);
void removeTree(NODE* &pRoot);
int Height(NODE* pRoot);
int countLess(NODE* pRoot, int x);
int countGreater(NODE* pRoot, int x);
bool isBST(NODE* pRoot);
bool isFullBST(NODE* pRoot);
void test(NODE* root) {
    if (!root) return;
    test(root->p_left);
    cout << root->key << " ";
    test(root->p_right);
}
/*
int main() {
    int a[] = {15, 10, 20, 8, 12, 17, 25};
    int n = sizeof(a) / sizeof(a[0]);

    NODE* root = createTree(a, n);

    cout << "Height: " << Height(root) << endl;

    cout << "Search 12: " << (Search(root, 12) != nullptr ? "Found" : "Not Found") << endl;

    cout << "Count less than 18: " << countLess(root, 18) << endl;
    cout << "Count greater than 18: " << countGreater(root, 18) << endl;

    cout << "Is BST: " << (isBST(root) ? "Yes" : "No") << endl;
    cout << "Is Full BST: " << (isFullBST(root) ? "Yes" : "No") << endl;

    cout << "Inserting 11...\n";
    Insert(root, 11);
    test(root); cout << endl;
    cout << "Search 11: " << (Search(root, 11) != nullptr ? "Found" : "Not Found") << endl;

    cout << "Removing 10...\n";
    Remove(root, 10);
    test(root); cout << endl;
    cout << "Search 10: " << (Search(root, 10) != nullptr ? "Found" : "Not Found") << endl;

    cout << "Removing tree...\n";
    removeTree(root);
    cout << "Tree is now " << (root == nullptr ? "empty." : "not empty!") << endl;

    return 0;
}
*/
NODE* findNode(NODE* root, int value) {
    if (!root) return nullptr;
    if (root->key == value) return root;

    NODE* leftSearch = findNode(root->p_left, value);
    if (leftSearch) return leftSearch;

    return findNode(root->p_right, value);
}

NODE* createNode(int data){
    NODE* node = new NODE;
    node->key = data;
    node->p_left = nullptr;
    node->p_right = nullptr;
    return node;
}

NODE* Search(NODE* pRoot, int x){
    if (!pRoot) return nullptr;
    if (pRoot->key == x) return pRoot;

    if (x < pRoot->key) return Search(pRoot->p_left, x);
    else return Search(pRoot->p_right, x);
}
void Insert(NODE* &pRoot, int x){
    if(!pRoot) {
        pRoot = createNode(x);
        return;
    }
    if(x < pRoot->key) {
        Insert(pRoot->p_left,x);
    }
    if(x > pRoot->key) {
        Insert(pRoot->p_right, x);
    }
    // Recursive
}

NODE* findMin(NODE* pRoot) {
    while (pRoot->p_left) {
        pRoot = pRoot->p_left;
    }
    return pRoot;
}
void Remove(NODE* &pRoot, int x){
    if(!pRoot) return;
    if(x < pRoot->key) Remove(pRoot->p_left,x);
    else if ( x > pRoot->key ) Remove(pRoot ->p_right ,x);
    else {
        // Leaf 
        if(!pRoot->p_left && !pRoot->p_right) {
            delete pRoot;
            pRoot = nullptr;
        }
        else if(!pRoot->p_left) {
            NODE* temp = pRoot;
            pRoot = pRoot ->p_right;
            delete temp;
        }
        else if(!pRoot->p_right) {
            NODE* temp = pRoot;
            pRoot = pRoot ->p_left;
            delete temp;
        } else {
            NODE* min = findMin(pRoot->p_right);
            pRoot -> key = min->key;
            Remove(pRoot->p_right, min->key);
        }
    }
}

NODE* createTree(int a[], int n){
    if (n == 0) return nullptr;
    NODE* pRoot = createNode(a[0]);
    for(int i = 1; i < n; i ++) {
        Insert(pRoot,a[i]);
    }
    return pRoot;
}

void removeTree(NODE* &pRoot){
    if (!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE* pRoot){
    if(!pRoot) return 0;
    return 1 + max(Height(pRoot->p_left),Height(pRoot->p_right));
}

int countLess(NODE* pRoot, int x){
    if (!pRoot) return 0;
    if (pRoot->key < x) {
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    } else {
        return countLess(pRoot->p_left, x);
    } 
}

int countGreater(NODE* pRoot, int x) {
    if(!pRoot) return 0;
    if (pRoot->key > x) {
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    } else {
        return countGreater(pRoot->p_right, x);
    } 
}

bool isBST(NODE* pRoot) {
    NODE* cur = pRoot;
    NODE* prev = nullptr;

    while (cur) {
        if (!cur->p_left) {
            if (prev && prev->key >= cur->key)
                return false;

            prev = cur;
            cur = cur->p_right;
        } else {
            NODE* pre = cur->p_left;
            while (pre->p_right && pre->p_right != cur)
                pre = pre->p_right;

            if (!pre->p_right) {
                pre->p_right = cur;
                cur = cur->p_left;
            } else {
                pre->p_right = nullptr;

                if (prev && prev->key >= cur->key)
                    return false;

                prev = cur;
                cur = cur->p_right;
            }
        }
    }

    return true;
}
bool isFullBST(NODE* pRoot) {
    if (!pRoot) return true;

    stack<NODE*> st;
    NODE* cur = pRoot;
    NODE* prev = nullptr;
    int lastValue = INT_MIN;
    bool first = true;

    while (!st.empty() || cur) {
        while (cur) {
            if ((cur->p_left == nullptr && cur->p_right != nullptr) ||
                (cur->p_left != nullptr && cur->p_right == nullptr)) {
                return false;
            }
            st.push(cur);
            cur = cur->p_left;
        }

        cur = st.top();
        st.pop();

        if (!first && cur->key <= lastValue)
            return false;

        lastValue = cur->key;
        first = false;

        cur = cur->p_right;
    }

    return true;
}
