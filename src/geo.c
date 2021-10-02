#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "path.h"
#include "block.h"

void readGeo(char* path, char* name, City* city){
    // Iniciar valores de leitura
    int n = 9999;
    double x, y, width, height, strokeThickness = 1;
    char stroke[25] = "black", fill[25] = "black";
    char cep[50];
    char command[30];

    char* fullPathGeo = catPath(path, name);

    FILE *geo = fopen(fullPathGeo,"r");

    // Caso não encontre o .geo
    if(geo == NULL){
        printf("Arquivo .geo nao encontrado!!\n");
        printf("%s", fullPathGeo);
        free(fullPathGeo);
        exit(1);
    }

    fscanf(geo,"%s", command);

    // Mudar o tamanho da tabela
    if(strcmp(command, "nx") == 0){
        fscanf(geo, "%d\n", &n);
    }

    rewind(geo);

    // Gera uma cidade com a tabela e a árvore
    *city = cityCreate(n);

    // Enquanto o arquivo tiver algo para se ler
    while(!feof(geo)){

        fscanf(geo,"%s", command);

        // Comando "q"
        if(strcmp(command, "q") == 0){
            fscanf(geo, "%s  %lf %lf %lf %lf\n", cep, &x, &y, &width, &height);
            Block block = blockCreate(cep, x, y, width, height, fill, stroke, strokeThickness);
            cityInsert(*city, block, x, y, cep);
        
        // Comando "cq" 
        }else if(strcmp(command, "cq") == 0){
            fscanf(geo, "%lf %s %s\n", &strokeThickness, fill, stroke);
        }
    }
    free(fullPathGeo);
    fclose(geo);
}