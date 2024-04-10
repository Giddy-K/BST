/* 
Author: Gideon Kipamet Kaiyian 
Student RegNo: SCT221-0255/2023
Author: Marylyne Nashipae Saoli 
Student RegNo: SCT221-0207/2023
*/
#include<stdio.h>
#include<stdlib.h>

// Define structure for binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to find index of value in inOrder array
int findIndex(int inOrder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inOrder[i] == value) {
            return i;
        }
    }
    return -1; // Value not found
}

// Function to construct BST from in-order and post-order traversals
struct Node* buildBST(int inOrder[], int postOrder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }
    
    // Create current node using postOrder array
    struct Node* node = newNode(postOrder[*postIndex]);
    (*postIndex)--;
    
    // If the node has no children, return it
    if (inStart == inEnd) {
        return node;
    }
    
    // Find index of current node in inOrder array
    int inIndex = findIndex(inOrder, inStart, inEnd, node->data);
    
    // Build right and left subtrees recursively
    node->right = buildBST(inOrder, postOrder, inIndex + 1, inEnd, postIndex);
    node->left = buildBST(inOrder, postOrder, inStart, inIndex - 1, postIndex);
    
    return node;
}

// Function to print nodes of BST in breadth-first search (DFS) traversal
void printBFS(struct Node* root) {
    if (root == NULL) {
        return;
    }
    
    // Create a queue for BFS
    struct Node* queue[100];
    int front = 0, rear = -1;
    
    queue[++rear] = root;
    
    while (front <= rear) {
        struct Node* temp = queue[front++];
        printf("%d ", temp->data);
        
        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }
        
        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }
}

// Function to construct BST from in-order and post-order traversals
struct Node* bst_construct(int inOrder[], int postOrder[], int size) {
    int postIndex = size - 1; // Start from end of post-order array
    return buildBST(inOrder, postOrder, 0, size - 1, &postIndex);
}

// Main function
int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int size = sizeof(inOrder) / sizeof(inOrder[0]);
    
    // Construct BST
    struct Node* root = bst_construct(inOrder, postOrder, size);
    
    // Print BST in BFS traversal
    printf("BFS traversal of constructed BST: ");
    printBFS(root);
    
    return 0;
}
