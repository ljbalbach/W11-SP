/*
 * DoublePipeline.c
 *
 *  Created on: 17 Apr 2021
 *      Author: 190012003
 */


#include "Pipeline.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int num_ints;

static void generateInts(int input, int output) {
    close(input); // not used in first pipeline stage
    printf("generateInts: process %i, parent %i\n", getpid(), getppid());
    for (int i = 1; i <= num_ints; i++) {
        write(output, &i, sizeof(int));
    }
}

static void doubleInts(int input, int output) {
    printf("doubleInts: process %i, parent %i\n", getpid(), getppid());
    int number;
    for (int i = 1; i <= num_ints; i++) {
        read(input, &number, sizeof(int));
        int out = number * 2;
        write(output, &out, sizeof(int));
    }
}

static void printInts(int input, int output) {
    close(output); // not used in last pipeline stage
    printf("printInts: process %i, parent %i\n", getpid(), getppid());
    int number;
    for (int i = 1; i <= num_ints; i++) {
        read(input, &number, sizeof(int));
        printf("Integer number %d: %d\n", i, number);
    }
}

static void cleanupExit(Pipeline *p) {
    if (p) {
        Pipeline_free(p);
    }
    exit(-1);
}

int main() {
    scanf("%d", &num_ints);
    printf("Setting up pipeline to calculate the the double of each integer 1 to %i.\n", num_ints);

    Pipeline *p = new_Pipeline();

    if (p == NULL) cleanupExit(p);
    if (!Pipeline_add(p, generateInts)) cleanupExit(p);
    if (!Pipeline_add(p, doubleInts)) cleanupExit(p);
    if (!Pipeline_add(p, printInts)) cleanupExit(p);
    Pipeline_execute(p);

    Pipeline_free(p);
    return 0;
}