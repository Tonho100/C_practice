#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fivechesses.h"
#include<stdlib.h>

void meun() 
{
	printf("     Welcome to FiveChesses     \n");
	printf("--------------------------------\n");
	printf("-----    1.Start game.     -----\n");
	printf("-----    0.Exit game.      -----\n");
	printf("--------------------------------\n");
}


void game()
{
	char board[SIZE][SIZE];
	initgame(board,SIZE,SIZE);    
	
	int i,j;        
	char chess;    
	int cont=1;     
	char ret=0;     
	
	system("cls");
	display(board,SIZE,SIZE);

	while(ret==0)
	{
		chess=turn(cont);         
		
		printf("%c->Entre your position:",chess);  
		scanf("%d %d",&i,&j);
		i-=1; j-=1;                       
		printf("\n");
		
		if(i<SIZE&&i>=0&&j<SIZE&&j>=0&&board[i][j]==' ')  
		{
			cont++;   
			board[i][j]=chess;
			system("cls");           
			display(board,SIZE,SIZE);      
			
		#if DEBUG 
			//test
			{
				int a,b,c,d;
				a=row(board,i,j);
				b=column(board,i,j);
				c=diagonal(board,i,j);
				d=back_diagonal(board,i,j);
				printf("%c -> row:%d, column:%d, diagonal:%d, back_diagnol:%d\n\n\n",board[i][j],a,b,c,d);
			}
		#endif 
		
			ret=referee(board,i,j);         
		} 
		
		else 
		{
			printf("INPUT ERROR!!\n");
			continue;
		}
		
	}
	
	if(ret=='w') printf("-----------%c WIN!-----------\n\n\n\n\n",chess);
	else printf("NO WINNER\n\n\n\n\n");
} 


int main()
{
	int input=0;
	
	do
	{
		meun();
		printf("Please select>:");
		scanf("%d",&input);
		
		switch(input)   
		{
			case 1:game(); break;
			case 0:printf("Exit...\n"); break;
			default:printf("Error select!");
		}
	}while(input);    
	return 0;
} 
