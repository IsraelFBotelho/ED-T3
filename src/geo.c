#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "path.h"
#include "block.h"

void readGeo(char* path, char* name, City* city){
    int n = 9999;
    double x, y, width, height, strokeThickness = 1;
    char stroke[25] = "black", fill[25] = "black";
    char cep[50];
    char command[30];

    char* fullPathGeo = catPath(path, name);

    FILE *geo = fopen(fullPathGeo,"r");

    if(geo == NULL){
        printf("Arquivo .geo nao encontrado!!\n");
        printf("%s", fullPathGeo);
        free(fullPathGeo);
        exit(1);
    }

    fscanf(geo,"%s", command);

    if(strcmp(command, "nx") == 0){
        fscanf(geo, "%d\n", &n);
    }

    rewind(geo);

    *city = cityCreate(n);

    while(!feof(geo)){

        fscanf(geo,"%s", command);

        if(strcmp(command, "q") == 0){
            fscanf(geo, "%s  %lf %lf %lf %lf\n", cep, &x, &y, &width, &height);
            Block block = blockCreate(cep, x, y, width, height, fill, stroke, strokeThickness);
            // printf("%s\n",getBlockCep(block));
            cityInsert(*city, block, x, y, cep);

        }else if(strcmp(command, "cq") == 0){
            fscanf(geo, "%lf %s %s\n", &strokeThickness, fill, stroke);
        }
    }
    free(fullPathGeo);
    fclose(geo);
}