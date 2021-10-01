#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "arg.h"
#include "svg.h"
// #include "qry.h"
#include "city.h"
#include "block.h"

int main(int argc, char* argv[]){

    char *pathOut = NULL;
    char *pathIn = NULL;
    char *nameArqGeo = NULL;
    char *nameArqQry = NULL;
    char *nameArqPm = NULL;
    City city = NULL;

    readArg(argc, argv, &pathOut, &pathIn, &nameArqGeo, &nameArqQry, &nameArqPm);

    readGeo(pathIn, nameArqGeo, &city);

    writeSvg(pathOut, nameArqGeo, city);

    // readQry(pathIn, pathOut, nameArqQry, nameArqGeo, treeRect, treeCircle);


    int test = blockDeleteAll(getCityTree(city), getCityHashTable(city));\

    // printf("%d", test);
    
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