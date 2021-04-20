/*
 * ListNode.h contains the struct for a ListNode.
 *
 *      Author: jonl, modified by 190012003
 */

#ifndef LISTNODE_H_
#define LISTNODE_H_

typedef void (*Function)(int input, int output);

typedef struct ListNode ListNode;
struct ListNode {
	Function f;
	ListNode *next;
};

/*
 * Creates a new ListNode containing a function and a next node in the linked list.
 */
ListNode *new_ListNode(Function f, ListNode *next);

/*
 * Frees memory associated with the ListNode.
 */
void ListNode_destroy(ListNode *this);

#endif /* LISTNODE_H_ */