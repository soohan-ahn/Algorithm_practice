/*
ID: soohanb002
PROB: pprime
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int st,en;
int set[1000000];
char a[1001],b[1001];
FILE *out = fopen("pprime.out","w");

void input()
{
	FILE *in = fopen("pprime.in","r");
	fscanf(in,"%d %d",&st,&en);
	fclose(in);
}

void makestr(int x)
{
	int i,temp = x;
	for(i = 0; i <= 1000; i++)
		a[i] = NULL;
	i = 0;
	while(1){
		a[i] = (temp % 10) + '0';
		temp /= 10;
		if(temp == 0) break;
		i++;
	}
}

void makeprime(int x, int y)
{
	int i,j,k,chk,p;
	for(i = x; i <= y; i++)
	{
		if(i % 2 == 0) continue;
		makestr(i);
		for(j = 0, k = strlen(a) - 1; j < (int)strlen(a); j++, k--)
			b[j] = a[k];
		chk = 1;
		
	/*	for(j = 0; j < (int)strlen(a); j++)
		{
			if(a[j] != b[j]){
				chk = 0;
				break;
			}
		}*/
		if(strcmp(a,b) == 0){
			if(i % 11 == 0 && i != 11) continue;
			p = sqrt(i);
			for(j = 2; j <= p; j++)
			{
				if(i % j == 0){
					chk = 0;
					break;
				}
			}
			if(chk == 1) fprintf(out,"%d\n",i);
		}
	}
}

void process()
{
	makeprime(st,en);
}

int main(void)
{
	input();
	process();
	fclose(out);
	return 0;
}
