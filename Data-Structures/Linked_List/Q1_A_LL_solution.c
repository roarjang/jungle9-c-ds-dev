////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode; // You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

///////////////////////// function prototypes ///////////////////////////////

// You Should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() /////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
			case 1:
				printf("Input an integer that you want to add to the linked list: \n");
				scanf("%d", &i);
				j = insertSortedLL(&ll, i);
				printf("The resulting linked list is: \n");
				printList(&ll);
				break;
			case 2:
				if (ll.size == 0)
					printf("The list is empty. No recent value.\n");
				else
					printf("The value %d was added at index %d\n", i, j);
				break;
			case 3:
				printf("The resulting sorted linked list is:\n");
				printList(&ll);
				break;
			case 0:
				removeAllItems(&ll);
				break;
			default:
				printf("Choice unkown.\n");
				break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item) {
	if (ll == NULL)
		return -1;

	ListNode *cur = ll->head;
	int idx = 0;

	// 리스트가 비어있을 경우 맨 앞에 삽입
	if (cur == NULL) {
		if (insertNode(ll, 0, item) == -1)
			return -1;

		return;
	}
	
	// 리스트 순회하며 중복 확인 및 삽입 위치 탐색
	while (cur != NULL) {
		if (cur->item == item)
			return -1; // 중복 항목 -> 삽입 금지
		
		if (cur->item > item) {
			// 정렬을 유지하면서 삽입
			if (insertNode(ll, idx, item) == -1)
				return -1;

			return idx;
		}

		cur = cur->next;
		idx++;
	}

	// 끝까지 탐색했는데, 더 큰 값을 찾지 못한 경우 -> 맨 뒤에 삽입
	if (insertNode(ll, idx, item) == -1)
		return -1;

	return idx;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll) {
	if (ll == NULL)
		return;

	ListNode *cur = ll->head;

	if (cur == NULL)
		printf("Empty\n");
	
	while (cur != NULL) {
		printf("%d ", cur->item);
		cur = cur->next;
	}
		
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	if (ll == NULL) return;

	ListNode *cur = ll->head;

	while (cur != NULL) {
		ListNode *next = cur->next;
		free(cur);
		cur = next;
	}

	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index) {
	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	// if (temp == NULL || index < 0) // (index < 0) 조건 중복 발생
	if (temp == NULL)
		return NULL;
	
	while (index > 0) {
		temp = temp->next;

		if (temp == NULL)
			return NULL;

		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value) {
	ListNode *newNode = malloc(sizeof(ListNode));

	if (newNode == NULL)
		return -1;

	newNode->item = value;
	newNode->next = NULL; // 기본 초기화
	
	if (ll->head == NULL || index == 0) {
		newNode->next = ll->head; // 기존 head를 다음으로 연결
		ll->head = newNode; // 새 노드를 head로 설정
	} else {
		ListNode *pre = findNode(ll, index - 1);

		if (pre == NULL)
			return -1;

		newNode->next = pre->next;
		pre->next = newNode;
	}

	ll->size++;

	return 0;
}

int removeNode(LinkedList *ll, int index) {
	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;
	
	// If removing first node, need to update head pointer
	if (index == 0) {
		ListNode *toDelete = ll->head;

		ll->head = ll->head->next;
		free(toDelete);

		ll->size--;
		
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	pre = findNode(ll, index - 1);

	if (pre == NULL || pre->next == NULL)
		return - 1;
		
	cur = pre->next;
	pre->next = cur->next;
	free(cur);
	ll->size--;

	return 0;
}