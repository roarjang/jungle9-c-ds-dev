//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

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
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// 함수 재사용
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	int index = 1;

	while (ll2->head != NULL) {
		int value = ll2->head->item;

		// 교차 위치에 삽입 실패 시 종료
		if (insertNode(ll1, index, value) == -1)
			break;
		
		removeNode(ll2, 0);

		index += 2;
	}
}

// void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
// {
// 	int index = 0;

// 	while (ll2->head != NULL) {
// 		// ll2에서 노드 하나 분리
// 		ListNode *cur = ll2->head;
// 		ll2->head = cur->next; // 다음 노드를 미리 저장하기
// 		cur->next = NULL; // ll2와 끊기
// 		ll2->size--;
		
// 		// ll1의 삽입 위치 노드 찾기
// 		ListNode *pre = findNode(ll1, index);
		
// 		if (pre != NULL) {
// 			// ll1에 cur 노드 삽입
// 			cur->next = pre->next;
// 			pre->next = cur;
// 			ll1->size++;

// 			index += 2;
// 		} else {
// 			// 더 이상 삽입할 위치가 없으면 다시 ll2에 되돌려 연결
// 			cur->next = ll2->head;
// 			ll2->head = cur;
// 			ll2->size++;

// 			break;
// 		}
// 	}
// }

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){
	if (ll == NULL) return;

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


ListNode *findNode(LinkedList *ll, int index){
	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

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

int insertNode(LinkedList *ll, int index, int value){
	ListNode *newNode = malloc(sizeof(ListNode));

	if (newNode == NULL)
		return -1;

	newNode->item = value;
	newNode->next = NULL; // 기본 초기화

	if (ll->head == NULL || index == 0) {
		newNode->next = ll->head; // 기존 head를 다음으로 변경
		ll->head = newNode; // 새 노드를 head로 설정
	} else {
		ListNode *pre = findNode(ll, index - 1);

		if (pre == NULL)
			return -1;
		
		newNode->next = pre->next; // 먼저 연결
		pre->next = newNode; // 그 다음 이전 노드가 새 노드 가리키도록
	}

	ll->size++;

	return 0;
}


int removeNode(LinkedList *ll, int index){
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
		return -1;

	cur = pre->next;
	pre->next = cur->next;
	free(cur);
	ll->size--;

	return 0;
}
