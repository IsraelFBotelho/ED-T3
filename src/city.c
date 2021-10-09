#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"
#include "block.h"

typedef struct cityStruct{

    Tree tree;
    HashTable table;

}CityStruct;

// Cria uma estrutura de cidade
City cityCreate(int tableSize){
    CityStruct* new = (CityStruct* ) malloc(sizeof(CityStruct));

    new->table = hashTableCreate(tableSize);
    new->tree = treeCreate("City");

    return new;
}

// Encerra uma estrutura de cidade
int cityEnd(City city){
    CityStruct* cityAux = (CityStruct* ) city;

    if(cityAux == NULL){
        return 0;
    }

    int tree = treeEnd(cityAux->tree);
    int table = hashTableEnd(cityAux->table);

    free(cityAux);
    return table == 0 || tree == 0 ? 0 : 1;
}

// Insere nas estruturas da cidade um elemento
int cityInsert(City city, Info info, double keyX, double keyY, double width, char* keyHash){
    CityStruct* cityAux = (CityStruct* ) city;

    if(cityAux == NULL){
        return 0;
    }

    int tree = treeInsert(cityAux->tree, info, keyX, keyY, width);
    int table = hashTableInsert(cityAux->table, keyHash, info);

    // printf("%s\n", getBlockCep(info));

    return tree == 0 || table == 0 ? 0 : 1;
}

// Remove uma quadra da cidade pelo Cep
int cityRemovebyCep(City city, char* cep){
    CityStruct* cityAux = (CityStruct* ) city;

    if(cityAux == NULL){
        return 0;
    }

    Block block = hashTableSearch(cityAux->table, cep);

    double x = getBlockX(block);
    double y = getBlockY(block);

    // Apaga da árvore e da tabela
    int tree = treeRemove(cityAux->tree, x, y);
    int table = hashTableRemove(cityAux->table, cep);

    // Apaga a quadra
    blockDelete(block);
    return tree == 0 || table == 0 ? 0 : 1;
}

// Recupera a árvore da cidade
Tree getCityTree(City city){
    CityStruct* cityAux = (CityStruct* ) city;

    return cityAux->tree;
}

// Recupera a tabela da cidade
HashTable getCityHashTable(City city){
    CityStruct* cityAux = (CityStruct* ) city;

    return cityAux->table;
}