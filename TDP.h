//
//  TDP.h
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#ifndef TDP_h
#define TDP_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Tree.h"
#include "LinkedList.h"
#include "Stack.h"

extern char *TDP_nextChar;
extern pNode TDP_root;
extern pStack stack;
extern int table[8][32];

extern bool TDP_matchT(char c);
extern bool TDP_isT(char c);
extern int catgToInt(char c);
extern pNode TDP_findSynCatg(pNode node);
extern void TDP_findProduction(int i);
extern void TDP_setProduction(char* c);
extern pNode TDP_Parse(char* input);

#endif /* TDP_h */
