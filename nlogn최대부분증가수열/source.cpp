#include<stdio.h>
#include<math.h>
int n,m = 0;
int set[1001];
int dy[1001];

void input()
{
	int i;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&n);
	for(i = 1; i <= n; i++)
		fscanf(in,"%d",&set[i]);
	fclose(in);
}

int bin(int left, int right, int key)
{
	int mid = (left + right) >> 1;
	if(left >= right) return right;
	else{
		if(dy[mid] > key) bin(left, mid - 1, key);
		else if(dy[mid] < key) bin(mid + 1, right, key);
		else if(dy[mid] == key) return mid;
	}
}

void process()
{
	int i,j,mid;
	for(i = 1; i <= n; i++)
	{
		mid = bin(1,m,set[i]);
		if(mid == m && dy[mid] < set[i]) dy[++m] = set[i];
		else dy[mid] = set[i];
	}
	for(i = 1; i <= m; i++)
		printf("%d ",dy[i]);
	printf("\n");
	printf("%d\n",m);
}

int main(void)
{
	input();
	process();
	return 0;
}