#ifndef __PERSON_H
#define __PERSON_H

typedef void* Person;

#include "hashtable.h"
#include "leasing.h"


/*
Função: Cria e retorna uma estrutura de pessoa;
Pré: Um char* com o nome, um char* com o sobrenome, um char* com o pdf, um char com o sexo, um int com o dia de nascimento,
     Um int com o mês de nascimento, um int com o ano de nascimento;
Pós: Retorna um void* com o endereço.
*/
Person personCreate(char* name, char* surname, char* cpf, char gender, int day, int month, int year);

/*
Função: Deleta uma estrutura de pessoa;
Pré: Um void* com o endereço da pessoa;
Pós: Retorna 1 para sucesso ou 0 para falha.
*/
int personDelete(Person person);

/*
Função: Deleta todas as pessoas dentro de uma tabela de espalhamento;
Pré: Um void* com o endereço de uma tabela;
Pós: Retorna 1 para sucesso ou 0 para falha.
*/
int personDeleteAll(HashTable table);

/*
Função: Retorna o CPF de uma pessoa;
Pré: Um void* com o endereço da pessoa;
Pós: Retorna um char* com o CPF.
*/
char* getPersonCpf(Person person);

/*
Função: Retorna o nome de uma pessoa;
Pré: Um void* com o endereço da pessoa;
Pós: Retorna um char* com o nome.
*/
char* getPersonName(Person person);

/*
Função: Retorna o sobrenome de uma pessoa;
Pré: Um void* com o endereço da pessoa;
Pós: Retorna um char* com o sobrenome.
*/
char* getPersonSurname(Person person);

/*
Função: Retorna o sexo de uma pessoa;
Pré: Um void* com o endereço da pessoa;
Pós: Retorna um char com o sexo.
*/
char getPersonGender(Person person);

/*
Função: Retorna o dia de nascimento de uma pessoa;
Pré: Um void* com o endereço da pessoa;
Pós: Retorna um int com o dia.
*/
int getPersonDay(Person person);

/*
Função: Retorna o mês de nascimento de uma pessoa;
Pré: Um void* com o endereço da pessoa;
Pós: Retorna um int com o mês.
*/
int getPersonMonth(Person person);

/*
Função: Retorna o ano de nascimento de uma pessoa;
Pré: Um void* com o endereço da pessoa;
Pós: Retorna um int com o ano.
*/
int getPersonYear(Person person);

/*
Função: Substitui a locação da pessoa por outra;
Pré: Um void* com o endereço da pessoa, um void* com o endereço da locação;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int setPeopleLeasing(Person person, Leasing leasing);

#endif