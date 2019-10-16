//
//  Stack.c
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Stack.h"
#include "LinkedList.h"

typedef struct Stack *pStack;
struct Stack{
    LinkedList *list;
};

pStack Stack_new(){
    pStack stack = malloc(sizeof(struct Stack));
    stack->list = LinkedList_new();
    return stack;
}

bool Stack_isEmpty(pStack stack){
    return LinkedList_is_empty(stack->list);
}

void Stack_push(pStack stack, char* data){
    LinkedList_add_at_front(stack->list, data);
}

char* Stack_pop(pStack stack){
    return (char*) LinkedList_pop(stack->list);
}

void Stack_free(pStack stack){
    LinkedList_free(stack->list,true);
    free(stack);
}
