#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};
NODE* createNode(int data);

void NLR_recursive(NODE* pRoot,vector<int>& res);
vector<int> NLR(NODE* pRoot);
vector<int> LNR(NODE* pRoot);
vector<int> LRN(NODE* pRoot);
vector< vector<int> > LevelOrder(NODE* pRoot);
int countNode(NODE* pRoot);
int sumNode(NODE* pRoot);
NODE* findNode(NODE* root, int value);
int height(NODE* root);
int heightNode(NODE* pRoot, int value);
int Level(NODE* pRoot,NODE* p);
int countLeaf(NODE* pRoot);
/*
int main() {
    // Sample Tree:
    //        10
    //       /  \
    //      5   20
    //     / \    \
    //    3   7   30

    NODE* root = createNode(10);
    root->p_left = createNode(5);
    root->p_right = createNode(20);
    root->p_left->p_left = createNode(3);
    root->p_left->p_right = createNode(7);
    root->p_right->p_right = createNode(30);

    // Preorder (NLR)
    vector<int> nlr = NLR(root);
    cout << "Preorder (NLR): ";
    for (int val : nlr) cout << val << " ";
    cout << endl;

    // Inorder (LNR)
    vector<int> lnr = LNR(root);
    cout << "Inorder (LNR): ";
    for (int val : lnr) cout << val << " ";
    cout << endl;

    // Postorder (LRN)
    vector<int> lrn = LRN(root);
    cout << "Postorder (LRN): ";
    for (int val : lrn) cout << val << " ";
    cout << endl;

    // Level-order
    vector< vector<int> > levels = LevelOrder(root);
    cout << "Level Order Traversal:" << endl;
    for (const auto& level : levels) {
        for (int val : level) cout << val << " ";
        cout << endl;
    }

    // Count nodes
    cout << "Total nodes: " << countNode(root) << endl;

    // Sum of all node values
    cout << "Sum of all nodes: " << sumNode(root) << endl;

    // Find a node
    int findVal = 7;
    NODE* found = findNode(root, findVal);
    cout << "Node " << findVal << (found ? " found." : " not found.") << endl;

    // Height of tree
    cout << "Height of tree: " << height(root) << endl;

    // Height of node with value
    cout << "Height of node " << findVal << ": " << heightNode(root, findVal) << endl;

    // Level of node
    cout << "Level of node " << findVal << ": " << Level(root, found) << endl;

    // Count leaf nodes
    cout << "Number of leaf nodes: " << countLeaf(root) << endl;

    return 0;
}
*/
NODE* createNode(int data){
    NODE* node = new NODE;
    node->key = data;
    node->p_left = nullptr;
    node->p_right = nullptr;
    return node;
}
void NLR_recursive(NODE* pRoot,vector<int>& res){
    if(!pRoot) return;
    res.push_back(pRoot->key);
    NLR_recursive(pRoot->p_left,res);
    NLR_recursive(pRoot->p_right,res);
}
vector<int> NLR(NODE* pRoot){
    vector<int> a;
    NLR_recursive(pRoot,a);
    return a;
}
vector<int> LNR(NODE* pRoot) {
    if(!pRoot) return vector<int>();
    // Phuong Phap Morris
    vector<int> res;
    NODE* cur = pRoot;
    while ( cur != nullptr ) {
        if(cur -> p_left == nullptr) {
            res.push_back(cur -> key);
            cur = cur -> p_right;
        }
        else {
            // Find inorder predecessor
            NODE* predecessor = cur->p_left;
            while (predecessor->p_right != nullptr && predecessor->p_right != cur) {
                predecessor = predecessor->p_right;
            }

            if (predecessor->p_right == nullptr) {
                predecessor -> p_right = cur;
                cur = cur -> p_left;
            }
            else {
                predecessor->p_right = nullptr;
                res.push_back(cur->key);
                cur = cur -> p_right;
            }
        }
    }
    return res;
}

vector<int> LRN(NODE* pRoot) {
    if(!pRoot) return vector<int>();
    vector <int> ans;
    stack<NODE*> s1,s2;
    s1.push(pRoot);
    while(!s1.empty()){
        NODE* cur = s1.top(); s1.pop();
        s2.push(cur);
        if (cur->p_left) {
            s1.push(cur->p_left);
        }
        if (cur->p_right) {
            s1.push(cur->p_right);
        }
    }

    while (!s2.empty()) {
        ans.push_back(s2.top()->key);
        s2.pop();
    }
    return ans;
}

vector< vector<int> > LevelOrder(NODE* pRoot) {
    if(!pRoot) return vector< vector<int> >();
    vector< vector<int> > result;
    queue<NODE*> q;
    q.push(pRoot);
    while(!q.empty()) {
        int size = q.size();
        vector<int> level;
        for(int i = 0; i < size; i++) {
            NODE* cur = q.front(); q.pop();
            level.push_back(cur->key);
            if(cur->p_left) q.push(cur->p_left);
            if(cur->p_right) q.push(cur->p_right);
        }
        result.push_back(level);
    }
    return result;
}

int countNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot -> p_right);    
}

int sumNode(NODE* pRoot) {
    if (!pRoot) return 0 ;
    return pRoot->key + sumNode(pRoot->p_right) + sumNode(pRoot->p_left);
}

NODE* findNode(NODE* root, int value) {
    if (!root) return nullptr;
    if (root->key == value) return root;

    NODE* leftSearch = findNode(root->p_left, value);
    if (leftSearch) return leftSearch;

    return findNode(root->p_right, value);
}

int height(NODE* root) {
    if (!root) return -1;
    return 1 + max(height(root->p_left), height(root->p_right));
}

int heightNode(NODE* pRoot, int value) {
    NODE* target = findNode(pRoot, value);
    if (!target) return -1;
    return height(target);
}
int Level(NODE* pRoot, NODE* p) {
    if(!pRoot||!p) return 0;
    queue<NODE*> q;
    q.push(pRoot);
    int level = 0;
    while(!q.empty()) {
        int size = q.size();
        for ( int i = 0; i < size; i++) {
            NODE* cur = q.front(); q.pop();
            if(cur == p) {
                return level;
            }
            if(cur->p_left) q.push(cur->p_left);
            if(cur->p_right) q.push(cur->p_right);
        }
        level++;
    }
    return -1; 
}
int countLeaf(NODE* pRoot) {
    if (!pRoot) return 0;
    int count = 0;
    queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        NODE* curr = q.front(); q.pop();

        if (!curr->p_left && !curr->p_right)
            count++;

        if (curr->p_left) q.push(curr->p_left);
        if (curr->p_right) q.push(curr->p_right);
    }

    return count;
}