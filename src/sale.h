#ifndef __SALE_H
#define __SALE_H

#include "hashtable.h"

typedef void* Sale;

Sale saleCreate(HashTable table, char* id, char* cep, char side, int num, char* complement, double ar, double v);

int saleDelete(Sale sale);

int saleDeleteAll(HashTable table);

char* getSaleId(Sale sale);

char* getSaleCep(Sale sale);

char getSaleSide(Sale sale);

int getSaleNumber(Sale sale);

char* getSaleComplement(Sale sale);

double getSaleAr(Sale sale);

double getSaleV(Sale sale);

double getSaleX(Sale sale);

double getSaleY(Sale sale);

int setSaleLeasing(Sale sale, int sw);

int isSaleLeasing(Sale sale);

#endif

