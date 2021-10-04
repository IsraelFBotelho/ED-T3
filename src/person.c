#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

typedef struct personStruct{

    char cpf[50];
    char name[50];
    char surname[50];
    char gender;
    int day, month, year;

    Block block;

}PersonStruct;

// Cria e retorna uma estrutura de pessoa
Person personCreate(char* name, char* surname, char* cpf, char gender, int day, int month, int year){
    PersonStruct* new = (PersonStruct* ) malloc(sizeof(PersonStruct));

    new->day = day;
    new->month = month;
    new->year = year;
    new->gender = gender;
    strcpy(new->cpf, cpf);
    strcpy(new->name, name);
    strcpy(new->surname, surname);

    new->block = NULL;

    return new;
}

// Deleta uma estrutura de pessoa
int personDelete(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    if(personAux == NULL){
        return 0;
    }

    free(personAux);
    return 1;
}

// Deleta todas as pessoas de uma tabela
int personDeleteAll(HashTable table){
    if(table == NULL){
        return 0;
    }

    // Primeiro for acessa indice a indice da tabela
    for(int i = 0; i < getHashTableSize(table); i++){
        List list = getHashTableList(table, i);
        if(list == NULL){
            continue;
        }

        // Segundo for acessa pessoa a pessoa da lista
        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            PersonStruct* personAux = (PersonStruct* ) getListInfo(nodeAux);
            if(personAux != NULL){
                free(personAux);
            }
        }
        endList(list);
    }

    return 1;
}

// Retorna o CPF da pessoa
char* getPersonCpf(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    return personAux->cpf;
}

// Retorna o nome da pessoa
char* getPersonName(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    return personAux->name;
}

// Retorna o sobrenome da pessoa
char* getPersonSurname(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    return personAux->surname;
}

// Retorna o sexo da pessoa
char getPersonGender(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    return personAux->gender;
}

// Retorna o dia de nascimento da pessoa
int getPersonDay(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    return personAux->day;
}

// Retorna o mês de nascimento da pessoa
int getPersonMonth(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    return personAux->month;
}

// Retorna o ano de nascimento da pessoa
int getPersonYear(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    return personAux->year;
}

// Substitui a locação da pessoa
int setPeopleHomeBlock(Person person, Block block){
    PersonStruct* personAux = (PersonStruct* ) person;

    if(block == NULL || person == NULL){
        return 0;
    }

    personAux->block = block;
    return 1;
}