/*
 * ListNode.c
 *
 *      Author: jonl, modified by 190012003
 */

#include "ListNode.h"

#include <stddef.h>
#include <stdlib.h>


ListNode *new_ListNode(Function f, ListNode *next) {
	ListNode *this = (ListNode*) malloc(sizeof(ListNode));
	this->f = f;
	this->next = next;
	return this;
}

void ListNode_destroy(ListNode *this) {
	free(this);
}