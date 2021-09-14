#ifndef __ARG_H
#define __ARG_H
/*
Função: Lê e armazena os valores de argumentos de entrada da main, os armazenando em suas devidas variaveis.
Pré: Um int com o argc, Um char** com o argv, Uma referencia de char* do caminho de saida, Uma referencia de char* do caminho de entrada, 
     Uma referencia de char* do nome do .geo, Uma referencia de char* do nome do .qry, Uma referencia de cha* do .pm.
Pós: Nenhum retorno.
*/
void readArg(int argc, char** argv, char** pathOut, char** pathIn, char** nameArqGeo, char** nameArqQry, char** nameArqPm);

#endif