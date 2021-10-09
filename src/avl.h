#ifndef __AVL_H
#define __AVL_H

typedef void* Info;
typedef void* Tree;
typedef void* Node;

#include "list.h"
#include "hashtable.h"


/*
Função: Dado uma arvore, um ponteiro pra Info e uma chave, insere na árvore e balanceia-a.
Pré: void* para a árvore, void* para a info, double com valor de x, double com valor de y.
Pós: Retorna 1 caso bem sucedido ou 0 para key de valor igual.
*/
int treeInsert(Tree tree, Info info, double keyX, double keyY, double width);

/*
Função: Dado uma árvore e uma chave, acha o nó correspondete e o remove da árvore.
Pré: void* para a árvore,double com valor de x, um double com valor de y.
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int treeRemove(Tree tree, double keyX, double keyY);

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
Função: Busca e recupera um info correspondente a chave X e Y;
Pré: void* para a árvore, double com valor de x, double com o valor de y;
Pós: Retorna void* com a info se existir ou NULL caso não encontre.
*/
Info treeSearch(Tree tree, double keyX,  double keyY);

/*
Função: Retorna o nó a direita dessa subarvore;
Pré: void* para a raiz da subarvore;
Pós: Retorna void* com o endereço do nó a direita ou NULL se não existir.
*/
Node getTreeRight(Node root);

/*
Função: Retorna o nó a esquerda dessa subarvore;
Pré: void* para a raiz da subarvore;
Pós: Retorna void* com o endereço do nó a esquerda ou NULL se não existir.
*/
Node getTreeLeft(Node root);

/*
Função: Retorna a raiz de uma estrutura de árvore;
Pré: void* para a árvore;
Pós: Retorna void* com o nó.
*/
Node getTreeRoot(Tree tree);

/*
Função: Busca e recupera uma lista com todos os dados do nó;
Pré: void* para o nó;
Pós: Retorna void* com a info se existir ou NULL caso não encontre.
*/
List getTreeNodeItens(Node root);

Info getTreeListItem(Info item);

double getTreeListKeyY(Info item);

double getTreeBiggerX(Node root);

double getTreeLesserX(Node root);

int getTreeSize(Tree tree);

double getTreeKey(Node root);

int getTreeHeight(Node root);

#endif