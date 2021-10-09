#ifndef __QRY_H
#define __QRY_H

#include "city.h"
/*
Função: Abre e lê um arquivo .qry, lê seus comandos e os execulta gerando arquivos no diretorio de saída;
Pré: Um char* com o caminho de entrada, um char* com o caminho de saída, um char* com o nome do .qry, um char* com o nome do .geo,
     um void* com o endereço da cidade, um void* com o endereço da tabela de pessoas, um void* com o endereço de locações,
     um void* com o endereço com a tabela de moradores;
Pós: Retorna 1 se sucesso ou 0 para falha;
*/
int readQry(char *pathIn, char* pathOut ,char *nameQry, char *nameGeo, City city, HashTable personTable, HashTable leasingTable, HashTable residentTable);
#endif