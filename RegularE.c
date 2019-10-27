//
//  RegularE.c
//  rexp
//
//  Created by Kyle Ding on 10/16/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#include "RegularE.h"
#include "Tree.h"

// 4 for atomic
// 5 for closure
// 6 for union
// 7 for concat

pNode RegularE_get(pNode node){
    if(node == NULL){
        return NULL;
    }
    pNode root = RegularE_E(node);
    return root;
}

pNode RegularE_E(pNode node){
    if(node == NULL) return NULL;
    pNode left = RegularE_C(Tree_getLeftMostChild(node));
    pNode right = RegularE_ET(Tree_getRightS(Tree_getLeftMostChild(node)));
    if(left == NULL && right == NULL) {
        return NULL;
    }else if(left == NULL){
        return NULL;
    }else if(right == NULL) {
        return left;
    }else{
        // 6 for union
        pNode root = Tree_newNode('6');
        Tree_setLeftMostChild(root, left);
        Tree_setRightSibling(left, right);
        return root;
    }
}

pNode RegularE_ET(pNode node){
    if(node == NULL) {
        // printf("Iasdfasdf");
        return NULL;
    }
    if(Tree_getData(Tree_getLeftMostChild(node)) == '0'){
        return NULL;
    }
    // Then, we know the left child is |
    return RegularE_E(Tree_getRightS(Tree_getLeftMostChild(node)));
}

pNode RegularE_C(pNode node){
    if(node == NULL) return NULL;
    pNode left = RegularE_S(Tree_getLeftMostChild(node));
    pNode right = RegularE_CT(Tree_getRightS(Tree_getLeftMostChild(node)));
    if(left == NULL && right == NULL) return NULL;
    if(left == NULL) return NULL;
    if(right == NULL) return left;
    pNode root = Tree_newNode('7');
    Tree_setLeftMostChild(root, left);
    Tree_setRightSibling(left, right);
    return root;
}

pNode RegularE_CT(pNode node){
    if(node == NULL) return NULL;
    if(Tree_getData(Tree_getLeftMostChild(node)) == '0') return NULL;
    return RegularE_C(Tree_getRightS(Tree_getLeftMostChild(node)));
}

pNode RegularE_S(pNode node){
    if(node == NULL) return NULL;
    pNode left = RegularE_A(Tree_getLeftMostChild(node));
    pNode right = RegularE_ST(Tree_getRightS(Tree_getLeftMostChild(node)));
    if(left == NULL && right == NULL) return NULL;
    if(left == NULL) return NULL;
    if(right == NULL) return left;
    Tree_setLeftMostChild(right, left);
    return right;
}

pNode RegularE_A(pNode node){
    if(node == NULL){
        return NULL;
    }
    if(Tree_getData(Tree_getLeftMostChild(node)) == '('){
        pNode temp = RegularE_E(Tree_getRightS(Tree_getLeftMostChild(node)));
        if(temp == NULL) return NULL;
        return temp;
    }
    // <X>
    pNode root = Tree_newNode('4');
    // printf("%c", Tree_getData(Tree_getLeftMostChild(node)));
    pNode child = RegularE_X(Tree_getLeftMostChild(node));
    Tree_setLeftMostChild(root, child);
    return root;
}

pNode RegularE_ST(pNode node){
    if(node == NULL) return NULL;
    if(Tree_getData(Tree_getLeftMostChild(node)) == '0') return NULL;
    return Tree_newNode('5');
}

pNode RegularE_X(pNode node){
    if(node == NULL) return NULL;
    if(Tree_getData(Tree_getLeftMostChild(node))>= 'a' && Tree_getData(Tree_getLeftMostChild(node))<= 'z'){
        return Tree_newNode(Tree_getData(Tree_getLeftMostChild(node)));
    }
    return NULL;
}

void RegularE_print(pNode root){
    if(root == NULL){
        return;
    }
    if(Tree_getData(root) >= 'a' && Tree_getData(root) <= 'z'){
        printf("%c", Tree_getData(root));
        return;
    }
    
    printf("（");

    // first, get indexs into words
    char output = Tree_getData(root);
    switch (output) {
        case '4':
            printf("ATOMIC ");
            break;
        case '5':
            printf("CLOSURE ");
            break;
        case '6':
            printf("UNION ");
            break;
        case '7':
            printf("CONCAT ");
            break;
        default:
            break;
    }
    RegularE_print(Tree_getLeftMostChild(root));
    if(Tree_getLeftMostChild(root)!=NULL){
        RegularE_print(Tree_getRightS(Tree_getLeftMostChild(root)));
    }
    
    printf(")");
    return;
}
