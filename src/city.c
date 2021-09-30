#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"

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

    int tree = treeEnd(cityAux->tree);
    int table = hashTableEnd(cityAux->table);
    return table == 0 || tree == 0 ? 0 : 1;
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