#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "path.h"
#include "city.h"
#include "block.h"

// Cria um FILE* para o svg
FILE* createSvg(char *fullPathSvg){

    FILE *svg = fopen(fullPathSvg, "w");

    if(!svg){
        printf("Erro na criacao do SVG!!\n");
        free(fullPathSvg);
        exit(1);
    }

    fprintf(svg,"<!--nome do aluno: Israel Faustino Botelho Junior-->\n");
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/2000/xlink\">\n");
    return svg;
}

// Fecha o arquivo svg
void endSvg(FILE *svg){

    if(!svg){
        printf("Erro na finalizacao do SVG!!\n");
        exit(1);
    }

    fprintf(svg, "</svg>");
    fclose(svg);
}

// Utilizando a árvore ele desenha todas as quadras
void recursiveDrawBlock(FILE *svg, Tree root){

    if(root == NULL){
        return;
    }

    recursiveDrawBlock(svg, getTreeLeft(root));

    List list = getTreeNodeItens(root);

    for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
        Block block = getTreeListItem(getListInfo(nodeAux));

        double x, y, height, width;
        char *cep, *fill, *stroke;

        x = getBlockX(block);
        y = getBlockY(block);
        height = getBlockHeight(block);
        width = getBlockWidth(block);
        cep = getBlockCep(block);
        fill = getBlockFill(block);
        stroke = getBlockStroke(block);

        if(strcmp(fill, "@") == 0){
            fill = "none";
        }

        if(strcmp(stroke, "@") == 0){
            fill = "none";
        }
        
        fprintf(svg, "\t<rect id=\"%s\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" stroke-opacity=\"0.5\" />\n", cep, x, y, width, height, stroke, fill);
    }

    recursiveDrawBlock(svg, getTreeRight(root));
}

// Desenhar as quadras
void drawBlocks(FILE *svg, Tree tree){

    if(tree == NULL){
        return;
    }

    Node root = getTreeRoot(tree);
    
    recursiveDrawBlock(svg, root);
}

// Escreve o SVG e tudo que precisa nele
void writeGeoSvg(char *pathOut, char *nameArq, City city){
    char s[] = "svg";
    char* nameSvg = s;
    char* nameArqExtr = (char* ) extractName(nameArq);
    char* nameArqSvg = insertExtension(nameArqExtr, nameSvg);
    char* fullPathSvg = catPath(pathOut, nameArqSvg);

    FILE* svg = createSvg(fullPathSvg);

    drawBlocks(svg, getCityTree(city));

    endSvg(svg);

    free(nameArqExtr);
    free(nameArqSvg);
    free(fullPathSvg);
}