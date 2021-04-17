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
    return true;
}


void Pipeline_execute(Pipeline* this) {
    ListNode *current = this->head;

    Pipe pipeList[this->current_size];
    if (pipe(pipeList[0]) != 0) {
        printf("Failed to create pipe");
        exit(1);
    }
    int child;
    if ((child = fork()) < 0) {
        printf("Failed to create child #0");
        exit(1);
    }
    
    if (child != 0) {           //parent
        printf("initial parent: process %i", getpid());
        wait(NULL);
        printf("initial parent: process %i", getpid());
        close(pipeList[0][1]);
        current->f(pipeList[0][1], 0);
        close(pipeList[0][0]);
    } else {                    //child
        for (int i = 1; i < this->current_size; i++) {
            current = current->next;
            int tempChild;
            
            if ((tempChild = fork()) < 0) {
                printf("Failed to create child #%d", i);
                exit(1);
            }

            if (tempChild != 0) {        //parent
                printf("looping parent: process %i, parent %i\n", getpid(), getppid());
                wait(NULL);
                close(pipeList[i - 1][1]);
                close(pipeList[i][0]);
                current->f(pipeList[i - 1][0], pipeList[i][1]);
                close(pipeList[i - 1][0]);
                close(pipeList[i][1]);
                exit(0);
            } else if (current->next == NULL) {
                printf("end of list: process %i, parent %i\n", getpid(), getppid());
                /*close(pipeList[i][0]);
                current->f(0, pipeList[i][1]);
                close(pipeList[i][1]);*/
                exit(0);
            }
        }
    }







    /*
    Pipe pipelist[this->current_size];
    if (pipe(pipelist[0]) != 0)
        err_sysexit("Failed to create pipe");
    
    for (int i = 1; i < this->current_size; i++) {
        pid_t child;
        if (pipe(pipelist[i]) != 0)
            err_sysexit("Failed to create pipe #%d", i);

        if ((child = fork()) < 0)
            err_sysexit("Failed to create child #%d", i);

        if (child == 0) {            //is child
            fd_close(pipeList[i - 1][]);
            fd_close(pipeList[i][]);
        }
    }















    int child = fork();
    while (current != NULL) {
        if (child == 0) {
            if (current->next == NULL) {
                int fd[2];                              //call
                pipe(fd);

                current->f(0, fd);
                exit(0);
            } else {
                child = fork()                          //find child
                wait();
                current->f(0, fd);
            }
        } else {
            wait();
            int fd[2];                                  //call
            pipe(fd);

            current->f(0, fd);
        }
        current = current->next;
    }




    while (current->next != NULL) {
        int child = fork();
        if (child == 0) {
            int fd[2];
            pipe(fd);

            current->f(0, fd);
            exit(0);
        } else {

        }
        current = current->next;
    }
    



    for (int i = 0; i < this->current_size; i++) {
        int child = fork();
        if (child == 0) {
            int fd[2];
            pipe(fd);

            current->f(0, fd);
            exit(0);
        }
        current = current->next;
    }*/
}


void Pipeline_free(Pipeline* this) {
    ListNode *current = this->head;
    while (current != NULL) {           //free all nodes
        ListNode *temp = current;
        current = current->next;
        ListNode_destroy(temp);
        this->current_size--;
    }
    free(this);                             //free the pipeline
}
