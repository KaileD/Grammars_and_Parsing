//
//  Stack.h
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Stack.h"
#include "LinkedList.h"

typedef struct Stack *pStack;
struct Stack;

extern pStack Stack_new(void);
extern bool Stack_isEmpty(pStack stack);
extern void Stack_push(pStack stack, char* data);
extern char* Stack_pop(pStack stack);
extern void Stack_free(pStack stack);

#endif /* Stack_h */
