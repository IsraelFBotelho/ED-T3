#ifndef __SALE_H
#define __SALE_H

#include "hashtable.h"

typedef void* Sale;

/*
Função: Cria e retorna uma estrutura de oferta;
Pré: Um void* com o endereço da tabela de quadras, um char* com o id, um char* com o cep, um char com a face, um int com o número,
     um char* com o complemento, um double com a área, um double com o valor;
Pós: Retorna um void* com o endereço da oferta.
*/
Sale saleCreate(HashTable table, char* id, char* cep, char side, int num, char* complement, double ar, double v);

/*
Função: Deleta uma estrutura de oferta;
Pré: Um void* com o endereçon da oferta;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int saleDelete(Sale sale);

/*
Função: Deleta todas as ofertas de uma tabela;
Pré: Um void* com o endereço da tabela;
Pós: Retorna se sucesso ou 0 para falha.
*/
int saleDeleteAll(HashTable table);

/*
Função: Retorna o Id de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um char* com valor.
*/
char* getSaleId(Sale sale);

/*
Função: Retorna o Cep de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um char* com valor.
*/
char* getSaleCep(Sale sale);

/*
Função: Retorna a face de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um char com valor.
*/
char getSaleSide(Sale sale);

/*
Função: Retorna o número de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um int com valor.
*/
int getSaleNumber(Sale sale);

/*
Função: Retorna o complemento de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um char* com valor.
*/
char* getSaleComplement(Sale sale);

/*
Função: Retorna a área de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um double com valor.
*/
double getSaleAr(Sale sale);

/*
Função: Retorna o valor de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um double com valor.
*/
double getSaleV(Sale sale);

/*
Função: Retorna a posição X de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um double com valor.
*/
double getSaleX(Sale sale);

/*
Função: Retorna a posição Y de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um double com valor.
*/
double getSaleY(Sale sale);

/*
Função: Substitui o estado de uma oferta;
Pré: Um void* com o endereço da oferta, um int com o novo estado;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int setSaleLeasing(Sale sale, int sw);

/*
Função: Verifica o estado de uma oferta;
Pré: Um void* com o endereço da oferta;
Pós: Retorna um int com 1, 0 ou -1.
*/
int isSaleLeasing(Sale sale);

#endif

