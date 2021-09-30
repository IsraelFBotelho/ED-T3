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

int blockDelete(Block block){

    BlockStruct* blockAux = (BlockStruct* ) block;

    if(blockAux == NULL){
        return 0;
    }

    free(blockAux);
    return 1;
}

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
        Info block = getListInfo(nodeAux);
        blockDelete(block);
    }
    endList(list);
}

void blockDeleteAllHashTable(HashTable table){
    for(int i = 0; i < getHashTableSize(table); i++){
        List list = getHashTableList(table, i);

        for(NodeL* nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Info block = getListInfo(nodeAux);
            blockDelete(block);
        }
        endList(list);
    }

}

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