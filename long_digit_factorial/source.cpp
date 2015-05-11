#include<stdio.h>
#include<string.h>
#include<math.h>
char a[1001];
char b[1001];
char c[1001][1001];

void input()
{
	FILE *in = fopen("input.txt","r");
	fscanf(in,"%s",&a);
	fclose(in);
}

void minus()
{
	int i,k,temp = 0,temp1 = 0;
	for(i = strlen(b) - 1; i >= 0; i--)
	{
		if(i == strlen(b) - 1) k = 1;
		else k = 0;
		temp = ((b[i] - '0') - k);
		if(i == 0 && b[i] == '0') break;

		if(temp < 0){
			temp1 = 1;
			b[i] = ((temp + 10)) + '0';
			b[i - 1] = ((b[i - 1] - '0') - 1) + '0';
		}
		else b[i] = temp + '0';
	}
}

void reverse()
{
	int i,st = 1000;
	for(i = 1000; i >= 0; i--)
	{
		if(c[(int)strlen(b)][i] >= '1' && c[(int)strlen(b)][i] <= '9'){
			st = i; 
			break;
		}
	}

	for(i = st; i >= 0; i--)
	{
		a[st - i] = c[(int)strlen(b)][i];
	}
}

int numb()
{
	int i,temp = 0;
	int p = (int)strlen(b) - 1;
	for(i = (int)strlen(b) - 1; i >= 0; i--)
	{
		temp += (pow(10,p) * (b[i] - '0'));
		if(temp > 1) return 0;		
	}
	return 1;
}

void mult()
{
	int i,j,k,temp;
	for(i = 0; i <= 1000; i++)
		for(j = 0; j <= 1000; j++)
			c[i][j] = '0';

	for(i = strlen(b) - 1; i >= 0; i--)
	{
		temp = 0;
		for(j = strlen(a) - 1, k = (strlen(b) - 1) - i; j >= 0; j--, k++)
		{
			temp = (b[i] - '0') * (a[j] - '0') + temp;
			c[i][k] = (temp % 10) + '0';
			temp /= 10;
		}

		for(j = k; ; k++)
		{
			c[i][j] = (temp % 10) + '0';
			temp /= 10;
			if(temp == 0) break;
		}
	}
	
	temp = 0;
	for(i = 0; i < 10; i++)
	{
		for(j = strlen(b) - 1; j >= 0; j--)
		{
			temp += (c[j][i] - '0');
		}
		c[(int)strlen(b)][i] = (temp % 10 + '0');
		temp /= 10;
	}
}


void process()
{
	int i,j,k;
	int temp,temp1 = 0;
	for(i = 0; i < (int)strlen(a); i++)
		b[i] = a[i];
	
	a[0] = '1'; a[1] = '8'; a[2] = '5';
	b[0] = '7';
	mult();
	reverse();
/*
	while(1){
		minus();
		printf("%s\n%s\n",a,b);
		if(numb() == 1) break;
		mult();

		reverse();
	}*/
	printf("%s\n",a);
}

int main(void)
{
	input();
	process();
	return 0;
}