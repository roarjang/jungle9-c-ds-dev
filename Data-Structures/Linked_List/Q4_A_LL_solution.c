//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveEvenItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all even integers to the back of the linked list:\n");
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
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveEvenItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving even integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveEvenItemsToBack(LinkedList *ll) {
	if (ll == NULL || ll->head == NULL)
		return;

	LinkedList *oddList = malloc(sizeof(LinkedList));
	LinkedList *evenList = malloc(sizeof(LinkedList));

	if (oddList == NULL || evenList == NULL) {
		free(oddList);
		free(evenList);

		return;
	}

	oddList->head = NULL, oddList->size = 0;
	evenList->head = NULL, evenList->head = 0;

	ListNode *cur = ll->head;

	while (cur != NULL) {
		if (cur->item % 2 == 0) {
			if (insertNode(evenList, evenList->size, cur->item) == -1) {
				removeAllItems(oddList);
				removeAllItems(evenList);
				free(oddList);
				free(evenList);

				return;
			}
		} else {
			if (insertNode(oddList, oddList->size, cur->item) == -1) {
				removeAllItems(oddList);
				removeAllItems(evenList);
				free(oddList);
				free(evenList);

				return;
			}
		}
		cur = cur->next;
	}

	// 기존 리스트 비우기;
	removeAllItems(ll);

	if (oddList->head == NULL) {
		ll->head = evenList->head;
	} else {
		ll->head = oddList->head;

		ListNode *oddTail = findNode(oddList, oddList->size -1);
		oddTail->next = evenList->head;
	}

	ll->size = oddList->size + evenList->size;
	
	// 구조체 포인터 해제 (노드는 ll로 넘어간 상태)
	free(oddList);
	free(evenList);
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
		ListNode *next = cur->next; // 다음 노드 저장
		// cur->next = NULL; // optional (댕글링 포인터 예방)
		free(cur); // 현재 노드 해제
		cur = next; // 다음 노드로 이동
	}

	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index) {
	if (ll == NULL || ll->head == NULL || index < 0 || index >= ll->size)
		return NULL;
	
	ListNode *cur = ll->head;

	while(index > 0) {
		cur = cur->next;
		index--;
	}

	return cur;
}

int insertNode(LinkedList *ll, int index, int value) {
	if (ll == NULL || index < 0 || index > ll->size)
		return -1;

	ListNode *newNode = malloc(sizeof(ListNode));
	if (newNode == NULL)
		return -1;

	newNode->item = value;
	newNode->next = NULL;

	// idnex == 0: head에 삽입
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
	free(toDelete);
	ll->size--;

	return 0;
}