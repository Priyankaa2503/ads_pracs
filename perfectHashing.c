#include <stdio.h>
#include <stdlib.h>

// Define the secondary table structure
typedef struct
{
    int *table; // Pointer to the array that will hold the keys
    int size;   // Size of the secondary table
} SecondaryTable;

// Define the perfect hash table structure
typedef struct
{
    SecondaryTable *secondaryTables; // Array of secondary tables
    int size;                        // Size of the primary table
} PerfectHashTable;

// Primary hash function
int primaryHashFunction(int key, int size)
{
    return key % size; // Simple modulus hash function
}

// Secondary hash function
int secondaryHashFunction(int key, int size)
{
    int prime = 101;                       // Prime number
    int a = 3;                             // Coefficient a for the hash function
    int b = 42;                            // Coefficient b for the hash function
    return ((a * key + b) % prime) % size; // Hash function formula
}

// Function to create a new perfect hash table
PerfectHashTable *createPerfectHashTable(int size)
{
    PerfectHashTable *newTable = malloc(sizeof(PerfectHashTable));     // Allocate memory for the perfect hash table
    newTable->secondaryTables = malloc(sizeof(SecondaryTable) * size); // Allocate memory for the array of secondary tables
    newTable->size = size;                                             // Set the size of the primary table
    for (int i = 0; i < size; i++)
    {
        newTable->secondaryTables[i].table = NULL; // Initialize each secondary table to NULL
        newTable->secondaryTables[i].size = 0;     // Initialize the size of each secondary table to 0
    }
    return newTable; // Return the new perfect hash table
}

// Function to insert a key into the perfect hash table
void insert(PerfectHashTable *perfectTable, int key)
{
    int primaryIndex = primaryHashFunction(key, perfectTable->size);               // Calculate the primary index
    SecondaryTable *secondaryTable = &perfectTable->secondaryTables[primaryIndex]; // Get the secondary table at the primary index
    if (secondaryTable->table == NULL)                                             // If the secondary table is NULL
    {
        secondaryTable->table = malloc(sizeof(int)); // Allocate memory for one key
        secondaryTable->size = 1;                    // Set the size of the secondary table to 1
    }
    else // If the secondary table is not NULL
    {
        secondaryTable->table = realloc(secondaryTable->table, sizeof(int) * (secondaryTable->size + 1)); // Reallocate memory to hold one more key
        secondaryTable->size++;                                                                           // Increase the size of the secondary table by 1
    }
    secondaryTable->table[secondaryTable->size - 1] = key; // Insert the key at the end of the secondary table
}

// Function to print the perfect hash table
void printPerfectHashTable(PerfectHashTable *perfectTable)
{
    for (int i = 0; i < perfectTable->size; i++) // For each primary index
    {
        SecondaryTable *secondaryTable = &perfectTable->secondaryTables[i]; // Get the secondary table at the primary index
        printf("Primary index %d:\n", i);                                   // Print the primary index
        for (int j = 0; j < secondaryTable->size; j++)                      // For each secondary index
        {
            printf("  Secondary index %d: %d\n", j, secondaryTable->table[j]); // Print the secondary index and the key at that index
        }
    }
}

// Main function
int main()
{
    PerfectHashTable *perfectTable = createPerfectHashTable(9); // Create a new perfect hash table with a primary table size of 9
    insert(perfectTable, 75);                                   // Insert the key 75
    insert(perfectTable, 15);                                   // Insert the key 15
    insert(perfectTable, 32);                                   // Insert the key 32
    printPerfectHashTable(perfectTable);                        // Print the perfect hash table
    return 0;                                                   // End the program
}