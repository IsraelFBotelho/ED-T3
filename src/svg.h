#ifndef __SVG__
#define __SVG__

#include <stdio.h>
#include "block.h"
#include "city.h"

/*
Função: Cria e Preenche um arquivo svg com os arquivos de uma lista passada para um diretorio de saida;
Pre: Um char* com a string do caminho de saida, Um char* com a string do nome do SVG;
Pos: Nenhum retorno.
*/
void writeSvg(char* pathOut, char* nameArq, City city);

#endif