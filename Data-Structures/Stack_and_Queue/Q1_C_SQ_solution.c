//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList


typedef struct _queue
{
	LinkedList ll;
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the queue from the linked list:\n");
	printf("3: Remove odd numbers from the queue:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // You need to code this function
			printf("The resulting queue is: ");
			printList(&(q.ll));
			break;
		case 3:
			removeOddValues(&q); // You need to code this function
			printf("The resulting queue after removing odd integers is: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
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

void createQueueFromLinkedList(LinkedList *ll, Queue *q) {
	if (ll == NULL || isEmptyQueue(q))
		return;

	// 0. 기존 큐 초기화
	if (!isEmptyQueue(q)) {
		removeAllItemsFromQueue(q);
	}

	// 1. LinkedList를 순회하며 큐에 삽입
	ListNode *cur = ll->head;
	while (cur != NULL) {
		enqueue(q, cur->item);

		cur = cur->next;
	}

	return;
}

// Remove all odd values from the queue, keeping only even numbers
void removeOddValues(Queue *q) {
	// Safety check: Null Pointer or empty queue
	if (q == NULL || q->ll.head == NULL)
		return;

	int original_size = q->ll.size;

	for (int i = 0; i < original_size; i++) {
		int value = dequeue(q);

		// Keep only even values
		if (value % 2 == 0) {
			enqueue(q, value);
		}
	}
	return;
}

// 값만 보고 새 리스트로 복사 - 1
// void removeOddValues(Queue *q) {
// 	if (q == NULL || q->ll.head == NULL)
// 		return;

// 	LinkedList *evenList = malloc(sizeof(LinkedList));
// 	LinkedList *ll = &(q->ll);
// 	ListNode *cur = ll->head;

// 	evenList->head = NULL;
// 	evenList->size = 0;

// 	while (cur != NULL) {
// 		if (cur->item % 2 == 0){
// 			if (insertNode(EvenList, evenList->size, cur->item) == -1) {
// 				free(evenList);
// 				return;
// 			}
// 		}
// 		cur = cur->next;
// 	}

// 	// 기존 리스트 메모리 해제
// 	removeAllItemFromQueue(q);

// 	// 새로운 리스트 내용을 큐에 복사
// 	q->ll = *evenList;
// 	free(evenList); // 구조체 껍데기만 해제 (노드는 q->ll이 갖고 있음)

// 	return;
// }

// // 값만 보고 새 리스트로 복사 - 2 (malloc으로 Stack 메모리 활용)
// void removeOddValues(Queue *q) {
// 	if (q == NULL || q->ll.head == NULL)
// 		return;

// 	// 1. 짝수만 담을 임시 큐 선언 (스택에 할당)
// 	Queue evenQueue;
// 	evenQueue.ll.head = NULL;
// 	evenQueue.ll.size = 0;

// 	// Queue temp = {0}; // 모든 필드 0으로 초기화
	
// 	// 2. 기존 큐에서 하나씩 꺼내서 짝수만 temp에 넣기
// 	while (!isEmptyQueue(q)) {
// 		int val = dequeue(q);

// 		if (val % 2 == 0)
// 			enqueue(&evenQueue, val);
// 	}

// 	// 3. evenQueue를 원래 큐로 덮어쓰기
// 	removeAllItemsFromQueue(q); // 기존 노드들 메모리 해제
// 	*q = evenQueue;

// 	return;
// }

// // 값만 보고 새 리스트로 복사 - 3 (malloc으로 Heap 메모리 활용)
// void removeOddValues(Queue *q) {
// 	if (q == NULL || q->ll.head == NULL)
// 		return;

// 	// 1. 짝수만 담을 임시 큐를 힙에 동적 할당
// 	Queue *evenQueue = malloc(sizeof(Queue));

// 	if (evenQueue == NULL)
// 		return;

// 	evenQueue->ll.head = NULL;
// 	evenQueue->ll.size = 0;

// 	// 2. 기존 큐에서 하나씩 꺼내 짝수만 evenQueue에 enqueue
// 	while (!isEmptyQueue(q)) {
// 		int val = dequeue(q);

// 		if (val % 2 == 0) {
// 			enqueue(evenQueue, val);
// 		}
// 	}

// 	// 3. 기존 큐를 정리하고 새 큐 내용 복사
// 	removeAllItemsFromQueue(q);
// 	*q = *evenQueue;

// 	// 4. 동적 할당한 임시 큐 껍데기 해제
// 	free(evenQueue);
// }

// void removeOddValues(Queue *q) {
// 	if (q == NULL || q->ll.head == NULL)
// 		return;

// 	LinkedList *ll = &(q->ll);
// 	ListNode *cur = ll->head;
// 	ListNode *next = cur->next;
// 	ListNode *prev = NULL;

// 	while (cur != NULL) {
// 		next = cur->next; // 다음 노드를 미리 저장

// 		if (cur->item % 2 != 0) {
// 			if (prev == NULL) {
// 				removeNode(ll, 0); // head 노드이면 바로 삭제
// 			} else {
// 				int index = 0;
// 				ListNode *toDelete = ll->head;

// 				while (toDelete != cur) {
// 					toDelete = toDelete->next;
// 					index++;
// 				}
// 				removeNode(ll, index);
// 			}
// 		} else {
// 			prev = cur;
// 		}
// 		cur = next;
// 	}

// 	return;
// }

//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q) {
	int item;

	if (!isEmptyQueue(q)) {
		item = ((q->ll).head)->item;
		removeNode(&(q->ll), 0);
		return item;
	}
	return -1;
}

int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
