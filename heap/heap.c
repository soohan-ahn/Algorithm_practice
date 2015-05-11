#include <stdio.h>

#define MAX_ELEMENT 200
typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;	// heap �ȿ� ����� key�� ��
} HeapType;

// �ʱ�ȭ �Լ�
init(HeapType *h)
{
	h->heap_size =0;
}
// ���� ���� ��� �Լ�
print_heap(HeapType *h)
{
	int i;
	int level=1;
	printf("\n===================");
	for(i=1;i<=h->heap_size;i++){
		if( i == level ) {
			printf("\n");
			level *= 2;
		}
		printf("\t%d", h->heap[i].key);
	}
	printf("\n===================\n");
}

// ���� �Լ�
void insert_max_heap(HeapType *h, element item) 
{ 
    int i; 
    i = ++(h->heap_size); 

    //  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
    while((i != 1) && (item.key > h->heap[i/2].key)){ 
	   h->heap[i] = h->heap[i/2]; 
       i /= 2; 
    } 
    h->heap[i] = item;     // ���ο� ��带 ����
}
 
// ���� �Լ�
element delete_max_heap(HeapType *h) 
{ 
	int st = 1;
	int temp;
	element result;
	result = h->heap[1];
	h->heap[1] = h->heap[h->heap_size];
	h->heap[h->heap_size--].key = -1;
	while((h->heap[st].key < h->heap[st * 2].key || h->heap[st].key < h->heap[st * 2 + 1].key)){
		if(h->heap[st * 2].key > h->heap[st * 2 + 1].key){
			temp = h->heap[st].key;
			h->heap[st].key = h->heap[st * 2].key;
			h->heap[st * 2].key = temp;
			st = st * 2;
		}
		else if(h->heap[st].key < h->heap[st * 2 + 1].key){
			temp = h->heap[st].key;
			h->heap[st].key = h->heap[st * 2 + 1].key;
			h->heap[st * 2 + 1].key = temp;
			st = st * 2 + 1;
		}
	}

	return result;
} 


void main()
{
	element e1, e2, e3;
	element e4, e5, e6;

	HeapType heap;	// ���� ����
	init(&heap);		// �ʱ�ȭ

	e1.key = 10, e2.key = 5, e3.key = 30;
	
	// ����
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	print_heap(&heap);
	
	// ����
	e4 = delete_max_heap(&heap);
	printf("< %d > ", e4.key);
	e5 = delete_max_heap(&heap);
	printf("< %d > ", e5.key);
	e6 = delete_max_heap(&heap);
	printf("< %d > \n", e6.key);
}
