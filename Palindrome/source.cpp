#include<stdio.h>
#include<string.h>
int n;
char a[5001],b[5001];
int dy[5001][5001];

void input()
{
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d\n",&n);
	fscanf(in,"%s\n",&a);
	fclose(in);
}

void process()
{
	int i,j,k;
	strcpy(b,a);
	strrev(b);
	for(i = 1; i <= (int)strlen(a); i++)
	{
		for(j = 1; j <= (int)strlen(b); j++)
		{
			if(a[i - 1] == b[j - 1]) k = 1; else k = 0;
			if(dy[i][j] < dy[i][j - 1]) dy[i][j] = dy[i][j - 1];
			if(dy[i][j] < dy[i - 1][j]) dy[i][j] = dy[i - 1][j];
			if(k == 1 && dy[i][j] < dy[i - 1][j - 1] + k) dy[i][j] = dy[i - 1][j - 1] + k;
		}
	}


	FILE *out = fopen("output.txt","w");
	fprintf(out,"%d\n",n - dy[(int)strlen(a)][(int)strlen(b)]);
	fclose(out);
}

int main(void)
{
	input();
	process();
	return 0;
}