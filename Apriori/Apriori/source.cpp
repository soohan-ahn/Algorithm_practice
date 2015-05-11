#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int n;
int count_item[1000];
int item_set[10000][1000];
int min_support;
int flag[100000];
int L_set[2][10000][1000];
int C_set[10000][1000];
int tmp_cand[1000];
int tmp_subset[1000];
int subset_flag[1000];
int k,max_item;
int current_cnt;
int cand_cnt;
int next_cnt;
char input_file_name[50];
char output_file_name[50];
int _from[1000], from_cnt;
int _to[1000], to_cnt;
FILE *out;

void input()
{
	int temp_num = 0;
	int is_int = 0;
	char temp;
	FILE *in = fopen(input_file_name,"r");
	while(1){
		temp = fgetc(in);
		if(temp == EOF){ // End of file..
			if(is_int){
				item_set[n][count_item[n]++] = temp_num;
				if(temp_num > max_item) max_item = temp_num;
				flag[temp_num]++;
				temp_num = 0;
				n++;
			}
			break;
		}
		else if(temp == '\n'){ // End of item set
			if(is_int){
				item_set[n][count_item[n]++] = temp_num;
				if(temp_num > max_item) max_item = temp_num;
				flag[temp_num]++;
				temp_num = 0;
				n++;
				is_int = 0;
			}
		}
		else if(temp == '\t'){ // Insert item to array
			if(is_int){
				item_set[n][count_item[n]++] = temp_num;
				if(temp_num > max_item) max_item = temp_num;
				flag[temp_num]++;
				temp_num = 0;
				is_int = 0;
			}
		}
		else{
			is_int = 1;
			temp_num *= 10;
			temp_num += (temp - '0');
		}
	}
	fclose(in);
}

int has_infrequent_subset() 
{
	int i,j,l,p;
	int subset_cnt;
	int chk;
	for(i = 0; i < k; i++)
	{
		subset_cnt = 0;
		for(j = 0; j < k; j++) //tmp_cand¿¡¼­ (k-1)-subset extract.. -> tmp_subset[]
		{			
			if(i != j){
				subset_flag[subset_cnt] = 0;
				tmp_subset[subset_cnt++] = tmp_cand[j];
			}
		}

		chk = 0;
		for(j = 0; j < current_cnt; j++) // find if there's infrequent subset
		{
			for(p = 0; p < subset_cnt; p++)			
			{
				for(l = 0; l < k - 1; l++)
				{
					if(tmp_subset[p] == L_set[(k - 1) % 2][j][l]) subset_flag[p] = 1;
				}
			}

			chk = 1;
			for(p = 0; p < subset_cnt; p++)
			{
				if(subset_flag[p] == 0){
					chk = 0;
					break;
				}
			}

			if(chk == 1) break; 
			else{
				for(p = 0; p < subset_cnt; p++)
					subset_flag[p] = 0;
			}
		}

		if(chk == 0) return 1; // This subset is infrequent subset. Thus it can't be a candidate.

	}
	
	return 0;
}

void apriori_gen()
{
	int i,j,l;
	int chk;
	for(i = 0; i < current_cnt; i++)
	{
		for(j = 0; j < current_cnt; j++)
		{
			chk = 0;
			for(l = 0; l < k - 2; l++)
			{
				if(L_set[(k - 1) % 2][i][l] != L_set[(k - 1) % 2][j][l]){
					chk = 1;
					break;
				}
			}
			if(chk == 0 && L_set[(k - 1) % 2][i][k - 2] < L_set[(k - 1) % 2][j][k - 2]){ // (l1[1] == l2[1]) ^ .. ^(l1[k -1] > l2[k - 1])
				for(l = 0; l < k - 1; l++) //join
				{
					tmp_cand[l] = L_set[(k - 1) % 2][i][l];
				}
				tmp_cand[k - 1] = L_set[(k - 1) % 2][j][k - 2];

				if(!has_infrequent_subset()){
					for(l = 0; l < k; l++) // add c to Ck
						C_set[cand_cnt][l] = tmp_cand[l];
					cand_cnt++;
				}
			}
		}
	}
}

void _association(int sup_cnt, int cand_pt, int pt) // Create association rules.
{
	int i,j;
	int chk, l, p;
	int con_cnt;
	float support;
	float confidence;
	if(pt == k){ // One of association rule has been made.
		fprintf(out,"[ ");
		for(i = 0; i < from_cnt - 1; i++)
		{
			fprintf(out,"%d, ",_from[i]);
		}
		fprintf(out,"%d ] -> [ ",_from[i]);

		for(i = 0; i < to_cnt - 1; i++)
		{
			fprintf(out,"%d, ",_to[i]);
		}

		support = (float)sup_cnt; // calculate support
		support /= (float)n;
		support *= 100;

		fprintf(out,"%d ] support=%.1f0,",_to[i], support); // print support

		con_cnt = 0;
		for(j = 0; j < n; j++) // Count x's count from [x]->[y] 
		{
			chk = 0;
			for(p = 0; p < from_cnt; p++)					
			{
				chk = 0;
				for(l = 0; l < count_item[j]; l++)
				{
					if(item_set[j][l] == _from[p]){
						chk = 1;
						break;
					}
				}
				if(chk == 0) break;
			}
			if(chk == 1) con_cnt++;
		}
		confidence = (float)sup_cnt; // Calculate confidence
		confidence /= (float)(con_cnt);
		confidence *= 100;

		fprintf(out," confidence=%.2f\n",confidence); // Print confidence.
		return;
	}
	else{
		if(from_cnt < k - 1){ // Make association rule that element of order pt belongs to left side of rule.
			_from[from_cnt++] = C_set[cand_pt][pt];
			_association(sup_cnt, cand_pt, pt + 1);
			from_cnt--;
		}

		if(to_cnt < k - 1){  // Make association rule that element of order pt belongs to right side of rule.
			_to[to_cnt++] = C_set[cand_pt][pt];
			_association(sup_cnt, cand_pt, pt + 1);
			to_cnt--;
		}
	}
}

void process()
{
	int i,j;
	int p,l;
	int chk;
	int sup_cnt;

	k = 1;
	current_cnt = 0;
	for(i = 0; i <= max_item; i++)
	{
		if(flag[i] >= min_support) L_set[k][current_cnt++][0] = i; // find_frequent_1-itemsets
	}
	
	while(k++){
		if(current_cnt == 0) break; // If L(k)-set is empty, break! (Terminate programme.)
		else{
			apriori_gen(); // Generate candidates.
			for(i = 0; i < cand_cnt; i++) // Count support value of each candidate.
			{
				sup_cnt = 0;
				for(j = 0; j < n; j++)				
				{
					chk = 0;
					for(p = 0; p < k; p++)					
					{
						chk = 0;
						for(l = 0; l < count_item[j]; l++)
						{
							if(item_set[j][l] == C_set[i][p]){
								chk = 1;
								break;
							}
						}
						if(chk == 0) break;
					}
					if(chk == 1) sup_cnt++;
				}				
				
				if(sup_cnt >= min_support){ // If its support is bigger than minimum support, run association rule.
					from_cnt = 0; to_cnt = 0;
					_association(sup_cnt, i, 0); 

					for(j = 0; j < k; j++) // Certainly, it belongs to L(k)-set.
					{
						L_set[k % 2][next_cnt][j] = C_set[i][j];
					}
					next_cnt++;
				}
			}

			current_cnt = next_cnt;
			next_cnt = 0;
			cand_cnt = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	strcpy(input_file_name, argv[2]);
	strcpy(output_file_name, argv[3]);
	min_support = atoi(argv[1]);

	out = fopen(output_file_name, "w");
	input();
	process();
	fclose(out);
	return 0;
}

/*
int main(void)
{
	strcpy(input_file_name, "input.txt");
	strcpy(output_file_name, "output.txt");
	min_support = 10;

	out = fopen(output_file_name, "w");
	input();
	process();
	fclose(out);
	return 0;
}
*/