/*
 * Pipeline.c
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl, modified by 190012003
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "Pipeline.h"


Pipeline* new_Pipeline() {
    Pipeline* this = (Pipeline *) malloc(sizeof(Pipeline));
    this->head = NULL;
    this->current_size = 0;
    return this;
}


bool Pipeline_add(Pipeline* this, Function f) {
    this->head = new_ListNode(f, this->head);
	this->current_size++;
    return (this->head != NULL);
}


void Pipeline_execute(Pipeline* this) {
    ListNode *current = this->head;
    int child;
    Pipe pipeList[this->current_size];                      //idea from https://stackoverflow.com/questions/19825489/forking-and-piping-processes-in-c

    for (int i = 1; i < this->current_size + 1; i++) {
        
        if (pipe(pipeList[i]) != 0) {                       //pipe the used pipe
            printf("Failed to create pipe");
            exit(1);
        }

        if ((child = fork()) < 0) {                         //create another process
            printf("Failed to create child #0");
            exit(1);
        }

        if (child != 0) {                                   //parent
            current->f(pipeList[i][0], pipeList[i - 1][1]);
            wait(NULL);
            if (i != 1) {                                   //ultimate parent cannot exit or the program will not continue
                exit(0);
            }
            break;                                          //ultimate parent leaves loop and returns to the main function
        } else if (current->next == NULL) {                 //end of list?
            exit(0);
        }
        current = current->next;                            //child continues to next stage of loop
    }
}


void Pipeline_free(Pipeline* this) {
    ListNode *current = this->head;
    while (current != NULL) {               //free all nodes
        ListNode *temp = current;
        current = current->next;
        ListNode_destroy(temp);
        this->current_size--;
    }
    free(this);                             //free the pipeline
}

