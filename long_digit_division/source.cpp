#include<stdio.h>
#include<string.h>
#include<math.h>
int chk;
char ia[51],a[51];
char ib[51],b[51];
char c[51];
char one[51];

void input()
{
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%s\n",&ia);
	fscanf(in,"%s\n",&ib);
	fclose(in);
}

void sub()
{
	int i,temp = 0;
	for(i = 0; i < 50; i++)
	{
		temp = (a[i] - '0') - (b[i] - '0');
		if(temp < 0){
			a[i + 1] = ((a[i + 1] - '0') - 1) + '0';
			a[i] = (temp + 10) + '0';
		}
		else a[i] = temp + '0';
	}
	if(temp < 0) a[50] = ((a[50] - '0') - 1) + '0';
}

void sub1()
{
	int i,temp = 0;
	one[0] = '1';
	for(i = 0; i < 50; i++)
	{
		temp += (c[i] - '0') + (one[i] - '0');
		c[i] = (temp % 10) + '0';
		temp /= 10;
	}
}

int returnb()
{
	int i,temp1,temp2,chk1 = 0;
	for(i = 50; i >= 1; i--)
	{
		temp1 = (a[i] - '0');
		temp2 = (b[i] - '0');
		if(temp1 < temp2) return 1;
		else if(temp1 > temp2) return 0;
	}

	temp1 = (a[0] - '0');
	temp2 = (b[0] - '0');
	if(temp1 == temp2){
		chk = 1;
		return 0;
	}

	return 1;
}

void output()
{
	int i,st;
	for(st = 50; st >= 0; st--)
		if(c[st] >= '1' && c[st] <= '9') break;
	for(i = st; i >= 0; i--)
		printf("%c",c[i]);
	printf("\n");
}

void process()
{
	int i = 0;
	while(1){
		if(returnb() == 1) break;
		else{
			i++;
		//	if(i < 100) printf("%s\n",a);
			sub();
			sub1();
			if(chk == 1) break;
		}
	}
	output();
}

void fresh()
{
	int i;
	for(i = 0; i < (int)strlen(ia); i++)
		a[i] = ia[(int)strlen(ia) - 1 - i];
	for(i = 0; i < (int)strlen(ib); i++)
		b[i] = ib[(int)strlen(ib) - 1 - i];

	for(i = 0; i <= 50; i++)
	{
		if(a[i] == NULL) a[i] = '0';
		if(b[i] == NULL) b[i] = '0';
		one[i] = '0';
		c[i] = '0';
	}
}

int main(void)
{
	input();
	fresh();
	process();
	return 0;
}