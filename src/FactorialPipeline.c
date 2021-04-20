/*
 * FactorialPipeline.c finds the sum of a certain number of factorials
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
 * Creates a bunch of ints 0 - num_ints to be sent to the next function.
 */
static void generateInts(int input, int output) {
    close(input); // not used in first pipeline stage
    printf("generateInts: process %i, parent %i\n", getpid(), getppid());
    for (int i = 0; i <= num_ints; i++) {
        write(output, &i, sizeof(int));
    }
}

/*
 * Simple performs the factorial calculations.
 */
static int factor(int in) {
    if (in == 0) {
        return 1;
    }
    return in * factor(in - 1);
}

/*
 * Reads and finds the factorial for each individual number.
 */
static void calculateFactorials(int input, int output) {
    printf("doubleInts: process %i, parent %i\n", getpid(), getppid());
    int number;
    for (int i = 0; i <= num_ints; i++) {
        read(input, &number, sizeof(int));
        int out = factor(number);
        write(output, &out, sizeof(int));
    }
}

/*
 * Sums each factorial and prints the final output.
 */
static void printFactorialSum(int input, int output) {
    close(output); // not used in last pipeline stage
    printf("printInts: process %i, parent %i\n", getpid(), getppid());
    int number;
    int out = 0;
    for (int i = 0; i <= num_ints; i++) {
        read(input, &number, sizeof(int));
        out += number;
    }
    printf("The sum of factorials is %d\n", out);
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
 * Creates a Pipeline and uses it to execute two simple functions.
 */
int main() {
    scanf("%d", &num_ints);
    printf("Setting up pipeline to calculate the the sum of factorials from 0 to %i.\n", num_ints);

    Pipeline *p = new_Pipeline();

    if (p == NULL) cleanupExit(p);
    if (!Pipeline_add(p, generateInts)) cleanupExit(p);
    if (!Pipeline_add(p, calculateFactorials)) cleanupExit(p);
    if (!Pipeline_add(p, printFactorialSum)) cleanupExit(p);
    Pipeline_execute(p);

    Pipeline_free(p);
    return 0;
}
