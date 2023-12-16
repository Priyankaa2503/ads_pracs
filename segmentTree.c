#include <stdio.h>
#include <stdlib.h>

#define MAX_N 8

// Structure to represent a node in the Segment Tree
struct SegmentTreeNode
{
    int sum;
    int min;
    int max;
};

// Function to build the Segment Tree from an input array
void buildSegmentTree(int arr[], struct SegmentTreeNode *tree, int start, int end, int index)
{
    if (start == end)
    {
        tree[index].sum = arr[start];
        tree[index].min = arr[start];
        tree[index].max = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;

    buildSegmentTree(arr, tree, start, mid, leftIndex);
    buildSegmentTree(arr, tree, mid + 1, end, rightIndex);

    tree[index].sum = tree[leftIndex].sum + tree[rightIndex].sum;
    tree[index].min = (tree[leftIndex].min < tree[rightIndex].min) ? tree[leftIndex].min : tree[rightIndex].min;
    tree[index].max = (tree[leftIndex].max > tree[rightIndex].max) ? tree[leftIndex].max : tree[rightIndex].max;
}

// Function to query the Segment Tree for the sum, minimum, or maximum of a given interval
void querySegmentTree(struct SegmentTreeNode *tree, int start, int end, int qstart, int qend, int index, int operation)
{
    // No overlap
    if (qstart > end || qend < start)
    {
        return;
    }

    // Complete overlap
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

    // Partial overlap, recursively query both left and right children
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
    int height = 1;
    while ((1 << height) < MAX_N)
    {
        height++;
    }
    // Calculate the total number of nodes in the Segment Tree
    int treeSize = (1 << (height + 1)) - 1;
    // Create and initialize the Segment Tree
    struct SegmentTreeNode *segmentTree = (struct SegmentTreeNode *)malloc(treeSize * sizeof(struct SegmentTreeNode));
    buildSegmentTree(inputArray, segmentTree, 0, MAX_N - 1, 0);
    int choice, qstart, qend;
    do
    {
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
            printf("Enter interval [start end]: ");
            scanf("%d %d", &qstart, &qend);
            querySegmentTree(segmentTree, 0, MAX_N - 1, qstart, qend, 0, choice);
            break;
        case 4:
            displaySegmentTree(segmentTree, treeSize);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    // Free memory
    free(segmentTree);

    return 0;
}
