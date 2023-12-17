#include <stdio.h>
#include <stdlib.h>
// Structure to represent an interval
struct Interval
{
    int low;
    int high;
};
// Structure to represent a node in the interval tree
struct IntervalNode
{
    struct Interval *interval;
    int max; // Maximum endpoint in the subtree rooted at this node
    struct IntervalNode *left;
    struct IntervalNode *right;
};
// Function to create a new interval
struct Interval *createInterval(int low, int high)
{
    struct Interval *newInterval = (struct Interval *)malloc(sizeof(struct Interval));
    if (newInterval != NULL)
    {
        newInterval->low = low;
        newInterval->high = high;
    }
    return newInterval;
}
// Function to create a new interval tree node
struct IntervalNode *createIntervalNode(struct Interval *interval)
{
    struct IntervalNode *newNode = (struct IntervalNode *)malloc(sizeof(struct IntervalNode));
    if (newNode != NULL)
    {
        newNode->interval = interval;
        newNode->max = interval->high;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}
// Function to insert an interval into the interval tree
struct IntervalNode *insertInterval(struct IntervalNode *root, struct Interval *interval)
{
    if (root == NULL)
    {
        return createIntervalNode(interval);
    }
    // Get the low endpoint of the interval at the root
    int low = root->interval->low;

    if (interval->low < low)
    {   // Insert into the left subtree
        root->left = insertInterval(root->left, interval);
    }
    else
    {   // Insert into the right subtree
        root->right = insertInterval(root->right, interval);
    }

    if (root->max < interval->high)
    {
        root->max = interval->high;
    }
    
    return root;
}
// Function to check if two intervals overlap
int doOverlap(struct Interval *a, struct Interval *b)
{
    return (a->low <= b->high && b->low <= a->high);
}
// Function to search for overlapping intervals in the interval tree
void searchOverlap(struct IntervalNode *root, struct Interval *interval)
{
    if (root == NULL)
    {
        return;
    }

    if (doOverlap(root->interval, interval))
    {
        printf("Overlap found: [%d, %d] overlaps with [%d, %d]\n",
               root->interval->low, root->interval->high,
               interval->low, interval->high);
    }

    // Check if the left subtree needs to be searched
    if (root->left != NULL && root->left->max >= interval->low)
    {
        searchOverlap(root->left, interval);
    }

    // Check if the right subtree needs to be searched
    if (root->right != NULL && root->right->max >= interval->low)
    {
        searchOverlap(root->right, interval);
    }
}
// Function to display in-order traversal of the interval tree
void inOrderTraversal(struct IntervalNode *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("[%d, %d] ", root->interval->low, root->interval->high);
        inOrderTraversal(root->right);
    }
}
// Function to free memory allocated for the interval tree
void freeIntervalTree(struct IntervalNode *root)
{
    if (root != NULL)
    {
        freeIntervalTree(root->left);
        freeIntervalTree(root->right);
        free(root->interval);
        free(root);
    }
}
int main()
{
    struct IntervalNode *root = NULL;
    int choice;

    do
    {
        printf("\n1. Insert Interval");
        printf("\n2. Search Overlapping Intervals");
        printf("\n3. Display In-order Traversal");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int low, high;
            printf("Enter interval low: ");
            scanf("%d", &low);
            printf("Enter interval high: ");
            scanf("%d", &high);
            struct Interval *newInterval = createInterval(low, high);
            root = insertInterval(root, newInterval);
            printf("Interval inserted successfully.\n");
            break;
        }
        case 2:
        {
            int searchLow, searchHigh;
            printf("Enter search interval low: ");
            scanf("%d", &searchLow);
            printf("Enter search interval high: ");
            scanf("%d", &searchHigh);
            struct Interval searchInterval = {searchLow, searchHigh};
            // printf("Searching for overlaps with [%d, %d]\n", searchInterval.low, searchInterval.high);
            searchOverlap(root, &searchInterval);
            break;
        }
        case 3:
        {
            printf("Interval Tree (In-order traversal): ");
            inOrderTraversal(root);
            printf("\n");
            break;
        }
        case 4:
        {   // Free memory
            freeIntervalTree(root);
            printf("Exiting...\n");
            break;
        }
        default:
        {
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }
        }
    } while (choice != 4);

    return 0;
}