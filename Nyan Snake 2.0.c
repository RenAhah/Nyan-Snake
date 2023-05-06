#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "method.h" 
#define N 30

typedef struct snake
{
	int x;
	int y;
}Snake;
Snake snake[N*N]={10,10,10,9,10,8,10,7,10,6,0,0};
Snake snake_old[N*N];
int i,j,px=0,py=0,flag_again=0,l=5,m=0;
int record[11],record_temp;
int main () 
{
	FILE *fp=NULL;
	char *filename="./log.txt";		
	char c=' ';
	int screen[N+2][N+2];
	srand(time(NULL));
	Start:
		if(flag_again)
		{
		snake[0].x=N/2;
		snake[0].y=N/2;
		for(i=1;i<l+1;i++)
		{
			snake[i].x=0;
			snake[i].y=0;
			snake_old[i]=snake[i];
		}
		l=1;	m=0;	px=py=1;	flag_again=0;	c=0;};
	
	fp = fopen(filename,"r");
	for(i=0;i<10;i++)
	fscanf(fp,"%d\n",&record[i]);
	px=rand()%N+1;
	py=rand()%N+1;
	for(i=0;i<N+2;i++) 
	{
		for(j=0;j<N+2;j++)
			{
			if(i==0||i==N+1||j==0||j==N+1)	screen[i][j]=1;
			else							screen[i][j]=0;			
			}
	}
	for(i=0;i<N+2;i++)
	{
		for(j=0;j<N+2;j++)
		{
			switch(screen[i][j])
			{
				case 0:{printf("  ");	break;}
				case 1:{color(1);	printf("■");	color(7);	break;} 
				case 2:{color(6);	printf("●");	color(7);	break;}
			} 
		}
		printf("\n");
	}
	while(1)
	{
	screen[py][px]=2;
	for(i=0;snake[i].x;i++)
	{
		screen[snake[i].y][snake[i].x]=1;
		snake_old[i]=snake[i]; 
	}
	screen[snake_old[l].y][snake_old[l].x]=0;
	gotoxy(0,0);
	for(i=1;i<N+1;i++)
	{
		gotoxy(2,i);
		for(j=1;j<N+1;j++)
		{
			switch(screen[i][j])
			{
				case 0:{printf("  ");	break;}
				case 1:{color(l%15+1);	printf("■");	color(7);	break;} 
				case 2:{color(6);	printf("●");	color(7);	break;}
			} 
		}
	}
	gotoxy(0,N+2);
	color(9);	printf("得分：%d\n操作：",l);	
	switch(c)
	{
		case 'M':	{	printf("→");		break;		}
		case 'P':	{	printf("↓");		break;		}
		case 'K':	{	printf("←");		break;		}
		case 'H':	{	printf("↑");		break;		}
	}
	if(!m)
	{
	printf("\n\n"); 
	color(6);
	printf("————排行榜————\n");
	for(i=0;i<10;i++)
	printf("No.%d:\t%d\n",i+1,record[i]);
	colorSet(1,9);	 
	printf("\tCopyright 2019 RenAhah.\n\t  All Rights Reserved. \n");	color(7);
	m++;
	}
	if(kbhit())
	{
	c=getch();
	} 
	switch(c)
	{
		case 'M':	{	snake[0].x+=1;		break;		}
		case 'P':	{	snake[0].y+=1;		break;		}
		case 'K':	{	snake[0].x-=1;		break;		}
		case 'H':	{	snake[0].y-=1;		break;		}
		case ' ':	{	while(getch()!='M'||getch()!='P'||getch()!='K'||getch()!='H')	break;			}
	}
	if(snake[0].x==px&&snake[0].y==py)	
	{
	setFood:
	px=rand()%N+1;
	py=rand()%N+1;
	for(i=0;i<l;i++)
	if(px==snake[i].x&&py==snake[i].y)	goto setFood; 
	l+=1;	
	}
	for(i=0;i<l;i++)
	snake[i+1]=snake_old[i];
	if(snake[0].x==0||snake[0].x==N+1||snake[0].y==0||snake[0].y==N+1)	break;
	for(i=2;i<l;i++)
	if(snake[0].x==snake[i].x&&snake[0].y==snake[i].y)	goto game_over;
	}
	game_over:
	record[10]=l; 
	fp = fopen(filename,"r");	
	for(i=0;i<10;i++)
	fscanf(fp,"%d\n",&record[i]); 
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		if(record[j+1]>=record[j])
		{
			record_temp=record[j];
			record[j]=record[j+1]; 
			record[j+1]=record_temp;
		}
	}
	fp = fopen(filename,"w");
	for(i=0;i<10;i++)	
	fprintf(fp,"%d\n",record[i]);
	fclose(fp);		
	gotoxy(0,N+2);
	color(4);
	printf("GAME OVER\n长度：%d\n任意键重新开始游戏",l);
	gotoxy(0,N+5);
	color(6);
	printf("————排行榜————\n");
	for(i=0;i<10;i++)
	printf("No.%d:\t%d\n",i+1,record[i]);
	color(7);
	if(getch())
	{ 
	flag_again=1;
	system("cls");	
	goto Start;
	} 
	}  
