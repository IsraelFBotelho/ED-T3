#ifndef __CITY_H
#define __CITY_H

#include "avl.h"
#include "hashtable.h"

typedef void* City;


/*
Função: Cria e retorna uma estrutura de cidade;
Pré: Um int com a quantidade de quadras da cidade;
Pós: Retorna um void* com o endereço da cidade.
*/
City cityCreate(int tableSize);

/*
Função: Encerra uma estrutura de cidade;
Pré: Um void* com o endereço da cidade;
Pós: Retorna um int caso bem sucedido ou 0 para falha.
*/
int cityEnd(City city);

int cityInsert(City city, Info info, double keyY, double keyX, char* keyHash);

/*
Função: Recupera a estrutura de árvore na estrutura de cidade;
Pré: Um void* com o endereço da cidade;
Pós: Retorna um void* com o endereço da árvore.
*/
Tree getCityTree(City city);

/*
Função: Recupera a estrutura de tabela de espalhamento na estrutura de cidade;
Pré: Um void* com o endereço da cidade;
Pós: Retorna um void* com o endereço da tabela.
*/
HashTable getCityHashTable(City city);

#endif