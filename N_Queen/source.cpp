#include<stdio.h>
int n;
int set[1001];
int flag[1001];
int map[1001][1001];

void output()
{
	int i,j;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			map[i][j] = 0;

	for(i = 1; i <= n; i++)
		map[i][set[i]] = 1;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
			printf("%d ",map[i][j]);
		printf("\n");
	}
	printf("\n");
}

void recur(int x)
{
	int i;
	int tempx1,tempx2,tempy1,tempy2;
	if(x == n + 1){

//		output();

		for(i = 1; i < n; i++)
		{
		//	compare(i,set[i] & x - 1,set[x] and if it is impossible return;
			tempx1 = i; tempy1 = set[i]; tempx2 = n; tempy2 = set[n];
		//	if(tempx2 == tempx1) return;
			if(((double)(tempy1 - tempy2) / (double)(tempx1 - tempx2)) == -1 || ((double)(tempy1 - tempy2) / (double)(tempx1 - tempx2)) == 1) return;
		}

		output();
		return;
	}
	else{
		for(i = 1; i < x - 1; i++)
		{
		//	compare(i,set[i] & x - 1,set[x] and if it is impossible return;
			tempx1 = i; tempy1 = set[i]; tempx2 = x - 1; tempy2 = set[x - 1];
		//	if(tempx2 == tempx1) return;
			if(((double)(tempy1 - tempy2) / (double)(tempx1 - tempx2)) == -1 || ((double)(tempy1 - tempy2) / (double)(tempx1 - tempx2)) == 1) return;
		}

		for(i = 1; i <= n; i++)
		{
			if(flag[i] == 0){
				flag[i] = 1;
				set[x] = i;
				recur(x + 1);
				set[x] = 0;
				flag[i] = 0;
			}
		}
	}
}

int main(void)
{
	scanf("%d",&n);
	recur(1);
	return 0;
}