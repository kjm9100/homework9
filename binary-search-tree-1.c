#include <stdio.h>
#include <stdlib.h>

typedef struct node { // 노드를 위한 구조체
	int key;
	struct node *left; // 왼쪽 자식 노드(헤드 노드의 경우, root노드 포인팅)
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

// 추가적으로 구현한 함수
Node* searchIterative_B(Node* head, int key); // Iterative식으로 입력값을 가진 노드의 상위 노드를 탐색하는 함수 선언 
void deleteLeafNode_u(Node* head); // Leaf노드를 삭제하는 함수 선언


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


int insert(Node* head, int key) // 노드를 삽입하는 함수
{	
	// 삽입할 노드 생성
	Node* NodetoInsert = (Node*)malloc(sizeof(Node));
	NodetoInsert->key = key;
	NodetoInsert->left = NULL;
	NodetoInsert->right = NULL;
	
	if(head->left==NULL) // root 노드가 없을 경우
	{	// root노드 삽입
		head->left = NodetoInsert;	
		return 0;
	}

	Node* SearchNode = head->left;

	while(1)
	{
		if(SearchNode->key > key) //  입력값이 탐색노드의 값보다 작을 경우
		{
			if(SearchNode->left == NULL) // 탐색노드의 왼쪽 자식 노드가 없다면
			{	
				// 왼쪽 자식 노드로 입력값을 가진 노드 삽입
				SearchNode->left = NodetoInsert; 
				return 0;
			}
			else // 탐색노드의 왼쪽 자식 노드가 있다면
			{ 
				// 탐색할 노드를 왼쪽 자식 노드로 변경
				SearchNode = SearchNode->left;
			}
		}
		else if(SearchNode->key < key) // 입력값이 탐색노드의 값보다 클 경우
		{
			if(SearchNode->right == NULL) // 탐색노드의 오른쪽 자식 노드가 없다면
			{	
				// 오른쪽 자식 노드로 입력값을 가진 노드 삽입
				SearchNode->right = NodetoInsert;
				return 0;
			}
			else // 탐색노드의 오른쪽 자식 노드가 있다면
			{ 
				// 탐색할 노드를 오른쪽 자식 노드로 변경
				SearchNode = SearchNode->right;
			}
		}
		else // 탐색노드의 값과 입력값이 동일할 경우
		{
			// 삽입하려고 했던 노드에 할당된 메모리 해제 후 오류 메시지 출력
			free(NodetoInsert);
			printf("The key to insert already exists.\n\n");
			return 0;
		}
	}

	return 0;
}

int deleteLeafNode(Node* head, int key) // 입력값을 가진 Leaf노드를 삭제하는 함수
{
	// 삭제하려는 입력값을 가진 노드와 그 부모 노드를 검색
	Node* NodetoDelete = searchIterative(head, key);
	Node* NodetoDelete_B = searchIterative_B(head, key);

	if(NodetoDelete == NULL) // 이진탐색트리가 존재하지 않을 경우, 오류 메시지 출력
	{
		printf("There's no node for the key.\n");
		return 0;
	}
	else // 이진탐색트리가 존재할 경우
	{	// 삭제할 노드가 Leaf노드일 경우
		if(NodetoDelete->left == NULL && NodetoDelete->right == NULL)
		{	// 삭제할 노드를 포인팅하는 부모 노드의 부분을 NULL로 변경
			if(NodetoDelete_B->key > key)
			{ NodetoDelete_B->left = NULL; }
			else{ NodetoDelete_B->right = NULL; }
			// 삭제할 노드에 할당된 메모리를 해제
			free(NodetoDelete);
			return 0;
		}
		else // 삭제할 노드가 Leaf노드가 아닐 경우, 오류 메시지 출력
		{
			printf("The node for the key isn't a leaf Node.\n");
			return 0;
		}
	}
}

Node* searchRecursive(Node* ptr, int key) // Recursive식으로 입력값을 가진 노드 탐색하는 함수
{
	if(ptr != NULL) // 검색할 노드가 있을 경우
	{
		if(ptr->key==key) // 검색하는 노드의 값이 입력값과 같을 경우
		{
			return ptr; // 해당 노드의 주소값을 반환
		}
		else if(ptr->key > key) // 검색하는 노드의 값이 입력값보다 클 경우
		{	// 왼쪽 자식 노드에 대해 검색
			return searchRecursive(ptr->left, key); 
		}
		else // 검색하는 노드의 값이 입력값보다 작을 경우
		{	// 오른쪽 자식 노드에 대해 검색
			return searchRecursive(ptr->right, key);
		}	
	}

	return NULL; // 검색할 노드가 없을 경우, NULL 반환
}

Node* searchIterative(Node* head, int key) // Iterative식으로 입력값을 가진 노드를 탐색하는 함수
{
	Node* SearchNode = head->left;

	// 이진탐색트리에 검색할 노드가 존재하는 경우
	while(SearchNode != NULL)
	{	// 검색하는 노드의 값과 입력값이 동일한 값을 갖는 경우
		if(SearchNode->key == key)
		{
			return SearchNode; // 검색하는 노드의 주소값을 반환
		}
		
		if(SearchNode->key > key) // 검색하는 노드의 값이 입력값보다 클 경우
		{	// 검색하는 노드를 그 노드의 왼쪽 자식 노드로 변경
			SearchNode = SearchNode->left; 
		}
		else // 검색하는 노드의 값이 입력값보다 작을 경우
		{	// 검색하는 노드를 그 노드의 오른쪽 자식 노드로 변경
			SearchNode = SearchNode->right;
		}
	}

	return NULL; // 입력값을 가진 노드가 존재하지 않을 경우, NULL 반환
}


int freeBST(Node* head) // 이진탐색트리의 노드에 할당된 메모리를 모두 해제하는 함수
{
	while(head->left != NULL) // root노드까지 노드 삭제 및 메모리 할당 해제
	{
		deleteLeafNode_u(head);
	}
	free(head); // head 노드에 할당된 메모리 해제
}


Node* searchIterative_B(Node* head, int key) // 입력값과 동일한 값을 가진 노드의 이전 노드를 탐색하는 함수
{
	Node* SearchNode = head->left;
	Node* SearchNode_B = head;

	// 검색할 노드가 존재할 경우
	while(SearchNode != NULL)
	{	// 검색하는 노드의 값이 입력값과 동일할 경우
		if(SearchNode->key == key)
		{
			return SearchNode_B; // 해당 노드를 가리키는 노드, 즉, 그 노드의 상위 노드의 주소값을 반환
		}
		
		SearchNode_B = SearchNode;

		// 검색하는 노드의 값이 입력값보다 클 경우
		if(SearchNode->key > key)
		{
			SearchNode = SearchNode->left; // 검색하는 노드를 검색노드의 왼쪽 자식 노드로 변경 
		}
		else // 검색하는 노드의 값이 입력값보다 작을 경우
		{	
			SearchNode = SearchNode->right; // 검색하는 노드를 검색노드의 오른쪽 자식 노드로 변경
		}
	}

	return NULL; // 입력값을 가진 노드가 없을 경우, NULL 반환
}

void deleteLeafNode_u(Node* head) // Leaf노드를 삭제하는 함수
{
	Node* p = head;
	Node* p_B = p;

	// Leaf노드를 탐색
	while(p->left != NULL || p->right != NULL )
	{	// 부모노드의 왼쪽 sub트리부터 탐색
		if(p->left != NULL) 
		{
			p_B = p;
			p = p->left;
		}
		else if(p->right != NULL) // 왼쪽 sub트리가 모두 삭제한 후, 오른쪽 sub트리 탐색  
		{
			p_B = p;
			p = p->right;
		}
	}

	// Leaf노드의 부모노드의 왼쪽 자식 노드가 존재할 경우
	if(p_B->left != NULL)
	{	// 왼쪽 자식 노드를 포인팅하는 부분을 NULL로 변경
		p_B->left = NULL;
	}else if(p_B->right != NULL) // Leaf노드의 부모노드의 왼쪽 자식 노드가 존재하지 않고, 오른쪽 자식 노드가 존재할 경우
	{	// 오른쪽 자식 노드를 포인팅하는 부분을 NULL로 변경
		p_B->right = NULL;
	}
	
	free(p); // 자식 노드이자 Leaf노드인 노드에 할당된 메모리를 해제
}


