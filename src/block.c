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
}

int blockDeleteAll(Tree tree, HashTable table, int sw){
    
}