#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

// Structure for a Red-Black Tree Node
struct RBNode
{
    int key;               // Node's key
    int color;             // Node's color (RED or BLACK)
    struct RBNode *parent; // Pointer to parent node
    struct RBNode *left;   // Pointer to left child
    struct RBNode *right;  // Pointer to right child
};

// Structure for a Red-Black Tree
struct RBTree
{
    struct RBNode *root; // Pointer to root of the tree
};

// Function to create a new node
struct RBNode *createNode(int key)
{
    struct RBNode *newNode = (struct RBNode *)malloc(sizeof(struct RBNode));
    if (newNode != NULL)
    {
        newNode->key = key;
        newNode->color = RED; // New nodes are always red
        newNode->parent = NULL;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// Function to perform left-rotation of tree
void leftRotate(struct RBTree *tree, struct RBNode *x)
{
    struct RBNode *y = x->right; // Set y
    x->right = y->left;          // Turn y's left subtree into x's right subtree

    if (y->left != NULL)
    {
        y->left->parent = x;
    }

    y->parent = x->parent; // Link x's parent to y

    if (x->parent == NULL)
    {
        tree->root = y; // If x has no parent, y becomes the root of the tree
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y; // If x is a left child, set y to be left child of x's parent
    }
    else
    {
        x->parent->right = y; // If x is a right child, set y to be right child of x's parent
    }

    y->left = x; // Put x on y's left
    x->parent = y;
}

// Function to perform right-rotation of tree
void rightRotate(struct RBTree *tree, struct RBNode *y)
{
    struct RBNode *x = y->left; // Set x
    y->left = x->right;         // Turn x's right subtree into y's left subtree

    if (x->right != NULL)
    {
        x->right->parent = y;
    }

    x->parent = y->parent; // Link y's parent to x

    if (y->parent == NULL)
    {
        tree->root = x; // If y has no parent, x becomes the root of the tree
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x; // If y is a left child, set x to be left child of y's parent
    }
    else
    {
        y->parent->right = x; // If y is a right child, set x to be right child of y's parent
    }

    x->right = y; // Put y on x's right
    y->parent = x;
}

// Function to fix the red-black tree after insertion of a node
void fixInsert(struct RBTree *tree, struct RBNode *z)
{
    // While z's parent is red
    while (z->parent != NULL && z->parent->color == RED)
    {
        // If z's parent is left child of its parent
        if (z->parent == z->parent->parent->left)
        {
            struct RBNode *y = z->parent->parent->right; // Uncle of z

            // Case 1: If uncle is red, only recoloring required
            if (y != NULL && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                // Case 2: If z is right child, left rotation required
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                // Case 3: If z is left child, right rotation required
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        }
        else
        {
            // Similar logic to the above, but mirrored
            struct RBNode *y = z->parent->parent->left; // Uncle of z

            if (y != NULL && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK; // Root must always be black
}

// Function to insert a node to the tree
void insert(struct RBTree *tree, int key)
{
    struct RBNode *z = createNode(key); // Create a new node
    struct RBNode *y = NULL;
    struct RBNode *x = tree->root;

    // Traverse the tree down to a leaf
    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;

    // Decide whether to insert as left or right child
    if (y == NULL)
    {
        tree->root = z; // If tree was empty, z becomes root
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    // Fix the tree
    fixInsert(tree, z);
}

// Function for in-order tree traversal
void inOrderTraversal(struct RBNode *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

// Function to display the tree
void displayRBTree(struct RBTree *tree)
{
    if (tree->root != NULL)
    {
        inOrderTraversal(tree->root);
        printf("\n");
    }
    else
    {
        printf("Tree is empty.\n");
    }
}

// Main function
int main()
{
    struct RBTree *tree = (struct RBTree *)malloc(sizeof(struct RBTree));
    tree->root = NULL;

    int choice, key;

    do
    {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Display Red-Black Tree\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the key to insert: ");
            scanf("%d", &key);
            insert(tree, key);
            printf("Key %d inserted.\n", key);
            break;
        case 2:
            printf("Red-Black Tree: ");
            displayRBTree(tree);
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    free(tree);

    return 0;
}