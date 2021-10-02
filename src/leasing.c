#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leasing.h"

typedef struct leasingStruct{

    char cep[50];
    char side;
    int num;
    char complement[50];

    Person resident;
    Block block;

}LeasingStruct;

// Cria e retorna uma estrutura de locação
Leasing leasingCreate(HashTable table, char* cep, char side, int num, char* complement){
    LeasingStruct* new = (LeasingStruct* ) malloc(sizeof(LeasingStruct));

    new->num = num;
    new->side = side;
    strcpy(new->cep, cep);
    strcpy(new->complement, complement);

    new->resident = NULL;

    new->block = hashTableSearch(table, cep);

    if(new->block == NULL){
        free(new);
        return NULL;
    }

    return new;
}

// Deleta uma estrutura de locação
int leasingDelete(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    if(leasingAux == NULL){
        return 0;
    }

    free(leasingAux);
    return 1;
}

// Deleta todas as locações de uma tabela
int leasingDeleteAll(HashTable table){
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
            LeasingStruct* leasingAux = (LeasingStruct* ) getListInfo(nodeAux);
            if(leasingAux != NULL){
                free(leasingAux);
            }
        }
    }

    return 1;
}

// Retorna o Cep onde a locação está
char* getLeasingCep(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    return leasingAux->cep;
}

// Retorna o lado onde a locação está
char getLeasingSide(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    return leasingAux->side;
}

// Retorna o numero da locação
int getLeasingNum(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    return leasingAux->num;
}

// Retorna o complemento da locação
char* getLeasingComplement(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    return leasingAux->complement;
}

// Retorna o morador da locação
Person getLeasingResident(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    return leasingAux->resident;
}

// Substitui o morador da locação
int setLeasingResident(Leasing leasing, Person person){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    if(leasingAux == NULL){
        return 0;
    }

    leasingAux->resident = person;

    if(person != NULL){
        setPeopleLeasing(person, leasing);
    }

    return 1;
}
