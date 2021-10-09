#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "list.h"

typedef void* HashTable;

/*
Função: Cria uma estrutura de tabela de espalhamento e armazena o tamanho;
Pré: Um int com o tamanho;
Pós: Retorna um void* com o endereço da tabela.
*/
HashTable hashTableCreate(int size);

/*
Função: Encerra uma estrutura de tabela de espalhamento;
Pré: Um void* com a tabela;
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int hashTableEnd(HashTable table);

/*
Função: Insere um valor na tabela codificado com um Hash;
Pré: Um void* com a tabela, Um char[50] com a chave, Um void* com a informação;
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int hashTableInsert(HashTable table, char key[50], Info info);

/*
Função: Remove um valor da tabela;
Pré: Um void* com a tabela, Um char[50] com a chave;
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int hashTableRemove(HashTable table, char key[50]);

/*
Função: Com a chave busca a informação com a chave;
Pré: Um void* com a tabela, Um char[50] com a chave;
Pós: Retorna um void* com a informação.
*/
Info hashTableSearch(HashTable table, char key[50]);

/*
Função: Retorna uma lista preenchida com todas as informações de determinado índice;
Pré: Um void* com a tabela, Um int com o índice;
Pós: Retorna um void* com a lista.
*/
List getHashTableList(HashTable table, int index);

/*
Função: Retorna o tamanho da tabela de espalhamento;
Pré: Um void* com a tabela;
Pós: Retorna um int com o tamanho.
*/
int getHashTableSize(HashTable table);

/*
Função: Retorna o Info dentro do Item da tabela da espalhamento;
Pré: Um void* com a tabela;
Pós: Retorna um void* com o info.
*/
Info getHashTableListItem(Info item);

/*
Função: Retorna a chave dentro do Item da tabela da espalhamento;
Pré: Um void* com a tabela;
Pós: Retorna um char* com a chave.
*/
char* getHashTableListKey(Info item);

#endif