#ifndef __PM_H
#define __PM_H

#include "city.h"


/*
Função: Abre e lê um arquivo .pm, lê seus comandos e armazena as informações em estruturas de dados;
Pré: Um char* com o caminho de entrada, um void* com o endereço da cidade, um void** com o endereço da tabela de pessoas,
     um void** com o endereço da tabela de locações, um void** com a tabela de moradores;
Pós: Nenhum retorno.
*/
void readPm(char* path, char* name, City city, HashTable* personTable, HashTable* leasingTable, HashTable* residentTable);

#endif