#include<stdio.h>
int n,m;
int set[100][100];
int dy[100][100];
int track[100][100];

void input()
{
	int i,j;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d %d",&n,&m);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			fscanf(in,"%d",&set[i][j]);
	fclose(in);
}

void process()
{
	int i,j,k;
	for(i = 1; i <= n; i++)
		dy[1][i] = set[i][1];
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{
			for(k = 0; k <= j; k++)
				if(dy[i][j] < dy[i - 1][j - k] + set[k][i]){
					dy[i][j] = dy[i - 1][j - k] + set[k][i];
					track[i][j] = k;
				}
		}
	}

	j = n;
	printf("%d\n",j);
	for(i = m; i >= 1; i--)
		printf("%d ",track[i][j]);

	printf("\n%d\n",dy[m][n]);
}

int main(void)
{
	input();
	process();
	return 0;
}