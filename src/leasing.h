#ifndef __LEASING_H
#define __LEASING_H


#include "block.h"
#include "city.h"
#include "person.h"

typedef void* Leasing;

/*
Função: Cria e retorna uma estrutura de locação;
Pré: Um void* com a tabela da quadra, um char* com o cep, um char com a face, um int com o numero, um char* com o complemento;
Pós: Retorna um void* com o endereço da locação.
*/
Leasing leasingCreate(HashTable table, char* cep, char side, int num, char* complement);

/*
Função: Deleta uma estrutura de locação;
Pré: Um void* com a estrutura de locação;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int leasingDelete(Leasing leasing);

/*
Função: Deleta todas as locações dentro de uma tabela de espalhamento;
Pré: Um void* para a tabela com as locações;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int leasingDeleteAll(HashTable table);

/*
Função: Retorna o Cep de uma locação;
Pré: Um void* de uma locação;
Pós: Retorna um char* com o Cep.
*/
char* getLeasingCep(Leasing leasing);

/*
Função: Retorna a face de uma locação;
Pré: Um void* de uma locação;
Pós: Retorna um char com a face.
*/
char getLeasingSide(Leasing leasing);

/*
Função: Retorna o número de uma locação;
Pré: Um void* de uma locação;
Pós: Retorna um iny1 com o número.
*/
int getLeasingNum(Leasing leasing);

/*
Função: Retorna o complemento de uma locação;
Pré: Um void* de uma locação;
Pós: Retorna um char* com o complemento.
*/
char* getLeasingComplement(Leasing leasing);

/*
Função: Retorna o morador de uma locação;
Pré: Um void* de uma locação;
Pós: Retorna um void* com o morador.
*/
Person getLeasingResident(Leasing leasing);

/*
Função: Substitui o morador de uma locação;
Pré: Um void* de uma locação, um void* de uma pessoa;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int setLeasingResident(Leasing leasing, Person person);

#endif