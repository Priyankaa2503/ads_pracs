#include <stdio.h>
#include <stdlib.h>
// Define the secondary table structure
struct SecondaryTable
{
    int *table; // Pointer to the array that will hold the keys
    int size;   // Size of the secondary table
} ;
// Define the perfect hash table structure
struct PerfectHashTable
{
    struct SecondaryTable *secondaryTables; // Array of secondary tables
    int size;                        // Size of the primary table
} ;

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
struct PerfectHashTable *createPerfectHashTable(int size)
{
    struct PerfectHashTable *newTable = malloc(sizeof(struct PerfectHashTable));     // Allocate memory for the perfect hash table
    newTable->secondaryTables = malloc(sizeof(struct SecondaryTable) * size);         // Allocate memory for the array of secondary tables
    newTable->size = size;                                             // Set the size of the primary table
    for (int i = 0; i < size; i++)
    {
        newTable->secondaryTables[i].table = NULL; // Initialize each secondary table to NULL
        newTable->secondaryTables[i].size = 0;     // Initialize the size of each secondary table to 0
    }
    return newTable; // Return the new perfect hash table
}
// Function to insert a key into the perfect hash table
void insert(struct PerfectHashTable *perfectTable, int key)
{
    int primaryIndex = primaryHashFunction(key, perfectTable->size);               // Calculate the primary index
    struct SecondaryTable *secondaryTable = &perfectTable->secondaryTables[primaryIndex]; // Get the secondary table at the primary index
    if (secondaryTable->table == NULL)                                             // If the secondary table is NULL
    {
        secondaryTable->table = malloc(sizeof(int) * perfectTable->size); // Allocate memory for the secondary table
        for (int i = 0; i < perfectTable->size; i++)                      // Initialize all elements to -1
        {
            secondaryTable->table[i] = -1;
        }
        secondaryTable->size = perfectTable->size; // Set the size of the secondary table
    }
    // Calculate the secondary index
    int secondaryIndex = secondaryHashFunction(key, secondaryTable->size);
    // Insert the key at the secondary index
    secondaryTable->table[secondaryIndex] = key;
}
// Function to print the perfect hash table
void printPerfectHashTable(struct PerfectHashTable *perfectTable)
{
    for (int i = 0; i < perfectTable->size; i++) // For each primary index
    {
        struct SecondaryTable *secondaryTable = &perfectTable->secondaryTables[i]; // Get the secondary table at the primary index
        printf("Primary index %d:\n", i);                                  
        for (int j = 0; j < secondaryTable->size; j++)                      // For each secondary index
        {
            printf("  Secondary index %d: %d\n", j, secondaryTable->table[j]); // Print the secondary index and the key at that index
        }
    }
}
int main()
{
    struct PerfectHashTable *perfectTable = createPerfectHashTable(9);
    insert(perfectTable, 75);                                
    insert(perfectTable, 15);                                 
    insert(perfectTable, 32);                                  
    printPerfectHashTable(perfectTable);                       
    return 0;                                                 
}

