#include "avl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"
#define FLAG_STOP_REMOVE -9999

typedef struct item{

    Info info;
    double keyX;
    double keyY;

}Item;

typedef struct node {

    List list;
    int height;
    struct node* left;
    struct node* right;
    double key;
    double widthBlock;
    double lesserX;
    double biggerX;

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

    for(NodeL* nodeAux = getListFirst(root->list); nodeAux; nodeAux = getListNext(nodeAux)){
        Item* item = (Item* ) getListInfo(nodeAux);
        if(item != NULL){
            free(item);
        }
    }

    endList(root->list);
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
void rotateLL(NodeStruct** root){
    NodeStruct* node;
    node = (*root)->left;

    (*root)->left = node->right;

    node->right = (*root);

    (*root)->height = biggest(nodeHeight((*root)->left), nodeHeight((*root)->right)) + 1;

    node->height = biggest(nodeHeight((*root)->left), (*root)->height) + 1;

    *root = node;
}

// Rotaciona a arvore tipo direita direita
void rotateRR(NodeStruct** root){
    NodeStruct* node;
    node = (*root)->right;

    (*root)->right = node->left;

    node->left = (*root);

    (*root)->height = biggest(nodeHeight((*root)->left), nodeHeight((*root)->right)) + 1;

    node->height = biggest(nodeHeight((*root)->right), (*root)->height) + 1;

    (*root) = node;
}

// Rotaciona a arvore tipo Esquerda Direita
void rotateLR(NodeStruct** root){
    rotateRR(&(*root)->left);
    rotateLL(root);
}

// Rotaciona a arvore tipo Direita Esquerda
void rotateRL(NodeStruct** root){
    rotateLL(&(*root)->right);
    rotateRR(root);
}

// Busca o menor nó
NodeStruct* searchLesser(NodeStruct* this){
    NodeStruct* node1 = this;
    if(node1 == NULL){
        return NULL;
    }
    NodeStruct* node2 = this->left;

    while(node2 != NULL){
        node1 = node2;
        node2 = node2->left;
    }

    return node1;
}

// Busca o maior nó
NodeStruct* searchBigger(NodeStruct* this){
    NodeStruct* node1 = this;
    if(node1 == NULL){
        return NULL;
    }
    NodeStruct* node2 = this->right;


    while(node2 != NULL){
        node1 = node2;
        node2 = node2->right;
    }

    return node1;
}

// Correge o X máximo e mínimo
int recChangeBiggerLesser(NodeStruct* root){

    if(root == NULL){
        return 0;
    }

    NodeStruct* big = searchBigger(root->right);
    NodeStruct* small = searchLesser(root->left);
    root->biggerX = big != NULL? big->key + big->widthBlock : root->key + root->widthBlock;
    root->lesserX = small != NULL? small->key : root->key;

    recChangeBiggerLesser(root->left);
    recChangeBiggerLesser(root->right);

    return 1;
}

// Função de inserção recursiva
int recTreeInsert(NodeStruct** root, Info info, double keyX, double keyY, double width){
    int res = 0;
    // Nó folha ou primeiro nó
    if(*root == NULL){
        NodeStruct* new = (NodeStruct* ) malloc(sizeof(NodeStruct));
        if(new == NULL){
            return 0;
        }

        Item* item = (Item*) malloc(sizeof(Item));
        item->info = info;
        item->keyX = keyX;
        item->keyY = keyY;

        new->list = createList();
        insertListElement(new->list,item);
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
        new->widthBlock = width;
        new->key = keyX;
        new->biggerX = keyX + width;
        new->lesserX = keyX;
        *root = new;
        return 1;
    }

    NodeStruct* this = *root;


    // Enquanto for passando pelos nós atualiza o maior e menor :)
    if(this->biggerX < keyX + width){
        this->biggerX = keyX + width;
    }
    if(this->lesserX > keyX){
        this->lesserX = keyX;
    }

    // Adiciona a esquerda e se precisar rotaciona a arvore
    if(keyX < this->key){
        if((res=recTreeInsert(&(this->left), info, keyX, keyY, width)) == 1){
            if(nodeFactor(this) >= 2){
                if(keyX < this->left->key){
                    rotateLL(root);
                }else{
                    rotateLR(root);
                }
            }
        }
    }else{
        // Adiciona a direita e se precisar rotaciona a arvore
        if(keyX > this->key){
            if((res = recTreeInsert(&(this->right), info, keyX, keyY, width)) == 1){
                if(nodeFactor(this) >= 2){
                    if(keyX > this->right->key){
                        rotateRR(root);
                    }else{
                        rotateRL(root);
                    }
                }
            }
        }else{
            // Caso o X seja igual, ele adiciona na lista do nó correspondente
            Item* item = malloc(sizeof(Item));
            item->info = info;
            item->keyX = keyX;
            item->keyY = keyY;
            insertListElement(this->list, item);
            return 0;
        }
    }

    // Atualiza a altura do nó para balancear!
    this->height = biggest(nodeHeight(this->left), nodeHeight(this->right)) + 1;

    return res;
}

// Chama a função recursiva de inserir
int treeInsert(Tree tree, Info info, double keyX, double keyY, double width){
    TreeStruct* treeAux = (TreeStruct* ) tree;
    int aux = recTreeInsert(&(treeAux->root), info, keyX, keyY, width);

    if(aux == 1){
        // Se a inserção foi bem sucessida, verifica atualiza os mínimos e máximos
        recChangeBiggerLesser(treeAux->root);
        treeAux->size++;
    }

    return aux;

}

// Função de remoção recursiva
int recTreeRemove(NodeStruct** root, double keyX, double keyY){
    int res = 0;
    if(*root == NULL){
        return 0;
    }

    // Se for menor que o nó atual vai para a esquerda e balanceia se precisar
    if(keyX < (*root)->key){
        if((res = recTreeRemove(&(*root)->left, keyX, keyY)) == 1){
            if(nodeFactor(*root) >= 2){
                if(nodeHeight((*root)->right->left) <= nodeHeight((*root)->right->right)){
                    rotateRR(root);
                }else{
                    rotateRL(root);
                }
            }
        }
    }

    // Se for maior que o nó atual vai para o nó da direita e balanceia se precisar
    if(keyX > (*root)->key){
        if((res = recTreeRemove(&(*root)->right, keyX, keyY)) == 1){
            if(nodeFactor(*root) >= 2){
                if(nodeHeight((*root)->left->right) <= nodeHeight((*root)->left->left)){
                    rotateLL(root);
                }else{
                    rotateLR(root);
                }
            }
        }
    }

    // Se for igual e a lista tem mais de um elemento remove da lista
    if(keyX == (*root)->key && (getListSize((*root)->list) > 1 && keyY != FLAG_STOP_REMOVE)){
        for(NodeL nodeAux = getListFirst((*root)->list); nodeAux; nodeAux = getListNext(nodeAux)){
            Item* item = (Item* ) getListInfo(nodeAux);
            if(keyY == item->keyY){
                removeListNode((*root)->list, nodeAux);
                free(item);
                return 1;
            }
        }
    }

    // Se for igual ao valor do nó e unico elemento ou é pra substituir outro nó na recursão, remove e balanceia
    if((keyX == (*root)->key && getListSize((*root)->list) == 1) || (keyX == (*root)->key && keyY == FLAG_STOP_REMOVE)){
            if((*root)->left == NULL || (*root)->right == NULL){
                NodeStruct* oldNode = (*root);
                if((*root)->left != NULL){
                    (*root) = (*root)->left;
                }else{
                    (*root) = (*root)->right;
                }
            
                // endList(oldNode->list);
                free(oldNode);
            }else{
                NodeStruct* temp = searchLesser((*root)->right);

                endList((*root)->list);
                (*root)->list = temp->list;
                (*root)->key = temp->key;
                NodeStruct* big = searchBigger((*root)->right);
                NodeStruct* small = searchLesser((*root)->left);
                (*root)->biggerX = big != NULL? big->key + big->widthBlock : (*root)->key + (*root)->widthBlock;
                (*root)->lesserX = small != NULL? small->key : (*root)->key;

                recTreeRemove(&(*root)->right, (*root)->key, FLAG_STOP_REMOVE);
                if(nodeFactor(*root) >= 2){
                    if(nodeHeight((*root)->left->right) <= nodeHeight((*root)->left->left)){
                        rotateLL(root);
                    }else{
                        rotateLR(root);
                    }
                }
            }
        return 1;
    }

    // Caso remova o nó troca os maiores e menores
    NodeStruct* big = searchBigger((*root)->right);
    NodeStruct* small = searchLesser((*root)->left);
    (*root)->biggerX = big != NULL? big->key + big->widthBlock: (*root)->key + (*root)->widthBlock;
    (*root)->lesserX = small != NULL? small->key : (*root)->key;


    return res;
}

// Chama a função recursiva de remover
int treeRemove(Tree tree, double keyX, double keyY){
    TreeStruct* treeAux = (TreeStruct* ) tree;
    int aux = recTreeRemove(&(treeAux->root), keyX, keyY);

    if(aux == 1){
        treeAux->size--;
    }

    return aux;
}

// Recursivamente busca com a key a lista com os valores
List recTreeSearch(NodeStruct* root, double keyX){
    if(root == NULL){
        return  NULL;
    }

    if(root->key == keyX){
        return root->list;
    }

    List aux;

    if(keyX > root->key){
        aux = recTreeSearch(root->right, keyX);
    }else{
        aux = recTreeSearch(root->left, keyX);
    }

    return aux;
}

// Chama a função que retorna a lista
Info treeSearch(Tree tree, double keyX,  double keyY){
    TreeStruct* treeAux = (TreeStruct* ) tree;

    List* list = recTreeSearch(treeAux->root, keyX);

    for(NodeL* nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
        Item* item = getListInfo(nodeAux);

        if(item->keyX == keyX && item->keyY == keyY){
            return item->info;
        }
    }

    return NULL;
}

// Retorna o nó à direita
Node getTreeRight(Node root){
    NodeStruct* rootAux = (NodeStruct* ) root;

    return rootAux->right;
}

// Retorna o nó à esquerda
Node getTreeLeft(Node root){
    NodeStruct* rootAux = (NodeStruct* ) root;

    return rootAux->left;
}

// Retorna a raiz da árvore
Node getTreeRoot(Tree tree){
    TreeStruct* treeAux = (TreeStruct* ) tree;

    return treeAux->root;
}

// Gera uma lista com os Infos de um nó caso queira obte-los por inteiro
List getTreeNodeItens(Node root){
    NodeStruct* rootAux = (NodeStruct* ) root;
    if(rootAux == NULL){
        return NULL;
    }
    if(rootAux->list == NULL){
        return NULL;
    }

    return rootAux->list;
}

// Retorna o Info do Item da lista no nó
Info getTreeListItem(Info item){
    Item* itemAux = (Item* ) item;

    return itemAux->info;
}

// Retorna a chave do Item da lista no nó
double getTreeListKeyY(Info item){
    Item* itemAux = (Item* ) item;

    return itemAux->keyY;
}

// Renorna o x Máximo
double getTreeBiggerX(Node root){
    NodeStruct* rootAux = (NodeStruct* ) root;

    return rootAux->biggerX;
}

// Retorna o X Mínimo
double getTreeLesserX(Node root){
    NodeStruct* rootAux = (NodeStruct* ) root;

    return rootAux->lesserX;
}

// Retorna o tamanho da árvore
int getTreeSize(Tree tree){
    TreeStruct* treeAux = (TreeStruct* ) tree;

    return treeAux->size;
}

// Retorna a chave da árvore
double getTreeKey(Node root){
    NodeStruct* rootAux = (NodeStruct* ) root;

    return rootAux->key;
}

// Retorna a altura do nó da árvore
int getTreeHeight(Node root){
    NodeStruct* rootAux = (NodeStruct* ) root;

    return rootAux->height;
}