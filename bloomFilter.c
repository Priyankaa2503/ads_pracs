#include <stdio.h>
#include <stdbool.h>
#define SIZE 10
// Bloom Filter sketch
bool sketch[SIZE];
// Hash function 1
unsigned int hash1(char* value) {
    unsigned int hash = 0;
    for (int i = 0; value[i] != '\0'; i++) {
        hash = hash + value[i];
    }
    return hash % SIZE;
}
// Hash function 2
unsigned int hash2(char* value) {
    unsigned int hash = 0;
    for (int i = 0; value[i] != '\0'; i++) {
        hash = hash * 31 + value[i];
    }
    return hash % SIZE;
}
// Hash function 3
unsigned int hash3(char* value) {
    unsigned int hash = 5381;
    for (int i = 0; value[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + value[i];
    }
    return hash % SIZE;
}
// Insert an element into the Bloom Filter
void insert(char* value) {
    sketch[hash1(value)] = true;
    sketch[hash2(value)] = true;
    sketch[hash3(value)] = true;
}
// Check if an element is present in the Bloom Filter
bool contains(char* value) {
    return sketch[hash1(value)] && sketch[hash2(value)] && sketch[hash3(value)];
}
int main() {
    insert("apple");
    insert("apple");
    insert("cherry");

    printf("Contains apple: %d\n", contains("apple"));
    printf("Contains banana: %d\n", contains("banana"));
    printf("Contains cherry: %d\n", contains("cherry"));
    printf("Contains mango: %d\n", contains("mango"));
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", sketch[i]);
    }

    return 0;
}
