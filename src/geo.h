#ifndef __GEO_H
#define __GEO_H

#include "city.h"

/*
Função: Abre e Lê um arquivo .geo, le os seus comandos e armazena as informaçoes em uma estrutura de dados;
Pre: Um char* com o caminho, um char* com o nome, um void* com a estrutura da cidade;
Pos: Nenhum retorno.
*/
void readGeo(char* path, char* name, City* city);

#endif