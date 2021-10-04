#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "arg.h"
#include "svg.h"
#include "pm.h"
// #include "qry.h"
#include "city.h"
#include "block.h"
#include "leasing.h"
#include "person.h"

int main(int argc, char* argv[]){

    char *pathOut = NULL;
    char *pathIn = NULL;
    char *nameArqGeo = NULL;
    char *nameArqQry = NULL;
    char *nameArqPm = NULL;
    City city = NULL;
    HashTable personTable = NULL;
    HashTable leasingTable = NULL;

    readArg(argc, argv, &pathOut, &pathIn, &nameArqGeo, &nameArqQry, &nameArqPm);

    readGeo(pathIn, nameArqGeo, &city);

    writeSvg(pathOut, nameArqGeo, city);

    readPm(pathIn, nameArqPm, city, &personTable, &leasingTable);

    // readQry(pathIn, pathOut, nameArqQry, nameArqGeo, treeRect, treeCircle);


    blockDeleteAll(getCityTree(city), getCityHashTable(city));

    leasingDeleteAll(leasingTable);

    personDeleteAll(personTable);

    // printf("%d", test);

    hashTableEnd(personTable);
    hashTableEnd(leasingTable);
    
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