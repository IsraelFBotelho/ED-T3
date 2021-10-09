#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "arg.h"
#include "svg.h"
#include "pm.h"
#include "qry.h"
#include "city.h"
#include "block.h"
#include "leasing.h"
#include "person.h"
#include "resident.h"

// Função main
int main(int argc, char* argv[]){

    // Inicializando valores
    char *pathOut = NULL;
    char *pathIn = NULL;
    char *nameArqGeo = NULL;
    char *nameArqQry = NULL;
    char *nameArqPm = NULL;
    City city = NULL;
    HashTable personTable = NULL;
    HashTable leasingTable = NULL;
    HashTable residentTable = NULL;

    // Leitura dos argumentos da linha de comando
    readArg(argc, argv, &pathOut, &pathIn, &nameArqGeo, &nameArqQry, &nameArqPm);

    // Leitura e armazenamento do .geo
    readGeo(pathIn, nameArqGeo, &city);

    // Desenhando o .svg do .geo
    writeGeoSvg(pathOut, nameArqGeo, city);

    // Leitura e armazenamento do .pm
    readPm(pathIn, nameArqPm, city, &personTable, &leasingTable, &residentTable);

    // Leitura e modificações do .qry
    readQry(pathIn, pathOut, nameArqQry, nameArqGeo, city, personTable, leasingTable, residentTable);


    // Desalocação de valores

    blockDeleteAll(getCityTree(city), getCityHashTable(city));

    leasingDeleteAll(leasingTable);

    personDeleteAll(personTable);

    residentDeleteAll(residentTable);

    hashTableEnd(personTable);
    hashTableEnd(leasingTable);
    hashTableEnd(residentTable);
    
    cityEnd(city);

    if(pathOut){
        free(pathOut);
    }
    if(nameArqGeo){
        free(nameArqGeo);
    }
    if(pathIn){
        free(pathIn);
    }
    if(nameArqQry){
        free(nameArqQry);
    }
    if(nameArqPm){
        free(nameArqPm);
    }

    return 0;
}