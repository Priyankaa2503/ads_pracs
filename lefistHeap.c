#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in a Leftist Heap
struct LeftistNode
{
    int key;                   // Key of the node
    int rank;                  // Rank of the node
    struct LeftistNode *left;  // Pointer to the left child node
    struct LeftistNode *right; // Pointer to the right child node
};

// Function to create a new Leftist node
struct LeftistNode *createLeftistNode(int key)
{
    // Allocate memory for a new node
    struct LeftistNode *newNode = (struct LeftistNode *)malloc(sizeof(struct LeftistNode));
    // If memory allocation is successful, initialize the new node
    if (newNode != NULL)
    {
        newNode->key = key;
        newNode->rank = 0;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    // Return the new node
    return newNode;
}

// Function to merge two Leftist Heaps
struct LeftistNode *mergeLeftistHeaps(struct LeftistNode *heap1, struct LeftistNode *heap2)
{
    // If one of the heaps is empty, return the other heap
    if (heap1 == NULL)
    {
        return heap2;
    }
    if (heap2 == NULL)
    {
        return heap1;
    }

    // heap1's root has a higher key
    if (heap1->key > heap2->key)
    {
        // Swap heap1 and heap2
        struct LeftistNode *temp = heap1;
        heap1 = heap2;
        heap2 = temp;
    }

    // Recursively merge the right subtree of heap1 with heap2
    heap1->right = mergeLeftistHeaps(heap1->right, heap2);

    // Update ranks to maintain leftist property
    if (heap1->left == NULL || (heap1->right != NULL && heap1->left->rank < heap1->right->rank))
    {
        // Swap the left and right children of heap1
        struct LeftistNode *temp = heap1->left;
        heap1->left = heap1->right;
        heap1->right = temp;
    }

    // Update the rank of heap1
    if (heap1->right == NULL)
    {
        heap1->rank = 0;
    }
    else
    {
        heap1->rank = heap1->right->rank + 1;
    }

    // Return the merged heap
    return heap1;
}

// Function to display the Leftist Heap
void displayLeftistHeap(struct LeftistNode *root)
{
    // If the heap is empty, return
    if (root == NULL)
    {
        return;
    }

    // Print the key of the root node
    printf("%d ", root->key);
    // Recursively display the left and right subtrees
    displayLeftistHeap(root->left);
    displayLeftistHeap(root->right);
}

// Example usage
int main()
{
    // Create two heaps
    struct LeftistNode *heap1 = createLeftistNode(3);
    heap1->left = createLeftistNode(10);
    heap1->right = createLeftistNode(8);

    struct LeftistNode *heap2 = createLeftistNode(6);
    heap2->left = createLeftistNode(7);
    heap2->right = createLeftistNode(5);

    // Display the heaps
    printf("Heap 1: ");
    displayLeftistHeap(heap1);
    printf("\n");

    printf("Heap 2: ");
    displayLeftistHeap(heap2);
    printf("\n");

    // Merge the heaps
    struct LeftistNode *mergedHeap = mergeLeftistHeaps(heap1, heap2);

    // Display the merged heap
    printf("Merged Heap: ");
    displayLeftistHeap(mergedHeap);
    printf("\n");

    return 0;
}