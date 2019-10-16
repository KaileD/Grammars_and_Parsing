//
//  RDP.c
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "RDP.h"
#include "Tree.h"

pNode RDP_root;
char *RDP_nextChar;

bool RDP_lookAhead(char c){
    return *RDP_nextChar == c;
}

bool RDP_MatchT(char c){
    if(RDP_lookAhead(c)){
        RDP_nextChar++;
        return true;
    }
    else{
        return false;
    }
}

pNode X(){
    pNode XNode = Tree_newNode('X');
    if(*RDP_nextChar >= 'a' && *RDP_nextChar <= 'z'){
        // if it's a lower case
        pNode p = Tree_newNode(*RDP_nextChar);
        Tree_setLeftMostChild(XNode, p);
        // go to the next input
        RDP_nextChar++;
    }else{
        return NULL;
    }
    return XNode;
}

// <CT> -> .<C>|e
pNode CT(){
    pNode CTNode = Tree_newNode('2');
    if(!RDP_lookAhead('.')){
        Tree_setLeftMostChild(CTNode, Tree_newNode('0'));
    }else{
        if(!RDP_MatchT('.')) return NULL;

        pNode p = C();
        if(p == NULL){
            return NULL;
        }
        pNode symbol = Tree_newNode('.');
        Tree_setLeftMostChild(CTNode, symbol);
        Tree_setRightSibling(symbol, p);
    }
    return CTNode;
}

// <ET> -> |<E>|e
pNode ET(){
    pNode ETNode = Tree_newNode('1');  // use 0 for epslion
    if(!RDP_lookAhead('|')){
        Tree_setLeftMostChild(ETNode, Tree_newNode('0'));
    }else{
        if(!RDP_MatchT('|')) return NULL;

        pNode p = E();
        if(p == NULL){
            return NULL;
        }
        
        pNode symbol = Tree_newNode('|');
        Tree_setLeftMostChild(ETNode, symbol);
        Tree_setRightSibling(symbol, p);
    }
    
    return ETNode;
}

// <E> -> <C><ET>
pNode E(){
    pNode ENode = Tree_newNode('E');
    
    if(*RDP_nextChar == '\n'){
        Tree_setLeftMostChild(ENode, Tree_newNode('0'));
    }else{
        pNode p1 = C();
        if(p1 == NULL){
            return NULL;
        }
        pNode p2 = ET();
        if(p2 == NULL){
            return NULL;
        }
        
        Tree_setLeftMostChild(ENode, p1);
        Tree_setRightSibling(p1, p2);
    }
    
    return ENode;
}

// <A> -> (<E>)|<X>
pNode A(){
    pNode ANode = Tree_newNode('A');
    
    if(!RDP_lookAhead('(')){
        pNode p = X();
        if(p == NULL){
            return NULL;
        }
        Tree_setLeftMostChild(ANode, p);
    }else{
        //(<E>)
        if(!RDP_MatchT('(')) return NULL;
        pNode p = E();
        if(p == NULL) return NULL;
        if(!RDP_MatchT(')')) return NULL;
        pNode temp = Tree_newNode('(');
        Tree_setLeftMostChild(ANode, temp);
        Tree_setRightSibling(temp, p);
        Tree_setRightSibling(p, Tree_newNode(')'));
    }
    
    return ANode;
}

// <ST> -> *<ST>|e
pNode ST(){
    pNode STNode = Tree_newNode('3');
    if(!RDP_lookAhead('*')){
        Tree_setLeftMostChild(STNode, Tree_newNode('0'));
    }else{
        // *<ST>
        if(!RDP_MatchT('*')) return NULL;

        pNode p = ST();
        if(p == NULL) return NULL;
        pNode symbol = Tree_newNode('*');
        Tree_setLeftMostChild(STNode, symbol);
        Tree_setRightSibling(symbol, p);
    }
    return STNode;
}

// <S> -> <A><ST>
pNode S(){
    
    pNode SNode = Tree_newNode('S');
    
    pNode p1 = A();
    if(p1 == NULL){
        return NULL;
    }
    pNode p2 = ST();
    if(p2 == NULL){
        return NULL;
    }
        
    Tree_setLeftMostChild(SNode, p1);
    Tree_setRightSibling(p1, p2);
    
    return SNode;
    
}

// <C> -> <S><CT>
pNode C(){
    
    pNode CNode = Tree_newNode('C');
    
    pNode p1 = S();
    if(p1 == NULL){
        return NULL;
    }
    pNode p2 = CT();
    if(p2 == NULL){
        return NULL;
    }
        
    Tree_setLeftMostChild(CNode, p1);
    Tree_setRightSibling(p1, p2);
    
    return CNode;
    
}


pNode RDP_new(char *input){
    RDP_nextChar = input;
    RDP_root = E();
    
    if(RDP_root == NULL){
        return NULL;
    }
    if(!RDP_MatchT('\n')){
        return NULL;
    }
    
    return RDP_root;
}


