#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dot.h"
#include "path.h"
#include "block.h"

// Insere o sulfixo no nome do arquivo
char* getDotFileName(char* fullNameGeo, char* suffix){
    char* nameGeo = extractName(fullNameGeo);
    char* fullName = malloc((strlen(nameGeo) + strlen(suffix) + 2) *sizeof(char));
    sprintf(fullName ,"%s-%s", nameGeo, suffix);

    free(nameGeo);
    return fullName;
}

// Cria um arquivo .dot e escreve as forma como os nós ficam
FILE* createDot(char* fullPathDot, int size){
    FILE* dot = fopen(fullPathDot, "w");

    if(!dot){
        printf("Erro na criacao do .dot!!\n");
        free(fullPathDot);
        exit(1);
    }

    fprintf(dot ,"digraph israelBotelho {\n");
    fprintf(dot, "\tsize=\"%d\";\n", size);
    fprintf(dot, "\tnode [color=lightblue, style=filled];\n");

    return dot;
}

// Finaliza um arquivo .dot
void endDot(FILE* dot){
    if(!dot){
        printf("Erro na finalizacao do .dot!!\n");
        exit(1);
    }

    fprintf(dot, "}");
    fclose(dot);
}

// Desenha de forma recursiva os nós no arquivo escrevendo as informações no mesmo
void recDrawNodes(FILE* dot, Node root){

    if(root == NULL){
        return;
    }

    Node right = getTreeRight(root);
    Node left = getTreeLeft(root);

    double keyThis = getTreeKey(root);

    // Imprime as informações do nó
    if(getListSize(getTreeNodeItens(root)) > 2){
        NodeL nodeAux = getListFirst(getTreeNodeItens(root));
        char* cep1 = getBlockCep(getTreeListItem(getListInfo(nodeAux)));
        nodeAux = getListNext(nodeAux);
        char* cep2 = getBlockCep(getTreeListItem(getListInfo(nodeAux)));

        fprintf(dot, "\t\"%lf\" [label=\"X:%.2lf\\nAltura Do Nó:%d\\nCep:%s\\nCep:%s\\n...\\nX Máximo:%.2lf\\nX Mínimo:%.2lf\\n\"];\n", keyThis, getTreeKey(root), getTreeHeight(root), cep1, cep2, getTreeBiggerX(root), getTreeLesserX(root));
    }else{
        NodeL nodeAux = getListFirst(getTreeNodeItens(root));
        char* cep1 = getBlockCep(getTreeListItem(getListInfo(nodeAux)));

        fprintf(dot, "\t\"%lf\" [label=\"X:%.2lf\\nAltura Do Nó:%d\\nCep:%s\\nX Máximo:%.2lf\\nX Mínimo:%.2lf\\n\"];\n", keyThis, getTreeKey(root), getTreeHeight(root), cep1, getTreeBiggerX(root), getTreeLesserX(root));
    }


    // Caso Tenha filhos
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

// Cria, desenha e finaliza um arquivo .dot
int drawDotFile(char* pathOut, char* nameArq, char* sufix, Tree tree){


    // Preprarando o caminho e o nome do .dot
    char* fullNameDot = getDotFileName(nameArq, sufix);
    char d[] = "dot";
    char* nameDot = d;
    char* nameArqExtr = (char* ) extractName(fullNameDot);
    char* nameArqDot = insertExtension(nameArqExtr, nameDot);
    char* fullPathDot = catPath(pathOut, nameArqDot);

    // Criando o .dot
    FILE* dot = createDot(fullPathDot, getTreeSize(tree));

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