//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int identical(BTNode *tree1, BTNode *tree2);

BTNode* createBTNode(int item);

BTNode* createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("Please input your choice(1/2/3/0): ");
        if(scanf("%d", &c) > 0)

        {

            switch(c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if(s){
                printf("Both trees are structurally identical.\n");
                }
                else{
                printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int identical(BTNode *tree1, BTNode *tree2) {
    // 둘 다 NULL이면 동일 (리프 노드까지 내려감)
    if (tree1 == NULL && tree2 == NULL)
        return 1;

    // 한 쪽만 NULL이면 다름
    if (tree1 == NULL || tree2 == NULL)
        return 0;

    // 값이 다르면 다름
    if (tree1->item != tree2->item)
        return 0;
    
    // 왼쪽, 오른쪽 서브트리 각각 재귀적으로 확인
    return identical(tree1->left, tree2->left) &&
           identical(tree1->right, tree2->right);
}

/////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item) {
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree() {
    Stack stk;
    stk.top = NULL; // 스택 초기화

    BTNode *root = NULL, *parent = NULL;
    int item;

    printf("Input an intger to build the binary tree.\n");
	printf("Any non-integer input (like 'x') will be treated as NULL.\n");
	
    // 루트 노드 입력
    printf("Enter root value: ");
    if (scanf("%d", &item) == 1) {
        root = createBTNode(item);
        push(&stk, root);
    } else {
        while (getchar() != '\n'); // 잘못된 입력 버퍼 지우기
        return NULL;
    }

    // 스택을 활용한 트리 구성 (레벨 순서)
    while ((parent = pop(&stk)) != NULL) {
        // 왼쪽 자식 입력
        printf("Enter left child of %d: ", parent->item);
        if (scanf("%d", &item) == 1) {
            parent->left = createBTNode(item);
        } else {
            while (getchar() != '\n');
        }

        // 오른쪽 자식 입력
        printf("Enter right child of %d: ", parent->item);
        if (scanf("%d", &item) == 1) {
            parent->right = createBTNode(item);
        } else {
            while (getchar() != '\n');
        }

        // push 순서: right 먼저, left 나중에
        // 스택은 LIFO 구조이므로, 나중에 넣은 게 먼저 꺼내진다
        if (parent->right != NULL) {
            push(&stk, parent->right);
        }

        if (parent->left != NULL) {
            push(&stk, parent->left);
        }
    }
    return root;
}

void push(Stack *stk, BTNode *node) {
    if (stk == NULL) return;

    // 1. 새로운 스택 노드 생성 (메모리 동적 할당)
    StackNode *newNode = malloc(sizeof(StackNode));
    if (newNode == NULL) return; // malloc 실패 시 안전하게 반환

    // 2. 데이터 설정
    newNode->btnode = node;

    // 3. 현재 top을 새 노드의 next로 연결
    newNode->next = stk->top;

    // 4. 새 노드를 스택의 top으로 설정
    stk->top = newNode;
}

BTNode *pop(Stack *stk) {
    if (stk == NULL || stk->top == NULL) return NULL;

    StackNode *temp = stk->top;           // top 노드를 임시 저장
    BTNode *retNode = stk->top->btnode;   // 반환할 트리 노드 저장

    stk->top = temp->next;                // top을 다음 노드로 이동
    free(temp);                           // pop된 스택 노드 메모리 해제

    return retNode;                       // 트리 노드 반환
}

void printTree(BTNode *node) {
    if (node == NULL) return;

    printTree(node->left);       // 왼쪽 서브트리
    printf("% d", node->item);   // 현재 노드
    printTree(node->right);      // 오른쪽 서브트리
}

void removeAll(BTNode **node) {
    if (node == NULL || *node == NULL) return;

    removeAll(&((*node)->left));
    removeAll(&((*node)->right));
    free(*node);       // 실제 트리 노드 해제
    *node = NULL;      // dangling pointer 방지
}