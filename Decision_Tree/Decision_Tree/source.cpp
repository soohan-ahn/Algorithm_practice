#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct Attribute{
	int n;
	char name[50];
	char value[500][50];
} Attribute;

typedef struct DataSet{
	int n;  // number of attribute
	int an; // number of data
	Attribute attr[500];
	int flag[500];
} Dataset;

typedef struct TreeNode{
	int n; // number of child.
	int label_num;
	char name[50]; // Node's Attribute.
	char attr_value[100][50]; // edge to the child.
	TreeNode *child[100];
} Node;
Dataset Training,Test;
Attribute attr_list[500];
char Train_input_file_name[500];
char Test_input_file_name[500];
Dataset init_data;
Node* root;
int order;

void input()
{
	int i = 0,j,k;
	int chk, chk2;
	char temp;
	FILE *in = fopen(Train_input_file_name,"r");
	FILE *in1 = fopen(Test_input_file_name,"r");
	while(1){ // get input of attribute name of training set.
		fscanf(in,"%c",&temp);
		if(temp != '\t' && temp != '\n') Training.attr[Training.n].name[i++] = temp;
		else if(temp == '\t'){
			strcpy(attr_list[Training.n].name, Training.attr[Training.n].name);
			Training.n++;
			i = 0;
		}
		else if(temp == '\n'){
			strcpy(attr_list[Training.n].name, Training.attr[Training.n].name);
			Training.n++;
			break;
		}
	}

	chk = 0;
	while(1){ // get input of attribute value of training set.

		for(i = 0; i < Training.n; i++)
		{
			j = 0;
			while(1){
				fscanf(in,"%c",&temp);
				if(temp == '\n'){
					chk++;
					if(chk > 1) break;
					chk2 = 0;
					for(k = 0; k < attr_list[i].n; k++)
					{
						if(strcmp(attr_list[i].value[k], Training.attr[i].value[Training.an]) == 0){
							chk2 = 1;
							break;
						}
					}
					if(!chk2){
						strcpy(attr_list[i].value[attr_list[i].n], Training.attr[i].value[Training.an]);
						attr_list[i].n++;
					}					
					break;
				}
				if(temp != '\t' && temp != '\n' && temp != EOF){
					chk = 0;
					Training.attr[i].value[Training.an][j++] = temp;
				}
				else{
					chk2 = 0;
					for(k = 0; k < attr_list[i].n; k++)
					{
						if(strcmp(attr_list[i].value[k], Training.attr[i].value[Training.an]) == 0){
							chk2 = 1;
							break;
						}
					}
					if(!chk2){
						strcpy(attr_list[i].value[attr_list[i].n], Training.attr[i].value[Training.an]);
						attr_list[i].n++;
					}
					break;
				}
			}
			if(chk > 0) break;
		}		
		if(chk >= 2) break;
		Training.an++;
	}
	fclose(in);	

	
	while(1){ // get input of attribute name of test set.
		fscanf(in1,"%c",&temp);
		if(temp != '\t' && temp != '\n') Test.attr[Test.n].name[i++] = temp;
		else if(temp == '\t'){
			Test.n++;
			i = 0;
		}
		else if(temp == '\n'){
			Test.n++;
			break;
		}
	}

	chk = 0;
	while(1){ // get input of attribute value of test set.

		for(i = 0; i < Test.n; i++)
		{
			j = 0;
			while(1){
				fscanf(in1,"%c",&temp);
				if(temp == '\n'){
					chk++;
					break;
				}
				if(temp != '\t' && temp != '\n' && temp != EOF){
					chk = 0;
					Test.attr[i].value[Test.an][j++] = temp;
				}
				else break;
			}
			if(chk > 0) break;
		}		
		if(chk >= 2) break;
		Test.an++;
	}
	fclose(in1);
}

void init() // initialise necessary data
{
	int i;
//	strcpy(Train_input_file_name, "training_sample.txt");
//	strcpy(Test_input_file_name, "test_sample.txt");
	Training.n = 0;
	Test.n = 0;
	for(i = 0; i < 500; i++)
		attr_list[i].n = 0;
}

int Attribute_selection_method(Dataset* current_data) // determine the best partition.
{
	int i,j,k,l;
	int count[100];
	int count_attr[100];
	int chk;
	double infoD = 0;
	double infoA;
	double info = -999.0;
	int return_info;
	double tempa,tempb,tempc;
	for(i = 0; i < attr_list[current_data->n - 1].n; i++)
		count[i] = 0;
	for(i = 0; i < current_data->an; i++) //count attribute value of Attribute[n]
	{
		for(j = 0; j < attr_list[current_data->n - 1].n; j++)
		{
			if(!strcmp(attr_list[current_data->n - 1].value[j], current_data->attr[current_data->n - 1].value[i])){
				count[j]++; 
			}
		}
	}
	
	for(i = 0; i < attr_list[current_data->n - 1].n; i++) // calculate infoD - information gain of Attribute[n]
	{
		tempa = log((double)count[i] / current_data->an);
		tempb = log(2.0);
		infoD += (-1.0 * ((double)count[i] / current_data->an) * (tempa / tempb));
	}

	for(i = 0; i < current_data->n - 1; i++)
	{
		if(!current_data->flag[i]){
			for(l = 0; l < attr_list[current_data->n - 1].n; l++)
				count[l] = 0;
			for(l = 0; l < attr_list[i].n; l++)
				count_attr[l] = 0;

			for(j = 0; j < current_data->an; j++) // count the number of attribute[j] for each attribute value.
			{
				for(k = 0; k < attr_list[i].n; k++)
				{
					if(!strcmp(attr_list[i].value[k], current_data->attr[i].value[j])){
						count_attr[k]++;
					}
				}
			}

			infoA = 0.0;
			for(j = 0; j < attr_list[i].n; j++)
			{

				for(l = 0; l < attr_list[current_data->n - 1].n; l++)
					count[l] = 0;
				
				for(k = 0; k < current_data->an; k++) // count the number of attribute[n] value for each attribute.
				{
					if(!strcmp(current_data->attr[i].value[k], attr_list[i].value[j])){
						for(l = 0; l < attr_list[current_data->n - 1].n; l++)
						{
							if(!strcmp(attr_list[current_data->n - 1].value[l], current_data->attr[current_data->n - 1].value[k])){
								count[l]++;
							}
						}
					}
				}
				
				tempc = 0.0;
				chk = 0;
				for(k = 0; k < attr_list[current_data->n - 1].n; k++) // calculate information gain for each attribute.
				{
					if(count[k] == 0 || count[k] == count_attr[j]){
						chk = 1;
						break;
					}
					tempa = log((double)count[k] / count_attr[j]);
					tempb = log(2.0);
					tempc += (-1.0 * ((double)count[k] / count_attr[j]) * (tempa / tempb));					
				}
				infoA += (((double)count_attr[j]/current_data->an) * (tempc));
			}

			if(info < (infoD - infoA)){ // Determine maximum information gain.
				info = infoD - infoA;
				return_info = i;
			}
		}
	}

	return return_info;
}

Node* Generate_decision_Tree(Dataset* current_data)
{
	int i,j,k,chk;
	int label;
	int count[500];
	Dataset* divide;
	Node* new_node = (Node*)malloc(sizeof(Node)); // Create a node.
	Node* new_child;
	new_node->n = 0;

	chk = 0;
	for(i = 1; i < current_data->an; i++) // check if the tuples are in same class C.
	{
		if(strcmp(current_data->attr[current_data->n - 1].value[0], current_data->attr[current_data->n - 1].value[i])){
			chk = 1;
			break;
		}
	}
	if(!chk){ //if the tuples are in same class, return node as a leat node labeled with the class C
		new_node->label_num = current_data->n - 1;
		strcpy(new_node->name , current_data->attr[current_data->n - 1].value[0]);
		return new_node;
	}

	chk = 0;
	for(i = 0; i < current_data->n - 1; i++) // check if attribute list is empty.
	{
		if(current_data->flag[i] == 0){
			chk = 1;
			break;
		}
	}
	if(!chk){ //if attribute list is empty, return node as a leaf node labeled with the majority class in tuples.
		for(i = 0; i < current_data->an; i++)
		{
			for(j = 0; j < attr_list[Training.n - 1].n; j++)
			{
				if(!strcmp(current_data->attr[Training.n - 1].value[i], attr_list[Training.n - 1].value[j])) count[j]++;
			}
		}

		i = 0;
		for(j = 1; j < attr_list[Training.n - 1].n; j++)
			if(count[j] > count[i]) i = j;

		new_node->label_num = current_data->n - 1;
		strcpy(new_node->name , attr_list[Training.n - 1].value[i]);
		return new_node;
	}

	label = Attribute_selection_method(current_data); // label node with splitting criterion.	
	strcpy(new_node->name, current_data->attr[label].name);
	new_node->label_num = label;
	current_data->flag[label] = 1; // remove splitting_attribute.

	new_node->n = attr_list[label].n;
	for(i = 0; i < attr_list[label].n; i++) // for each outcome i.
	{
		strcpy(new_node->attr_value[i], attr_list[label].value[i]); // split the data with outcome i
		divide = (Dataset*)malloc(sizeof(Dataset)); // produce new Data partition Di
		*divide = *current_data;
		divide->an = 0;
		for(j = 0; j < current_data->an; j++)
		{
			if(!strcmp(attr_list[label].value[i], current_data->attr[label].value[j])){ // add tuples on Di.
				for(k = 0; k < current_data->n; k++)
				{
					strcpy(divide->attr[k].value[divide->an], current_data->attr[k].value[j]);
				}
				divide->an++;
			}
		}

		if(divide->an == 0){ // if Dj is empty, attach a leaf labeled with the majority class in D to node N.
			new_child = (Node*)malloc(sizeof(Node));
			for(k = 0; k < current_data->an; k++)
			{
				for(j = 0; j < attr_list[Training.n - 1].n; j++)
				{
					if(!strcmp(current_data->attr[Training.n - 1].value[k], attr_list[Training.n - 1].value[j])) count[j]++;
				}
			}

			i = 0;
			for(j = 1; j < attr_list[Training.n - 1].n; j++)
				if(count[j] > count[i]) i = j;

			new_child->label_num = current_data->n - 1;
			strcpy(new_child->name , attr_list[Training.n - 1].value[i]);
			new_node->child[i] = new_child;
		}
		else new_node->child[i] = Generate_decision_Tree(divide); // attach the node returned by Generate_decision_tree.
		free(divide);
	}
	
	return new_node;
}

void Decision(Node *current, int x)
{
	int i;
	if(current->label_num == Training.n - 1){ // if current node is leaf.
		strcpy(Test.attr[current->label_num].value[x], current->name);
		return;
	}
	else{
		for(i = 0; i < current->n; i++)
		{
			if(!strcmp(current->attr_value[i], Test.attr[current->label_num].value[x])){ // travel by the attribute value.
				Decision(current->child[i], x);
				return;
			}
		}
	}
}

void process()
{
	int i;

	init_data = Training;
	root = Generate_decision_Tree(&init_data); // construct decision tree

	for(i = 0; i < Test.an; i++)
	{
		Decision(root, i); // determine each for test set.
	}
}

void output()
{
	FILE *out = fopen("result.txt","w");
	int i,j;
	for(j = 0; j < Training.n; j++)
		fprintf(out,"%s\t",Training.attr[j].name);
	fprintf(out,"\n");

	for(i = 0; i < Test.an; i++)
	{
		for(j = 0; j < Training.n; j++)
			fprintf(out,"%s\t",Test.attr[j].value[i]);
		fprintf(out,"\n");
	}
	fclose(out);
}
/*
int main(void)
{
	init();
	input();
	process();
	output();
	return 0;
}
*/

int main(int argv, char* argc[])
{
	strcpy(Train_input_file_name, argc[1]);
	strcpy(Test_input_file_name, argc[2]);
	init();
	input();
	process();
	output();
	return 0;
}
