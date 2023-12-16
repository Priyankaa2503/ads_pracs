#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26
// Trie node structure
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};
// Function to initialize a new trie node
struct TrieNode *createNode()
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        node->children[i] = NULL;
    }
    node->isEndOfWord = 0;
    return node;
}
// Function to check if a node has no children
int isNodeEmpty(struct TrieNode *node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            return 0;
        }
    }
    return 1;
}

// Function to insert a word into the trie
void insert(struct TrieNode *root, const char *word)
{
    struct TrieNode *currentNode = root;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL)
        {
            currentNode->children[index] = createNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = 1;
}

// Function to search for a word in the trie
int search(struct TrieNode *root, const char *word)
{
    struct TrieNode *currentNode = root;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL)
        {
            return 0; // Word not found
        }
        currentNode = currentNode->children[index];
    }
    return (currentNode != NULL && currentNode->isEndOfWord);
}

// Function to delete a word from the trie
int deleteWord(struct TrieNode *root, const char *word, int depth)
{
    if (root == NULL)
    {
        return 0;
    }
    // Base case: If the last character of the word is reached
    if (depth == strlen(word))
    {
        if (root->isEndOfWord)
        {
            root->isEndOfWord = 0;

            // Check if the node has no children, then it can be deleted
            int isEmpty = 1;
            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                if (root->children[i] != NULL)
                {
                    isEmpty = 0;
                    break;
                }
            }

            return isEmpty;
        }
    }
    else
    {
        int index = word[depth] - 'a';
        if (deleteWord(root->children[index], word, depth + 1))
        {
            free(root->children[index]);
            root->children[index] = NULL;

            // Check if the current node is not the end of another word and has no other children
            return !(root->isEndOfWord) && isNodeEmpty(root);
        }
    }

    return 0;
}
// Function to free the memory allocated for the trie
void freeTrie(struct TrieNode *root)
{
    if (root == NULL)
    {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        freeTrie(root->children[i]);
    }
    free(root);
}

// Function to display the menu
void displayMenu()
{
    printf("\nMenu:\n");
    printf("1. Insert a word\n");
    printf("2. Search for a word\n");
    printf("3. Delete a word\n");
    printf("4. Exit\n");
}

int main()
{
    struct TrieNode *root = createNode();
    int choice;
    char word[50];

    do
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the word to insert: ");
            scanf("%s", word);
            insert(root, word);
            printf("Word '%s' inserted into the trie.\n", word);
            break;
        case 2:
            printf("Enter the word to search: ");
            scanf("%s", word);
            if (search(root, word))
            {
                printf("Word '%s' found in the trie.\n", word);
            }
            else
            {
                printf("Word '%s' not found in the trie.\n", word);
            }
            break;
        case 3:
            printf("Enter the word to delete: ");
            scanf("%s", word);
            if (deleteWord(root, word, 0))
            {
                printf("Word '%s' deleted from the trie.\n", word);
            }
            else
            {
                printf("Word '%s' not found in the trie.\n", word);
            }
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
  // Free the allocated memory
    freeTrie(root);
    return 0;
}