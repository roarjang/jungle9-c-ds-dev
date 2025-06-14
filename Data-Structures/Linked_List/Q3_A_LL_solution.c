//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

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
void moveOddItemsToBack(LinkedList *ll);

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
	printf("2: Move all odd integers to the back of the linked list:\n");
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
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
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

void moveOddItemsToBack(LinkedList *ll) {
	// 예외 처리: 빈 리스트가 NULL 포인터일 경우 아무 작업도 하지 않음
	if (ll == NULL || ll->head == NULL)
		return;

	// 짝수, 홀수 리스트를 위한 메모리 동적 할당
	LinkedList *evenList = malloc(sizeof(LinkedList));
	LinkedList *oddList = malloc(sizeof(LinkedList));
	if (evenList == NULL || oddList == NULL) {
		free(evenList); // 둘 중 하나라도 NULL이면 둘 다 해제
		free(oddList);
		return;
	}

	// 두 리스트 초기화
	evenList->head = NULL, evenList->size = 0;
	oddList->head = NULL, oddList->size = 0;

	ListNode *cur = ll->head;

	// 1. 원본 리스트 순회하며 짝수/홀수 분류
	while (cur != NULL) {
		if (cur->item % 2 == 0) {
			if (insertNode(evenList, evenList->size, cur->item) == -1) {
				// 메모리 할당 실패 시 cleanup
				removeAllItems(evenList);
				removeAllItems(oddList);
				free(evenList);
				free(oddList);

				return;
			}
		} else {
			if (insertNode(oddList, oddList->size, cur->item) == - 1) {
				removeAllItems(evenList);
				removeAllItems(oddList);
				free(evenList);
				free(oddList);

				return;
			}
		}

		cur = cur->next;
	}
	// 2. 기존 리스트 비우기
	removeAllItems(ll);

	// 3. 짝수 리스트 뒤에 홀수 리스트 연결
	if (evenList->size > 0) {
	ll->head = evenList->head;

		ListNode *evenLast = findNode(evenList, evenList->size - 1);
		evenLast->next = oddList->head;
	} else {
		ll->head = oddList->head;
	}

	ll->size = evenList->size + oddList->size;

	// 임시 리스트 구조체 메모리 해제 (노드 해제는 위에서 처리됨)
	free(evenList);
	free(oddList);
}

// void moveOddItemsToBack(LinkedList *ll) {
// 	// 예외 처리: 빈 리스트가 NULL 포인터일 경우 아무 작업도 하지 않음
// 	if (ll == NULL || ll->head == NULL)
// 		return;

// 	int index = 0; // 현재 노드의 인덱스를 추적
// 	int originalSize = ll->size; // 초기 리스트 크기 저장 (반복 횟수 고정)
// 	ListNode *cur = ll->head; // 현재 순회 중인 노드 포인터

// 	// 초기 크기만큼만 순회 (중간에 ㄴ드를 삽입해도 추가 순회는 하지 않음)
// 	for (int i = 0; i < originalSize; i++) {
// 		ListNode *next = cur->next; // 다음 노드를 미리 저장 (현재 노드 삭제 가능성 때문)

// 		if (cur->item % 2 != 0) {
// 			// 현재 노드의 값이 홀수인 경우
// 			// 1. 리스트의 끝에 삽입 (뒤로 보내기)
// 			if (insertNode(ll, originalSize, cur->item) == -1)
// 				return; // 메모리 할당 실패 등 오류 발생 시 종료
			
// 			// 2. 현재 홀수 노드를 삭제
// 			if (removeNode(ll, index) == -1)
// 				return;

// 				// index는 그대로 유지 (삭제했으므로 다음 인덱스가 자동 당겨짐)
// 		} else {
// 			// 짝수 노드는 그대로 두고 다음 인덱스로 이동
// 			index++;
// 		}

// 		// 다음 노드로 이동
// 		cur = next;
// 	}

// 	return;
// }

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){
	if (ll == NULL)
		return;

	ListNode *cur = ll->head;

	if (cur == NULL) {
		printf("Empty\n");
		return;
	}
	
	while (cur != NULL) {
		printf("%d ", cur->item);
		cur = cur->next;
	}

	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	if (ll == NULL || ll->head == NULL)
		return;

	ListNode *cur = ll->head;

	while (cur != NULL) {
		ListNode *next = cur->next;
		// cur->next = NULL; // optional
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
		newNode->next = ll->head; // 기존 head를 다음으로 연결
		ll->head = newNode; // 새 노드를 head로 설정
	} else {
		ListNode *pre = findNode(ll, index - 1);

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

int removeNode(LinkedList *ll, int index){
	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0) {
		ListNode *toDelete = ll->head;

		ll->head = toDelete->next;
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