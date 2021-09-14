#ifndef __LIST_H
#define __LIST_H

typedef void* List;
typedef void* NodeL;

#include "avl.h"

/*
Função: Cria Uma lista dinamica.
Pré: Nenhum requesito.
Pós: Retorna um void* com o endereço da lista
*/
List createList();

/*
Função: Encerra uma lista dinamica.
Pré: Um void* com o endereço da lista.
Pós: Nenhum retorno.
*/
void endList(List list);

/*
Função: Insere um elemento criando um no na ultima posição da lista dinamica.
Pré: Um void* com o endereço da lista, Um void* com o endereço da informaçao.
Pós: Nenhum retorno.
*/
void insertListElement(List list, Info info);

/*
Função: Remove um no informado na lista dinamica.
Pré: Um void* com o endereço da lista, Um void* com o endereço do no.
Pós: Nenhum retorno.
*/
void removeListNode(List list, NodeL node);

/*
Função: Recupera um void* de informaçao de um no na lista dinamica.
Pré: Um void* com o endereço do no.
Pós: Um void* com o endereço da informaçao.
*/
Info getListInfo(NodeL node);

/*
Função: Recupera o proximo no apontado por outro no na lista dinamica.
Pré: Um void* com o endereço da lista, Um void* com o endereço do no.
Pós: Um void* com o endereço do no.
*/
Node getListNext(List list, NodeL node);

/*
Função: Recupera o no anterior apontado por outro no na lista dinamica.
Pré: Um void* com o endereço da lista, Um void* com o endereço do no.
Pós: Um void* com o endereço do no.
*/
Node getListBack(List list, NodeL node);

/*
Função: Recupera o primeiro no de uma lista dinamica.
Pré: Um void* com o endereço da lista.
Pós: Um void* com o endereço do no.
*/
Node getListFirst(List list);

/*
Função: Recupera a quantidade de elementos dentro da lista dinamica.
Pré: Um void* com o endereço da lista.
Pós: Um int com o valor.
*/
int getListSize(List list);

/*
Função: Recupera a quantidade de visitas relativo a lista dinamica.
Pré: Um void* com o endereço da lista.
Pós: Um int com o valor.
*/
int getListVisit(List list);

#endif