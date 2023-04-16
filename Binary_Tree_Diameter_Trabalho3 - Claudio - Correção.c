#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int totalNodes = 0;

struct TreeNode *newNode(int val){
    struct TreeNode *node = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    node->val = val;   
    node->left = NULL;
    node->right = NULL;    

    return node;
}

int comp(int a, int b){
    return (a > b)? a : b;
}

int height(struct TreeNode *node){
    if (node == NULL){
        return 0;
    }

    int leftHeight = (height(node->left));
    int rightHeight = (height(node->right));

    return (comp(leftHeight, rightHeight) + 1);
}


int diameterOfBinaryTree(struct TreeNode *root){
    if (root == NULL){
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    int leftDiameter = diameterOfBinaryTree(root->left);
    int rightDiameter = diameterOfBinaryTree(root->right);

    return (comp(leftHeight + rightHeight, comp(leftDiameter, rightDiameter)));
}

struct TreeNode *insert(struct TreeNode *node, int val){

    if (val < -100 || val > 100){
        printf("Value out of acceptable range! (-100, 100)");
        return node;
    }

    if(node == NULL){
        totalNodes++;
        if(totalNodes < 0 || totalNodes > pow(10, 4)){
            printf("Number of nodes out of bounds! ");
            return node;
        }
        return newNode(val);
    }


    if(node->left == NULL){
        node->left = insert(node->left, val);
    } else if (node->left != NULL && node->right == NULL){
        node->right = insert(node->right, val);
    } else if (node->left != NULL && node->right != NULL){
        node->left = insert(node->left, val);
    }

    return node;
}

void freeBinaryTree(struct TreeNode *root){
    if (root == NULL){
        return;
    }

    freeBinaryTree(root->left);
    freeBinaryTree(root->right);

    free(root);
}

int main(){
    struct TreeNode *root = NULL;

    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 5);

    printf("Diameter: %d", diameterOfBinaryTree(root));
    
    freeBinaryTree(root);
    return 0; 
}