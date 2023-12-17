#include <stdio.h>
#include <stdlib.h>
#define MAX_N 8 // Maximum number of elements in the input array
// Structure to represent a node in the Segment Tree
struct SegmentTreeNode
{
    int sum; // Sum of the elements in the interval represented by this node
    int min; // Minimum element in the interval represented by this node
    int max; // Maximum element in the interval represented by this node
};
// Function to build the Segment Tree from an input array
void buildSegmentTree(int arr[], struct SegmentTreeNode *tree, int start, int end, int index)
{
    // If the start and end of the interval are the same (i.e., the interval has only one element),
    // then the sum, minimum, and maximum are just the element itself
    if (start == end)
    {
        tree[index].sum = arr[start];
        tree[index].min = arr[start];
        tree[index].max = arr[start];
        return;
    }

    // Calculate the mid-point of the interval
    int mid = (start + end) / 2;
    // Calculate the indices of the left and right children of the current node
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;

    // Recursively build the left and right subtrees
    buildSegmentTree(arr, tree, start, mid, leftIndex);
    buildSegmentTree(arr, tree, mid + 1, end, rightIndex);

    // The sum, minimum, and maximum of the current node are calculated from its left and right children
    tree[index].sum = tree[leftIndex].sum + tree[rightIndex].sum;
    tree[index].min = (tree[leftIndex].min < tree[rightIndex].min) ? tree[leftIndex].min : tree[rightIndex].min;
    tree[index].max = (tree[leftIndex].max > tree[rightIndex].max) ? tree[leftIndex].max : tree[rightIndex].max;
}
// Function to query the Segment Tree for the sum, minimum, or maximum of a given interval
void querySegmentTree(struct SegmentTreeNode *tree, int start, int end, int qstart, int qend, int index, int operation)
{
    // If the query interval does not overlap with the interval represented by the current node, return
    if (qstart > end || qend < start)
    {
        return;
    }
    // If the query interval completely overlaps with the interval represented by the current node,
    // print the sum, minimum, or maximum as per the operation
    if (qstart <= start && qend >= end)
    {
        if (operation == 1)
        {
            // Sum
            printf("Sum of interval [%d, %d]: %d\n", start, end, tree[index].sum);
        }
        else if (operation == 2)
        {
            // Minimum
            printf("Minimum of interval [%d, %d]: %d\n", start, end, tree[index].min);
        }
        else if (operation == 3)
        {
            // Maximum
            printf("Maximum of interval [%d, %d]: %d\n", start, end, tree[index].max);
        }
        return;
    }

    // If the query interval partially overlaps with the interval represented by the current node,
    // recursively query both the left and right children
    int mid = (start + end) / 2;
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;

    querySegmentTree(tree, start, mid, qstart, qend, leftIndex, operation);
    querySegmentTree(tree, mid + 1, end, qstart, qend, rightIndex, operation);
}

// Function to display the elements of the Segment Tree
void displaySegmentTree(struct SegmentTreeNode *tree, int n)
{
    printf("Segment Tree:\n");
    // Loop through the Segment Tree and print the sum, minimum, and maximum of each node
    for (int i = 0; i < n; ++i)
    {
        printf("Index %d: Sum=%d, Min=%d, Max=%d\n", i, tree[i].sum, tree[i].min, tree[i].max);
    }
    printf("\n");
}

int main()
{
    // Hardcoded input array
    int inputArray[] = {1, 3, 5, 7, 9, 11, 13, 15};
    // Calculate the height of the Segment Tree
    int height = 3;
    // Keep doubling the height until it is large enough to accommodate all elements of the input array
    // while ((1 << height) < MAX_N)
    // {
    //     height++;
    // }
    // printf("Calculated height of the Segment Tree: %d\n", height); // Print the calculated height
    // Calculate the total number of nodes in the Segment Tree
    int treeSize = 15;
    // printf("Calculated size of the Segment Tree: %d\n", treeSize); // Print the calculated tree size

    // Create and initialize the Segment Tree
    struct SegmentTreeNode *segmentTree = (struct SegmentTreeNode *)malloc(treeSize * sizeof(struct SegmentTreeNode));
    // Build the Segment Tree from the input array
    buildSegmentTree(inputArray, segmentTree, 0, MAX_N - 1, 0);
    int choice, qstart, qend;
    do
    {
        // Display the menu and get the user's choice
        printf("Menu:\n");
        printf("1. Find Sum of Interval\n");
        printf("2. Find Minimum of Interval\n");
        printf("3. Find Maximum of Interval\n");
        printf("4. Display Segment Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        case 2:
        case 3:
            // If the user wants to find the sum, minimum, or maximum of an interval,
            // get the interval from the user and query the Segment Tree
            printf("Enter interval [start end]: ");
            scanf("%d %d", &qstart, &qend);
            querySegmentTree(segmentTree, 0, MAX_N - 1, qstart, qend, 0, choice);
            break;
        case 4:
            // If the user wants to display the Segment Tree, call the display function
            displaySegmentTree(segmentTree, treeSize);
            break;
        case 5:
            // If the user wants to exit, print a message and break from the loop
            printf("Exiting...\n");
            break;
        default:
            // If the user enters an invalid choice, print an error message
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    // Free the memory allocated for the Segment Tree
    free(segmentTree);

    return 0;
}