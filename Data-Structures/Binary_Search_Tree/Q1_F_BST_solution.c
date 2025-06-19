
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void levelOrderTraversal(BSTNode *root) {
	if (root == NULL) return;
	
	// 1. Create and initialize an empty queue
	Queue *queue = malloc(sizeof(Queue));
	if (queue == NULL) return;
	queue->head = NULL;
	queue->tail = NULL;

	// 2. Add the root node to the queue
	enqueue(&(queue->head), &(queue->tail), root);

	// 3. Process nodes level by level
	while (!isEmpty(queue->head)) {
		BSTNode *curr = dequeue(&(queue->head), &(queue->tail));
		printf("%d ", curr->item);

		// 4. Add left and right children to the queue, if they exist
		if (curr->left != NULL) {
            enqueue(&(queue->head), &(queue->tail), curr->left);
        }
        if (curr->right != NULL) {
            enqueue(&(queue->head), &(queue->tail), curr->right);
        }
	}
	// 5. Clean up the queue Strucutre (queue nodes are freed during dequeue)
	free(queue);
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value) {
	// 1. If the current node is NULL, allocate and initialize a new node
	if (*node == NULL) {
		*node = malloc(sizeof(BSTNode));
		if (*node == NULL) return; // Allocation failed, exit

		(*node)->item = value;
		(*node)->left = NULL;
		(*node)->right = NULL;
	}

	// 2. Otherwise, compare and recurse to the correct subtree
	if ((*node)->item > value) {
		insertBSTNode(&((*node)->left), value);
	} else if ((*node)->item < value) {
		insertBSTNode(&((*node)->right), value);
	}
	// 3. If value == item, do nothing (no duplicates allowed)
	return;
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node) {
	if (node == NULL)
		return;

	// 1. Allocate memory for a new queue node
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	if (newPtr == NULL) {
		printf("Failed to allocate memory. Node not inserted.\n");
		return;
	}

	// 2. Assign BST node to queue node's data
	newPtr->data = node;
	// 3. Initialize the next pointer
	newPtr->nextPtr = NULL;

	// If the queue is empty, set both head and tail to the new node
	if (isEmpty(*headPtr)) {
		*headPtr = newPtr;
	} else {
		// Otherwise, append the new node to the tail
		(*tailPtr)->nextPtr = newPtr;
	}
	// In both cases, update the tail to point to the new node
	*tailPtr = newPtr;
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr) {
	// Check if the queue is empty
	if (*headPtr == NULL) {
		return NULL;
	}

	// Save the BST node to return
	BSTNode *retNode = (*headPtr)->data;

	// Backup the current head node to free later
	QueueNode *tempPtr = *headPtr;

	// Move head to the next node
	*headPtr = (*headPtr)->nextPtr;

	// If the queue is now empty, set tail to NULL as well
	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	// Free the old head node
	free(tempPtr);

	// Return the dequeued BST node
	return retNode;
}

int isEmpty(QueueNode *head) {
	return head == NULL;
}

void removeAll(BSTNode **node) {
	if (*node == NULL)
		return;

	// 1. Recursively free left and right subtrees
	removeAll((*node)->left);
	removeAll((*node)->right);

	// 2. Free the current node
	free(*node);

	// 3. Set the pointer to NULL to avoid dangling reference
	*node = NULL;
}