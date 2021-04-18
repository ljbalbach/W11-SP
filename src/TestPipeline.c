/*
 * TestPipeline.c
 *
 * Very simple unit test file for Pipeline functionality.
 *
 *      Author: 190012003
 */

#include <stdio.h>
#include "Pipeline.h"
#include "myassert.h"



/*
 * The pipeline to use during tests
 */
static Pipeline* pipeline;


/*
 * The number of tests that succeeded.
 */
static int success_count = 0;

/*
 * The total number of tests run.
 */
static int total_count = 0;


/*
 * Setup function to run prior to each test.
 */
void setup() {
    pipeline = new_Pipeline();
}



/*
 * Teardown function to run after each test.
 */
void teardown(){
    Pipeline_free(pipeline);
}

/*
 * This function is called multiple times from main for each user-defined test function.
 */
void runTest(int (*testFunction)()) {
    total_count++;
    setup();

    if (testFunction()) success_count++;

    teardown();
}


/*
 * Checks that the Linked List constructor returns a non-NULL pointer.
 */
int newPipelineIsNotNull() {
    assert(pipeline != NULL);
    return TEST_SUCCESS;
}


/*
 * Checks that the size of an empty Linked List is 0.
 */
int newPipelineSizeZero() {
    assert(pipeline->current_size == 0);
    return TEST_SUCCESS;
}

/*
 * Simple initial function for adding to the pipeline.
 */
static void fakeInitialFunction(int input, int output) {
    close(input); // not used in first pipeline stage
    int i = 1;
    write(output, &i, sizeof(int));
}

/*
 * Simple intermediate function for adding to the pipeline.
 */
static void fakeMiddleFunction(int input, int output) {
    int number;
    read(input, &number, sizeof(int));
    int out = number * 2;
    write(output, &out, sizeof(int));
}

/*
 * Simple final function for adding to the pipeline.
 */
static void fakeFinalFunction(int input, int output) {
    close(output); // not used in last pipeline stage
    int number;
    read(input, &number, sizeof(int));
}

/*
 * Checks that one function is successfully added to the Linked List.
 */
int pushOneFunction() {
    assert(Pipeline_add(pipeline, fakeInitialFunction) == true);
    assert(pipeline->head == fakeInitialFunction);
    assert(pipeline->current_size == 1);
    return TEST_SUCCESS;
}

/*
 * Checks that two functions are successfully added to the Linked List.
 */
int pushTwoFunctions() {
    assert(Pipeline_add(pipeline, fakeInitialFunction) == true);
    assert(pipeline->head == fakeInitialFunction);
    assert(pipeline->current_size == 1);
    assert(Pipeline_add(pipeline, fakeFinalFunction) == true);
    assert(pipeline->head == fakeFinalFunction);
    assert(pipeline->current_size == 2);
    return TEST_SUCCESS;
}

/*
 * Checks that three functions are successfully added to the Linked List.
 */
int pushThreeFunctions() {
    assert(Pipeline_add(pipeline, fakeInitialFunction) == true);
    assert(pipeline->head == fakeInitialFunction);
    assert(pipeline->current_size == 1);
    assert(Pipeline_add(pipeline, fakeMiddleFunction) == true);
    assert(pipeline->head == fakeMiddleFunction);
    assert(pipeline->current_size == 2);
    assert(Pipeline_add(pipeline, fakeFinalFunction) == true);
    assert(pipeline->head == fakeFinalFunction);
    assert(pipeline->current_size == 3);
    return TEST_SUCCESS;
}

/*
 * Checks that pushing to a full list returns false.
 *
int pushFail() {
    float j = 1.5;
    for (int i = 0; i < MAX_VALUE - 1; i++) {
        Stack_push(stack, j);
    }
    assert(Stack_push(stack, j) == true);
    assert(Stack_push(stack, j) == false);
    return TEST_SUCCESS;
}*/



/*
 * Main function for the Linked List tests which will run each user-defined test in turn.
 */
int main() {
    runTest(newPipelineSizeZero);
    runTest(newPipelineIsNotNull);
    runTest(pushOneFunction);
    runTest(pushTwoFunctions);
    runTest(pushThreeFunctions);
    //runTest(pushFail);

    printf("Stack Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);
}
