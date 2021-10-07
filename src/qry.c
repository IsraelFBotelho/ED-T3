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
#include "sale.h"

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
        printf("Comando Dm: Erro! Morador não encontrado!!!\n");
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
        strcpy(rent, "Sim");
    }else{
        strcpy(rent, "Não");
    }

    fprintf(txt, "Morador: Nome: %s, Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d, Cpf: %s, Endereço: Cep: %s, Face: %c, Numero: %d, Complemento: %s, É alugada? %s\n", getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person), getResidentCpf(resident), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident), rent);
}

void commandMud(FILE* txt, FILE* svg, City city, HashTable residentTable, HashTable leasingTable, char* cpf, char* cep, char side, int num, char* complement){
    Resident resident = hashTableSearch(residentTable, cpf);

    if(resident == NULL){
        printf("Comando Mud: Erro! Morador não encontrado\n");
        return;
    }
    char key[50];
    sprintf(key, "%s/%c/%d", getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident));
    Leasing leasing = hashTableSearch(leasingTable, key);

    double x1 = getLeasingX(leasing);
    double y1 = getLeasingY(leasing);
    setLeasingResident(leasing, NULL);

    Person person = getResidentPerson(resident);

    fprintf(txt, "Morador: Nome: %s, Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d, Antigo Endereço: Cep: %s, Face: %c, Numero: %d, Complemento: %s ", getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));

    residentDelete(resident);
    hashTableRemove(residentTable, cpf);

    resident = residentCreate(cpf, cep, side, num, complement, person, 0);

    fprintf(txt, "Novo Endereço: Cep: %s, Face: %c, Numero: %d, Complemento: %s\n", cep, side, num, complement);

    sprintf(key, "%s/%c/%d", cep, side, num);
    leasing = hashTableSearch(leasingTable, key);

    if(leasing != NULL){
        setLeasingResident(leasing, resident);
        hashTableInsert(residentTable, cpf, resident);
    }else{
        leasing = leasingCreate(getCityHashTable(city), cep, side, num, complement);
        hashTableInsert(leasingTable, key, leasing);
        hashTableInsert(residentTable, cpf, resident);
        setLeasingResident(leasing, resident);
    }
    
    double x2 = getLeasingX(leasing);
    double y2 = getLeasingY(leasing);

    fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", x1, y1, x2, y2);
    fprintf(svg, "\t<circle  cx=\"%lf\" cy=\"%lf\" r=\"10\" stroke=\"white\" stroke-width=\"5\" fill=\"red\"/>\n", x1, y1);
    fprintf(svg, "\t<circle  cx=\"%lf\" cy=\"%lf\" r=\"10\" stroke=\"white\" stroke-width=\"5\" fill=\"blue\"/>\n", x2, y2);
} 

void commandOlocQMark(FILE* txt, FILE* svg, HashTable saleTable, double x, double y, double w, double h){
    fprintf(svg, "\t<rect id=\"oloc?\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"Red\" fill=\"none\" stroke-dasharray=\"2\"/>\n", x, y, w, h);

    for(int i = 0; i < getHashTableSize(saleTable); i++){
        List saleList = getHashTableList(saleTable, i);

        for(NodeL nodeSale = getListFirst(saleList); nodeSale; nodeSale = getListNext(nodeSale)){
            Sale sale = getHashTableListItem(getListInfo(nodeSale));
            double xAux = getSaleX(sale);
            double yAux = getSaleY(sale);
            
            if(xAux >= x && xAux <= (x+w)){
                if(yAux >= y && yAux <= (y+h)){
                    if(isSaleLeasing(sale) == 0){
                        fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\">*</text>",xAux, yAux);
                        fprintf(txt, "Locação: Id: %s, Cep: %s, Face: %c, Numero: %d, Complemento: %s, Área: %lfm², Preço: %.2lf mensais\n", getSaleId(sale), getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale), getSaleAr(sale), getSaleV(sale));
                    }
                }
            }
        }
    }
}

void commandLoc(FILE* txt, FILE* svg, City city, HashTable personTable, HashTable leasingTable, HashTable residentTable, HashTable saleTable, char* id, char* cpf){

    Sale sale = hashTableSearch(saleTable, id);

    if(sale == NULL){
        printf("Comando-Loc: Erro! Oferta não encontrada!\n");
        return;
    }

    Resident auxResident = hashTableSearch(residentTable, cpf);
    if(auxResident != NULL){
        char key[50];
        sprintf(key, "%s/%c/%d", getResidentCep(auxResident), getResidentSide(auxResident), getResidentNumber(auxResident));
        Leasing auxLeasing = hashTableSearch(leasingTable, key);
        setLeasingResident(auxLeasing, NULL);
        residentDelete(auxResident);
        hashTableRemove(residentTable, cpf);

    }


    char* cep = getSaleCep(sale);
    char side = getSaleSide(sale);
    int number = getSaleNumber(sale);
    char* complement = getSaleComplement(sale);

    Leasing leasing = leasingCreate(getCityHashTable(city), cep, side, number, complement);

    if(leasing != NULL){
        Person person = hashTableSearch(personTable, cpf);

        if(person != NULL){
            char key[100];
            sprintf(key, "%s/%c/%d", cep, side, number);
            hashTableInsert(leasingTable, key, leasing);
            Resident resident = residentCreate(cpf, cep, side, number, complement, person, 1);
            hashTableInsert(residentTable, cpf, resident);
            setLeasingResident(leasing, resident);
            setSaleLeasing(sale, 1);

            fprintf(txt, "Locação: Id: %s, Cep: %s, Face: %c, Numero: %d, Complemento: %s, Imóvel: Área: %lfm², Preço: %.2lf mensais, Pessoa: Cpf: %s  Nome: %s, Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d\n", getSaleId(sale), getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale), getSaleAr(sale), getSaleV(sale), getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person));

            fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", getLeasingX(leasing), getLeasingY(leasing), getLeasingX(leasing));
            fprintf(svg, "\t<text x=\"%lf\" y=\"0\"> Pessoa: Cpf:%s, Nome:%s, Sobrenome:%s, Sexo:%c, Nascimento: %d/%d/%d</text>\n", getLeasingX(leasing), getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person));
            fprintf(svg, "\t<text x=\"%lf\" y=\"20\"> Locação: Cep: %s, Face:%c, Numero:%d, Complemento:%s  </text>\n", getLeasingX(leasing), getLeasingCep(leasing), getLeasingSide(leasing), getLeasingNum(leasing), getLeasingComplement(leasing));
            fprintf(svg, "\t<text x=\"%lf\" y=\"40\"> Imóvel: Tamanho: %.2lf m², Valor: %.2lf mensais </text>\n", getLeasingX(leasing), getSaleAr(sale), getSaleV(sale));
    
        }else{
            leasingDelete(leasing);
        }
    }

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

    HashTable saleTable = hashTableCreate(1000);

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


        }else if(strcmp(command, "mud") == 0){
            fscanf(qry, "%s %s %c %d %s\n", cpf, cep, &side, &num, compl);
            fprintf(txt, "mud\n");
            commandMud(txt, svg, city, residentTable, leasingTable, cpf, cep, side, num, compl);


        }else if(strcmp(command, "oloc") == 0){
            fscanf(qry, "%s %s %c %d %s %lf %lf\n", id, cep, &side, &num, compl, &ar, &v);
            Sale sale = saleCreate(getCityHashTable(city), id, cep, side, num, compl, ar, v);
            if(sale == NULL){
                printf("Erro: CEP para OLOC é desconhecido\n");

            }else{
            hashTableInsert(saleTable, id, sale);

            }


        }else if((strcmp(command, "oloc?") == 0)){
            fscanf(qry, "%lf %lf %lf %lf\n", &x, &y, &w, &h);
            fprintf(txt, "oloc?\n");
            commandOlocQMark(txt, svg, saleTable, x, y, w, h);


        }else if((strcmp(command, "loc") == 0)){
            fscanf(qry, "%s %s\n", id, cpf);
            fprintf(txt, "loc\n");
            commandLoc(txt, svg, city, personTable, leasingTable, residentTable, saleTable, id, cpf);

        }
    }
    drawBlocks(svg, getCityTree(city));


    saleDeleteAll(saleTable);
    hashTableEnd(saleTable);

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