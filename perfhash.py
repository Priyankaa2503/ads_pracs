class PerfectHashing:
    def __init__(self, input_data):
        self.input_data = input_data
        self.hash_table = [None] * len(input_data)
        self.primary_hash_func = self.compute_primary_hash_func()
        self.secondary_hash_funcs = self.compute_secondary_hash_funcs()

    def compute_primary_hash_func(self):
        return lambda x: hash(x) % len(self.input_data)

    def compute_secondary_hash_funcs(self):
        return [
            lambda x: hash(x) % len(self.input_data)
            for _ in range(len(self.input_data))
        ]

    def insert(self, element):
        index = self.primary_hash_func(element)
        if self.hash_table[index] is None:
            self.hash_table[index] = element
        else:
            secondary_hash_func = self.secondary_hash_funcs[index]
            while self.hash_table[index] is not None:
                index = secondary_hash_func(element)
            self.hash_table[index] = element

    def lookup(self, element):
        index = self.primary_hash_func(element)
        if self.hash_table[index] == element:
            return index
        else:
            secondary_hash_func = self.secondary_hash_funcs[index]
            while self.hash_table[index] != element:
                index = secondary_hash_func(element)
                if self.hash_table[index] is None:
                    return -1
            return index


# Example usage
input_data = [1, 2, 3, 4, 5]
perfect_hashing = PerfectHashing(input_data)
perfect_hashing.insert(6)
index = perfect_hashing.lookup(6)
print(f"Element 6 is at index {index}")
