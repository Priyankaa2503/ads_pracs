#include <stdio.h>
#include <stdlib.h>
#define MAXN 11 // Maximum number of keys in the hash table
// Arrays to store the hash tables
int hashtable1[MAXN];
int hashtable2[MAXN];
// Function to create a hash function
int hashfunction(int function, int key)
{
    switch (function)
    {
    case 1:
        return key % MAXN;
    case 2:
        return (key / MAXN) % MAXN;
    }
    return 0;
}
// Function to place a key in the cuckoo hash table
void place(int key, int tableNumber)
{
    int pos, i, temp;
    for (i = 0; i < MAXN; i++)
    {
        if (tableNumber == 1)
        {
            pos = hashfunction(1, key);
            if (hashtable1[pos] == -1)
            {
                hashtable1[pos] = key;
                return;
            }
            temp = hashtable1[pos];
            hashtable1[pos] = key;
            key = temp;
            tableNumber = 2;
        }
        else
        {
            pos = hashfunction(2, key);
            if (hashtable2[pos] == -1)
            {
                hashtable2[pos] = key;
                return;
            }
            temp = hashtable2[pos];
            hashtable2[pos] = key;
            key = temp;
            tableNumber = 1;
        }
    }
}
// Function to insert a key into the hash table
void insert(int key)
{
    int pos = hashfunction(1, key);
    if (hashtable1[pos] != -1)
    {
        int temp = hashtable1[pos];
        hashtable1[pos] = key;
        place(temp, 2);
    }
    else
    {
        hashtable1[pos] = key;
    }
}

int main()
{
    int i;
    for (i = 0; i < MAXN; i++)
    {
        hashtable1[i] = -1;
        hashtable2[i] = -1;
    }

    insert(20);
    insert(50);
    insert(53);
    insert(75);
    insert(100);
    insert(67);
    insert(105);
    insert(3);
    insert(36);
    insert(39);

    printf("The hash table 1 is:\n");
    for (i = 0; i < MAXN; i++)
    {
        printf("%d ", hashtable1[i]);
    }

    printf("\nThe hash table 2 is:\n");
    for (i = 0; i < MAXN; i++)
    {
        printf("%d ", hashtable2[i]);
    }

    return 0;
}

// hashtable1 and hashtable2 are the two hash tables.
// The insert function first tries to insert the key into hashtable1. 
//If there's a collision, it replaces the key at the colliding position and tries to place the replaced key into hashtable2 using the place function.
// The place function alternates between the two tables until it finds an empty position or it has iterated MAXN times.
