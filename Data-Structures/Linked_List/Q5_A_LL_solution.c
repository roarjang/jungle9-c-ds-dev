//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
	    printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	if (ll == NULL || ll->head == NULL)
		return;

	int frontSize = (ll->size + 1) / 2;
	ListNode *cur = ll->head;
	
	for (int i = 0; i < ll->size; i++) {
		LinkedList *targetList = (i < frontSize) ? resultFrontList : resultBackList;

		if (insertNode(targetList, targetList->size, cur->item) == -1)
			return;

		cur = cur->next;
	}

	removeAllItems(ll);
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll) {
	if (ll == NULL)
		return;

	if (ll->head == NULL) {
		printf("Empty\n");
		return;
	}
	
	ListNode *cur = ll->head;

	while (cur != NULL) {
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll) {
	if (ll == NULL || ll->head == NULL)
		return;

	ListNode *cur = ll->head;
	while (cur != NULL) {
		ListNode *toDelete = cur;
		cur = cur->next;
		free(toDelete);
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index) {
	if (ll == NULL || ll->head == NULL || index < 0 || index >= ll->size)
		return NULL;

	if (index == 0)
		return ll->head;

	ListNode *cur = ll->head;
	for (int i = 0; i < index; i++) {
		cur = cur->next;
	}

	return cur;
}

int insertNode(LinkedList *ll, int index, int value) {
	if (ll == NULL || index < 0 || index > ll->size)
		return -1;

	ListNode *newNode = malloc(sizeof(ListNode));
	if (newNode == NULL) {
		return -1;
	}

	newNode->item = value;
	newNode->next = NULL;

	if (index == 0) {
		newNode->next = ll->head;
		ll->head = newNode;
	} else {
		ListNode *pre = findNode(ll, index -1);
		if (pre == NULL) {
			free(newNode);
			return -1;
		}

		newNode->next = pre->next;
		pre->next = newNode;
	}
	ll->size++;

	return 0;
}

int removeNode(LinkedList *ll, int index) {
	if (ll == NULL || ll->head == NULL || index < 0 || index >= ll->size)
		return -1;

	ListNode *toDelete;

	if (index == 0) {
		toDelete = ll->head;
		ll->head = toDelete->next;
	} else {
		ListNode *pre = findNode(ll, index - 1);
		if (pre == NULL || pre->next == NULL)
			return -1;

		toDelete = pre->next;
		pre->next = toDelete->next;
	}
	toDelete->next = NULL; // optional: dangling pointer 예방
	free(toDelete);
	ll->size--;

	return 0;
}