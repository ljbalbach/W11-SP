/*
 * DoublePipeline.c generates ints, doubles them, and finally prints them out.
 *
 *  Created on: 17 Apr 2021
 *      Author: 190012003
 */


#include "Pipeline.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int num_ints;

/*
 * Creates a bunch of ints 1 - num_ints to be sent to the next function.
 */
static void generateInts(int input, int output) {
    close(input); // not used in first pipeline stage
    printf("generateInts: process %i, parent %i\n", getpid(), getppid());
    for (int i = 1; i <= num_ints; i++) {
        write(output, &i, sizeof(int));
    }
}

/*
 * Receives ints and doubles them before sending them off to the next function.
 */
static void doubleInts(int input, int output) {
    printf("doubleInts: process %i, parent %i\n", getpid(), getppid());
    int number;
    for (int i = 1; i <= num_ints; i++) {
        read(input, &number, sizeof(int));
        int out = number * 2;
        write(output, &out, sizeof(int));
    }
}

/*
 * Prints the ints that were received.
 */
static void printInts(int input, int output) {
    close(output); // not used in last pipeline stage
    printf("printInts: process %i, parent %i\n", getpid(), getppid());
    int number;
    for (int i = 1; i <= num_ints; i++) {
        read(input, &number, sizeof(int));
        printf("Integer number %d: %d\n", i, number);
    }
}

/*
 * Frees the Pipeline and exits the program.
 */
static void cleanupExit(Pipeline *p) {
    if (p) {
        Pipeline_free(p);
    }
    exit(-1);
}

/*
 * Creates a Pipeline and uses it to execute the doubling functions.
 */
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
