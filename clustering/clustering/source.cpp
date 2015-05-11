#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int n;
int num_of_cluster;
int current_cluster;
typedef struct DD{
	double x,y;
}DATA;
DATA data[1000];
int sing_cluster[1000][1000];
int sing_clust[1000];
int sing_clust_cnt[1000];
int avg_cluster[1000][1000];
int avg_clust[1000];
int avg_clust_cnt[1000];
int lar_cluster[1000][1000];
int lar_clust[1000];
int lar_clust_cnt[1000];
int singx,singy;
int larx,lary;
int avgx,avgy;
double dis[1000][1000];
double temp_sing_dis[1000][1000];
double temp_lar_dis[1000][1000];
double temp_avg_dis[1000][1000];
double temp_avg_num[1000][1000];
char input_file[1000];

void input()
{
	FILE *in = fopen(input_file,"r");
	while(fscanf(in,"%lf\t%lf\n",&data[n].x, &data[n].y) == 2) n++;
	fclose(in);
}

void process()
{
	int i,j;
	double temp_sing_min, temp_lar_min, temp_avg_min;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			dis[i][j] = sqrt(((data[i].x - data[j].x) * (data[i].x - data[j].x)) + ((data[i].y - data[j].y) * (data[i].y - data[j].y)));

	for(i = 0; i < n; i++)
	{
		sing_cluster[i][0] = i;
		sing_clust[i] = i;
		sing_clust_cnt[i] = 1;

		avg_cluster[i][0] = i;
		avg_clust[i] = i;
		avg_clust_cnt[i] = 1;

		lar_cluster[i][0] = i;
		lar_clust[i] = i;
		lar_clust_cnt[i] = 1;
	}
	current_cluster = n;

	/* 
	single link : smallest distance
	complete link : largest distance
	average link : average
	*/
	
	while(current_cluster > num_of_cluster){ // single link : smallest distance
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
			{
				temp_sing_dis[i][j] = 2100000000.0;
				temp_avg_dis[i][j] = 0.0;
				temp_lar_dis[i][j] = -1.0;
				temp_avg_num[i][j] = 0.0;
			}

		for(i = 0; i < n; i++)
		{			
			for(j = 0; j < n; j++)
			{
				if(sing_clust[j] != sing_clust[i]){
					if(temp_sing_dis[sing_clust[i]][sing_clust[j]] >= dis[i][j]){
						temp_sing_dis[sing_clust[i]][sing_clust[j]] = dis[i][j];
					}
				}

				if(lar_clust[j] != lar_clust[i]){
					if(temp_lar_dis[lar_clust[i]][lar_clust[j]] <= dis[i][j]){
						temp_lar_dis[lar_clust[i]][lar_clust[j]] = dis[i][j];
					}
				}

				if(avg_clust[j] != avg_clust[i]){
					temp_avg_dis[avg_clust[i]][avg_clust[j]] += dis[i][j];
					temp_avg_num[avg_clust[i]][avg_clust[j]] = temp_avg_num[avg_clust[i]][avg_clust[j]] + 1.0;
				}
			}
		}

		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				temp_avg_dis[i][j] = temp_avg_dis[i][j] / temp_avg_num[i][j];

		temp_sing_min = 2100000000.0; 
		temp_lar_min = 2100000000.0;
		temp_avg_min = 2100000000.0;
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				if(temp_sing_dis[sing_clust[i]][sing_clust[j]] <= temp_sing_min && sing_clust[i] != sing_clust[j]){
					temp_sing_min = temp_sing_dis[sing_clust[i]][sing_clust[j]];
					singx = sing_clust[i];
					singy = sing_clust[j];
				}

				if(temp_avg_dis[avg_clust[i]][avg_clust[j]] <= temp_avg_min && avg_clust[i] != avg_clust[j]){
					temp_avg_min = temp_avg_dis[avg_clust[i]][avg_clust[j]];
					avgx = avg_clust[i];
					avgy = avg_clust[j];
				}

				if(temp_lar_dis[lar_clust[i]][lar_clust[j]] <= temp_lar_min && lar_clust[i] != lar_clust[j]){
					temp_lar_min = temp_lar_dis[lar_clust[i]][lar_clust[j]];
					larx = lar_clust[i];
					lary = lar_clust[j];
				}
			}
		}

		for(i = 0; i < n; i++)
		{
			if(sing_clust[i] == singy){
				sing_cluster[singx][sing_clust_cnt[singx]++] = i;
				sing_clust[i] = singx;
				sing_clust_cnt[i] = -1;
			}

			if(avg_clust[i] == avgy){
				avg_cluster[avgx][avg_clust_cnt[avgx]++] = i;
				avg_clust[i] = avgx;
				avg_clust_cnt[i] = -1;
			}

			if(lar_clust[i] == lary){
				lar_cluster[larx][lar_clust_cnt[larx]++] = i;
				lar_clust[i] = larx;
				lar_clust_cnt[i] = -1;
			}
		}

		current_cluster--;
	}
}

void output()
{
	int i,j,k;
	FILE *out;
	char t_output_name[100];
	char temp[100];
	char output_name[100];

	strcpy(t_output_name,"sing_cluster");
	for(i = 0, k = 0; i < n; i++)
	{
		if(sing_clust_cnt[i] != -1){
			printf("Sing %d, = %d\n",k,sing_clust_cnt[i]);

			itoa(++k, temp, 10);
			strcpy(output_name, t_output_name);
			strcat(temp,".txt");
			strcat(output_name, temp);

			out = fopen(output_name,"w");
			for(j = 0; j < sing_clust_cnt[i]; j++)
				fprintf(out,"%.3lf\t%.3lf\n",data[sing_cluster[i][j]].x,data[sing_cluster[i][j]].y);
			fclose(out);
		}
	}

	strcpy(t_output_name,"avg_cluster");
	for(i = 0, k = 0; i < n; i++)
	{
		if(avg_clust_cnt[i] != -1){
			printf("avg %d, = %d\n",k,avg_clust_cnt[i]);

			itoa(++k, temp, 10);
			strcpy(output_name, t_output_name);
			strcat(temp,".txt");
			strcat(output_name, temp);

			out = fopen(output_name,"w");
			for(j = 0; j < avg_clust_cnt[i]; j++)
				fprintf(out,"%.3lf\t%.3lf\n",data[avg_cluster[i][j]].x,data[avg_cluster[i][j]].y);
			fclose(out);
		}
	}

	strcpy(t_output_name,"com_cluster");
	for(i = 0, k = 0; i < n; i++)
	{
		if(lar_clust_cnt[i] != -1){
			printf("com %d, = %d\n",k,lar_clust_cnt[i]);

			itoa(++k, temp, 10);
			strcpy(output_name, t_output_name);
			strcat(temp,".txt");
			strcat(output_name, temp);

			out = fopen(output_name,"w");
			for(j = 0; j < lar_clust_cnt[i]; j++)
				fprintf(out,"%.3lf\t%.3lf\n",data[lar_cluster[i][j]].x,data[lar_cluster[i][j]].y);
			fclose(out);
		}
	}
}
/*
int main(int argv, char* argc[])
{
	num_of_cluster = atoi(argc[1]);
	strcpy(input_file, argc[2]);
	input();
	process();
	output();
	return 0;
}
*/

int main(void)
{
	num_of_cluster = 3;
	strcpy(input_file,"input.dat");
	input();
	process();
	output();
	return 0;
}