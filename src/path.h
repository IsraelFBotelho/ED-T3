#ifndef __PATH_H
#define __PATH_H

/*
Função: Recupera o nome de um arquivo, estando ele dentro ou nao de um caminho
Pré: Um char* com o nome e extensao e/ou caminho do arquivo
Pós: Um char* com o nome do arquivo
*/
char* extractName(char* path);

/*
Função: Concatena dois caminhos, em caso de barra dupla na concatenaçao, ele corrige
Pré: Um char* com o caminho, Um char* com o caminho
Pós: Um char* com o caminho combinado
*/
char* catPath(char* path1, char* path2);

/*
Função: Recupera um nome de arquivo com extensao, somente nome e extensao, sem caminho
Pré: Um char* com o nome do arquivo, Um char* com a extensao do arquivo
Pós: Um char* com o arquivo com extensao
*/
char* insertExtension(char* name, char* extension);

#endif