#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>
#define int long long
#define INF 1000000000000000000
using namespace std;

// AVL Tree
struct Node{
    int value;
    Node *left, *right, *parent;
    int height, size, sum, max;
    Node(int value){
        this->value = value;
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 1;
        size = 1;
        sum = value;
        max = value;
    }
};
unordered_map<int, Node*> node_map;
int height(Node* node) { 
    if (node == NULL) return 0; 
    return node->height; 
} 
int getSize(Node* node){
    if (node == NULL) return 0; 
    return node->size; 
}
int getSum(Node* node){
    if (node == NULL) return 0; 
    return node->sum; 
}
int getMax(Node* node){
    if (node == NULL) return 0; 
    return node->max; 
}
int dh(Node* node){
    if (node == NULL) return 0; 
    return height(node->left) - height(node->right); 
}
Node* rightRotate(Node* x){
    Node* y = x->left;
    Node* z = y->right;



    y->right = x;
    x->left = z;
    y->parent = x->parent;
    x->parent = y;
    if(z) z->parent = x;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    x->size = 1 + getSize(x->left) + getSize(x->right);
    y->size = 1 + getSize(y->left) + getSize(y->right);
    x->sum = x->value + getSum(x->left) + getSum(x->right);
    y->sum = y->value + getSum(y->left) + getSum(y->right);
    x->max = max(x->value, max(getMax(x->left), getMax(x->right)));
    y->max = max(y->value, max(getMax(y->left), getMax(y->right)));
    return y;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* z = y->left;

    x->right = z;

    y->left = x;
    
    y->parent = x->parent;
    x->parent = y;
    if(z) z->parent = x;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    x->size = 1 + getSize(x->left) + getSize(x->right);
    y->size = 1 + getSize(y->left) + getSize(y->right);
    x->sum = x->value + getSum(x->left) + getSum(x->right);
    y->sum = y->value + getSum(y->left) + getSum(y->right);
    x->max = max(x->value, max(getMax(x->left), getMax(x->right)));
    y->max = max(y->value, max(getMax(y->left), getMax(y->right)));
    return y;
}


Node* Insert(Node* node, int k, int value){
    if(node == NULL){
        node_map[value] = new Node(value);
        return node_map[value];
    }

    if(k <= getSize(node->left) + 1){
        node->left = Insert(node->left, k, value);
        node->left->parent = node;
    }else{
        node->right = Insert(node->right, k - getSize(node->left) - 1, value);
        node->right->parent = node;
    }

    node->height = 1 + max(height(node->left), height(node->right)); 
    node->size = 1 + getSize(node->left) + getSize(node->right);
    node->sum = node->value + getSum(node->left) + getSum(node->right);
    node->max = max(node->value, max(getMax(node->left), getMax(node->right)));
    int balance = dh(node); 

    if(balance > 1 && k <= getSize(node->left->left) + 1){
        return rightRotate(node);
    }
    else if(balance > 1 && k > getSize(node->left->left) + 1){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    else if(balance < -1 && k > getSize(node->right->left) + 1){
        return leftRotate(node);
    }
    else if(balance < -1 && k <= getSize(node->right->left) + 1){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node; 
}
Node * successor(Node* node) {
    Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}
Node* Remove(Node* node, int k) {
    if(node == NULL) return node;
    
    if(k < getSize(node->left) + 1){
        node->left = Remove(node->left, k);
        if(node->left) node->left->parent = node;
    }else if(k > getSize(node->left) + 1){
        node->right = Remove(node->right, k - getSize(node->left) - 1);
        if(node->right) node->right->parent = node;
    }
    else {
        
        if ((node->left == NULL) || (node->right == NULL)) {
            Node *temp = node->left ? node->left : node->right;
            
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else{
                
                Node* pp = node->parent;
                *node = *temp; 
                node->parent = pp;
                node_map[node->value] = node;
            } 
            free(temp);
            
        } else {
            Node* temp = successor(node->right);
            node->value = temp->value;
            node_map[node->value] = node;
            node->right = Remove(node->right, 1);
        }
    }

    if (node == NULL)
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    node->size = 1 + getSize(node->left) + getSize(node->right);

    node->sum = node->value + getSum(node->left) + getSum(node->right);
    node->max = max(node->value, max(getMax(node->left), getMax(node->right)));

    int balance = dh(node);
    if (balance > 1 && dh(node->left) >= 0){
        return rightRotate(node);
    }
        

    if (balance > 1 && dh(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && dh(node->right) <= 0){
        return leftRotate(node);
    }
        

    if (balance < -1 && dh(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int FindKth(Node* node, int k){
    

    if(k <= getSize(node->left)){
        return FindKth(node->left, k);
    }
    if(k == getSize(node->left) + 1){
        return node->value;
    }
    return FindKth(node->right, k - getSize(node->left) - 1);
}
int Sum(Node* node, int l, int r, int k1, int k2){
    if(node == NULL) return 0;
    if(k1 > k2) return 0;
    if (l == k1 && r == k2) {
        return getSum(node);
    }
    int m = getSize(node->left) + 1;
    int middle = 0;
    if(k1 <= m && m <= k2) middle = node->value;
    return Sum(node->left, l, m - 1, k1, min(k2, m - 1)) + Sum(node->right, m + 1 - getSize(node->left) - 1, r - getSize(node->left) - 1, max(k1, m + 1) - getSize(node->left) - 1, k2 - getSize(node->left) - 1) + middle;
}
int Max(Node* node, int l, int r, int k1, int k2){
    if(node == NULL) return -INF;
    if(k1 > k2) return -INF;
    if (l == k1 && r == k2) {
        return getMax(node);
    }
    int m = getSize(node->left) + 1;
    int middle = 0;
    if(k1 <= m && m <= k2) middle = node->value;
    return max(Max(node->left, l, m - 1, k1, min(k2, m - 1)), max(Max(node->right, m + 1 - getSize(node->left) - 1, r - getSize(node->left) - 1, max(k1, m + 1) - getSize(node->left) - 1, k2 - getSize(node->left) - 1), middle));
}

Node* head = NULL;
int ans = 0;
void Index(Node* node, Node* child){
    if(node == NULL) return;
    Index(node->parent, node);
    if(node->right == child || child == NULL) ans += getSize(node->left) + 1;
}
signed main(){

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto& i : a) cin >> i;
    for(auto i : a){
        if(head == NULL){
            node_map[i] = new Node(i);
            head = node_map[i];
        } 
        else head = Insert(head, getSize(head) + 1, i);
    }

    while (m--)
    {
        int op, x;
        cin >> op >> x;
        if (op == 1)
        {
            int k;
            cin >> k;
            if(head == NULL){
                node_map[k] = new Node(k);
                head = node_map[k];
            } 
            else head = Insert(head, x, k);
        }
        else if (op == 2)
        {
            head = Remove(head, x);
        }
        else if (op == 3)
        {
            cout << FindKth(head, x) << endl;
        }
        else if (op == 4)
        {
            ans = 0;

            Index(node_map[x], NULL);
            cout << ans << endl;
        }
        else if(op == 5)
        {
            int k;
            cin >> k;
            cout << Sum(head, 1, getSize(head), x, k) << endl;
        }else{
            int k;
            cin >> k;
            cout << Max(head, 1, getSize(head), x, k) << endl;
        }
        
    }
    
}
