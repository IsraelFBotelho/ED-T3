#ifndef __AVL_H
#define __AVL_H

typedef void* Info;
typedef void* Tree;
typedef void* Node;

/*
Função: Dado uma arvore, um ponteiro pra Info e uma chave, insere na árvore e balanceia-a.
Pré: void* para a árvore, void* para a info, double com valor.
Pós: Retorna 1 caso bem sucedido ou 0 para key de valor igual.
*/
int treeInsert(Tree tree, Info info, double key);

/*
Função: Dado uma árvore e uma chave, acha o nó correspondete e o remove da árvore.
Pré: void* para a árvore, um double com valor.
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int treeRemove(Tree tree, double key);

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

/*
Função: Busca e recupera a lista com todos os dados correspondete a key
Pré: void* para a árvore, double com valor
Pós:
*/
List treeSearch(Tree tree, double key);
#endif