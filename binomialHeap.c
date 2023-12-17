#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in a binomial heap
struct Node
{
    int key;              // Key of the node
    int degree;           // Degree of the node (order of the binomial tree)
    struct Node *parent;  // Pointer to the parent node
    struct Node *child;   // Pointer to the leftmost child node
    struct Node *sibling; // Pointer to the next sibling node
};

// Function to create a new node with a given key
struct Node *createNode(int key)
{
    // Allocate memory for a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    // If memory allocation fails, return NULL
    if (newNode == NULL)
    {
        return NULL;
    }
    // Initialize the new node
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to merge two binomial trees of the same order
struct Node *binomialHeapMerge(struct Node *h1, struct Node *h2)
{
    // If one of the heaps is empty, return the other heap
    if (h1 == NULL)
    {
        return h2;
    }
    else if (h2 == NULL)
    {
        return h1;
    }

    // Initialize pointers for the merged heap
    struct Node *head = NULL;   // Head of the merged heap
    struct Node *tail = NULL;   // Tail of the merged heap
    struct Node *prev = NULL;   // Pointer to the previous node in the merged heap
    struct Node *current1 = h1; // Pointer to the current node in the first heap
    struct Node *current2 = h2; // Pointer to the current node in the second heap

    // Merge the heaps until one of them becomes empty
    while (current1 != NULL && current2 != NULL)
    {
        // Compare the degrees of the current nodes in both heaps
        if (current1->degree <= current2->degree)
        {
            // If the tail is NULL, this is the first node in the merged heap
            if (tail == NULL)
            {
                head = current1;
            }
            else
            {
                // Otherwise, append the current node from the first heap to the merged heap
                tail->sibling = current1;
            }
            // Move the tail pointer to the newly added node
            tail = current1;
            // Move to the next node in the first heap
            current1 = current1->sibling;
        }
        else
        {
            // If the tail is NULL, this is the first node in the merged heap
            if (tail == NULL)
            {
                head = current2;
            }
            else
            {
                // Otherwise, append the current node from the second heap to the merged heap
                tail->sibling = current2;
            }
            // Move the tail pointer to the newly added node
            tail = current2;
            // Move to the next node in the second heap
            current2 = current2->sibling;
        }
        // Ensure the tail's sibling pointer is NULL
        tail->sibling = NULL;
    }

    // If there are remaining nodes in the first heap, append them to the merged heap
    while (current1 != NULL)
    {
        tail->sibling = current1;
        tail = current1;
        current1 = current1->sibling;
        tail->sibling = NULL;
    }

    // If there are remaining nodes in the second heap, append them to the merged heap
    while (current2 != NULL)
    {
        tail->sibling = current2;
        tail = current2;
        current2 = current2->sibling;
        tail->sibling = NULL;
    }

    // Return the head of the merged heap
    return head;
}

int main()
{
    // Create two heaps
    struct Node *heap1 = createNode(1);
    heap1->sibling = createNode(5);

    struct Node *heap2 = createNode(2);
    heap2->sibling = createNode(3);

    // Print the keys of the nodes in the first heap
    printf("Heap 1:\n");
    struct Node *current1 = heap1;
    while (current1 != NULL)
    {
        printf("%d ", current1->key);
        current1 = current1->sibling;
    }

    // Print the keys of the nodes in the second heap
    printf("\nHeap 2:\n");
    struct Node *current2 = heap2;
    while (current2 != NULL)
    {
        printf("%d ", current2->key);
        current2 = current2->sibling;
    }

    // Merge the two heaps
    struct Node *mergedHeap = binomialHeapMerge(heap1, heap2);

    // Print the keys of the nodes in the merged heap
    printf("\nMerged Heap:\n");
    struct Node *currentMerged = mergedHeap;
    while (currentMerged != NULL)
    {
        printf("%d ", currentMerged->key);
        currentMerged = currentMerged->sibling;
    }

    return 0;
}