#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE	10	// �ؽ� ���̺��� ũ��

typedef int element;

struct list
{   
	element key;
    struct list *link;
};
struct list *hash_table[TABLE_SIZE];


// ���� �Լ��� �̿��� Hash Function
// TABLE_SIZE�� ������ �������� Return�Ͽ� �ش�.
int hash_function(element item)
{
	return item % 10;
	// coding..
} 


// ü�̴��� �̿��Ͽ� ���̺� Ű�� ����
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

// ü�̴��� �̿��Ͽ� ���̺� ����� Ű�� Ž��
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

// �ؽ� ���̺��� ������ ���
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
		printf("���ϴ� ������ �Է��Ͻÿ�(0=�Է�, 1=Ž��, 2=���, 3=����)=");
		scanf("%d",&op);

		if( op == 0 ){	      // �Է�
			printf("Ű�� �Է��Ͻÿ�=");
			scanf("%d",&tmp);

			hash_chain_add(tmp, hash_table);
			hash_chain_print(hash_table);
		}

		else if( op == 1 ){   // Ž��
			printf("Ű�� �Է��Ͻÿ�=");
			scanf("%d",&tmp);

			hash_chain_find(tmp, hash_table);
		}

		else if( op == 2 ){   // ���
			hash_chain_print(hash_table);
		}
		else if( op == 3 ){   // ����
			break;
		}
	}
	printf("%d %d\n",11/10, 16/10);
}
