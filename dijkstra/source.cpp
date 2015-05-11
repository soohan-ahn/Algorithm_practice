/*
#include<stdio.h>
#define MAX 999999
int n,dy[1001],flag[1001],chk[1001];
int set[1001][1001];
int st,en;

void input()
{
	int i,j;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&n);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			fscanf(in,"%d ",&set[i][j]);
	fscanf(in,"%d %d",&st,&en);
	fclose(in);
}

void process()
{
	int i,j,now;
	for(i = 0; i <= n; i++)
	{
		dy[i] = MAX;
		flag[i] = -1;
	}

	now = st;
	dy[now] = 0;
	chk[now] = 1;
	for(i = 1; i <= n; i++)
	{
		if(dy[i] > dy[now] + set[now][i]){
			dy[i] = dy[now] + set[now][i];
			flag[i] = now;
		}
	}

	for(i = 1; i < n; i++)
	{
		now = 0;
		for(j = 1; j <= n; j++)
			if(chk[j] == 0 && dy[now] > dy[j]) now = j;
		chk[now] = 1;

		for(j = 1; j <= n; j++)
		{
			if(dy[j] > dy[now] + set[now][j]){
				dy[j] = dy[now] + set[now][j];
				flag[j] = now;
			}
		}		
	}

	printf("%d\n",dy[en]);
}

int main(void)
{
	input();
	process();
	return 0;
}
*/

































#include<stdio.h>
int n,cnt;
int set[101][101];
int dy[101];
int flag[101];
int track[101];
int rtrack[101];
int st,en;

void input()
{
	int i,j;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&n);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			fscanf(in,"%d",&set[i][j]);
	fscanf(in,"%d %d",&st,&en);
	fclose(in);
}

void process()
{
	int i,j,now;
	int min,minp;
	
	for(i = 1; i <= n; i++)
	{
		dy[i] = 999999;
		track[i] = -1;
	}

	flag[st] = 1;
	dy[st] = 0;
	track[st] = -1;
	now = st;

	for(i = 1; i < n; i++)
	{
		min = 999999;
		for(j = 1; j <= n; j++)
		{
			if(dy[j] > dy[now] + set[now][j] && set[now][j] != 0){
				dy[j] = dy[now] + set[now][j];
				track[j] = now;
			}
		}
		for(j = 1; j <= n; j++)
		{
			if(flag[j] == 0 && dy[j] < min){
				min = dy[j];
				minp = j;
			}
		}
		flag[minp] = 1;
		now = minp;
	}

	now = en;
	while(1){
		if(track[now] == -1){
			rtrack[++cnt] = now;
			break;
		}
		else{
			rtrack[++cnt] = now;
			now = track[now];
		}
	}
	for(i = cnt; i >= 1; i--)
		printf("%d ",rtrack[i]);
	printf("\n");
	printf("%d\n",dy[en]);
}

int main(void)
{
	input();
	process();
	return 0;
}
