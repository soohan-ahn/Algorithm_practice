#include<stdio.h>
#include<math.h>
int n,minp = 1;
int head;

struct DATA{
	int x,y;
	double tan;
}typedef;

DATA set[101];
DATA stack[101];

void input()
{
	int i;
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%d",&n);
	for(i = 1; i <= n; i++)
		fscanf(in,"%d %d",&set[i].x,&set[i].y);
	fclose(in);
}

void qsorty(int left, int right)
{
	DATA temp;
	if(left < right){
		int i = left - 1, j = right + 1, mid = set[(left + right) >> 1].y;
		while(1){
			while(set[++i].y < mid);
			while(set[--j].y > mid);
			if(i >= j) break;

			temp = set[i]; set[i] = set[j]; set[j] = temp;
		}
		qsorty(left, i - 1);
		qsorty(j + 1, right);
	}
}

void qsortan(int left, int right)
{
	DATA temp;
	if(left < right){
		int i = left - 1, j = right + 1;
		double mid = set[(left + right) >> 1].tan;
		while(1){
			while(set[++i].tan < mid);
			while(set[--j].tan > mid);
			if(i >= j) break;

			temp = set[i]; set[i] = set[j]; set[j] = temp;
		}
		qsortan(left, i - 1);
		qsortan(j + 1, right);
	}
}

int ccw(DATA a, DATA b, DATA c)
{
	double temp = (a.x * b.y) + (b.x * c.y) + (c.x * a.y) - ((a.y * b.x) + (b.y * c.x) + (c.y * a.x));
	if(temp < 0) return -1;
	if(temp == 0) return 0;
	if(temp > 0) return 1;
}

void process()
{
	int i;
	qsorty(1,n);
	for(i = 1; i <= n; i++)
		set[i].tan = atan2(set[i].x - set[1].x, set[i].y - set[1].y);
	qsortan(2,n);

	stack[++head] = set[1];
	stack[++head] = set[2];
	for(i = 3; i <= n; i++)
	{
		while(ccw(stack[head - 1], stack[head], set[i]) != -1) head--;
		stack[++head] = set[i];
	}
	for(i = 1; i <= head; i++)
		printf("%d %d\n",stack[i].x,stack[i].y);
}

int main(void)
{
	input();
	process();
	return 0;
}