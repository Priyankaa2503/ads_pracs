#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    struct node *children[26];
    bool isEndOfWord;
};

struct node *insert(struct node *head, char C[])
{
    struct node *temp = head;
    for (int i = 0; C[i] != '\0'; i++)
    {
        int index = C[i] - 'a';
        if (temp->children[index] == NULL)
        {
            struct node *newNode = (struct node *)malloc(sizeof(struct node));
            for (int j = 0; j < 26; j++)
            {
                newNode->children[j] = NULL;
            }
            newNode->isEndOfWord = false;
            temp->children[index] = newNode;
        }
        temp = temp->children[index];
    }
    temp->isEndOfWord = true;
    return head;
}

bool search(struct node *head, char C[])
{
    struct node *temp = head;
    for (int i = 0; C[i] != '\0'; i++)
    {
        int index = C[i] - 'a';
        if (temp->children[index] == NULL)
        {
            return false;
        }
        temp = temp->children[index];
    }
    if (temp->isEndOfWord == false)
    {
        return false;
    }
    return true;
}

struct node *del(struct node *head, char C[])
{
    struct node *temp = head;
    for (int i = 0; C[i] != '\0'; i++)
    {
        int index = C[i] - 'a';
        if (temp->children[index] == NULL)
        {
            return head;
        }
        temp = temp->children[index];
    }
    temp->isEndOfWord = false;
    return head;
}

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    for (int i = 0; i < 26; i++)
    {
        head->children[i] = NULL;
    }
    head->isEndOfWord = false;
    char C[] = "hello";
    insert(head, C);
    char C1[] = "hell";
    insert(head, C1);

    if (search(head, C1))
    {
        printf("Found\n");
    }
    else
    {
        printf("Not Found\n");
    }

    head = del(head, C1);

    if (search(head, C1))
    {
        printf("Found\n");
    }
    else
    {
        printf("Not Found\n");
    }
}