#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 10000
int n;
char **maze;
int front,rear,emptychk,resultcnt;

typedef struct{
	int x,y;
}Queue_Type;

Queue_Type queue[MAX_SIZE];
Queue_Type dir[4] = {{-1,0},{1,0},{0,-1},{0,1}}; // Structure Array for four way.
Queue_Type st,en;

void input()
{
	FILE *in = fopen("input.txt","r"); // Open file once.
	int i,j;
	char temp;
	while(1){
		fscanf(in,"%c",&temp);
		fscanf(in,"%c",&temp);
		n++;					// n is for counting maze's size.
		if(temp == '\n') break; // if newline is on input, then break.
	}
	fclose(in); // Close file
	
	maze = (char**)malloc(sizeof(char*) * (n + 1));  // maze's dynamic allocation
	for(i = 0; i < n; i++)
		maze[i] = (char*)malloc(sizeof(char)* (n + 1));

	in = fopen("input.txt","r"); // Open file once again for get maze data.
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			fscanf(in,"%c",&maze[i][j]);
			fscanf(in,"%c",&temp);
		}
		maze[i][j] = '\0';
	}
	fclose(in); // close file.
}

void enqueue(Queue_Type enq)
{
	queue[rear] = enq; // put data to the queue.
	rear = (rear + 1) % MAX_SIZE;
}

void init()
{
	int i,j;
	front = 0;
	rear = 0;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(maze[i][j] == 'E'){ // find start point (E,E)
				st.x = i;
				st.y = j;
			}
			if(maze[i][j] == 'X'){ // find end point (X,X)
				en.x = i;
				en.y = j;
			}
		}
	}
	enqueue(st); // put start point at queue.
}

void BFS()
{
	int i,stchk = 0;
	Queue_Type now,temp;
	FILE *out = fopen("result.txt","w"); // open output file.
	fprintf(out,"(E, E)\n");
	while(1){
		if(front == rear) break; // queue is empty
		if((rear + 1) % MAX_SIZE == front) break; // queue is full

		now = queue[front];  // get current point.
		front = (front + 1) % MAX_SIZE;
		resultcnt++; // count the visited point.

		if(now.x == en.x && now.y == en.y){ // if current point is end point
			fprintf(out,"(X, X)\n");
			break;
		}
		
		if(stchk == 0) stchk = 1; // if it is start point don't print anything.
		else fprintf(out,"(%d, %d)\n",now.x,now.y); // else print current point.

		for(i = 0; i < 4; i++) // Search four way.
		{
			temp.x = now.x + dir[i].x; // temp is point that is moved.
			temp.y = now.y + dir[i].y;
			// if moved point is available to go..
			if(temp.x >= 0 && temp.x < n && temp.y >= 0 && temp.y < n && (maze[temp.x][temp.y] == '0' || maze[temp.x][temp.y] == 'X')){
				enqueue(temp); // put moved point to queue.
				maze[temp.x][temp.y] = '.'; // check the moved point visited to the maze map.
			}
		}
	}

	fprintf(out,"\nPath length = %d\n",resultcnt); // print total path length.
	fclose(out);
}

int main(void)
{
	input(); // input function.
	init(); // initialize datas.
	BFS(); // Search the maze with Queue(BFS).
	return 0;
}