/*
 * Pipeline.c
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl, modified by 190012003
 */

#include <stdio.h>

#include "Pipeline.h"


Pipeline* new_Pipeline() {
    Pipeline* this = (Pipeline *) malloc(sizeof(Pipeline));
    this->head = NULL;
    this->current_size = 0;
    return this;
}


bool Pipeline_add(Pipeline* this, Function f) {
    ListNode *current = this->head;
    if (this->current_size == 0) {                  //set new node as head if empty
        this->head = new_ListNode(f, NULL);
    } else {
        while (current->next != NULL) {             //find end of the list and add on
            current = current->next;
        }
        current->next = new_ListNode(f, NULL);
    }
	this->current_size++;
    return this;
}


void Pipeline_execute(Pipeline* this) {
    
}


void Pipeline_free(Pipeline* this) {
    while (this->current_size > 0) {        //free all nodes
        ListNode_destroy(this->head);
    }
    free(this);                             //free the pipeline
}

