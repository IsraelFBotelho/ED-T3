#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg.h"

// Le os parametros de linha de comando e armazena os comandos passados
void readArg(int argc, char** argv, char** pathOut, char** pathIn, char** nameArqGeo, char** nameArqQry, char** nameArqPm){

    int i = 1;

    while(i < argc){
        if(strcmp("-f", argv[i]) == 0){
            i++;
            *nameArqGeo = (char *) malloc((strlen(argv[i])+ 1) * sizeof(char));
            strcpy(*nameArqGeo, argv[i]);

        }else if(strcmp("-o", argv[i]) == 0){
            i++;
            *pathOut = (char *) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathOut, argv[i]);

        }else if(strcmp("-e", argv[i]) == 0){
            i++;
            *pathIn = (char *) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathIn, argv[i]);

        }else if(strcmp("-q", argv[i]) == 0){
            i++;
            *nameArqQry = (char *) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameArqQry, argv[i]);

        }else if(strcmp("-pm", argv[i]) == 0){
            i++;
            *nameArqPm = (char *) malloc((strlen(argv[i])+ 1) * sizeof(char));
            strcpy(*nameArqPm, argv[i]);
        }
        i++;
        }

        // O programa não pode rodar sem um .geo
        if(!*pathOut || !*nameArqGeo){
            printf("Caminho de saida e/ou nome do arquivo .geo nao encontrado!\n");
            exit(1);
        }
        
    }