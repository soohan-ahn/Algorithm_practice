#include<stdio.h>
#include<stdlib.h>
int n,m,sum;

struct DOT{
	int x,y;
}typedef;
struct RECT{
	int x1,x2,y1,y2;
}typedef;

RECT set[10001];
DOT set2[10001];

void input()
{
	int i;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&m);
	for(i = 1; i <= m; i++)
	{	
		fscanf(in,"%d %d %d %d",&set[i].x1,&set[i].y1,&set[i].x2,&set[i].y2);
		set2[++n].x = set[i].x1;
		set2[n].y = set[i].y1;
		set2[++n].x = set[i].x2;
		set2[n].y = set[i].y2;
	}
	fclose(in);
}

void qsortx(int left, int right)
{
	int temp;
	if(left < right){
		int i = left - 1, j = right + 1, mid = set2[(left + right) >> 1].x;
		while(1){
			while(set2[++i].x < mid);
			while(set2[--j].x > mid);
			if(i >= j) break;

			temp = set2[i].x; set2[i].x = set2[j].x; set2[j].x = temp;
		}
		qsortx(left, i - 1);
		qsortx(j + 1, right);
	}
}

void qsorty(int left, int right)
{
	int temp;
	if(left < right){
		int i = left - 1, j = right + 1, mid = set2[(left + right) >> 1].y;
		while(1){
			while(set2[++i].y < mid);
			while(set2[--j].y > mid);
			if(i >= j) break;

			temp = set2[i].y; set2[i].y = set2[j].y; set2[j].y = temp;
		}
		qsorty(left, i - 1);
		qsorty(j + 1, right);
	}
}

int hit(int x1, int y1, int x2, int y2, RECT c)
{
	if(c.x1 <= x1 && x1 <= c.x2 && 
		c.y1 <= y1 && y1 <= c.y2 && 
		c.x1 <= x2 && x2 <= c.x2 && 
		c.y1 <= y2 && y2 <= c.y2) return 1;
	return 0;
}

void process()
{
	int i,j,k,flag;
	qsortx(1,n);
	qsorty(1,n);

	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			flag = 0;

			for(k = 1; k <= m; k++)
				if(hit(set2[i].x, set2[j].y, set2[i + 1].x, set2[j + 1].y, set[k]) == 1) flag = 1;

			if(flag == 1) sum += (set2[i + 1].x - set2[i].x) * (set2[j + 1].y - set2[j].y);
		}
	}
	printf("%d\n",sum);
}

int main(void)
{
	input();
	process();
	return 0;
}