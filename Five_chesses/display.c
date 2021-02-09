#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fivechesses.h"


void initgame(char board[SIZE][SIZE],int x,int y)
{
	memset(board,' ',x*y*sizeof(char)); 
}


void display(char board[SIZE][SIZE],int x,int y) 
{
	int i=0;
	int j=0;
	
	printf("  ");
	for(j=0;j<y;j++)
	{
		printf("%4d",j+1);
	}
	printf("\n");
	
	printf("   ");    
	printf("|");      
	
	for(j=0;j<y;j++)  
	{
		printf("---|");
	}
	printf("\n");
	
	for(i=0;i<x;i++)  
	{
		printf("%2d ",i+1);  
		printf("|");         
		
		for(j=0;j<y;j++)   
		{
			printf(" %c |",board[i][j]);
		}
		
		printf("\n");
		printf("   ");       
		printf("|");
		for(j=0;j<y;j++)
		{
			printf("---|");
		}
		printf("\n");
	}
	
}

		

