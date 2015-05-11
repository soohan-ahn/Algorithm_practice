/*
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n;
int set[1000000];

int main(void)
{
	FILE *out = fopen("1.in","w");
	int i,j;
	int temp;
	char filename[100];

	int m;
	
	for(i = 2; i <= 10; i++)
	{
		sprintf(filename,"%d.in",i);
		out = fopen(filename,"w");

//		srand(i);

		n = rand() % 100000 + 1;
		if(i == 10) n = 99999;
		fprintf(out,"%d\n",n);

		m = rand() % 30 + 1;
		fprintf(out,"%d\n",m);
		
		for(j = 0; j < n; j++)
		{
			temp = rand() % 1000000 + 1;
			fprintf(out,"%d\n",temp);
		}
		fclose(out);
	}


	return 0;
}
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define IN stdin
#define OUT stdout
int n,k;
int set[300000];
int res[300000];

int main(void)
{
	FILE *in, *out;

	int temp,temp1;
	int i,j;
	int cnt;
	char filename[100];
	//
	/*
	for(int t = 1; t <= 10; t++)
	{
		itoa(t, filename, 10);
		strcat(filename,".in");
		in = fopen(filename,"r");
		*/
		//
		fscanf(IN,"%d %d",&n,&k);
		for(i = 1; i <= 300000; i++)
			set[i] = -1;

		for(i = 1; i <= n; i++)
		{
			fscanf(IN,"%d",&set[i]);
		
			j = i;
			while(1){
				if(j <= 1) break;
				if(set[j / 2] < set[j]){
					temp = set[j / 2];
					set[j / 2] = set[j];
					set[j] = temp;

					j /= 2;
				}
				else break;
			}
		}

		for(i = 0; i < k; i++)
		{
			res[i] = set[1];

			set[1] = set[n];
			set[n--] = -1;

			j = 1;
			while(1){
				if(set[j * 2] > set[j * 2 + 1]) temp1 = j * 2;
				else temp1 = j * 2 + 1;

				if(set[temp1] > set[j]){
					temp = set[temp1];
					set[temp1] = set[j];
					set[j] = temp;

					j = temp1;
				}
				else break;
			}
		}

//		itoa(t, filename, 10);
//		strcat(filename,".out");
//		out = fopen(filename,"w");

		for(i = 0; i < k; i++)
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