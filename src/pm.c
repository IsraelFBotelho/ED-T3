#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"
#include "pm.h"
#include "city.h"
#include "person.h"
#include "leasing.h"
#include "resident.h"

// Leitura do arquivo .pm
void readPm(char* path, char* name, City city, HashTable* personTable, HashTable* leasingTable, HashTable* residentTable){

    if(name == NULL){
        return;
    }

    // Inicialização de valores
    int n = 9999, day, month, year, number;
    char cpf[50], personName[50], surname[50], gender, cep[50], side, complement[50];
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

    // Criando as tabelas para as pessoas, moradores e locações
    *personTable = hashTableCreate(n);
    *leasingTable = hashTableCreate(n);
    *residentTable = hashTableCreate(n);

    while(!feof(pm)){

        fscanf(pm,"%s", command);

        // Comando "p"
        if(strcmp(command, "p") == 0){
            fscanf(pm, "%s %s %s %c %d/%d/%d \n", cpf, personName, surname, &gender, &day, &month, &year);
            Person person = personCreate(personName, surname, cpf, gender, day, month, year);
            hashTableInsert((*personTable), cpf, person);


        // Comando "m"
        }else if(strcmp(command, "m") == 0){
            fscanf(pm, "%s %s %c %d %s\n", cpf, cep, &side, &number, complement);
            Leasing leasing = leasingCreate(getCityHashTable(city), cep, side, number, complement);
            if(leasing != NULL){
                Person person = hashTableSearch(*personTable, cpf);

                if(person != NULL){
                    char key[100];
                    sprintf(key, "%s/%c/%d", cep, side, number);
                    hashTableInsert(*leasingTable, key, leasing);
                    Resident resident = residentCreate(cpf, cep, side, number, complement, person, 0);
                    hashTableInsert(*residentTable, cpf, resident);
                    setLeasingResident(leasing, resident);

                }else{
                    leasingDelete(leasing);
                }
            }
        }
    }
    free(fullPathPm);
    fclose(pm);
}