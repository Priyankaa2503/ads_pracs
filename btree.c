#include <stdio.h>
#include <stdlib.h>

#define M 3 // Order of the B-tree

// Structure for BTree node
struct BTreeNode
{
    int leaf;                   // 1 if leaf, 0 if internal node
    int n;                      // Number of keys in the node
    int keys[M - 1];            // Array of keys
    struct BTreeNode *child[M]; // Array of child pointers
};

// Structure for BTree
struct BTree
{
    struct BTreeNode *root; // Pointer to root node
};

// Function to create a new B-tree node
struct BTreeNode *createNode()
{
    // Allocate memory for new node
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode != NULL)
    {
        newNode->leaf = 1; // Initialize as leaf
        newNode->n = 0;    // Initialize number of keys as 0
        for (int i = 0; i < M - 1; ++i)
        {
            newNode->keys[i] = 0;     // Initialize keys
            newNode->child[i] = NULL; // Initialize child pointers
        }
        newNode->child[M - 1] = NULL; // Initialize last child pointer
    }
    return newNode;
}

// Function to split a child node
void splitChild(struct BTreeNode *x, int i)
{
    // y is i-th child of x
    struct BTreeNode *y = x->child[i];
    // Allocate memory for new node z
    struct BTreeNode *z = createNode();

    // Update x's child pointers
    x->child[i] = y;
    x->child[i + 1] = z;

    // Copy y's properties to z
    z->leaf = y->leaf;
    z->n = (M - 1) / 2;

    // Copy y's keys to z
    for (int j = 0; j < z->n; ++j)
    {
        z->keys[j] = y->keys[j + (M + 1) / 2];
    }

    // If y is not a leaf, copy y's child pointers to z
    if (!y->leaf)
    {
        for (int j = 0; j <= z->n; ++j)
        {
            z->child[j] = y->child[j + (M + 1) / 2];
        }
    }

    // Update y's number of keys
    y->n = (M - 1) / 2;

    // Shift x's keys and child pointers to make room for new key and child
    for (int j = x->n; j > i; --j)
    {
        x->keys[j] = x->keys[j - 1];
        x->child[j + 1] = x->child[j];
    }

    // Copy middle key of y to x and update x's child pointer
    x->keys[i] = y->keys[(M - 1) / 2];
    x->child[i + 1] = z;
    x->n++; // Increment number of keys in x
}

// Function to insert a key into a B-tree
void insertBTree(struct BTree *tree, int key)
{
    struct BTreeNode *r = tree->root;
    if (r == NULL)
    {
        // If the tree is empty, create a new root
        tree->root = createNode();
        tree->root->keys[0] = key; // Insert key
        tree->root->n = 1;         // Update number of keys
    }
    else
    {
        if (r->n == M - 1)
        {
            // If the root is full, split it
            struct BTreeNode *s = createNode();
            tree->root = s;
            s->leaf = 0;           // s is an internal node
            s->child[0] = r;       // Make r child of s
            splitChild(s, 0);      // Split r and move one key to s
            insertNonFull(s, key); // Insert key into the B-tree rooted with s
        }
        else
        {
            // If the root is not full, call insertNonFull for r
            insertNonFull(r, key);
        }
    }
}

// Function to insert into a non-full B-tree node
void insertNonFull(struct BTreeNode *x, int key)
{
    int i = x->n - 1;
    if (x->leaf)
    {
        // If x is a leaf, insert the key into it
        while (i >= 0 && key < x->keys[i])
        {
            x->keys[i + 1] = x->keys[i]; // Shift keys
            i--;
        }
        x->keys[i + 1] = key; // Insert key
        x->n++;               // Increment number of keys
    }
    else
    {
        // If x is an internal node
        while (i >= 0 && key < x->keys[i])
        {
            i--; // Find location of new key
        }
        i++;
        if (x->child[i]->n == M - 1)
        {
            // If the found child is full, split it
            splitChild(x, i);
            if (key > x->keys[i])
            {
                i++; // After split, the key may go to the next child
            }
        }
        insertNonFull(x->child[i], key); // Insert key
    }
}

// Function to display the B-tree in-order
void inOrderTraversal(struct BTreeNode *root)
{
    if (root != NULL)
    {
        for (int i = 0; i < root->n; ++i)
        {
            inOrderTraversal(root->child[i]); // Recursive call for child
            printf("%d ", root->keys[i]);     // Print keys
        }
        inOrderTraversal(root->child[root->n]); // Recursive call for last child
    }
}

// Function to display the B-tree
void displayBTree(struct BTree *tree)
{
    if (tree->root != NULL)
    {
        inOrderTraversal(tree->root); // Call inOrderTraversal for root
        printf("\n");
    }
    else
    {
        printf("Tree is empty.\n");
    }
}


// Example usage
int main()
{
    struct BTree *tree = (struct BTree *)malloc(sizeof(struct BTree));
    tree->root = NULL;

    int choice, key;

    do
    {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Display B-tree\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the key to insert: ");
            scanf("%d", &key);
            insertBTree(tree, key); // Insert key
            printf("Key %d inserted.\n", key);
            break;
        case 2:
            printf("B-tree: ");
            displayBTree(tree); // Display B-tree
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}