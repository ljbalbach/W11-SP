/*
 * TestPipeline.c
 *
 *  Created on: 17 Apr 2021
 *      Author: 190012003
 */


#include "Pipeline.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void generateInt(int input, int output) {
    close(input); // not used in first pipeline stage
    printf("generateInt: process %i, parent %i\n", getpid(), getppid());
    int i = 1;
    printf("Sending integer: %d\n", i);
    write(output, &i, sizeof(int));
}

static void printInt(int input, int output) {
    close(output); // not used in last pipeline stage
    printf("printInt: process %i, parent %i\n", getpid(), getppid());
    int number;
    read(input, &number, sizeof(int));
    printf("Received integer: %d\n", number);
}

static void cleanupExit(Pipeline *p) {
    if (p) {
        Pipeline_free(p);
    }
    exit(-1);
}

int main() {
    printf("Setting up pipeline to send 1 between processes.\n");

    Pipeline *p = new_Pipeline();

    if (p == NULL) cleanupExit(p);
    if (!Pipeline_add(p, generateInt)) cleanupExit(p);
    if (!Pipeline_add(p, printInt)) cleanupExit(p);
    Pipeline_execute(p);

    Pipeline_free(p);
    return 0;
}
