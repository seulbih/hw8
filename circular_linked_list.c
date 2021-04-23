/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[-------[황슬비] [2018032027] ------");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	if(h->rlink==h){ //전처리검사
				insertFirst(h,key);
			}
			else{
				listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트노드 생성
				node->key=key;
				node->rlink=h; //node는 마지막 값이므로 rlink에 h을 넣어준다.
				node->llink=h->llink;//왼쪽 링크로 기존의 마지막 노드 가리키도록 함
				h->llink->rlink=node; //기존 마지막 노드의 오른쪽 링크가 node를 가리키도록 함
				node->rlink=h;
				h->llink=node;

			}
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if(h->rlink==h){ //전처리검사
						printf("Linked List is empty!!!!!");
						return 0;
					}


			listNode* temp = (listNode*)malloc(sizeof(listNode)); //삭제할 노드
			temp=h->llink;
			temp->llink->rlink=h;
			h->llink=temp->llink;
			free(temp);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //새로운 노드에 key값 넣어줌
	node->llink=h; //h와 node가 서로 가리키도록 함
	h->rlink=node;
	node->rlink=h;
	h->llink=node;

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if(h->rlink==h){ //전처리검사
				printf("Linked List is empty!!!!!");
				return 0;
			}
	listNode* temp = (listNode*)malloc(sizeof(listNode)); //임시노드 생성
			temp=h->rlink;
			h->rlink=temp->rlink;
			if(temp->rlink !=h){ //노드가 하나 이상인 경우
				temp->rlink->llink=h;
			}
			if(temp->rlink == h){
				deleteLast(h);
				return 0;
			}
			free(temp);

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) { ////////////////////다쉬!!!!!!!!!!!!11
	if(h->rlink==h){//전처리검사
			printf("Linked List is empty!!!!!");
			return 0;
		}

		listNode *temp, *p;
		temp=h;
		p=h->rlink;

		if(temp->rlink ==h){ //노드가 하나뿐일 때
			return h; //그대로 리턴
		}


		while(p != h){ //노드 두개 이상일 때
			temp=p->rlink;
			p->rlink=p->llink;
			p->llink=temp;
			p=p->rlink;
		}

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {
	if(h->rlink==h){ //전처리검사
					insertFirst(h,key);
					return 0;
				}
		listNode* node = (listNode*)malloc(sizeof(listNode));
		listNode* temp = (listNode*)malloc(sizeof(listNode)); //임시노드 생성
		node->key = key;
		temp=h->rlink;
		if(temp->key>=key){ //비교연산, 헤드와 첫번째 노드 사이에 넣음
				node->rlink=temp;
				node->llink=h;
				h->rlink=node;
				}
			else{
				while(1){
					if (temp->rlink == h){ //노드가 한개인 경우, temp=첫번째 노드
						temp->rlink=node;
						node->llink=temp;
						node->rlink=h;
						h->llink=node;
						break;
					}
					else if (temp->rlink->key>key){//temp->key <= key < temp->link->key
						node->llink=temp;
						node->rlink=temp->rlink;
						temp->rlink=node;
						break;
					}
					else //범위에 해당하지 않으면 temp 한칸 옮김
						temp=temp->rlink;
				}
			}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	if(h->rlink==h){
					printf("Linked List is empty!!!!!");
					return 0;
				}
			else{

			listNode* temp = (listNode*)malloc(sizeof(listNode)); //삭제할 노드
			temp=h->rlink;
			if(temp->key == key){ //첫번 째 노드가 key일 때
				deleteFirst(h);
			}
			temp=temp->rlink;
			while(temp !=h){ //노드검색
				if(temp->key == key){
					temp->llink->rlink=temp->rlink; //앞뒤 노드 서로 연결
					temp->rlink->llink=temp->llink;
					free(temp);
					return 0;
				}
			temp=temp->rlink; //한칸씩 옮김
			}

			if(temp==h){//key값이 노드에 없는 경우
			printf("Key is not founded in linked list\n");
				}
			}
	return 0;
}


