#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "block.h"
#include "avl.h"
#include "hashtable.h"

typedef struct blockStruct{

    char stroke[50];
    double strokeThickness;
    char fill[50];
    char cep[50];
    double x;
    double y;
    double width;
    double height;

}BlockStruct;

// Cria e retorna uma quadra
Block blockCreate(char cep[50], double x, double y, double width, double heigth, char fill[50], char stroke[50], double strokeThickness){
    BlockStruct* new = (BlockStruct* ) malloc(sizeof(BlockStruct));

    new->x = x;
    new->y = y;
    new->width = width;
    new->height = heigth;
    new->strokeThickness = strokeThickness;
    strcpy(new->stroke, stroke);
    strcpy(new->fill, fill);
    strcpy(new->cep, cep);

    return new;
}

// Deleta a quadra e retorna 1 se deu certo
int blockDelete(Block block){

    BlockStruct* blockAux = (BlockStruct* ) block;

    if(blockAux == NULL){
        return 0;
    }

    free(blockAux);
    return 1;
}

// Percorre uma estrutura de árvore e vai deletando todas as quadras das listas
void blockDeleteAllTree(Node root){
    if(root == NULL){
        return;
    }

    blockDeleteAllTree(getTreeRight(root));
    blockDeleteAllTree(getTreeLeft(root));

    List* list = getTreeNodeItens(root);

    if(list == NULL){
        return;
    }

    for(NodeL* nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
        Info block = getTreeListItem(getListInfo(nodeAux));
        
        blockDelete(block);
    }
}

// Percorre uma estrutura de tabela de espalhamento e vai deletando todas as quadras das listas
void blockDeleteAllHashTable(HashTable table){
    for(int i = 0; i < getHashTableSize(table); i++){
        List list = getHashTableList(table, i);

        for(NodeL* nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Info block = getHashTableListItem(getListInfo(nodeAux));
            blockDelete(block);
        }
    }

}

// Chama as funções que percorre as estruturas e vai deletando todas as quadras
int blockDeleteAll(Tree tree, HashTable table){
    if(tree == NULL && table == NULL){
        return 0;
    }

    if(tree != NULL){
        blockDeleteAllTree(getTreeRoot(tree));
        return 1;
    }else{
        blockDeleteAllHashTable(table);
        return 1;
    }

}

// Retorna o X da quadra
double getBlockX(Block block){
    BlockStruct* blockAux = (BlockStruct* ) block;

    return blockAux->x;
}

// Retorna o Y da quadra
double getBlockY(Block block){
    BlockStruct* blockAux = (BlockStruct* ) block;

    return blockAux->y;
}

// Retorna a largura da quadra
double getBlockWidth(Block block){
    BlockStruct* blockAux = (BlockStruct* ) block;

    return blockAux->width;
}

// Retorna a altura da quadra
double getBlockHeight(Block block){
    BlockStruct* blockAux = (BlockStruct* ) block;

    return blockAux->height;
}

// Retorna o CEP da quadra
char* getBlockCep(Block block){
    BlockStruct* blockAux = (BlockStruct* ) block;

    return blockAux->cep;
}

// Retorna a cor da borda da quadra
char* getBlockStroke(Block block){
    BlockStruct* blockAux = (BlockStruct* ) block;

    return blockAux->stroke;
}

// Retorna a cor do preenchimento da quadra
char* getBlockFill(Block block){
    BlockStruct* blockAux = (BlockStruct* ) block;

    return blockAux->fill;
}

// Retorna o tamanho da espessura da borda da quadra
double getBlockStrokeThickness(Block block){
    BlockStruct* blockAux = (BlockStruct* ) block;

    return blockAux->strokeThickness;
}

// Substitui o valor do tamanho da espessura da borda da quadra
void setBlockStrokeThickness(Block block, double strokeThickness){
    BlockStruct* blockAux = (BlockStruct* ) block;

    blockAux->strokeThickness = strokeThickness;
}

// Substitui o valor da cor da borda da quadra
void setBlockStroke(Block block, char* stroke){
    BlockStruct* blockAux = (BlockStruct* ) block;

    strcpy(blockAux->stroke, stroke);
}

// Substitui o valor da cor do preenchimento da quadra
void setBlockFill(Block block, char* fill){
    BlockStruct* blockAux = (BlockStruct* ) block;

    strcpy(blockAux->fill, fill);
}