#include<stdio.h>
#include<stdlib.h>
int n,m;
int gp[100][100];
int x[100];
int y[100];
int w[100];
int d[100];
int height[100];

void input()
{
	int i;
	FILE *in = fopen("kruskal.in","r");
	fscanf(in,"%d %d",&n,&m);
	for(i = 1; i <= m; i++)
	{
		fscanf(in,"%d %d %d",&x[i],&y[i],&w[i]);
		gp[x[i]][y[i]] = w[i];
		gp[y[i]][x[i]] = w[i];
	}
	fclose(in);
}

void qsort(int left, int right)
{
	int temp;
	if(left < right){
		int i = left - 1, j = right + 1, mid = w[(right + left) >> 1];
		while(1){
			while(w[++i] < mid);
			while(w[--j] > mid);
			if(i >= j) break;

			temp = w[i]; w[i] = w[j]; w[j] = temp;
			temp = x[i]; x[i] = x[j]; x[j] = temp;
			temp = y[i]; y[i] = y[j]; y[j] = temp;
		}
		qsort(left, i - 1);
		qsort(j + 1, right);
	}
}

void process()
{
	int i,j,sum = 0;
	qsort(1,m);

	for(i = 1; i <= m; i++)
	{
		if(d[x[i]] != 0 && d[y[i]] != 0){
			if(d[x[i]] != d[y[i]]){
				if(height[x[i]] > height[y[i]]){
					printf("%d %d %d\n",x[i],y[i],w[i]);
					for(j = 1; j <= n; j++)
						if(d[j] == y[i]){
							d[j] = d[x[i]];
							height[j] = height[x[i]];
						}
					sum += w[i];
				}
				else{
					printf("%d %d %d\n",x[i],y[i],w[i]);
					for(j = 1; j <= n; j++)
					{
						if(d[j] == x[i]){
							d[j] = d[y[i]];
							height[j] = height[y[i]];
						}
					}
					sum += w[i];
				}
			}
		}
		else{
			printf("%d %d %d\n",x[i],y[i],w[i]);
			d[y[i]] = x[i];
			d[x[i]] = x[i];
			sum += w[i];
			height[y[i]]++;
			height[x[i]]++;
		}
	}

	printf("%d\n",sum);
}

void main()
{
	input();
	process();
	exit(0);
}