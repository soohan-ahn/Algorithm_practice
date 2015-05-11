#include<stdio.h>
int n,m,cnt;

struct DATA{
	int x1,y1,x2,y2;
}typedef;


int x[101],y[101];
DATA set[1001];
DATA result[1001];
int flag[1001];

void input()
{
	int tx1,tx2,ty1,ty2;
	FILE *in = fopen("input.txt","r");
	while(fscanf(in,"%d %d %d %d",&tx1,&ty1,&tx2,&ty2) != EOF){
		set[++n].x1 = tx1; set[n].y1 = ty2;
		set[n].x2 = tx2; set[n].y2 = ty1;
		if(flag[tx1] < ty1) flag[tx1] = ty1;
		if(flag[tx2] < ty1) flag[tx2] = ty1;
		x[++m] = tx1; y[m] = ty1;
		x[++m] = tx2; y[m] = ty2;
	}
	fclose(in);
}

void qsortx(int left, int right)
{
	int temp;
	if(left < right){
		int i = left - 1, j = right + 1, mid = x[(left + right) >> 1];
		while(1){
			while(x[++i] < mid);
			while(x[--j] > mid);
			if(i >= j) break;

			temp = x[i]; x[i] = x[j]; x[j] = temp;
		}
		qsortx(left, i - 1);
		qsortx(j + 1, right);
	}
}

void qsorty(int left, int right)
{
	int temp;
	if(left < right){
		int i = left - 1, j = right + 1, mid = y[(left + right) >> 1];
		while(1){
			while(y[++i] < mid);
			while(y[--j] > mid);
			if(i >= j) break;

			temp = y[i]; y[i] = y[j]; y[j] = temp;
		}
		qsorty(left, i - 1);
		qsorty(j + 1, right);
	}
}

int in(int a, int b, DATA c)
{
	if( (c.x1 == a && c.y1 == b) || (c.x2 == a && c.y1 == b) || (c.x1 == a && c.y2 == b) || (c.x2 == a && c.y2 == b)) return 1;
	if(b == 0 && c.x1 < a && a < c.x2) return 0;
	if(c.x1 < a && a < c.x2 
		&& c.y1 < b && b < c.y2) return 0;
	return 1;
}

void process()
{
	int i,j,k,temp;
	qsortx(1,m);
	qsorty(1,m);
	y[0] = -1;
	for(i = 1; i <= 13; i++)
		printf("%d ",flag[i]);
	printf("\n");
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= m; j++)
		{
			if(y[j] > flag[x[i]] || y[j] == y[j - 1]) continue;
			temp = 1;
		//	printf("%d %d\n",x[i],y[j]);
			for(k = 1; k <= n; k++)
			{
				if(y[j] == 0 
					&& ((set[k].x1 == x[i] && set[k].y1 == y[j])
						|| (set[k].x2 == x[i] && set[k].y1 == y[j]))) continue;

				temp = in(x[i],y[j], set[k]);

				if(temp == 0) break;
			}
			if(temp == 1){
				result[++cnt].x1 = x[i];
				result[cnt].y1 = y[j];
			}
		}
	}

	for(i = 1; i <= cnt; i++)
	{
		if((double)result[i].x2 == (((double)(result[i - 1].x1 + result[i + 1].x1)) / 2)) continue;
		if((double)result[i].y2 == (((double)(result[i - 1].y1 + result[i + 1].y1)) / 2)) continue;
		printf("%d %d\n",result[i].x1,result[i].y1);
	}
}

int main(void)
{
	input();
	process();
	return 0;
}