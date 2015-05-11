#include<stdio.h>
int n;
int dy[1001];

void input()
{
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&n);
	fclose(in);
}

void process()
{
	int i,j;
	dy[0] = 1;
	for(i = 1; i <= n; i++)
		for(j = 0; j < i; j++)
			dy[i] += (dy[j] * dy[i - j - 1]);
	printf("%d\n",dy[n]);
}

int main(void)
{
	input();
	process();
	return 0;
}