#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

typedef struct item{

    Info info;
    char key[50];

}Item;

typedef struct nodeHashTable{

    List list;

}NodeHashTableStruct;

typedef struct hashTable{

    NodeHashTableStruct* nodes;
    int size;

}HashTableStruct;

HashTable hashTableCreate(int size){
    HashTableStruct* new = (HashTableStruct* ) malloc(sizeof(HashTableStruct));

    new->size = size;
    new->nodes = (NodeHashTableStruct* ) malloc(size*(sizeof(NodeHashTableStruct)));

    for(int i = 0; i < size; i++){
        new->nodes[i].list = createList();
    }

    return new;
}

int hashTableEnd(HashTable table){
    HashTableStruct* tableAux = (HashTableStruct* ) malloc(sizeof(HashTableStruct));

    if(tableAux == NULL){
        return 0;
    }

    if(tableAux->nodes != NULL){
        for(int i = 0;i < tableAux->size; i++){
            endList(tableAux->nodes[i].list);
        }

        free(tableAux->nodes);
    }
    free(tableAux);

    return 1;
}