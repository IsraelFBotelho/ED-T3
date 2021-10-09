#ifndef __RESIDENT_H
#define __RESIDENT_H

typedef void* Resident;

#include "hashtable.h"
#include "person.h"

/*
Função: Cria e retorna uma estrutura de morador;
Pré: Um char* com o cpf, um char* com o cep, um char com a face, um int com o número, um char* com o complemento,
     um void* com o endereço da pessoa, um int com se é alugado;
Pós: Retorna um void* com o endereço do morador.
*/
Resident residentCreate(char* cpf, char* cep, char side, int num, char* complement, Person person, int isRent);

/*
Função: Deleta uma estrutura de morador;
Pré: Um void* com o endereço do morador;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int residentDelete(Resident resident);

/*
Função: Deleta todos os moradores dentro de uma tabela;
Pré: Um void* com o endereço da tabela;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int residentDeleteAll(HashTable table);

/*
Função: Retorna o Cep de um morador;
Pré: Um void* com o endereço do morador;
Pós: Retorna um char* com valor.
*/
char* getResidentCep(Resident resident);

/*
Função: Retorna o Cpf de um morador;
Pré: Um void* com o endereço do morador;
Pós: Retorna um char* com valor.
*/
char* getResidentCpf(Resident resident);

/*
Função: Retorna a face de um morador;
Pré: Um void* com o endereço do morador;
Pós: Retorna um char com valor.
*/
char getResidentSide(Resident resident);

/*
Função: Retorna o número de um morador;
Pré: Um void* com o endereço do morador;
Pós: Retorna um int com valor.
*/
int getResidentNumber(Resident resident);

/*
Função: Retorna o Complemento de um morador;
Pré: Um void* com o endereço do morador;
Pós: Retorna um char* com valor.
*/
char* getResidentComplement(Resident resident);

/*
Função: Retorna a pessoa referente a um morador;
Pré: Um void* com o endereço do morador;
Pós: Retorna um void* com o endereço da pessoa.
*/
Person getResidentPerson(Resident resident);

/*
Função: Verifica se um morador paga aluguel;
Pré: Um void* com o endereço do morador;
Pós: Retorna int com 0 ou 1.
*/
int isResidentRent(Resident resident);

#endif