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

    // 0 para oferta disponível / 1 para oferta locada / -1 para oferta encerrada
    int isLeasing;

    double x;
    double y;

}SaleStruct;

// Cria e retorna uma estrutura de oferta
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

    // Calcula a posição da oferta conforme a face da quadra
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

// Deleta uma estrutura de oferta
int saleDelete(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    if(saleAux == NULL){
        return 0;
    }

    free(saleAux);
    return 1;
}

// Deleta todas as ofertas em uma tabela
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

        // Segundo for acessa a oferta da lista
        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            SaleStruct* saleAux = (SaleStruct* ) getHashTableListItem(getListInfo(nodeAux));
            if(saleAux != NULL){
                free(saleAux);
            }
        }

    }

    return 1;
}

// Retorna o Id de uma oferta
char* getSaleId(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->id;
}

// Retorna o Cep de uma oferta
char* getSaleCep(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->cep;
}

// Retorna a face de uma oferta
char getSaleSide(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->side;
}

// Retorna o número de uma oferta
int getSaleNumber(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->num;
}

// Retorna o complemento de uma oferta
char* getSaleComplement(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->complement;
}

// Retorna a área de uma oferta
double getSaleAr(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->ar;
}

// Retorna o valor de uma oferta
double getSaleV(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->v;
}

// Retorna a posição X de uma oferta
double getSaleX(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->x;
}

// Retorn a posição Y de uma oferta
double getSaleY(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->y;
}

// Substitui o estado de uma oferta
int setSaleLeasing(Sale sale, int sw){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    saleAux->isLeasing = sw;

    return sw;
}

// Verifica o estado de uma oferta
int isSaleLeasing(Sale sale){
    SaleStruct* saleAux = (SaleStruct* ) sale;

    return saleAux->isLeasing;
}
