/*
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n;
int set[1000000];

int main(void)
{
	FILE *out = fopen("1.in","w");
	int i,j,k;
	int temp;
	int term;
	char filename[100];

	int m;
	for(i = 2; i <= 2; i++)
	{
		sprintf(filename,"%d.in",i);
		out = fopen(filename,"w");

//		srand(i);

		k = 200000;
				
		n = 0; m = 0;
		for(j = 0; j < 100000; j++)
		{
			term = 0;
			while(1){
				temp = rand() % 3 + 1;
				if(temp == 1){
					if(n < 100000){
						term = 1;
						temp = rand() % 1000000 + 1;
						fprintf(out,"1 %d\n",temp);
						n++;
					}
				}
				if(term) break;
			}
		}

		for(j = 0; j < 100000; j++)
		{
			term = 0;
			while(1){
				temp = rand() % 3 + 1;
				if(temp == 2){
					if(n > 2){
						term = 1;
						n--;
						fprintf(out,"2\n");
					}
				}
				else if(temp == 3){
					if(n > 1){
						term = 1;
						temp = rand() % n + 1;
						fprintf(out,"3 %d ",temp);
						temp = rand() % 1000000 + 1;
						fprintf(out,"%d\n",temp);
					}
				}

				if(term) break;
			}
		}
		fprintf(out,"0\n");
		fclose(out);
	}
	
	for(i = 3; i <= 10; i++)
	{
		sprintf(filename,"%d.in",i);
		out = fopen(filename,"w");

//		srand(i);

		k = rand() % 300000 + 1;
				
		n = 0; m = 0;
		for(j = 0; j < k; j++)
		{
			term = 0;
			while(1){
				temp = rand() % 3 + 1;
				if(temp == 1){
					if(n < 100000){
						term = 1;
						temp = rand() % 1000000 + 1;
						fprintf(out,"1 %d\n",temp);
						n++;
					}
				}
				else if(temp == 2){
					if(n > 2){
						term = 1;
						n--;
						fprintf(out,"2\n");
					}
				}
				else if(temp == 3){
					if(n > 1){
						term = 1;
						temp = rand() % n + 1;
						fprintf(out,"3 %d ",temp);
						temp = rand() % 1000000 + 1;
						fprintf(out,"%d\n",temp);
					}
				}

				if(term) break;
			}
		}
		fprintf(out,"0\n");
		fclose(out);
	}


	return 0;
}
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define IN stdin
#define OUT stdout
int n,m;
int set[300001];
int res[300001];

void extract()
{
	int i;
	int temp;
	int max;
	res[m++] = set[1];
	set[1] = set[n--];
	i = 1;
	while(1){
		if(set[i * 2] > set[i * 2 + 1]) max = i * 2;
		else max = i * 2 + 1;
		
		if(set[max] > set[i]){
			temp = set[max];
			set[max]=  set[i];
			set[i] = temp;

			i = max;
		}
		else break;
	}
}

void insert_num(int x)
{
	int i;
	int temp;	
	set[++n] = x;	
	i = n;
	while(1){
		if(i <= 1) break;
		
		if(set[i / 2] < set[i]){
			temp = set[i / 2];
			set[i / 2] = set[i];
			set[i] = temp;

			i /= 2;
		}
		else break;
	}
}

void replace_it(int x, int key)
{
	int i;
	int temp;
	int max;
	i = x;
	set[x] = key;	
	if(set[x] > set[x / 2]){
		while(1){
			if(i <= 1) break;
		
			if(set[i / 2] < set[i]){
				temp = set[i / 2];
				set[i / 2] = set[i];
				set[i] = temp;

				i /= 2;
			}
			else break;
		}
	}
	else{
		while(1){
			if(set[i * 2] > set[i * 2 + 1]) max = i * 2;
			else max = i * 2 + 1;
		
			if(set[max] > set[i]){
				temp = set[max];
				set[max]=  set[i];
				set[i] = temp;

				i = max;
			}
			else break;
		}
	}
}

int main(void)
{
	int i,j,k;
	int temp1, temp2, temp3, temp;
	int terminate = 0;
	char filename[100];

	FILE *in, *out;
//	
	/*
	for(int t = 1; t <= 10; t++)
	{
		itoa(t, filename, 10);
		strcat(filename,".in");
		in = fopen(filename,"r");
		*/
//
		n = 0;
		m = 0;
		terminate = 0;

		for(i = 0; i <= 300000; i++)
			set[i] = -1;

		while(1){
			fscanf(IN,"%d",&temp1);
			switch(temp1){
			case 0:
				terminate = 1;
				break;
			case 1:
				fscanf(IN,"%d",&temp2);
				insert_num(temp2);
				break;
			case 2:
				extract();
				break;
			case 3:
				fscanf(IN,"%d %d",&temp2, &temp3);
				replace_it(temp2, temp3);
				break;
			}
			if(terminate) break;
		}
//
//		itoa(t, filename, 10);
//		strcat(filename,".out");
//		out = fopen(filename,"w");
		for(i = 0; i < m; i++)
			fprintf(OUT,"%d ",res[i]);
		fprintf(OUT,"\n");
		for(i = 1; i <= n; i++)
			fprintf(OUT,"%d ",set[i]);
		fprintf(OUT,"\n");
//		fclose(in);
//		fclose(out);
//	}
//

	return 0;
}