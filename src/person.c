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

}PersonStruct;

Person personCreate(char* name, char* surname, char* cpf, char gender, int day, int month, int year){
    PersonStruct* new = (PersonStruct* ) malloc(sizeof(PersonStruct));

    new->day = day;
    new->month = month;
    new->year = year;
    new->gender = gender;
    strcpy(new->cpf, cpf);
    strcpy(new->name, name);
    strcpy(new->surname, surname);

    return new;
}

int personDelete(Person person){
    PersonStruct* personAux = (PersonStruct* ) person;

    if(personAux == NULL){
        return 0;
    }

    free(personAux);
    return 1;
}

int personDeleteAll(HashTable table){
    if(table == NULL){
        return 0;
    }

    for(int i = 0; i < getHashTableSize(table); i++){
        List list = getHashTableList(table, i);
        if(list == NULL){
            continue;
        }

        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            PersonStruct* personAux = (PersonStruct* ) getListInfo(nodeAux);
            if(personAux != NULL){
                free(personAux);
            }
        }
    }

    return 1;
}