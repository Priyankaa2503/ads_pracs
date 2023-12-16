#include <stdio.h>
#include <stdlib.h>

#define MAX_REHASHES 3

typedef struct {
    int key;
    int value;
} Entry;

typedef struct {
    int num_buckets;
    int max_rehashes;
    Entry** buckets;
} HashTable;

int hash1(int key, int size) {
    return key % size;
}

int hash2(int key, int size) {
    return (key / size) % size;
}

HashTable* createHashTable(int num_buckets, int max_rehashes) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->num_buckets = num_buckets;
    hashTable->max_rehashes = max_rehashes;
    hashTable->buckets = (Entry**)calloc(num_buckets, sizeof(Entry*));
    return hashTable;
}

void resizeHashTable(HashTable* hashTable) {
    int new_num_buckets = hashTable->num_buckets * 2;
    Entry** new_buckets = (Entry**)calloc(new_num_buckets, sizeof(Entry*));

    for (int i = 0; i < hashTable->num_buckets; i++) {
        Entry* entry = hashTable->buckets[i];
        if (entry != NULL) {
            int hash = hash1(entry->key, new_num_buckets);
            if (new_buckets[hash] != NULL) {
                hash = hash2(entry->key, new_num_buckets);
            }
            if (new_buckets[hash] != NULL) {
                printf("Maximum rehashes reached. Unable to resize hash table.\n");
                return;
            }
            new_buckets[hash] = entry;
        }
    }

    free(hashTable->buckets);
    hashTable->buckets = new_buckets;
    hashTable->num_buckets = new_num_buckets;
}

void insert(HashTable* hashTable, int key, int value) {
    int hash = hash1(key, hashTable->num_buckets);
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = key;
    entry->value = value;

    if (hashTable->buckets[hash] == NULL) {
        hashTable->buckets[hash] = entry;
    } else {
        Entry* temp = hashTable->buckets[hash];
        hashTable->buckets[hash] = entry;
        hash = hash2(temp->key, hashTable->num_buckets);
        if (hashTable->buckets[hash] != NULL) {
            Entry* temp2 = hashTable->buckets[hash];
            hashTable->buckets[hash] = temp;
            insert(hashTable, temp2->key, temp2->value);
        } else {
            hashTable->buckets[hash] = temp;
        }
    }

    if (hashTable->max_rehashes > 0) {
        hashTable->max_rehashes--;
        if (hashTable->max_rehashes == 0) {
            resizeHashTable(hashTable);
        }
    }
}

int search(HashTable* hashTable, int key) {
    int hash = hash1(key, hashTable->num_buckets);
    if (hashTable->buckets[hash] != NULL && hashTable->buckets[hash]->key == key) {
        return hashTable->buckets[hash]->value;
    }

    hash = hash2(key, hashTable->num_buckets);
    if (hashTable->buckets[hash] != NULL && hashTable->buckets[hash]->key == key) {
        return hashTable->buckets[hash]->value;
    }

    return -1;
}

int main() {
    HashTable* hashTable = createHashTable(10, MAX_REHASHES);

    insert(hashTable, 1, 10);
    insert(hashTable, 2, 20);
    insert(hashTable, 3, 30);

    int value = search(hashTable, 2);
    printf("Value for key 2: %d\n", value);

    // delete(hashTable, 2);

    value = search(hashTable, 2);
    printf("Value for key 2: %d\n", value);

    return 0;
}
