#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int key);
Node *insert(Node *node, int key);
Node *rotateRight(Node *y);
Node *rotateLeft(Node *x);
int height(Node *num);
int comp(int a, int b);
int treeBalance(Node *node);
void order(Node *root);

int main(){
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    order(root);

    return 0;
}

Node *newNode(int key){
    Node *node = (Node*)malloc(sizeof(Node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

int height(Node *num){
    if (num == NULL){
        return 0;
    }
    return num->height;
}

int comp(int a, int b){
    return (a > b)? a : b;
}

int treeBalance(Node *node){
    if (node == NULL){
        return 0;
    }

    return (node->left - node->right);
}

Node *rotateRight(Node *y){
    Node *x = y->left;
    Node *temp = y->right;

    x->right = y;
    y->left = temp;

    x->height = 1 + comp(height(x->left), height(x->right));
    y->height = 1 + comp(height(y->left), height(y->right));

    return x;
}

Node *rotateLeft(Node *x){
    Node *y = x->right;
    Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + comp(height(x->left), height(x->right));
    y->height = 1 + comp(height(y->left), height(y->right));

    return y;
}

Node *insert(Node *node, int key){

    if (node == NULL){
        return newNode(key);
    }

    if (key < node->key){
        node->left = insert(node->left, key);
    } else if (key > node->key){
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + comp(height(node->left), height(node->right));

    int balance = treeBalance(node);
    if (balance > 1 && key < node->left->key ){
        return rotateRight(node);
    } 

    if (balance < -1 && key > node->right->key){
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->key){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < 1 && key < node->right->key){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void order(Node *root){
    if (root != NULL){
        printf("%d ", root->key);
        order(root->left);
        order(root->right);
    }
}
