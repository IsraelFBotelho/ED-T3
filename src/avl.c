#include "avl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {

    Info info;
    int height;
    struct node* left;
    struct node* right;
    int key;

}NodeStruct;

typedef struct tree{

    char type[20];
    NodeStruct* root;
    int size;

}TreeStruct;

// Cria e retorna uma arvore
Tree treeCreate(char type[20]){
    TreeStruct* new = (TreeStruct* ) malloc(sizeof(TreeStruct));

    strcpy(new->type, type);
    new->root = NULL;
    new->size = 0;

    return new;
}

// Encerra recursivamente nó por nó da árvore
void recTreeEnd(NodeStruct* root){

    if(root == NULL){
        return;
    }

    recTreeEnd(root->left);
    recTreeEnd(root->right);

    free(root);
}

// Encerra toda a árvore
int treeEnd(Tree tree){
    TreeStruct* treeAux = (TreeStruct* ) tree;

    if(treeAux == NULL){
        return 0;
    }

    recTreeEnd(treeAux->root);

    free(treeAux);

    return 1;
}

// Retorna a altura do nó, caso o nó não exista retorna -1
int nodeHeight(NodeStruct* node){
    if(node == NULL){
        return -1;
    }else{
        return node->height;
    }
}

// Retorna o fator de balanceamento;
int nodeFactor(NodeStruct* node){
    return labs(nodeHeight(node->left) - nodeHeight(node->right));
}

// Retorna o maior valor dentre 2 inteiros
int biggest(int x, int y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}

// Rotaciona a arvore tipo esquerda esquerda
void rotateLL(NodeStruct* root){
    NodeStruct* node;
    node = root->left;

    root->left = node->right;

    node->right = root;

    root->height = biggest(nodeHeight(root->left), nodeHeight(root->right)) + 1;

    node->height = biggest(nodeHeight(root->left), root->height) + 1;

    root = node;
}

// Rotaciona a arvore tipo direita direita
void rotateRR(NodeStruct* root){
    NodeStruct* node;
    node = root->right;

    root->right = node->left;

    node->left = root;

    root->height = biggest(nodeHeight(root->left), nodeHeight(root->right)) + 1;

    node->height = biggest(nodeHeight(root->right), root->height) + 1;

    root = node;
}

// Rotaciona a arvore tipo Esquerda Direita
void rotateLR(NodeStruct* root){
    rotateRR(root->left);
    rotateLL(root);
}

// Rotaciona a arvore tipo Direita Esquerda
void rotateRL(NodeStruct* root){
    rotateLL(root->right);
    rotateRR(root);
}

// Função de inserção recursiva
int recTreeInsert(NodeStruct* root, Info info, int key){
    int res = 0;
    // Nó folha ou primeiro nó
    if(root == NULL){
        NodeStruct* new = (NodeStruct* ) malloc(sizeof(NodeStruct));
        if(new == NULL){
            return 0;
        }

        new->info = info;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
        new->key = key;

        return 1;
    }

    NodeStruct* this = root;

    // Adiciona a esquerda e se precisar rotaciona a arvore
    if(key < this->key){
        if((res=recTreeInsert(this->left, info, key)) == 1){
            if(nodeFactor(this) >= 2){
                if(key < this->left->key){
                    rotateLL(root);
                }else{
                    rotateLR(root);
                }
            }
        }
    }else{
        // Adiciona a direita e se precisar rotaciona a arvore
        if(key > this->key){
            if((res = recTreeInsert(this->right, info, key)) == 1){
                if(nodeFactor(this) >= 2){
                    if(key > this->right->key){
                        rotateRR(root);
                    }else{
                        rotateRL(root);
                    }
                }
            }
        }else{
            // Valor igual então não é inserido
            return 0;
        }
    }

    this->height = biggest(nodeHeight(this->left), nodeHeight(this->right)) + 1;

    return res;
}

// Chama a função recursiva de inserir
int treeInsert(Tree tree, Info info, int key){
    TreeStruct* treeAux = (TreeStruct* ) tree;
    int aux = recTreeInsert(treeAux->root, info, key);

    if(aux == 1){
        treeAux->size++;
    }

    return aux;

}

NodeStruct* searchLesser(NodeStruct* this){
    NodeStruct* node1 = this;
    NodeStruct* node2 = this->left;

    while(node2 != NULL){
        node1 = node2;
        node2 = node2->left;
    }

    return node1;
}

// Função de remoção recursiva
int recTreeRemove(NodeStruct* root, int key){
    int res = 0;
    if(root == NULL){
        return 0;
    }

    // Se for menor que o nó atual vai para a esquerda e balanceia se precisar
    if(key < root->key){
        if((res = recTreeRemove(root->left, key)) == 1){
            if(nodeFactor(root) >= 2){
                if(nodeHeight(root->right->left) <= nodeHeight(root->right->right)){
                    rotateRR(root);
                }else{
                    rotateRL(root);
                }
            }
        }
    }

    // Se for maior que o nó atual vai para o nó da direita e balanceia se precisar
    if(key > root->key){
        if((res = recTreeRemove(root->right, key)) == 1){
            if(nodeFactor(root) >= 2){
                if(nodeHeight(root->left->right) <= nodeHeight(root->left->left)){
                    rotateLL(root);
                }else{
                    rotateLR(root);
                }
            }
        }
    }

    // Se for igual ao valor do nó o remove e balanceia se precisar
    if(key == root->key){
        if(root->left == NULL || root->right == NULL){
            NodeStruct* oldNode = root;
            if(root->left != NULL){
                root = root->left;
            }else{
                root = root->right;
            }
            free(oldNode);
        }else{
            NodeStruct* temp = searchLesser(root->right);
            root->info = temp->info;
            recTreeRemove(root->right, root->key);
            if(nodeFactor(root) >= 2){
                if(nodeHeight(root->left->right) <= nodeHeight(root->left->left)){
                    rotateLL(root);
                }else{
                    rotateLR(root);
                }
            }
        }
        return 1;
    }

    return res;
}

// Chama a função recursiva de remover
int treeRemove(Tree tree, int key){
    TreeStruct* treeAux = (TreeStruct* ) tree;
    int aux = recTreeRemove(treeAux->root, key);

    if(aux == 1){
        treeAux->size--;
    }

    return aux;
}