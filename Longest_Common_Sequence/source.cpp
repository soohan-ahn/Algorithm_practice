#include<stdio.h>
int n,m;
int set[30001];
int result[30001];

void input()
{
	int i;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&n);
	for(i = 1; i <= n; i++)
		fscanf(in,"%d",&set[i]);
	fclose(in);
}

void process()
{
	int i,left,right,mid,chk;

	result[++m] = set[1];
	for(i = 2; i <= n; i++)
	{
		left = 1; right = m;
		chk = 0;
		while(1){
			mid = (left + right) / 2;
			if(left + 1 >= right || mid == 0) break;
			
			if(set[i] > result[mid]){
				left = mid + 1;
				chk = mid;
			}
			else if(set[i] < result[mid]){
				right = mid - 1;
				chk = mid;
			}
			else if(set[i] == result[mid]) break;
		}

		printf("mid = %d   i = %d \n",result[chk],set[i]);
		for(int j = 1; j <= m; j++)
			printf("%d ",result[j]);
		printf("\n\n");

		if(result[chk] > set[i]) result[chk] = set[i];
		else if(result[chk] < set[i]) result[++m] = set[i];
	/*	if(mid == 0) result[1] = set[i];
		else if(mid != m) result[mid] = set[i];
		else if(mid == m && result[mid] < set[i]) result[++m] = set[i];
		else if(mid == m && result[mid] > set[i]) result[mid] = set[i];*/
	}

	printf("%d\n",m);
}	

int main(void)
{
	input();
	process();
	return 0;
}