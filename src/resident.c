#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resident.h"

typedef struct residentStruct{
    char cep[50];
    char side;
    int num;
    char complement[50];
    int isRent;

    char cpf[50];
    Person person;

}ResidentStruct;

// Cria uma estrutura de morador e retorna
Resident residentCreate(char* cpf, char* cep, char side, int num, char* complement, Person person, int isRent){
    ResidentStruct* new = (ResidentStruct* ) malloc(sizeof(ResidentStruct));
    
    strcpy(new->cpf, cpf);
    strcpy(new->cep, cep);
    new->num = num;
    new->side = side;
    strcpy(new->complement, complement);
    new->isRent = isRent;

    new->person = person;

    return new;
}

// Deleta uma estrutura de morador
int residentDelete(Resident resident){
    ResidentStruct* residentAux = (ResidentStruct* ) resident;

    if(residentAux == NULL){
        return 0;
    }

    free(residentAux);
    return 1;
}

// Percorre uma tabela e deleta todos os moradores que encontrar
int residentDeleteAll(HashTable table){
    if(table == NULL){
        return 0;
    }

    // Primeiro for acessa indice a indice da tabela
    for(int i = 0; i < getHashTableSize(table); i++){
        List list = getHashTableList(table, i);
        if(list == NULL){
            continue;
        }

        // Segundo for acessa o morador da lista
        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            ResidentStruct* residentAux = (ResidentStruct* ) getHashTableListItem(getListInfo(nodeAux));
            if(residentAux != NULL){
                free(residentAux);
            }
        }

    }

    return 1;
}

// Retorna o Cep do morador
char* getResidentCep(Resident resident){
    ResidentStruct* residentAux = (ResidentStruct* ) resident;

    return residentAux->cep;
}

// Retorna o Cpf do morador
char* getResidentCpf(Resident resident){
    ResidentStruct* residentAux = (ResidentStruct* ) resident;

    return residentAux->cpf;
}

// Retorna a Face do morador
char getResidentSide(Resident resident){
    ResidentStruct* residentAux = (ResidentStruct* ) resident;

    return residentAux->side;
}

// Retorna o numero do morador
int getResidentNumber(Resident resident){
    ResidentStruct* residentAux = (ResidentStruct* ) resident;

    return residentAux->num;
}

// Retorna o complemento do morador
char* getResidentComplement(Resident resident){
    ResidentStruct* residentAux = (ResidentStruct* ) resident;

    return residentAux->complement;
}

// Retorna a pessoa referente ao morador
Person getResidentPerson(Resident resident){
    ResidentStruct* residentAux = (ResidentStruct* ) resident;

    return residentAux->person;
}

// Retorna se o morador paga aluguel
int isResidentRent(Resident resident){
    ResidentStruct* residentAux = (ResidentStruct* ) resident;

    return residentAux->isRent;
}