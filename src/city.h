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

/*
Função: Insere um item na cidade, os adicionando nas 2 estruturas;
Pré: Um void* com o endereço da cidade, um void* com a info, um double a chave X, um double com a chave Y,
     um char* com uma chave para hash;
Pós: Retorna um int caso bem sucedido ou 0 para falha.
*/
int cityInsert(City city, Info info, double keyX, double keyY, char* keyHash);

/*
*/
int cityRemovebyCep(City city, char* cep);

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