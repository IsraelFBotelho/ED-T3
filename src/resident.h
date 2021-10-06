#ifndef __RESIDENT_H
#define __RESIDENT_H

typedef void* Resident;

#include "hashtable.h"
#include "person.h"


Resident residentCreate(char* cpf, char* cep, char side, int num, char* complement, Person person, int isRent);

int residentDelete(Resident resident);

int residentDeleteAll(HashTable table);

char* getResidentCep(Resident resident);

char* getResidentCpf(Resident resident);

char getResidentSide(Resident resident);

int getResidentNumber(Resident resident);

char* getResidentComplement(Resident resident);

Person getResidentPerson(Resident resident);

int isResidentRent(Resident resident);

#endif