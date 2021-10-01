#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pm.h"

void readPm(char* path, char* name, HashTable* table){

    if(name == NULL){
        return;
    }

    int n = 9999, day, month, year, number;
    char cpf[50], name[50], surname[50], gender, cep[50], side, complement[50];
    char command[30];

    char* fullPathPm = catPath(path, name);

    FILE *pm = fopen(fullPathPm,"r");

    if(pm == NULL){
        printf("Arquivo .pm nao encontrado!!\n");
        printf("%s", fullPathPm);
        free(fullPathPm);
        exit(1);
    }

    fscanf(pm,"%s", command);

    if(strcmp(command, "nx") == 0){
        fscanf(pm, "%d\n", &n);
    }

    rewind(pm);

    *table = hashTableCreate(n);

    while(!feof(pm)){

        fscanf(pm,"%s", command);

        if(strcmp(command, "p") == 0){
            fscanf(pm, "%s %s %s %c %d/%d/%d \n", cpf, name, surname, &gender, day, month, year);

        }else if(strcmp(command, "m") == 0){
            fscanf(pm, "%s %s %c %d %s\n", cpf, cep, side, number, complement);
        }
    }
    free(fullPathPm);
    fclose(pm);
}