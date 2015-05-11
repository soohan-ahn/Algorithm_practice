#include<stdio.h>
int n,chk;
int set[101][101];
int track[101];

void input()
{
	int temp1,temp2,temp3;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&n);
	while(fscanf(in,"%d %d %d",&temp1,&temp2,&temp3) != EOF){
		set[temp1][temp2] = temp3;
		set[temp2][temp1] = temp3;
	}
	fclose(in);
}

int allchk()
{
	int i,j;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			if(set[i][j] > 0) return 1;
	return 0;
}

void DFS(int x, int cnt)
{
	int i;
	if(allchk() == 0){
		chk = 1;
		for(i = 1; i < cnt; i++)
			printf("%d ",track[i]);
		printf("\n");
		return;
	}
	else{
		for(i = 1; i <= n; i++)
		{
			if(set[x][i] > 0){
				set[x][i]--;
				set[i][x]--;
				track[cnt] = i;
				DFS(i, cnt + 1);
				set[x][i]++;
				set[i][x]++;
			}
		}
	}
}

void process()
{
	track[1] = 1;
	DFS(1,2);
	if(chk == 0) printf("-1\n");
}

int main(void)
{
	input();
	process();
	return 0;
}