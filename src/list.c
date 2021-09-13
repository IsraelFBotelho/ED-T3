#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct nodeStruct{ 
    Info info;
    struct nodeStruct *next;
    struct nodeStruct *back;
} NodeStruct;

typedef struct listStruct{
    NodeStruct *head;
    NodeStruct *tail;
    int size;
} ListStruct;


void dRemoveNode(List list, NodeL node);

// Cria e retorna a lista
List createList(){
    ListStruct* new = (ListStruct* ) malloc(sizeof(ListStruct));

    new->head = NULL;
    new->tail = NULL;
    new->size = 0;

    return new;
}

// Encerra a lista e todos os nós no while
void endList(List list){
    ListStruct* listAux = (ListStruct* ) list;

    if(listAux->size != 0){

        NodeStruct* aux;
        while(listAux->head){

            aux = listAux->head;
            removeListNode(list, aux);
        }
    }

    free(listAux);
}

// Insere um elemento no fim da lista
void insertListElement(List list, Info info){
    ListStruct* listAux = (ListStruct* ) list;

    NodeStruct* new = (NodeStruct* ) malloc(sizeof(NodeStruct));

    if(listAux->size == 0){
        new->info = info;
        new->next = NULL;
        new->back = NULL;
        listAux->head = new;
        listAux->tail = new;
        listAux->size++;
    }else{
        new->info = info;
        new->next = NULL;
        new->back = listAux->tail;
        listAux->tail->next = new;
        listAux->tail = new;
        listAux->size++;
    }
}

// Remove o nó da lista que voce passou de parametro
void removeListNode(List list, NodeL node){
    ListStruct* listAux = (ListStruct* ) list;
    NodeStruct* nodeAux = (NodeStruct* ) node;
    

    if(listAux->size == 0)
        return;

    if(!nodeAux){
        return;
    }
       
    NodeStruct* aux;

    // Se tiver um anterior linka com o próximo/ se não ele se torna a cabeça
    if(nodeAux->back){
        aux = nodeAux->back;

        aux->next = nodeAux->next;
    }else{
        listAux->head = nodeAux->next;
    }

    // Se tiver próximo linka com o anterior/ se não ele se torna a calda
    if(nodeAux->next){
        aux = nodeAux->next;

        aux->back = nodeAux->back;
    }else{
        listAux->tail = nodeAux->back;
    }

    free(nodeAux);
    listAux->size--;
}

// Função que retorna o info do nó
Info getListInfo(NodeL node){
    NodeStruct* nodeAux = (NodeStruct* ) node;

    return nodeAux->info;
}

// Função que retorna o primeiro elemento da lista
Node getListFirst(List list){
    ListStruct *listAux = (ListStruct *) list;

    return listAux->head;
}

// Função que retorna o próximo elemento
Node getListNext(List list, NodeL node){
    NodeStruct *nodeAux = (NodeStruct *) node;

    return nodeAux->next;
}

// Função que retorna o elemento anterior
Node getListBack(List list, NodeL node){
    NodeStruct *nodeAux = (NodeStruct *) node;

    return nodeAux->back;
}

// Função que retorna o tamanho da lista
int getListSize(List list){
    ListStruct *listAux = (ListStruct *) list;

    return listAux->size;
}