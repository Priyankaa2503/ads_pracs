import random


class CuckooHashing:
    def __init__(self, size):
        self.size = size
        self.table1 = [None] * size
        self.table2 = [None] * size
        self.max_rehash_attempts = 10

    def hash_function1(self, key):
        return hash(key) % self.size

    def hash_function2(self, key):
        # Using a different hash function for variety
        return (2 * hash(key) + 1) % self.size

    def insert(self, key):
        return self._insert(key, self.max_rehash_attempts)

    def _insert(self, key, rehash_attempts):
        if rehash_attempts == 0:
            # Max rehash attempts reached, resize the tables
            self._resize()
            return self._insert(key, self.max_rehash_attempts)

        index1 = self.hash_function1(key)
        index2 = self.hash_function2(key)

        if self.table1[index1] is None:
            self.table1[index1] = key
            return True
        elif self.table2[index2] is None:
            self.table2[index2] = key
            return True
        else:
            # Kick out existing keys
            if random.choice([True, False]):
                kicked_key = self.table1[index1]
                self.table1[index1] = key
                return self._insert(kicked_key, rehash_attempts - 1)
            else:
                kicked_key = self.table2[index2]
                self.table2[index2] = key
                return self._insert(kicked_key, rehash_attempts - 1)

    def _resize(self):
        self.size *= 2
        self.table1 = [None] * self.size
        self.table2 = [None] * self.size

    def print_tables(self):
        print("Table 1:", self.table1)
        print("Table 2:", self.table2)


# Example usage
cuckoo_hash = CuckooHashing(size=8)

keys = [3, 6, 9, 12, 15, 18, 21, 24, 27]

for key in keys:
    success = cuckoo_hash.insert(key)
    if success:
        print(f"Inserted key {key} successfully.")
        cuckoo_hash.print_tables()
    else:
        print(f"Failed to insert key {key} after resizing.")
        print(f"Inserted key {key} successfully.")
