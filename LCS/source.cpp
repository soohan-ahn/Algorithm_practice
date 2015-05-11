#include<stdio.h>
#include<string.h>
int n,m,cnt;
char a[1001],b[1001];
int dy[1001][1001],track[1001][1001];
char result[1001];

void input()
{
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%s\n%s\n",a,b);
	n = strlen(a); m = strlen(b);
	fclose(in);
}

void process()
{
	int i,j,k;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= m; j++)
		{
			if(a[i - 1] == b[j - 1]) k = 1; else k = 0;

			if(dy[i][j] < dy[i][j - 1]){
				dy[i][j] = dy[i][j - 1];
				track[i][j] = 1;
			}
			if(dy[i][j] < dy[i - 1][j]){
				dy[i][j] = dy[i - 1][j];
				track[i][j] = 2;
			}
			if(dy[i][j] < dy[i - 1][j - 1] + k && k == 1){
				dy[i][j] = dy[i - 1][j - 1] + k;
				track[i][j] = 3;
			}
		}
	}
}

void output()
{
	int i,j;
	i = n; j = m;
	while(1){
		if(i <= 0 || j <= 0) break;
		else{
			if(track[i][j] == 1) j--;
			else if(track[i][j] == 2) i--;
			else{
				result[cnt] = a[i - 1];
				cnt++;
				i--; j--;
			}
		}
	}
	strrev(result);
	printf("%d\n%s\n",cnt,result);
}

int main(void)
{
	input();
	process();
	output();
	return 0;
}