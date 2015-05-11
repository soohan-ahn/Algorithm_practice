#include<stdio.h>
#define INF 1000L
int n;
int set[101][101];
int dist[101];
int flag[101];
int result;

void input()
{
	FILE *in = fopen("input.txt","r");
	int i,j;
	fscanf(in,"%d",&n);
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			fscanf(in,"%d",&set[i][j]);
			if(set[i][j] == 0 && i != j) set[i][j] = INF;
		}
	}
	fclose(in);
}

int getmin()
{
	int i,j;
	for(i = 1; i <= n; i++)
		if(flag[i] == 0) break;
	for(j = 1; j <= n; j++)
		if(!flag[j] && dist[i] > dist[j]) i = j;
	return i;
}

void process()
{
	int i,j,temp;
	for(i = 1; i <= n; i++)
		dist[i] = INF;
	dist[1] = 0;

	for(i = 1; i <= n; i++)
	{
		temp = getmin();
		flag[temp] = 1;
		printf("%d ",temp);
		for(j = 1; j <= n; j++)
		{
			if(dist[j] > set[temp][j]) dist[j] = set[temp][j];
		}
	}
	printf("\n");
}

int main(void)
{
	input();
	process();
	return 0;
}