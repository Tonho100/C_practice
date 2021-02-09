#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fivechesses.h"



int row(char board[SIZE][SIZE],int x,int y)   
{
	int cont=0; 
	char chess=board[x][y];
	int i,j;
	
	for(i=x,j=y;j<SIZE;j++) 
	{
		if(board[i][j]==chess) cont++;
		else break;
	} 
	
	for(i=x,j=y;j>=0;j--)    
	{
		if(board[i][j]==chess) cont++;
		else break;
	}
	
	cont-=1;
	return cont;   
}


int column(char board[SIZE][SIZE],int x,int y)  
{
	int cont=0;  
	char chess=board[x][y];
	int i,j;
	
	for(i=x,j=y;i<SIZE;i++)  
	{
		if(board[i][j]==chess) cont++;
		else break;
	} 
	
	for(i=x,j=y;i>=0;i--)   
	{
		if(board[i][j]==chess) cont++;
		else break;
	}
	
	cont-=1;
	
	return cont;  
}


int diagonal(char board[SIZE][SIZE],int x,int y)
{
	int cont=0; 
	char chess=board[x][y];
	int i,j;
	
	for(i=x,j=y;i>=0&&j<SIZE;i--,j++)
	{
		if(board[i][j]==chess) cont++;
		else break;
	}
	
	for(i=x,j=y;i<SIZE&&j>=0;i++,j--)
	{
		if(board[i][j]==chess) cont++;
		else break;
	}
	
	cont-=1;
	return cont;
}


int back_diagonal(char board[SIZE][SIZE],int x,int y)
{
	int cont=0;
	char chess=board[x][y];
	int i,j;
	
	for(i=x,j=y;i<SIZE&&j<SIZE;i++,j++)
	{
		if(board[i][j]==chess) cont++;
		else break;
	}
	
	for(i=x,j=y;i>=0&&j>=0;i--,j--)
	{
		if(board[i][j]==chess) cont++;
		else break; 
	}
	
	cont-=1;
	return cont;
 } 


char referee(char board[SIZE][SIZE],int x,int y) 
{
	char ret=0;
	int cont=0;
	
	cont=row(board,x,y);
	if(cont<WIN) cont=column(board,x,y);
	if(cont<WIN) cont=diagonal(board,x,y);
	if(cont<WIN) cont=back_diagonal(board,x,y);
	
	if(cont>=WIN) ret='w';
	
	return ret;
}


char turn(int cont) 
{
	int chess;
	
	if(cont%2) chess='O';
	else chess='X';
	
	return chess;
} 
