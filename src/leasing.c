#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leasing.h"

typedef struct leasingStruct{

    char cep[50];
    char side;
    int num;
    char complement[50];

    Resident resident;
    Block block;

    double x;
    double y;

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

    if(side == 'S'){
        new->y = getBlockY(new->block) + (num/2);
        new->x = getBlockX(new->block) + num;
    }else if(side == 'N'){
        new->x = getBlockX(new->block) + num;
        new->y = getBlockY(new->block) + getBlockHeight(new->block) - (num/2);
    }else if(side == 'L'){
        new->x = getBlockX(new->block) + (num/2);
        new->y = getBlockY(new->block) + num;
    }else{
        new->x = getBlockX(new->block) + getBlockWidth(new->block) - (num/2);
        new->y = getBlockY(new->block) + num;
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
            LeasingStruct* leasingAux = (LeasingStruct* ) getHashTableListItem(getListInfo(nodeAux));
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
Resident getLeasingResident(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    return leasingAux->resident;
}

// Substitui o morador da locação
int setLeasingResident(Leasing leasing, Resident resident){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    if(leasingAux == NULL){
        return 0;
    }

    leasingAux->resident = resident;
    return 1;
}

double getLeasingX(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    return leasingAux->x;
}

double getLeasingY(Leasing leasing){
    LeasingStruct* leasingAux = (LeasingStruct* ) leasing;

    return leasingAux->y;
}