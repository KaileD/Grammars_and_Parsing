//
//  main.c
//  rexp
//
//  Created by Kyle Ding on 10/15/19.
//  Copyright © 2019 Kyle Ding. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "TDP.h"
#include "Tree.h"
#include "RDP.h"

int main(int argc, const char * argv[]) {

    while(1) {
        printf("\nPlease enter an expression:");
        char *input = malloc(100);

        fgets(input, 65, stdin);

        printf("\nRecursive-descent Parser:\n");

        pNode root = RDP_new(input);

        if(root == NULL) {
            printf("Input is not Well-Formed!!\n");
        }else {
            Tree_print(root);
        }

        Tree_free(root);
        
        printf( "\nTABLE DRIVEN PARSING:\n");
        //char *input = (char *) malloc(65);

        pNode root1 = TDP_Parse(input);
        if(root1 == NULL){
            printf("Input is not Well-Formed!!\n");
        }else {
            Tree_print(root1);
        }
        Tree_free(root1);


    }
    
    return 0;
}
