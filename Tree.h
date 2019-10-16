//
//  Tree.h
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"

typedef struct NODE *pNode;
struct NODE;

extern pNode Tree_newNode(char input);
extern void Tree_setLeftMostChild(pNode node, pNode leftChild);
extern void Tree_setRightSibling(pNode node, pNode rightS);
extern void Tree_setParent(pNode node, pNode parent);
extern void Tree_free(pNode node);
extern char Tree_getdData(pNode node);
extern pNode Tree_getLeftMostChild(pNode node);
extern pNode Tree_getRightS(pNode node);
extern pNode Tree_getParent(pNode node);
extern void Tree_print(pNode node);
extern int Tree_countHelper(pNode node);
extern void Tree_countDep(pNode node);

#endif /* Tree_h */
