#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "geo.h"
#include "arg.h"
// #include "svg.h"
// #include "qry.h"
#include "hashtable.h"
#include "avl.h"

int main(int argc, char* argv[]){

    char *pathOut = NULL;
    char *pathIn = NULL;
    char *nameArqGeo = NULL;
    char *nameArqQry = NULL;
    char *nameArqPm = NULL;


    readArg(argc, argv, &pathOut, &pathIn, &nameArqGeo, &nameArqQry, &nameArqPm);

    // readGeo(pathIn, nameArqGeo, treeRect, treeCircle);

    // writeSvg(treeRect, treeCircle, NULL, NULL, NULL, NULL, pathOut, nameArqGeo);

    // readQry(pathIn, pathOut, nameArqQry, nameArqGeo, treeRect, treeCircle);


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