#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "city.h"
#include "leasing.h"
#include "path.h"
#include "person.h"
#include "svg.h"
#include "resident.h"

FILE *getTxtFile(char* nameArq, char* pathOut){
    char t[] = "txt";
    char* nameTxt = t;
    char *nameArqExtr =(char *) extractName(nameArq);
    char *nameArqTxt = insertExtension(nameArqExtr, nameTxt);
    char *fullPathTxt = catPath(pathOut, nameArqTxt);

    FILE *txt = fopen(fullPathTxt, "w");

    if(!txt){
        printf("Erro na criacao do TXT!!\n");
        free(fullPathTxt);
        exit(1);
    }

    fprintf(txt, "Nome do Aluno: Israel Faustino Botelho Junior\n");

    free(nameArqExtr);
    free(nameArqTxt);
    free(fullPathTxt);
    return txt;
    
}

char *getQryFileName(char* fullNameGeo, char* nameQry){
    char* nameGeo = extractName(fullNameGeo);
    char* fullName = malloc((strlen(nameGeo) + strlen(nameQry) + 2) *sizeof(char));
    sprintf(fullName,"%s-%s",nameGeo,nameQry);

    free(nameGeo);
    return fullName;
}

void commandDel(FILE* txt, FILE* svg, City city, HashTable leasingTable, char* cep){
    for(int i = 0; i < getHashTableSize(leasingTable); i++){
        List list = getHashTableList(leasingTable, i);

        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Leasing leasing = getHashTableListItem(getListInfo(nodeAux));
            if(strcmp(getLeasingCep(leasing), cep) == 0){

                if(leasing == NULL){
                    printf ("1\n");
                }

                fprintf(txt, "Locação: Cep: %s, Face: %c, Numero: %d, Complemento: %s\n",getLeasingCep(leasing), getLeasingSide(leasing), getLeasingNum(leasing), getLeasingComplement(leasing));
                char key[50];
                sprintf(key, "%s/%c/%d", getLeasingCep(leasing), getLeasingSide(leasing), getLeasingNum(leasing));
                printf("%s\n",key);

                Resident resident = getLeasingResident(leasing);
                Person person = getResidentPerson(resident);
                fprintf(txt, "Morador: Cpf: %s, Nome: %s, Sobrenome: %s, Sexo: %c, Nascimento: %d/%d/%d, Endereço: %s, %c, %d, %s\n", getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));

                leasingDelete(leasing);
                hashTableRemove(leasingTable, key);

                break;
                i--;
            }
        }
    }
    double x, y;
    Block block = hashTableSearch(getCityHashTable(city), cep);
    x = getBlockX(block) + (getBlockWidth(block) / 2);
    y = getBlockY(block) + (getBlockHeight(block) / 2);
    fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:rgb(255,0,0);stroke-width:2\"/>\n",x, y, x);
    fprintf(svg, "\t<text x=\"%lf\" y=\"0\"> %s </text>\n", x, cep);
    fprintf(txt, "Quadra: Cep: %s\n", cep);
    cityRemovebyCep(city, cep);
}

void commandMQMark(FILE* txt, City city, HashTable residentTable, char* cep){
    Block block = hashTableSearch(getCityHashTable(city), cep);
    if(block == NULL){
        fprintf(txt, "Erro: Quadra não existe!!\n");
        return;
    }

    for(int i = 0; i < getHashTableSize(residentTable); i++){
        List list = getHashTableList(residentTable, i);

        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Resident resident = getHashTableListItem(getListInfo(nodeAux));
            if(strcmp(cep, getResidentCep(resident)) == 0){
                Person person = getResidentPerson(resident);
                fprintf(txt, "Morador: Nome: %s, Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d, Cpf: %s, Endereço: Cep: %s, Face: %c, Numero: %d, Complemento: %s\n", getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person), getResidentCpf(resident), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));
            }
        }
    }
}

void commandDMQMark(FILE* txt, FILE* svg, HashTable residentTable, HashTable leasingTable, char* cpf){

    Resident resident = hashTableSearch(residentTable, cpf);

    if(resident == NULL){
        fprintf(txt,"Erro: Morador não encontrado!!!\n");
        return;
    }

    char key[50];
    sprintf(key, "%s/%c/%d", getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident));
    Leasing leasing = hashTableSearch(leasingTable, key);
    Person person = getResidentPerson(resident);
    fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", getLeasingX(leasing), getLeasingY(leasing), getLeasingX(leasing));
    fprintf(svg, "\t<text x=\"%lf\" y=\"0\"> %s </text>\n", getLeasingX(leasing), getPersonName(person));
    fprintf(svg, "\t<text x=\"%lf\" y=\"20\"> %s </text>\n", getLeasingX(leasing), getPersonCpf(person));
    fprintf(svg, "\t<text x=\"%lf\" y=\"40\"> %s/%c/%d - %s </text>\n", getLeasingX(leasing), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));
    
    char rent[10];
    if(isResidentRent(resident) == 1){
        strcpy(rent,"Sim");
    }else{
        strcpy(rent, "Não");
    }

    fprintf(txt, "Morador: Nome: %s, Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d, Cpf: %s, Endereço: Cep: %s, Face: %c, Numero: %d, Complemento: %s, É alugada? %s\n", getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person), getResidentCpf(resident), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident), rent);
}

int readQry(char *pathIn, char* pathOut ,char *nameQry, char *nameGeo, City city, HashTable personTable, HashTable leasingTable, HashTable residentTable){

    if(!nameQry){
        return 0;
    }

    char cep[50], command[30], cpf[50], compl[50], side, id[50], sfx[50];

    double x = 0, y = 0, w = 0, h = 0, ar = 0, v = 0;

    int num = 0;

    char* fullPathQry = catPath(pathIn, nameQry);

    FILE *qry = fopen(fullPathQry, "r");

    if(qry == NULL){
        printf("\nArquivo .qry nao foi encontrado");
        free(fullPathQry);
        return 0;
    }

    char* aux = extractName(nameQry);
    char* fullNameQry = getQryFileName(nameGeo, aux);
    free(aux);

    char s[] = "svg";
    char* nameSvg = s;
    char* nameArqExtr = (char* ) extractName(fullNameQry);
    char* nameArqSvg = insertExtension(nameArqExtr, nameSvg);
    char* fullPathSvg = catPath(pathOut, nameArqSvg);

    FILE *txt = getTxtFile(fullNameQry, pathOut);
    FILE *svg = createSvg(fullPathSvg);

    while(!feof(qry)){
        fscanf(qry,"%s",command);

        if(strcmp(command, "del") == 0){
            fscanf(qry, "%s\n", cep);
            fprintf(txt,"del\n");
            commandDel(txt , svg, city, leasingTable, cep);

        }else if(strcmp(command, "m?") == 0){
            fscanf(qry, "%s\n", cep);
            fprintf(txt, "m?\n");
            commandMQMark(txt, city, residentTable, cep);

        }else if(strcmp(command, "dm?") == 0){
            fscanf(qry, "%s\n", cpf);
            fprintf(txt, "dm?\n");
            commandDMQMark(txt, svg, residentTable, leasingTable, cpf);

        }else if(strcmp(command, "im") == 0){
            fscanf(qry, "%lf %lf\n", &x, &y);
            fprintf(txt, "im\n");


        }else if(strcmp(command, "t30") == 0){
            fscanf(qry, "\n");
            fprintf(txt, "t30\n");


        }else if((strcmp(command, "nve") == 0)){
            fscanf(qry, "%lf %lf\n", &x, &y);
            fprintf(txt, "nve\n");

        }
    }
    drawBlocks(svg, getCityTree(city));

    endSvg(svg);
    fclose(txt);
    free(fullNameQry);
    free(fullPathQry);
    free(nameArqExtr);
    free(nameArqSvg);
    free(fullPathSvg);
    fclose(qry);
    return 1;
}