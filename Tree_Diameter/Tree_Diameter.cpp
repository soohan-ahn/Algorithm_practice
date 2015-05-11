#include<stdio.h>
int n,max = -9999;

struct DATA{
	int root,baby,dis;
}typedef;

struct DYNAMIC{
	int max1,max2,dis;
}typedef;

DATA set[10001];
DYNAMIC dy[10001];

void input()
{
	int i;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&n);
	for(i = 1; i <= n; i++)
		fscanf(in,"%d %d %d",&set[i].root,&set[i].baby,&set[i].dis);
	fclose(in);
}

void process()
{
	int i;
	for(i = n; i >= 1; i--)
	{
		dy[set[i].root].max1 += (dy[set[i].baby].max2 + set[i].dis);
		if(dy[set[i].root].dis < set[i].dis){
			dy[set[i].root].dis = set[i].dis;
			dy[set[i].root].max2 = dy[set[i].baby].max2 + set[i].dis;
		}
		if(max < dy[set[i].root].max1) max = dy[set[i].root].max1;
	}
	printf("%d\n",max);
}

int main(void)
{
	input();
	process();
	return 0;
}