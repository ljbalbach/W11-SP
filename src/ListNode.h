/*
 * ListNode.h
 *
 *      Author: jonl, modified by 190012003
 */

#ifndef LISTNODE_H_
#define LISTNODE_H_

#include "Pipeline.h"

typedef struct ListNode ListNode;
struct ListNode {
	Function f;
	ListNode *next;
};

ListNode *new_ListNode(Function f, ListNode *next);

void ListNode_destroy(ListNode *this);

#endif /* LISTNODE_H_ */