#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dot.h"
#include "path.h"

char* getDotFileName(char* fullNameGeo, char* suffix){
    char* nameGeo = extractName(fullNameGeo);
    char* fullName = malloc((strlen(nameGeo) + strlen(suffix) + 2) *sizeof(char));
    sprintf(fullName ,"%s-%s", nameGeo, suffix);

    free(nameGeo);
    return fullName;
}

FILE* createDot(char* fullPathDot, char* sufix, int size){
    FILE* dot = fopen(fullPathDot, "w");

    if(!dot){
        printf("Erro na criacao do .dot!!\n");
        free(fullPathDot);
        exit(1);
    }

    fprintf(dot ,"digraph %s {\n", sufix);
    fprintf(dot, "\tsize=\"%d\";\n", size);
    fprintf(dot, "\tnode [color=lightblue, style=filled];\n");

    return dot;
}

void endDot(FILE* dot){
    if(!dot){
        printf("Erro na finalizacao do .dot!!\n");
        exit(1);
    }

    fprintf(dot, "}");
    fclose(dot);
}

void recDrawNodes(FILE* dot, Node root){

    if(root == NULL){
        return;
    }

    Node right = getTreeRight(root);
    Node left = getTreeLeft(root);

    double keyThis = getTreeKey(root);

    // List list;
    // int height;
    // struct node* left;
    // struct node* right;
    // double key;
    // double lesserX;
    // double biggerX;

    fprintf(dot, "\t\"%lf\" [label=\"X:%.2lf\\nAltura Do Nó:%d\\nX Máximo:%.2lf\\nX Mínimo:%.2lf\\n\"];", keyThis, getTreeKey(root), getTreeHeight(root), getTreeBiggerX(root), getTreeLesserX(root));

    if(left != NULL){
        double keyLeft = getTreeKey(left);
        fprintf(dot, "\t\"%lf\" -> \"%lf\";\n", keyThis, keyLeft);
    }
    if(right != NULL){
        double keyRight = getTreeKey(right);
        fprintf(dot, "\t\"%lf\" -> \"%lf\";\n", keyThis, keyRight);
    }


    if(left != NULL){
        recDrawNodes(dot, left);
    }
    if(right != NULL){
        recDrawNodes(dot, right);
    }


}

int drawDotFile(char* pathOut, char* nameArq, char* sufix, Tree tree){


    // Preprarando o caminho e o nome do .dot
    char* fullNameDot = getDotFileName(nameArq, sufix);
    char d[] = "dot";
    char* nameDot = d;
    char* nameArqExtr = (char* ) extractName(fullNameDot);
    char* nameArqDot = insertExtension(nameArqExtr, nameDot);
    char* fullPathDot = catPath(pathOut, nameArqDot);

    // Criando o .dot
    FILE* dot = createDot(fullPathDot, sufix, getTreeSize(tree));

    // Função que vai desenhando no dot
    recDrawNodes(dot, getTreeRoot(tree));

    // Terminando o .dot
    endDot(dot);

    free(nameArqDot);
    free(fullPathDot);
    free(nameArqExtr);
    free(fullNameDot);

    return 1;
}