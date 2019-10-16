//
//  Tree.c
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE *pNode;
struct NODE {
    char data;
    int depth;
    pNode leftmostChild, rightSibling, parent;
};

pNode Tree_newNode(char input){
    pNode node = malloc(sizeof(struct NODE));
    node->data = input;
    node->depth = 0;
    node->leftmostChild = NULL;
    node->parent = NULL;
    node->rightSibling = NULL;
    return node;
}

void Tree_setLeftMostChild(pNode node, pNode leftChild){
    node->leftmostChild = leftChild;
    Tree_setParent(leftChild, node);
}

void Tree_setRightSibling(pNode node, pNode rightS){
    node->rightSibling = rightS;
    Tree_setParent(rightS, node->parent);
}

void Tree_setParent(pNode node, pNode parent){
   node->parent= parent;
}

void Tree_free(pNode node){
    if(node != NULL){
        Tree_free(node->leftmostChild);
        Tree_free(node->rightSibling);
        free(node);
    }
}

char Tree_getdData(pNode node){
    return node->data;
}

pNode Tree_getLeftMostChild(pNode node){
    return node->leftmostChild;
}

pNode Tree_getRightS(pNode node){
    return node->rightSibling;
}

pNode Tree_getParent(pNode node){
    return node->parent;
}

void Tree_print(pNode node){
    Tree_countDep(node);
    if(node != NULL){
        for(int i = 0; i < node->depth; i++){
            printf("  ");
        }
        printf("%c\n", node->data);
        Tree_print(node->leftmostChild);
        Tree_print(node->rightSibling);
    }
}

int Tree_countHelper(pNode node){
    if(node->parent == NULL){
        return 0;
    }else{
        return Tree_countHelper(node->parent)+1;
    }
}

void Tree_countDep(pNode node){
    if(node != NULL){
        node->depth = Tree_countHelper(node);
        Tree_countDep(node->leftmostChild);
        Tree_countDep(node->rightSibling);
    }
}
