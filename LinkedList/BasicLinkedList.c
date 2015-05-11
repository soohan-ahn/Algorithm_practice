#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>


typedef int element;

typedef struct ListNode { 
	element data;
	struct ListNode *link;   	
} ListNode; // ����� ����ü

typedef struct {
	ListNode *head;     // ��� ������
	int length;		// ����� ����
} ListType; // ���� ����Ʈ�� ����ü 


void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}


// ����Ʈ�� �ʱ�ȭ�Ѵ�.
void init(ListType *list)
{
	if( list == NULL ) return;
	list->length = 0;
	list->head = NULL;
}

// phead: ����Ʈ�� ��� �������� ������
// p : ���� ���
// new_node : ���Ե� ��� 
void insert_node(ListNode **phead, ListNode *p, 
					ListNode *new_node) 
{
	if( *phead == NULL ){	// ���鸮��Ʈ�� ���
		new_node->link = NULL; 
		*phead = new_node; 
	}
	else if( p == NULL ){ // p�� NULL�̸� ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else {			 // p ������ ����
		new_node->link = p->link; 
		p->link = new_node; 
	}
}


// ����Ʈ�ȿ��� pos ��ġ�� ��带 ��ȯ�Ѵ�.
ListNode *get_node_at(ListType *list, int pos)
{
	int i;
	ListNode *tmp_node = list->head;
	if( pos < 0 ) return NULL;
	for (i=0; i<pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
} 


// �־��� ��ġ�� �����͸� �����Ѵ�.
void add(ListType *list, int position, element data) 
{
	ListNode *p;
	if ((position >= 0) && (position <= list->length)){

		ListNode*node=	(ListNode *)malloc(sizeof(ListNode)); 

		if( node == NULL ) error("�޸� �Ҵ翡��");
   
		node->data = data;
		p = get_node_at(list, position-1);
		insert_node(&(list->head), p, node); 
		list->length++;
	}
}

// ����Ʈ�� ���� �����͸� �����Ѵ�.
// phead: ����Ʈ�� ��� �������� ������
// p : ���� ���
// new_node : ���Ե� ��� 
/*
void insert_node(ListNode **phead, ListNode *p, 
					ListNode *new_node) 
ListNode *get_node_at(ListType *list, int pos)
					*/
void add_last(ListType *list, element data)
{
	ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
	ListNode *temp_node = (ListNode*)malloc(sizeof(ListNode));
	int i;
	temp_node = temp_node = get_node_at(list, list->length - 1);
	
	new_node->data = data;

	insert_node(&(list->head), temp_node, new_node);
	(list->length)++;
} 

void add_first(ListType *list, element data)
{
	ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
	ListNode *temp_node = (ListNode*)malloc(sizeof(ListNode));
	temp_node = get_node_at(list, -1);
	
	new_node->data = data;

	insert_node(&(list->head), temp_node, new_node);
	(list->length)++;
}  


// ����Ʈ���� �ش� �����͸� ������ ����� ��ġ�� ��ȯ�Ѵ�.
int search(ListType *list, element data)
{
	ListType* temp_node = (ListType*)malloc(sizeof(ListType));
	ListNode* temp_node1 = (ListNode*)malloc(sizeof(ListNode));
	int i = 0;

	for(i = 0, temp_node1 = list->head; i < list->length; temp_node1 = temp_node1->link, i++)
	{
		if(temp_node1->data == data){
			printf("Search - %d : %d��° ���\n",temp_node1->data,i);
			return 1;
		}
	}
	return 0;
}


// ���� ����Ʈ�� ������ ����Ѵ�. 
void display(ListType *list)
{
	ListNode* temp_node1 = (ListNode*)malloc(sizeof(ListNode));
	int i = 0;

	for(i = 0, temp_node1 = list->head; i < (list->length) - 1; temp_node1 = temp_node1->link,i++)
	{
		printf("%d - ",temp_node1->data);
	}
	printf("%d\n",temp_node1->data);
}


void main()
{
	ListType list1;

	init(&list1);
	add(&list1, 0, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);

	display(&list1);

	search(&list1, 20);

}

