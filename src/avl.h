#ifndef __AVL_H
#define __AVL_H

typedef void* Info;
typedef void* Tree;
typedef void* Node;

/*
Função: Dado uma arvore, um ponteiro pra Info e uma chave, insere na árvore e balanceia-a.
Pré: void* para a árvore, void* para a info, int com valor.
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int treeInsert(Tree tree, Info info, int key);

/*
Função: Dado uma árvore e uma chave, acha o nó correspondete e o remove da árvore
Pré: void* para a árvore, um int com valor
Pós: Retorna 1 caso bem sucedido ou 0 para falha
*/
int treeRemove(Tree tree, int key);

#endif