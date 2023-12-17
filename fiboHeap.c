#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a node in a Fibonacci heap
struct FibonacciNode
{
    int key;                      // The key value of the node
    int degree;                   // The degree of the node, i.e., the number of children it has
    int marked;                   // Flag to indicate whether the node has lost a child since the last time it was made the child of another node
    struct FibonacciNode *parent; // Pointer to the parent node
    struct FibonacciNode *child;  // Pointer to one of the child nodes
    struct FibonacciNode *left;   // Pointer to the node to the left in the circular doubly linked list
    struct FibonacciNode *right;  // Pointer to the node to the right in the circular doubly linked list
};

// Structure to represent a Fibonacci heap
struct FibonacciHeap
{
    struct FibonacciNode *minNode; // Pointer to the node with the minimum key value
    int numNodes;                  // The total number of nodes in the heap
};

// Function to create a new Fibonacci heap
struct FibonacciHeap *createFibonacciHeap()
{
    // Allocate memory for the heap
    struct FibonacciHeap *heap = (struct FibonacciHeap *)malloc(sizeof(struct FibonacciHeap));
    if (heap != NULL)
    {
        heap->minNode = NULL; // Initialize the minNode pointer to NULL
        heap->numNodes = 0;   // Initialize the number of nodes to 0
    }
    return heap; // Return the newly created heap
}

// Function to create a new Fibonacci node
struct FibonacciNode *createFibonacciNode(int key)
{
    // Allocate memory for the node
    struct FibonacciNode *newNode = (struct FibonacciNode *)malloc(sizeof(struct FibonacciNode));
    if (newNode != NULL)
    {
        newNode->key = key;       // Set the key value of the node
        newNode->degree = 0;      // Initialize the degree of the node to 0
        newNode->marked = 0;      // Initialize the marked flag to 0
        newNode->parent = NULL;   // Initialize the parent pointer to NULL
        newNode->child = NULL;    // Initialize the child pointer to NULL
        newNode->left = newNode;  // Initialize the left pointer to point to the node itself
        newNode->right = newNode; // Initialize the right pointer to point to the node itself
    }
    return newNode; // Return the newly created node
}

// Function to link two Fibonacci trees of the same degree
void link(struct FibonacciNode *y, struct FibonacciNode *x)
{
    // Remove y from the root list
    y->left->right = y->right;
    y->right->left = y->left;

    // Make y a child of x
    y->parent = x;
    if (x->child == NULL)
    {
        x->child = y;
        y->left = y;
        y->right = y;
    }
    else
    {
        // Insert y into x's child list
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }

    // Increase the degree of x and unmark y
    x->degree++;
    y->marked = 0;
}

// Function to consolidate the root list of a Fibonacci heap
void consolidate(struct FibonacciHeap *heap)
{
    // The maximum degree of a node in a Fibonacci heap with n nodes is approximately log(n)
    // Here we assume a 32-bit integer, so the maximum degree is 32
    int maxDegree = 32;

    // Initialize an array to store the roots of the trees in the root list
    struct FibonacciNode *array[maxDegree];
    for (int i = 0; i < maxDegree; i++)
    {
        array[i] = NULL;
    }

    // Traverse the root list
    struct FibonacciNode *current = heap->minNode;
    struct FibonacciNode *rootList = heap->minNode;
    do
    {
        struct FibonacciNode *x = current;
        int d = x->degree;

        // If there is another node in the root list with the same degree, then link the two nodes
        while (array[d] != NULL)
        {
            struct FibonacciNode *y = array[d];
            if (x->key > y->key)
            {
                struct FibonacciNode *temp = x;
                x = y;
                y = temp;
            }
            link(y, x);
            array[d] = NULL;
            d++;
        }
        array[d] = x;

        current = current->right;
    } while (current != rootList);

    // Reconstruct the root list from the array
    heap->minNode = NULL;
    for (int i = 0; i < maxDegree; i++)
    {
        if (array[i] != NULL)
        {
            if (heap->minNode == NULL)
            {
                heap->minNode = array[i];
            }
            else
            {
                // If the key of the node in the array is less than the key of the minimum node, then update the minimum node
                if (array[i]->key < heap->minNode->key)
                {
                    heap->minNode = array[i];
                }
            }
        }
    }
}

// Function to merge two Fibonacci heaps
struct FibonacciHeap *mergeFibonacciHeaps(struct FibonacciHeap *heap1, struct FibonacciHeap *heap2)
{
    // Create a new Fibonacci heap to store the result
    struct FibonacciHeap *resultHeap = createFibonacciHeap();

    // If both heaps are empty, then return the empty result heap
    if (heap1->minNode == NULL && heap2->minNode == NULL)
    {
        return resultHeap;
    }
    else if (heap1->minNode == NULL)
    {
        // If heap1 is empty, then return heap2
        resultHeap->minNode = heap2->minNode;
        resultHeap->numNodes = heap2->numNodes;
    }
    else if (heap2->minNode == NULL)
    {
        // If heap2 is empty, then return heap1
        resultHeap->minNode = heap1->minNode;
        resultHeap->numNodes = heap1->numNodes;
    }
    else
    {
        // If both heaps are non-empty, then merge the two heaps
        resultHeap->minNode = heap1->minNode;

        // Concatenate the root lists of both heaps
        struct FibonacciNode *temp = heap1->minNode->right;
        heap1->minNode->right = heap2->minNode->right;
        heap2->minNode->right->left = heap1->minNode;
        heap2->minNode->right = temp;
        temp->left = heap2->minNode;

        // Update the minimum node if necessary
        if (heap2->minNode->key < resultHeap->minNode->key)
        {
            resultHeap->minNode = heap2->minNode;
        }

        // Update the total number of nodes
        resultHeap->numNodes = heap1->numNodes + heap2->numNodes;
    }

    return resultHeap; // Return the merged heap
}

// Function to display the Fibonacci heap
void displayFibonacciHeap(struct FibonacciNode *node)
{
    if (node == NULL)
    {
        return; // If the node is NULL, then return
    }

    // Traverse the root list and recursively display each tree
    struct FibonacciNode *current = node;
    do
    {
        printf("%d ", current->key);
        displayFibonacciHeap(current->child);
        current = current->right;
    } while (current != node);
}

// Example usage
int main()
{
    struct FibonacciHeap *heap1 = createFibonacciHeap();
    struct FibonacciHeap *heap2 = createFibonacciHeap();

    // Insert nodes into heap1
    heap1->minNode = createFibonacciNode(1);
    heap1->numNodes = 1;

    // Insert nodes into heap2
    heap2->minNode = createFibonacciNode(3);
    heap2->numNodes = 1;

    // Display heap1
    printf("Heap 1: ");
    displayFibonacciHeap(heap1->minNode);
    printf("\n");

    // Display heap2
    printf("Heap 2: ");
    displayFibonacciHeap(heap2->minNode);
    printf("\n");

    // Merge heap1 and heap2
    struct FibonacciHeap *mergedHeap = mergeFibonacciHeaps(heap1, heap2);

    // Display the merged heap
    printf("Merged Heap: ");
    displayFibonacciHeap(mergedHeap->minNode);
    printf("\n");

    return 0;
}