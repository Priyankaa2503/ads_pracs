#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 26

typedef struct TrieNode TrieNode;
struct TrieNode
{
    char data;
    TrieNode *children[N];
    int is_leaf;
};

TrieNode *make_trienode(char data)
{
    TrieNode *node = (TrieNode *)calloc(1, sizeof(TrieNode));
    for (int i = 0; i < N; i++)
        node->children[i] = NULL;
    node->is_leaf = 0;
    node->data = data;
    return node;
}

void free_trienode(TrieNode *node)
{
    for (int i = 0; i < N; i++)
    {
        if (node->children[i] != NULL)
        {
            free_trienode(node->children[i]);
        }
    }
    free(node);
}

TrieNode *insert_trie(TrieNode *root, char *word)
{
    TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = (int)word[i] - 'a';
        if (temp->children[idx] == NULL)
        {
            temp->children[idx] = make_trienode(word[i]);
        }
        temp = temp->children[idx];
    }

    temp->is_leaf = 1;
    return root;
}

int search_trie(TrieNode *root, char *word)
{
    TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1)
        return 1;
    return 0;
}

// Function to delete a word from the trie
TrieNode *delete_trie(TrieNode *root, char *word)
{
    TrieNode *temp = root;
    TrieNode *path[N];
    int length = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL)
            return root; // Word not found, nothing to delete
        path[length++] = temp;
        temp = temp->children[position];
    }

    if (temp != NULL && temp->is_leaf == 1)
    {
        temp->is_leaf = 0; // Mark the node as non-leaf
        // Check if the node has no children, if so, remove it from the parent
        if (temp->is_leaf == 0)
        {
            for (int i = length - 1; i >= 0; i--)
            {
                int position = word[i] - 'a';
                if (temp->is_leaf == 0 && temp->children[position] == NULL)
                {
                    free(temp);
                    path[i]->children[position] = NULL;
                }
                else
                {
                    break; // Stop if we find a non-empty child
                }
                temp = path[i];
            }
        }
    }

    return root;
}

void print_trie(TrieNode *root)
{
    if (!root)
        return;
    TrieNode *temp = root;
    printf("%c -> ", temp->data);
    for (int i = 0; i < N; i++)
    {
        print_trie(temp->children[i]);
    }
}

void print_search(TrieNode *root, char *word)
{
    printf("Searching for %s: ", word);
    if (search_trie(root, word) == 0)
        printf("Not Found\n");
    else
        printf("Found!\n");
}

int main()
{
    TrieNode *root = make_trienode('\0');
    int choice = 3;
    char str[25];

    while (1)
    {
        printf("\nEnter 1 to insert\nEnter 2 to search\nEnter 3 to delete word\nEnter 0 to exit\n");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 0:
            free_trienode(root);
            printf("\nTrie deleted");
            return 0;
        case 1:
            printf("Enter word to insert\n");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            root = insert_trie(root, str);
            print_trie(root);
            break;
        case 2:
            printf("Enter word to search\n");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            print_search(root, str);
            break;
        case 3:
            printf("Enter word to delete\n");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            root = delete_trie(root, str);
            print_trie(root);
            break;
        }
    }
}
