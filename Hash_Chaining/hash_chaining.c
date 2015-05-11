#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE	10	// 해싱 테이블의 크기

typedef int element;

struct list
{   
	element key;
    struct list *link;
};
struct list *hash_table[TABLE_SIZE];


// 제산 함수를 이용한 Hash Function
// TABLE_SIZE로 나누어 나머지를 Return하여 준다.
int hash_function(element item)
{
	return item % 10;
	// coding..
} 


// 체이닝을 이용하여 테이블에 키를 삽입
void hash_chain_add(element item, struct list *ht[])
{
	int mod = hash_function(item);
	struct list *add = (struct list*)malloc(sizeof(struct list));
	struct list *temp = ht[mod];
	add->key = item;
	add->link = NULL;
	if(temp == NULL){
		ht[mod] = (struct list*)malloc(sizeof(struct list));
		ht[mod]->link = add;
	}
	else{
		while(1){
			if(temp->link == NULL){
				temp->link = add;
				break;
			}
			temp = temp->link;
		}
	}
}

// 체이닝을 이용하여 테이블에 저장된 키를 탐색
void hash_chain_find(element item, struct list *ht[])
{
	int mod = hash_function(item);
	struct list *temp = ht[mod];
	if(temp != NULL){
		while(1){
			if(temp->key == item){
				printf("%d hash table\n",mod);
				return;
			}
			if(temp->link == NULL) break;
			temp = temp->link;
		}
	}
	printf("Not found\n");
}

// 해싱 테이블의 내용을 출력
void hash_chain_print(struct list *ht[])
{
	int i;
	struct list *temp;
	for(i = 0; i < TABLE_SIZE; i++)
	{
		temp = ht[i];
		printf("[%d] ",i);
		if(temp != NULL){
			temp = temp->link;
			while(1){
				printf("-> %d ",temp->key);
				if(temp->link == NULL) break;
				temp = temp->link;
			}
		}
		printf("\n");
	}

	// coding..
}


void main()
{
	element tmp;
	int op;
	while(1){
		printf("원하는 연산을 입력하시오(0=입력, 1=탐색, 2=출력, 3=종료)=");
		scanf("%d",&op);

		if( op == 0 ){	      // 입력
			printf("키를 입력하시오=");
			scanf("%d",&tmp);

			hash_chain_add(tmp, hash_table);
			hash_chain_print(hash_table);
		}

		else if( op == 1 ){   // 탐색
			printf("키를 입력하시오=");
			scanf("%d",&tmp);

			hash_chain_find(tmp, hash_table);
		}

		else if( op == 2 ){   // 출력
			hash_chain_print(hash_table);
		}
		else if( op == 3 ){   // 종료
			break;
		}
	}
	printf("%d %d\n",11/10, 16/10);
}
