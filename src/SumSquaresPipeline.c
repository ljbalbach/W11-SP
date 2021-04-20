/*
 * SumSquaresPipeline.c sums the squares of a certain number of numbers.
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl
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
 * Squares all of the received ints and sends them to the next function.
 */
static void squareInts(int input, int output) {
    printf("squareInts: process %i, parent %i\n", getpid(), getppid());
    for (int i = 1; i <= num_ints; i++) {
        int number;
        read(input, &number, sizeof(int));
        int result = number * number;
        write(output, &result, sizeof(int));
    }
}

/*
 * Sums all of the squared ints and prints them.
 */
static void sumIntsAndPrint(int input, int output) {
    close(output); // not used in last pipeline stage
    printf("sumIntsAndPrint: process %i, parent %i\n", getpid(), getppid());
    int number = 0;
    int result = 0;
    for (int i = 1; i <= num_ints; i++) {
        read(input, &number, sizeof(int));
        result += number;
    }
    printf("sumIntsAndPrint: result = %i\n", result);
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
 * Creates a Pipeline and uses it to execute the three functions.
 */
int main() {
    scanf("%d", &num_ints);
    printf("Setting up pipeline to calculate the sum of squares of integers 1 to %i.\n", num_ints);

    Pipeline *p = new_Pipeline();

    if (p == NULL) cleanupExit(p);
    if (!Pipeline_add(p, generateInts)) cleanupExit(p);
    if (!Pipeline_add(p, squareInts)) cleanupExit(p);
    if (!Pipeline_add(p, sumIntsAndPrint)) cleanupExit(p);
    Pipeline_execute(p);

    Pipeline_free(p);
    return 0;
}
