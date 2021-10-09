#ifndef __DOT_H_
#define __DOT_H

#include "avl.h"

/*
Função: Cria um arquivo .dot com as informações da árvore;
Pré: Um char* com o caminho de saída, um char* com o nome do .geo, um char* sulfixo para o .dot, um void* com o endereço da árvore;
Pós: Retorna 1 para sucesso ou 0 para falha.
*/
int drawDotFile(char* pathOut, char* nameArq, char* sufix, Tree tree);

#endif