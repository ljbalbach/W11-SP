/*
 * Pipeline.h contains the struct for a basic Pipeline.
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl, modified by 190012003
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <stdbool.h>
#include "ListNode.h"

typedef int Pipe[2];

/*
 * Definition of a basic Pipeline.
 */
typedef struct Pipeline {
    ListNode *head;
    int current_size;
} Pipeline;

/*
 * Creates a new empty processing pipeline.
 */
Pipeline* new_Pipeline();

/*
 * Adds the specified function to the pipeline.
 * Returns true on success and false if unable to add the new stage.
 */
bool Pipeline_add(Pipeline* this, Function f);

/*
 * Executes the specified pipeline.
 */
void Pipeline_execute(Pipeline* this);


/*
 * Frees memory associated with the pipeline.
 */
void Pipeline_free(Pipeline* this);

#endif /* PIPELINE_H_ */
