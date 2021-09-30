#ifndef __BLOCK_H
#define __BLOCK_H

typedef void* Block;

#include "avl.h"

/*
Função: Cria e retorna uma estrutura de quadra com as informações;
Pré: Um char* com o cep, um double com o x, um double com o y, um double com a largura, um double com a altura, um char* com o preenchimento,
     Um char* com a borda, um double com a largura da borda;
Pós: Retorna um void* com o endereço da quadra.
*/
Block blockCreate(char cep[50], double x, double y, double width, double heigth, char fill[50], char stroke[50], double strokeThickness);

/*
Função: Deleta uma estrutura de quadra;
Pré: Um void* com a quadra;
Pós: Retorna 1 se bem sucessido ou 0 se falha.
*/
int blockDelete(Block block);

/*
Função: Deleta todas as quadras de uma estrutura de árvore ou tabela;
Pré: Um void* com o endereço da árvore, um void* com o endereço da tabela;
Pós: Retorna 1 se bem sucessido ou 0 se falha.
*/
int blockDeleteAll(Tree tree, HashTable table);

/*
Função: Recupera o valor de X da quadra;
Pré: Um void* com o endereço da quadra;
Pós: Retorna um double com o valor de X.
*/
double getBlockX(Block block);

/*
Função: Recupera o valor de Y da quadra;
Pré: Um void* com o endereço da quadra;
Pós: Retorna um double com o valor de Y.
*/
double getBlockY(Block block);

/*
Função: Recupera o valor da largura da quadra;
Pré: Um void* com o endereço da quadra;
Pós: Retorna um double com o valor da largura.
*/
double getBlockWidth(Block block);

/*
Função: Recupera o valor de altura da quadra;
Pré: Um void* com o endereço da quadra;
Pós: Retorna um double com o valor da altura.
*/
double getBlockHeight(Block block);

/*
Função: Recupera o valor da espessura da borda da quadra;
Pré: Um void* com o endereço da quadra;
Pós: Retorna um double com o valor da espessura da borda.
*/
double getBlockStrokeThickness(Block block);

/*
Função: Recupera a cor de preenchimento da quadra;
Pré: Um void* com o endereço da quadra;
Pós: Retorna um char* com a cor.
*/
char* getBlockFill(Block block);

/*
Função: Recupera a cor da borda da quadra;
Pré: Um void* com o endereço da quadra;
Pós: Retorna um char* com a cor.
*/
char* getBlockStroke(Block block);

/*
Função: Recupera CEP da quadra;
Pré: Um void* com o endereço da quadra;
Pós: Retorna um double com o CEP.
*/
char* getBlockCep(Block block);

/*
Função: Substitui a cor de preenchimento da quadra;
Pré: Um void* com o endereço da quadra, um char* com valor;
Pós: Nenhum retorno;
*/
void setBlockFill(Block block, char* fill);

/*
Função: Substitui a cor da borda da quadra;
Pré: Um void* com o endereço da quadra, um char* com valor;
Pós: Nenhum retorno;
*/
void setBlockStroke(Block block, char* stroke);

/*
Função: Substitui a espessura da borda da quadra;
Pré: Um void* com o endereço da quadra, um double com valor;
Pós: Nenhum retorno;
*/
void setBlockStrokeThickness(Block block, double strokeThickness);

#endif