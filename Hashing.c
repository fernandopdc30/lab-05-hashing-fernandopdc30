#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// entrada en la tabla
typedef struct Entry {
    int key;
    int value;
    struct Entry* next;
} Entry;

// definimos una tabla 
typedef struct {
    Entry** table;
    int size;
} HashTable;

// funcion
int customHash(int x, int tableSize) {
    return x % tableSize;
}


HashTable* initHashTable(int tableSize) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->table = (Entry**)malloc(tableSize * sizeof(Entry*));
    for (int i = 0; i < tableSize; i++) {
        ht->table[i] = NULL;
    }
    ht->size = tableSize;
    return ht;
}

void insert(HashTable* ht, int key, int value) {
    int index = customHash(key, ht->size);
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = ht->table[index];
    ht->table[index] = newEntry;
}

// buscar un elemento en la tabla
int find(HashTable* ht, int key) {
    int index = customHash(key, ht->size);
    Entry* current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

int main() {
    srand(time(NULL));
    HashTable* ht = initHashTable(10);

    int x = 1234567;
    long long y = 76554334234LL; 
    insert(ht, x, x);
    printf("%d\n", find(ht, 1234567));

    for (int i = 0; i < ht->size; i++) {
        Entry* current = ht->table[i];
        while (current != NULL) {
            Entry* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(ht->table);
    free(ht);
    return 0;
}
