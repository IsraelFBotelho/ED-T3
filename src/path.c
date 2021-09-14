#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "path.h"

// Extrai o nome do arquivo retirando o caminho e a extensão
char* extractName(char* pathAux){

    char* path = (char *) malloc((strlen(pathAux) + 1) *sizeof(char));
    strcpy(path,pathAux);

    char* aux = NULL;

    // Tira o caminho
    aux = strchr(path, '/') != NULL ? strrchr(path, '/') + 1 : path;

    // Tira a extensão
    aux = strtok(aux, ".");

    char* name = malloc((strlen(aux) +1) *sizeof(char));
    strcpy(name, aux);

    free(path);
    return name;
}

// Concatena 2 caminhos
char* catPath(char* path1, char* path2){
    char* fullPath;

    // Caso sõ tenha somente o 2 caminho
    if(!path1){
        fullPath = (char* ) malloc((strlen(path2) + 1) * sizeof(char));
        strcpy(fullPath, path2);
        return fullPath;

    // Caso só tenha somente o 1 caminho
    }else if(!path2){
        char* fullPath = (char* ) malloc((strlen(path1) + 1) * sizeof(char));
        strcpy(fullPath, path1);
        return fullPath;

    // Caso não tenha caminho retorna nulo
    }else if(!path1 && !path2){
        return NULL;
    }

    // Caso tenha os 2 caminhos os junta ignorando uma possivel / entre eles
    if(path1[strlen(path1) - 1] != '/'){
        fullPath = (char* ) malloc((strlen(path1) + strlen(path2) + 2) * sizeof(char));
        sprintf(fullPath,"%s/%s",path1,path2);
    }else{
        fullPath = (char* ) malloc((strlen(path1) + strlen(path2) + 1) * sizeof(char));
        sprintf(fullPath,"%s%s",path1,path2);
    }
    return fullPath;
}

    // Insere uma extensão em um nome
char* insertExtension(char* name, char* extension){
    char* fullFile = NULL;

    if(!name || !extension){
        return fullFile;
    }

    fullFile = (char* ) malloc((strlen(name) + strlen(extension) + 2) * sizeof(char));
    sprintf(fullFile,"%s.%s",name, extension);

    return fullFile;
}