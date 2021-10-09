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
void writeGeoSvg(char *pathOut, char *nameArq, City city);

/*
Função: Cria e retorna um .svg com o nome do aluno e a estrutura inicial;
Pré: Um char* com o caminho completo para escrever o arquivo;
Pós Um FILE* com o arquivo.
*/
FILE* createSvg(char *fullPathSvg);

/*
Função: Finaliza um arquivo .svg;
Pré: Um FILE* com o arquivo;
Pós Nenhum retorno.
*/
void endSvg(FILE *svg);

/*
Função: Desenha as quadras de uma árvore no .svg;
Pré: Um FILE* com o svg, um void* com o endereço da arvore;
Pós: Nenhum retorno.
*/
void drawBlocks(FILE *svg, Tree tree);

#endif