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

// Retorna um int positivo com valor de hash
unsigned long int hashIndex(char key[50], int size){
    unsigned long int hash;

    for (hash = 0; *key != '\0'; key++)
        hash = *key + 31*hash;

    return hash % size;
}

// Cria a tabela, aloca cada nó e inicia cada lista de cada nó
HashTable hashTableCreate(int size){
    HashTableStruct* new = (HashTableStruct* ) malloc(sizeof(HashTableStruct));

    new->size = size;
    new->nodes = (NodeHashTableStruct* ) malloc(size*(sizeof(NodeHashTableStruct)));

    for(int i = 0; i < size; i++){
        new->nodes[i].list = createList();
    }

    return new;
}

// Deleta a tabela e se tiver nó deleta eles e as listas
int hashTableEnd(HashTable table){
    HashTableStruct* tableAux = (HashTableStruct* ) table;

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

// Função de inserir um valor na hashtable
int hashTableInsert(HashTable table, char key[50], Info info){
    HashTableStruct* tableAux = (HashTableStruct* ) table;

    if((key == NULL || info == NULL) || table == NULL){
        return 0;
    }

    Item* new = (Item* ) malloc(sizeof(Item));

    // Preencho o item para caso de conflito
    strcpy(new->key, key);
    new->info = info;

    // Função hash para o index
    int index = hashIndex(key, tableAux->size);
    insertListElement(tableAux->nodes[index].list, new);

    return 1;
}

int hashTableRemove(HashTable table, char key[50]){
    HashTableStruct* tableAux = (HashTableStruct* ) table;
    int res = 0;
    if(key == NULL || table == NULL){
        return 0;
    }

    // Função hash para o index
    int index = hashIndex(key, tableAux->size);

    // Percorre a lista e se encontrar o CEP da free() no item
    for(NodeL nodeAux = getListFirst(tableAux->nodes[index].list); nodeAux; nodeAux = getListNext(nodeAux)){
        Item* item = (Item*) getListInfo(nodeAux);

        if(strcmp(key, item->key) == 1){
            free(item);
            res = 1;
            break;
        }
    }

    return res;
}

// Acessa o endereço do hash e percorre a lista retornando o Info se existir
Info hashTableSearch(HashTable table, char key[50]){
    HashTableStruct* tableAux = (HashTableStruct* ) table;

    if(key == NULL || table == NULL){
        return NULL;
    }

    // Função hash para o index
    int index = hashIndex(key, tableAux->size);

    // Percorre a lista e se encontrar o CEP da free() no item
    for(NodeL nodeAux = getListFirst(tableAux->nodes[index].list); nodeAux; nodeAux = getListNext(nodeAux)){
        Item* item = (Item*) getListInfo(nodeAux);

        if(strcmp(key, item->key) == 1){
            return item->info;
            break;
        }
    }

    return NULL;
}
