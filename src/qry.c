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
#include "dot.h"

// Gera um .txt escreve o nome do aluno
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

// Concatena o nome do .geo e .qry
char *getQryFileName(char* fullNameGeo, char* nameQry){
    char* nameGeo = extractName(fullNameGeo);
    char* fullName = malloc((strlen(nameGeo) + strlen(nameQry) + 2) *sizeof(char));
    sprintf(fullName,"%s-%s",nameGeo,nameQry);

    free(nameGeo);
    return fullName;
}

// Comando del {Deleta uma quadra a partir do seu CEP e tudo relacionado a ela}
void commandDel(FILE* txt, FILE* svg, City city, HashTable leasingTable, HashTable residentTable, HashTable saleTable, char* cep){
    Block block = hashTableSearch(getCityHashTable(city), cep);

    if(block == NULL){
        return;
    }
    
    // Deleta as locações que estão no CEP
    for(int i = 0; i < getHashTableSize(leasingTable); i++){
        List list = getHashTableList(leasingTable, i);

        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Leasing leasing = getHashTableListItem(getListInfo(nodeAux));
            if(strcmp(getLeasingCep(leasing), cep) == 0){

                fprintf(txt, "Locação: Cep: %s, Face: %c, Numero: %d, Complemento: %s\n",getLeasingCep(leasing), getLeasingSide(leasing), getLeasingNum(leasing), getLeasingComplement(leasing));
                char key[50];
                sprintf(key, "%s/%c/%d/%s", getLeasingCep(leasing), getLeasingSide(leasing), getLeasingNum(leasing), getLeasingComplement(leasing));

                // Deleta os moradores da locação
                Resident resident = getLeasingResident(leasing);
                Person person = getResidentPerson(resident);
                fprintf(txt, "Morador: Cpf: %s, Nome: %s, Sobrenome: %s, Sexo: %c, Nascimento: %d/%d/%d, Endereço: %s, %c, %d, %s\n", getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));

                hashTableRemove(residentTable, getResidentCpf(resident));
                residentDelete(resident);
                leasingDelete(leasing);
                hashTableRemove(leasingTable, key);

                break;
                i--;
            }
        }
    }

    // Deleta as ofertas no CEP
    for(int i = 0; i < getHashTableSize(saleTable); i++){
        List list = getHashTableList(saleTable, i);

        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Sale sale = getHashTableListItem(getListInfo(nodeAux));

            if(strcmp(cep, getSaleCep(sale)) == 0){
                
                fprintf(txt, "Oferta: Id: %s, Cep: %s, Face: %c, Numero: %d, Complemento: %s, Área: %.2lf, Valor: %.2lf mensais\n", getSaleId(sale), getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale), getSaleAr(sale), getSaleV(sale));
                
                hashTableRemove(saleTable, getSaleId(sale));
                saleDelete(sale);

                break;
                i--;

            }
        }
    }

    // Deleta a quadra
    double x, y;
    x = getBlockX(block) + (getBlockWidth(block) / 2);
    y = getBlockY(block) + (getBlockHeight(block) / 2);
    fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:rgb(255,0,0);stroke-width:2\"/>\n",x, y, x);
    fprintf(svg, "\t<text x=\"%lf\" y=\"0\"> %s </text>\n", x, cep);
    fprintf(txt, "Quadra: Cep: %s\n", cep);
    cityRemovebyCep(city, cep);
}

// Comando m? {Lista os moradores de um CEP}
void commandMQMark(FILE* txt, City city, HashTable residentTable, char* cep){

    // Caso a quadra não existe reporta erro!
    Block block = hashTableSearch(getCityHashTable(city), cep);
    if(block == NULL){
        fprintf(txt, "Erro: Quadra não existe!!\n");
        return;
    }

    // Percorre a tabela e verifica o cep da residencia do morador
    for(int i = 0; i < getHashTableSize(residentTable); i++){
        List list = getHashTableList(residentTable, i);

        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Resident resident = getHashTableListItem(getListInfo(nodeAux));
            if(strcmp(cep, getResidentCep(resident)) == 0){

                // Se mora no CEP, notifica no .txt
                Person person = getResidentPerson(resident);
                fprintf(txt, "Morador: Nome: %s, Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d, Cpf: %s, Endereço: Cep: %s, Face: %c, Numero: %d, Complemento: %s\n", getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person), getResidentCpf(resident), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));
            }
        }
    }
}

// Comando dm? {Imprime as informações de um morador a partir de seu CPF}
void commandDMQMark(FILE* txt, FILE* svg, HashTable residentTable, HashTable leasingTable, char* cpf){

    Resident resident = hashTableSearch(residentTable, cpf);

    // Caso o morador não exista não faz nada!
    if(resident == NULL){
        // printf("Comando Dm: Erro! Morador não encontrado!!!\n");
        return;
    }

    // Com as informações do morador se acha sua locação e imprime tudo relacionado aos dois
    char key[50];
    sprintf(key, "%s/%c/%d/%s", getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));
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

// Comando mud {Muda uma pessoa de uma locação para outra}
void commandMud(FILE* txt, FILE* svg, City city, HashTable residentTable, HashTable leasingTable, char* cpf, char* cep, char side, int num, char* complement){
    Resident resident = hashTableSearch(residentTable, cpf);

    if(resident == NULL){
        // printf("Comando Mud: Erro! Morador não encontrado\n");
        return;
    }
    
    // Encontra a locação atual da pessoa, reporta os dados e apaga o morador
    char key[50];
    sprintf(key, "%s/%c/%d/%s", getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));
    Leasing leasing = hashTableSearch(leasingTable, key);

    double x1 = getLeasingX(leasing);
    double y1 = getLeasingY(leasing);
    setLeasingResident(leasing, NULL);

    Person person = getResidentPerson(resident);

    fprintf(txt, "Morador: Nome: %s, Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d, Antigo Endereço: Cep: %s, Face: %c, Numero: %d, Complemento: %s \n", getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person), getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));

    residentDelete(resident);
    hashTableRemove(residentTable, cpf);

    // Cria um novo morador para a pessoa e reporta os dados
    resident = residentCreate(cpf, cep, side, num, complement, person, 0);

    fprintf(txt, "Novo Endereço: Cep: %s, Face: %c, Numero: %d, Complemento: %s\n", cep, side, num, complement);

    sprintf(key, "%s/%c/%d/%s", cep, side, num, complement);
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

// Comando oloc? {Verifica quais as ofertas disponíveis em uma área}
void commandOlocQMark(FILE* txt, FILE* svg, HashTable saleTable, double x, double y, double w, double h){
    fprintf(svg, "\t<rect id=\"oloc?\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"Red\" fill=\"none\" stroke-dasharray=\"2\"/>\n", x, y, w, h);

    // Busca na tabela das ofertas e reporta os dados
    for(int i = 0; i < getHashTableSize(saleTable); i++){
        List saleList = getHashTableList(saleTable, i);

        for(NodeL nodeSale = getListFirst(saleList); nodeSale; nodeSale = getListNext(nodeSale)){
            Sale sale = getHashTableListItem(getListInfo(nodeSale));
            double xAux = getSaleX(sale);
            double yAux = getSaleY(sale);
            
            if(xAux >= x && xAux <= (x+w)){
                if(yAux >= y && yAux <= (y+h)){
                    if(isSaleLeasing(sale) == 0){
                        fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\">*</text>\n",xAux, yAux);
                        fprintf(txt, "Locação: Id: %s, Cep: %s, Face: %c, Numero: %d, Complemento: %s, Área: %lfm², Preço: %.2lf mensais\n", getSaleId(sale), getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale), getSaleAr(sale), getSaleV(sale));
                    }
                }
            }
        }
    }
}

// Comando loc {Pessoa com um tal CPF se muda pra uma oferta ID}
void commandLoc(FILE* txt, FILE* svg, City city, HashTable personTable, HashTable leasingTable, HashTable residentTable, HashTable saleTable, char* id, char* cpf){

    Sale sale = hashTableSearch(saleTable, id);

    // Verifica se a oferta existe e se foi encerrada
    if(sale == NULL){
        // printf("Comando-Loc: Erro! Oferta não encontrada!\n");
        return;
    }

    if(isSaleLeasing(sale) == -1){
        // printf("Comando-Loc: Erro! Oferta encerrada!\n");
        return;
    }

    // Se a pessoa ja tinha residencia, ele saí de lá e vai para a oferta
    Resident auxResident = hashTableSearch(residentTable, cpf);
    if(auxResident != NULL){
        char key[50];
        sprintf(key, "%s/%c/%d/%s", getResidentCep(auxResident), getResidentSide(auxResident), getResidentNumber(auxResident), getResidentComplement(auxResident));
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
            sprintf(key, "%s/%c/%d/%s", cep, side, number, complement);
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

// Comando loc? {Reporta a situação da oferta ID}
void commandLocQMark(FILE* txt, FILE* svg, HashTable saleTable, HashTable leasingTable, char* id){
    Sale sale = hashTableSearch(saleTable, id);

    // Verifica se existe oferta, se existe imprime os dados
    if(sale == NULL){
        // printf("Comando Loc?: Erro! Oferta não encontrada!");
        return;
    }

    char saleStatus;

    if(isSaleLeasing(sale) == 0){
        saleStatus = '$';

    }else if(isSaleLeasing(sale) == 1){
        saleStatus = '*';

    }else{
        saleStatus = '#';

    }

    double x = getSaleX(sale);
    double y = getSaleY(sale);

    fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\">%c</text>\n",x, y, saleStatus);

    fprintf(txt, "Locação: Id: %s, Cep: %s, Face: %c, Numero: %d, Complemento: %s, Área: %lfm², Preço: %.2lf mensais\n", getSaleId(sale), getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale), getSaleAr(sale), getSaleV(sale));

    if(isSaleLeasing(sale) == 1){
        char key[50];
        sprintf(key, "%s/%c/%d/%s", getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale));
        Leasing leasing = hashTableSearch(leasingTable, key);
        Resident resident = getLeasingResident(leasing);
        Person person = getResidentPerson(resident);

        fprintf(txt, "Pessoa: Cpf:%s, Nome:%s, Sobrenome:%s, Sexo:%c, Nascimento: %d/%d/%d\n", getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person));

    }
}

// Comando dloc {Encerra uma oferta ID}
void commandDloc(FILE* txt, FILE* svg, HashTable saleTable, HashTable residentTable, HashTable leasingTable, char* id){
    Sale sale = hashTableSearch(saleTable, id);

    // Verifica se existe a oferta
    if(sale == NULL){
        return;
    }

    // Se ela tinha uma pessoa morando, reporta os dados e apaga o morador e a locação
    if(isSaleLeasing(sale) == 1){
        char key[50];
        sprintf(key, "%s/%c/%d/%s", getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale));
        Leasing leasing = hashTableSearch(leasingTable, key);
        Resident resident = getLeasingResident(leasing);
        Person person = getResidentPerson(resident);

        fprintf(txt, "Locação: Id: %s, Cep: %s, Face: %c, Numero: %d, Complemento: %s, Imóvel: Área: %lfm², Preço: %.2lf mensais, Pessoa: Cpf: %s  Nome: %s, Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d\n", getSaleId(sale), getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale), getSaleAr(sale), getSaleV(sale), getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person));

        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", getLeasingX(leasing), getLeasingY(leasing), getLeasingX(leasing));
        fprintf(svg, "\t<text x=\"%lf\" y=\"0\"> Pessoa: Cpf:%s, Nome:%s, Sobrenome:%s, Sexo:%c, Nascimento: %d/%d/%d</text>\n", getLeasingX(leasing), getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person));
        fprintf(svg, "\t<text x=\"%lf\" y=\"20\"> Locação: Cep: %s, Face:%c, Numero:%d, Complemento:%s  </text>\n", getLeasingX(leasing), getLeasingCep(leasing), getLeasingSide(leasing), getLeasingNum(leasing), getLeasingComplement(leasing));
        fprintf(svg, "\t<text x=\"%lf\" y=\"40\"> Imóvel: Tamanho: %.2lf m², Valor: %.2lf mensais </text>\n", getLeasingX(leasing), getSaleAr(sale), getSaleV(sale));
    

        char* cpf = getResidentCpf(resident);
        residentDelete(resident);
        hashTableRemove(residentTable, cpf);
        
        leasingDelete(leasing);
        hashTableRemove(leasingTable, key);


    // Se não só reporta os dados
    }else if(isSaleLeasing(sale) == 0){

        fprintf(txt, "Locação: Id: %s, Cep: %s, Face: %c, Numero: %d, Complemento: %s, Imóvel: Área: %lfm², Preço: %.2lf mensais\n", getSaleId(sale), getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale), getSaleAr(sale), getSaleV(sale));
        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n",getSaleX(sale), getSaleY(sale), getSaleX(sale));
        fprintf(svg, "\t<text x=\"%lf\" y=\"0\" >Locação: Id: %s, Cep: %s, Face: %c, Numero: %d, Complemento: %s, Área: %lfm², Preço: %.2lf mensais</text>\n",getSaleX(sale), getSaleId(sale), getSaleCep(sale), getSaleSide(sale), getSaleNumber(sale), getSaleComplement(sale), getSaleAr(sale), getSaleV(sale));
    }

    setSaleLeasing(sale, -1);
}

// Comando hom {Reporta os moradores homens em uma área}
void commandHom(FILE* txt, FILE* svg, HashTable leasingTable, HashTable residentTable, double x, double y, double w, double h){

    // Percorre a tabela de moradores
    for(int i = 0; i < getHashTableSize(residentTable); i++){
        List list = getHashTableList(residentTable, i);

        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Resident resident = getHashTableListItem(getListInfo(nodeAux));

            if(resident == NULL){
                continue;
            }

            char key[50];
            sprintf(key,"%s/%c/%d/%s", getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));
            Leasing leasing = hashTableSearch(leasingTable, key);

            double xAux = getLeasingX(leasing);
            double yAux = getLeasingY(leasing);
            
            // Se a coordenada do residente estiver dentro da área e o sexo for masculino imprime os dados
            if(xAux >= x && xAux <= (x+w)){
                if(yAux >= y && yAux <= (y+h)){
                    Person person = getResidentPerson(resident);
                    if(getPersonGender(person) == 'M'){
                        fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"3\" fill=\"Blue\" stroke=\"Blue\"/>\n",xAux, yAux);
                        fprintf(txt, "Moradia: Cep: %s, Face: %c, Numero: %d, Complemento: %s, Pessoa: Cpf: %s Nome: %s Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d\n", getLeasingCep(leasing), getLeasingSide(leasing), getLeasingNum(leasing), getLeasingComplement(leasing), getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person));
                    }
                }
            }
        }
    }

}

// Comando mul {Reporta as moradoras mulheres em uma área}
void commandMul(FILE* txt, FILE* svg, HashTable leasingTable, HashTable residentTable, double x, double y, double w, double h){

    // Percorre a tabela de moradores
    for(int i = 0; i < getHashTableSize(residentTable); i++){
        List list = getHashTableList(residentTable, i);

        for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
            Resident resident = getHashTableListItem(getListInfo(nodeAux));

            if(resident == NULL){
                continue;
            }

            char key[50];
            sprintf(key,"%s/%c/%d/%s", getResidentCep(resident), getResidentSide(resident), getResidentNumber(resident), getResidentComplement(resident));
            Leasing leasing = hashTableSearch(leasingTable, key);

            double xAux = getLeasingX(leasing);
            double yAux = getLeasingY(leasing);
            
            // Se estiver na área e o sexo for feminino imprime os dados
            if(xAux >= x && xAux <= (x+w)){
                if(yAux >= y && yAux <= (y+h)){
                    Person person = getResidentPerson(resident);
                    if(getPersonGender(person) == 'F'){
                        fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"3\" fill=\"Pink\" stroke=\"Pink\"/>\n",xAux, yAux);
                        fprintf(txt, "Moradia: Cep: %s, Face: %c, Numero: %d, Complemento: %s, Pessoa: Cpf: %s Nome: %s Sobrenome: %s, Sexo: %c, Data de Nascimento: %d/%d/%d\n", getLeasingCep(leasing), getLeasingSide(leasing), getLeasingNum(leasing), getLeasingComplement(leasing), getPersonCpf(person), getPersonName(person), getPersonSurname(person), getPersonGender(person), getPersonDay(person), getPersonMonth(person), getPersonYear(person));
                    }
                }
            }
        }
    }

}

// Função recursiva referente ao catac
void recCommandCatac(List listBlocks, Node root, double x, double y, double w, double h){
    if(root == NULL){
        return;
    }

    recCommandCatac(listBlocks , getTreeLeft(root), x, y, w, h);
    recCommandCatac(listBlocks , getTreeRight(root), x, y, w, h);

    List list = getTreeNodeItens(root);

    for(NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
        Block block = getTreeListItem(getListInfo(nodeAux));

        double xAux = getBlockX(block);
        double yAux = getBlockY(block);
        double wAux = getBlockWidth(block);
        double hAux = getBlockHeight(block);

        // Se a quadra estiver na área adiciona a lista
        if(xAux >= x && (xAux + wAux) <= (x+w)){
            if(yAux >= y && (yAux + hAux) <= (y+h)){
                insertListElement(listBlocks, block);
            }
        }
    }
}

// Comando catac {Deleta as quadras em uma área e tudo relacionado à elas}
void commandCatac(FILE* txt, FILE* svg, City city, HashTable leasingTable, HashTable residentTable, HashTable saleTable, double x, double y, double w, double h){

    fprintf(svg,"\t<rect id=\"catac\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"#AA0044\" fill=\"#AB37C8\" fill-opacity=\"0.5\" stroke-opacity=\"0.5\"/>\n", x, y, w, h);

    // Chama uma função que busca todas as quadras na área 
    List listBlock = createList();
    recCommandCatac(listBlock, getTreeRoot(getCityTree(city)), x, y, w, h);

    // Percorre a lista e chama o comando del para cada uma
    for(NodeL nodeAux = getListFirst(listBlock); nodeAux; nodeAux = getListNext(nodeAux)){
        Block block = getListInfo(nodeAux);

        commandDel(txt, svg, city, leasingTable, residentTable, saleTable, getBlockCep(block));
    }

    endList(listBlock);
}

// Lê e execulta as consultas do .qry
int readQry(char *pathIn, char* pathOut ,char *nameQry, char *nameGeo, City city, HashTable personTable, HashTable leasingTable, HashTable residentTable){

    if(!nameQry){
        return 0;
    }

    // Inicializando valores
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

    // Preparando o .svg e .txt de saída
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

    // Tabela de ofertas
    HashTable saleTable = hashTableCreate(1000);

    while(!feof(qry)){
        fscanf(qry,"%s",command);

        // Comando "del"
        if(strcmp(command, "del") == 0){
            fscanf(qry, "%s\n", cep);
            fprintf(txt,"del\n");
            commandDel(txt , svg, city, leasingTable, residentTable, saleTable, cep);

        // Comando "m?"
        }else if(strcmp(command, "m?") == 0){
            fscanf(qry, "%s\n", cep);
            fprintf(txt, "m?\n");
            commandMQMark(txt, city, residentTable, cep);

        // Comando "dm?"
        }else if(strcmp(command, "dm?") == 0){
            fscanf(qry, "%s\n", cpf);
            fprintf(txt, "dm?\n");
            commandDMQMark(txt, svg, residentTable, leasingTable, cpf);

        // Comando "mud"
        }else if(strcmp(command, "mud") == 0){
            fscanf(qry, "%s %s %c %d %s\n", cpf, cep, &side, &num, compl);
            fprintf(txt, "mud\n");
            commandMud(txt, svg, city, residentTable, leasingTable, cpf, cep, side, num, compl);

        // Comando "oloc"
        }else if(strcmp(command, "oloc") == 0){
            fscanf(qry, "%s %s %c %d %s %lf %lf\n", id, cep, &side, &num, compl, &ar, &v);
            Sale sale = saleCreate(getCityHashTable(city), id, cep, side, num, compl, ar, v);
            if(sale == NULL){
                printf("Erro: CEP para OLOC é desconhecido\n");

            }else{
            hashTableInsert(saleTable, id, sale);

            }

        // Comando "oloc?"
        }else if((strcmp(command, "oloc?") == 0)){
            fscanf(qry, "%lf %lf %lf %lf\n", &x, &y, &w, &h);
            fprintf(txt, "oloc?\n");
            commandOlocQMark(txt, svg, saleTable, x, y, w, h);

        // Comando "loc"
        }else if((strcmp(command, "loc") == 0)){
            fscanf(qry, "%s %s\n", id, cpf);
            fprintf(txt, "loc\n");
            commandLoc(txt, svg, city, personTable, leasingTable, residentTable, saleTable, id, cpf);

        // Comando "loc?"
        }else if((strcmp(command, "loc?") == 0)){
            fscanf(qry, "%s\n", id);
            fprintf(txt, "loc?\n");
            commandLocQMark(txt, svg, saleTable, leasingTable, id);

        // Comando "dloc"
        }else if((strcmp(command, "dloc") == 0)){
            fscanf(qry, "%s\n", id);
            fprintf(txt, "dloc\n");
            commandDloc(txt, svg, saleTable, residentTable, leasingTable, id);

        // Comando "hom"
        }else if((strcmp(command, "hom") == 0)){
            fscanf(qry, "%lf %lf %lf %lf\n", &x, &y, &w, &h);
            fprintf(txt, "hom\n");
            commandHom(txt, svg, leasingTable, residentTable, x, y, w, h);

        // Comando "mul"
        }else if((strcmp(command, "mul") == 0)){
            fscanf(qry, "%lf %lf %lf %lf\n", &x, &y, &w, &h);
            fprintf(txt, "mul\n");
            commandMul(txt, svg, leasingTable, residentTable, x, y, w, h);

        // Comando "dmpt"
        }else if((strcmp(command, "dmpt") == 0)){
            fscanf(qry, "%s\n", sfx);
            drawDotFile(pathOut, nameGeo, sfx, getCityTree(city));

        // Comando "catac"
        }else if((strcmp(command, "catac") == 0)){
            fscanf(qry, "%lf %lf %lf %lf\n", &x, &y, &w, &h);
            fprintf(txt, "catac\n");
            commandCatac(txt, svg, city, leasingTable, residentTable, saleTable, x, y, w, h);

        }
    }
    // Desenhando as quadras no .svg
    drawBlocks(svg, getCityTree(city));


    // Desalocando todas as ofertas e sua tabela
    saleDeleteAll(saleTable);
    hashTableEnd(saleTable);

    // Desalocando valores
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