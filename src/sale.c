#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sale.h"
#include "block.h"

typedef struct saleStruct{

    char id[50];
    char cep[50];
    char side;
    int num;
    char complement[50];
    double ar;
    double v;

    int isLeasing;

    double x;
    double y;

}SaleStruct;

Sale saleCreate(HashTable table, char* id, char* cep, char side, int num, char* complement, double ar, double v){
    SaleStruct* new = (SaleStruct* ) malloc(sizeof(SaleStruct));

    strcpy(new->id, id);
    strcpy(new->cep, cep);
    strcpy(new->complement, complement);
    new->side = side;
    new->num = num;
    new->ar = ar;
    new->v = v;
    new->isLeasing = 0;

    Block block = hashTableSearch(table, cep);

    if(block == NULL){
        free(new);
        return NULL;
    }

    if(side == 'S'){
        new->y = getBlockY(block) + (num/2);
        new->x = getBlockX(block) + num;
    }else if(side == 'N'){
        new->x = getBlockX(block) + num;
        new->y = getBlockY(block) + getBlockHeight(block) - (num/2);
    }else if(side == 'L'){
        new->x = getBlockX(block) + (num/2);
        new->y = getBlockY(block) + num;
    }else{
        new->x = getBlockX(block) + getBlockWidth(block) - (num/2);
        new->y = getBlockY(block) + num;
    }

    return new;
}

int saleDelete(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    if(saleAux == NULL){
        return 0;
    }

    free(saleAux);
    return 1;
}

int saleDeleteAll(HashTable table){
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
            SaleStruct* saleAux = (SaleStruct* ) getHashTableListItem(getListInfo(nodeAux));
            if(saleAux != NULL){
                free(saleAux);
            }
        }

    }

    return 1;
}

char* getSaleId(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->id;
}

char* getSaleCep(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->cep;
}

char getSaleSide(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->side;
}

int getSaleNumber(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->num;
}

char* getSaleComplement(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->complement;
}

double getSaleAr(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->ar;
}

double getSaleV(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->v;
}

double getSaleX(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->x;
}

double getSaleY(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->y;
}

int setSaleLeasing(Sale sale, int sw){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    saleAux->isLeasing = sw;

    return sw;
}

int isSaleLeasing(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->isLeasing;
}
