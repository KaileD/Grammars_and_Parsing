//
//  RDP.h
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#ifndef RDP_h
#define RDP_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "RDP.h"
#include "Tree.h"

extern pNode RDP_root;
extern char *RDP_nextChar;

extern bool RDP_lookAhead(char c);
extern bool RDP_MatchT(char c);
extern pNode X();
extern pNode CT();
extern pNode ET();
extern pNode E();
extern pNode A();
extern pNode ST();
extern pNode S();
extern pNode C();
extern pNode RDP_new(char *input);

#endif /* RDP_h */
