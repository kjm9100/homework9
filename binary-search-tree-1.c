#include <stdio.h>
#include <stdlib.h>

typedef struct node { // 노드를 위한 구조체
	int key;
	struct node *left; // 왼쪽 자식 노드
	struct node *right; // 오른쪽 자식 노드
} Node;

int initializeBST(Node** h); // 이진탐색트리 초기화 및 헤드노드 생성하는 함수 선언


void inorderTraversal(Node* ptr); // recursive inorder식으로 Traversal하는 함수 선언
void preorderTraversal(Node* ptr); // recursive preorder식으로 Traversal하는 함수 선언
void postorderTraversal(Node* ptr); // recursive postorder식으로 Traversal하는 함수 선언
int insert(Node* head, int key); // 이진탐색트리에 입력값을 가진 노드를 삽입하는 함수 선언
int deleteLeafNode(Node* head, int key); // 이진탐색트리에 있는 Leaf노드들 중 입력값을 가진 노드를 삭제하는 함수 선언
Node* searchRecursive(Node* ptr, int key); // Recursive식으로 입력값을 가진 노드를 탐색하는 함수 선언
Node* searchIterative(Node* head, int key); // Iterative식으로 입력값을 가진 노드를 탐색하는 함수 선언
int freeBST(Node* head); // 이진탐색트리의 노드들에 할당된 메모리를 모두 해제하는 함수 선언



int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;

	printf("[----- [김지민] [2021041068] -----]\n\n");

	do{ // 메뉴 출력
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		// 명령키 선택
		printf("Command = ");
		scanf(" %c", &command);

		// 선택된 명령키에 따라 다른 동작을 수행
		switch(command) {
		case 'z': case 'Z': // z, Z 명령키 선택 시, 이진탐색트리 초기화 및 헤드노드 생성
			initializeBST(&head);
			break;
		case 'q': case 'Q': // q, Q 명령키 선택 시, 이진탐색트리에 할당된 메모리 모두 해제
			freeBST(head);
			break;
		case 'n': case 'N': // n, N 명령키 선택 시, 이진탐색트리에 입력값을 가진 노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': // d, D 명령키 선택 시, 이진탐색트리의 입력값을 가진 Leaf노드를 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F': // f, F 명령키 선택 시, Iterative식으로 입력값을 가진 노드 검색한 후 출력
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': // s, S 명령키 선택 시, Recursive식으로 입력값을 가진 노드 검색한 후 출력
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I': // i, I 명령키 선택 시, inorder식으로 이진탐색트리 순회
			inorderTraversal(head->left);
			break;
		case 'p': case 'P': // i, I 명령키 선택 시, preorder식으로 이진탐색트리 순회
			preorderTraversal(head->left);
			break;
		case 't': case 'T': // i, I 명령키 선택 시, postorder식으로 이진탐색트리 순회
			postorderTraversal(head->left);
			break;
		default: // 그 외의 명령키 선택 시, 오류 메시지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q, Q 명령키 선택 시에만, 프로그램 종료

	return 1;
}

int initializeBST(Node** h) { // Binary-Search-Tree 초기화 및 헤드노드 생성하는 함수  

	// Binary-Search-Tree가 이미 있다면, 노드들에 할당된 메모리 모두 해제
	if(*h != NULL)
		freeBST(*h);

	// Binary-Search-Tree의 헤드노드 생성
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL; // root 노드를 포인팅할 부분
	(*h)->right = *h;
	(*h)->key = -9999;

	return 1;
}



void inorderTraversal(Node* ptr) // 이진탐색트리를 inorder식으로 Traversal하는 함수
{
	if(ptr != NULL) // 노드가 존재한다면
	{
		// 해당 노드의 왼쪽 자식 노드를 inorder식으로 Traversal  
		inorderTraversal(ptr->left);
		// 왼쪽 자식 노드 Traversal이 끝나면, 해당 노드(자기 자신)가 가진 값을 출력
		printf("[%d]", ptr->key);
		// 해당 노드의 오른쪽 자식 노드를 inorder식으로 Traversal
		inorderTraversal(ptr->right);
	}	
}

void preorderTraversal(Node* ptr) // 이진탐색트리를 preorder식으로 Traversal하는 함수
{
	if(ptr != NULL) // 노드가 존재한다면
	{
		// 해당 노드(자기 자신)가 가진 값을 먼저 출력한 후, 해당 노드의 자식 노드들을 Traversal
		printf("[%d]", ptr->key);
		// 해당 노드의 왼쪽 자식 노드를 Traversal
		preorderTraversal(ptr->left);
		// 해당 노드의 오른쪽 자식 노드를 Traversal
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr) // 이진탐색트리를 postorder식으로 Traversal하는 함수
{
	if(ptr != NULL) // 노드가 존재한다면
	{
		// 해당 노드의 왼쪽 자식 노드를 Traversal
		postorderTraversal(ptr->left);
		// 해당 노드의 오른쪽 자식 노드를 Traversal
		postorderTraversal(ptr->right);
		// 해당 노드의 자식 노드들을 Traversal한 후, 해당 노드(자기 자신)가 가진 값을 출력
		printf("[%d]", ptr->key);
	}
}


int insert(Node* head, int key)
{
	
}

int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{

}

Node* searchIterative(Node* head, int key)
{

}


int freeBST(Node* head)
{
	

	while()
	{

	}
}





