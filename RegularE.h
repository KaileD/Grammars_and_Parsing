//
//  RegularE.h
//  rexp
//
//  Created by Kyle Ding on 10/16/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#ifndef RegularE_h
#define RegularE_h

#include <stdio.h>
#include "RegularE.h"
#include "Tree.h"

extern pNode RegularE_get(pNode root);
extern pNode RegularE_ET(pNode node);
extern pNode RegularE_C(pNode node);
extern pNode RegularE_CT(pNode node);
extern pNode RegularE_S(pNode node);
extern pNode RegularE_A(pNode node);
extern pNode RegularE_E(pNode node);
extern pNode RegularE_X(pNode node);
extern pNode RegularE_ST(pNode node);
extern void RegularE_print(pNode root);


#endif /* RegularE_h */
