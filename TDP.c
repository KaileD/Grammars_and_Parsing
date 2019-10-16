//
//  TDP.c
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Tree.h"
#include "LinkedList.h"
#include "Stack.h"

// Table Driven Parser

char *TDP_nextChar;
pNode TDP_root;
pStack stack;
int table[8][32] = {
    //    {a,  b,  c,  d,  e,  f,  g,  h,  i,  j,  k,  l,  m,  n,  o,  p,  q,  r,  s,  t,  u,  v,  w,  x,  y,  z,  (,  ),  *,  |,  .,  0}  // 0 is epslion
    /*E*/ {3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, -1, -1, -1, -1, -1},
    /*ET*/{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0},
    /*C*/ {6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6, -1, -1, -1, -1, -1},
    /*CT*/{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0},
    /*S*/ {7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, -1, -1, -1, -1, -1},
    /*ST*/{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0},
    /*A*/ {8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  5, -1, -1, -1, -1, -1},
    /*X*/ {9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, -1, -1, -1, -1, -1, -1}
};


bool TDP_matchT(char c){
    if(*TDP_nextChar == c){
        TDP_nextChar++;
        return true;
    }else{
        return false;
    }
}

bool TDP_isT(char c){
    if((c>='a' && c<='z') || c == '(' || c == ')' || c == '*' || c == '|' || c == '.' || c == '0'){
        return true;
    }
    else{
        return false;
    }
}

int catgToInt(char c){
    switch (c) {
        case 'E':
            return 0;
        case '1':
            return 1;
        case 'C':
            return 2;
        case '2':
            return 3;
        case 'S':
            return 4;
        case '3':
            return 5;
        case 'A':
            return 6;
        case 'X':
            return 7;
        default:
            return -1;
    }
}

int iToInt(char c){
    if(c == '\n'){
        return -1;
    }
    if(c >= 'a' && c <= 'z'){
        return ((int)c - 97);  // Not sure, but I hope this works
    }
    switch (c) {
        case '(':
            return 26;
        case ')':
            return 27;
        case '*':
            return 28;
        case '|':
            return 29;
        case '.':
            return 30;
        case '0':
            return 31;
        default:
            return 100;
    }
}

pNode TDP_findSynCatg(pNode node){
    if(Tree_getLeftMostChild(node) != NULL){
        pNode tempN = TDP_findSynCatg(Tree_getLeftMostChild(node));
        if(tempN != NULL){
            return tempN;
        }
    }else if(!TDP_isT(Tree_getdData(node))){
        return node;
    }
    if(Tree_getRightS(node)!=NULL){
        pNode temp = TDP_findSynCatg(Tree_getRightS(node));
        if(temp != NULL) return temp;
    }
    return NULL;
}

void TDP_findProduction(int i){
    pNode node = TDP_findSynCatg(TDP_root);
    switch (i) {
        case -1:
            while(!Stack_isEmpty(stack)){
                Stack_pop(stack);
            }
            TDP_root = NULL;
            break;
        case 0:
            Stack_push(stack, "0");
            // printf("%c", Tree_getdData((node)));
            Tree_setLeftMostChild(node, Tree_newNode('0'));
            break;
        case 3:
            Stack_push(stack, "1");
            Stack_push(stack, "C");
            Tree_setLeftMostChild(node, Tree_newNode('C'));
            Tree_setRightSibling(Tree_getLeftMostChild(node), Tree_newNode('1'));
            break;
        case 1:
            Stack_push(stack, "E");
            Stack_push(stack, "|");
            Tree_setLeftMostChild(node, Tree_newNode('|'));
            Tree_setRightSibling(Tree_getLeftMostChild(node), Tree_newNode('E'));
            break;
        case 6:
            Stack_push(stack, "2");
            Stack_push(stack, "S");
            Tree_setLeftMostChild(node, Tree_newNode('S'));
            Tree_setRightSibling(Tree_getLeftMostChild(node), Tree_newNode('2'));
            break;
        case 4:
            Stack_push(stack, "C");
            Stack_push(stack, ".");
            Tree_setLeftMostChild(node, Tree_newNode('.'));
            Tree_setRightSibling(Tree_getLeftMostChild(node), Tree_newNode('C'));
            break;
        case 7:
            Stack_push(stack, "3");
            Stack_push(stack, "A");
            Tree_setLeftMostChild(node, Tree_newNode('A'));
            Tree_setRightSibling(Tree_getLeftMostChild(node), Tree_newNode('3'));
            break;
        case 2:
            Stack_push(stack, "3");
            Stack_push(stack, "*");
            Tree_setLeftMostChild(node, Tree_newNode('*'));
            Tree_setRightSibling(Tree_getLeftMostChild(node), Tree_newNode('3'));
            break;
        case 8:
            Stack_push(stack, "X");
            Tree_setLeftMostChild(node, Tree_newNode('X'));
            break;
        case 5:
            Stack_push(stack, ")");
            Stack_push(stack, "E");
            Stack_push(stack, "(");
            pNode temp1 = Tree_newNode('(');
            pNode temp2 = Tree_newNode('E');
            pNode temp3 = Tree_newNode(')');
            Tree_setLeftMostChild(node, temp1);
            Tree_setRightSibling(temp1, temp2);
            Tree_setRightSibling(temp2, temp3);
            break;
        case 9:
            Stack_push(stack, "a");
            Tree_setLeftMostChild(node, Tree_newNode('a'));
            break;
        case 10:
            Stack_push(stack, "b");
            Tree_setLeftMostChild(node, Tree_newNode('b'));
            break;
        case 11:
            Stack_push(stack, "c");
            Tree_setLeftMostChild(node, Tree_newNode('c'));
            break;
        case 12:
            Stack_push(stack, "d");
            Tree_setLeftMostChild(node, Tree_newNode('d'));
            break;
        case 13:
            Stack_push(stack, "e");
            Tree_setLeftMostChild(node, Tree_newNode('e'));
            break;
        case 14:
            Stack_push(stack, "f");
            Tree_setLeftMostChild(node, Tree_newNode('f'));
            break;
        case 15:
            Stack_push(stack, "g");
            Tree_setLeftMostChild(node, Tree_newNode('g'));
            break;
        case 16:
            Stack_push(stack, "h");
            Tree_setLeftMostChild(node, Tree_newNode('h'));
            break;
        case 17:
            Stack_push(stack, "i");
            Tree_setLeftMostChild(node, Tree_newNode('i'));
            break;
        case 18:
            Stack_push(stack, "j");
            Tree_setLeftMostChild(node, Tree_newNode('j'));
            break;
        case 19:
            Stack_push(stack, "k");
            Tree_setLeftMostChild(node, Tree_newNode('k'));
            break;
        case 20:
            Stack_push(stack, "l");
            Tree_setLeftMostChild(node, Tree_newNode('l'));
            break;
        case 21:
            Stack_push(stack, "m");
            Tree_setLeftMostChild(node, Tree_newNode('m'));
            break;
        case 22:
            Stack_push(stack, "n");
            Tree_setLeftMostChild(node, Tree_newNode('n'));
            break;
        case 23:
            Stack_push(stack, "o");
            Tree_setLeftMostChild(node, Tree_newNode('o'));
            break;
        case 24:
            Stack_push(stack, "p");
            Tree_setLeftMostChild(node, Tree_newNode('p'));
            break;
        case 25:
            Stack_push(stack, "q");
            Tree_setLeftMostChild(node, Tree_newNode('q'));
            break;
        case 26:
            Stack_push(stack, "r");
            Tree_setLeftMostChild(node, Tree_newNode('r'));
            break;
        case 27:
            Stack_push(stack, "s");
            Tree_setLeftMostChild(node, Tree_newNode('s'));
            break;
        case 28:
            Stack_push(stack, "t");
            Tree_setLeftMostChild(node, Tree_newNode('t'));
            break;
        case 29:
            Stack_push(stack, "u");
            Tree_setLeftMostChild(node, Tree_newNode('u'));
            break;
        case 30:
            Stack_push(stack, "v");
            Tree_setLeftMostChild(node, Tree_newNode('v'));
            break;
        case 31:
            Stack_push(stack, "w");
            Tree_setLeftMostChild(node, Tree_newNode('w'));
            break;
        case 32:
            Stack_push(stack, "x");
            Tree_setLeftMostChild(node, Tree_newNode('x'));
            break;
        case 33:
            Stack_push(stack, "y");
            Tree_setLeftMostChild(node, Tree_newNode('y'));
            break;
        case 34:
            Stack_push(stack, "z");
            Tree_setLeftMostChild(node, Tree_newNode('z'));
            break;
        default:
            return;
    }
}

void TDP_setProduction(char *c){
    int prod = table[catgToInt(*c)][iToInt(*TDP_nextChar)];
    if(iToInt(*TDP_nextChar) == -1){
        prod = 0;
    }
    if(iToInt(*TDP_nextChar) == 100){
        prod = -1;
    }
    TDP_findProduction(prod);
}

pNode TDP_Parse(char *input){
    TDP_nextChar = input;
    stack = Stack_new();
    Stack_push(stack, "E");
    TDP_root = Tree_newNode('E');
    while(!Stack_isEmpty(stack)){
        char *temp = Stack_pop(stack);
        // printf("%c", *temp);
        if(TDP_isT(*temp)){
            TDP_matchT(*temp);
        }
        else{
            TDP_setProduction(temp);
        }
    }
    Stack_free(stack);
    if(*TDP_nextChar != '\n') return NULL;
    if(TDP_root == NULL) return NULL;
    return TDP_root;
}

