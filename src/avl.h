#ifndef __AVL_H
#define __AVL_H

typedef void* Info;
typedef void* Tree;
typedef void* Node;

/*
Função: Dado uma arvore, um ponteiro pra Info e uma chave, insere na árvore e balanceia-a.
Pré: void* para a árvore, void* para a info, int com valor.
Pós: Retorna 1 caso bem sucedido ou 0 para key de valor igual.
*/
int treeInsert(Tree tree, Info info, int key);

/*
Função: Dado uma árvore e uma chave, acha o nó correspondete e o remove da árvore.
Pré: void* para a árvore, um int com valor.
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int treeRemove(Tree tree, int key);

/*
Função: Dada uma árvore desaloca todos os nós e a própria árvore.
Pré: void* para a árvore.
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int treeEnd(Tree tree);

/*
Função: Cria uma estrutura de Árvore AVL e armazena o tipo;
Pré: char[20] com o que vai ser armazenado. Ex: "Retangulo";
Pós: Retorna um void* com o endereço da árvore.
*/
Tree treeCreate(char type[20]);

#endif