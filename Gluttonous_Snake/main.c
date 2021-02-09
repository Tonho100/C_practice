#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<process.h>
#include<windows.h>
#include<conio.h>
#include"snakegame.h"

/*****************************************************************************************/

void game()
{
	system("cls"); 
	system("title ̰贪吃蛇[游戏中]"); 

 
	char before_click;
	int key;
	
	HideCursor();    
	creatgraph();    
	creatsnake();   
	creatfood();    
	goto_print(head->x,head->y); 
	 
	do
	{	
		if(_kbhit()) 
		{	
			before_click=_getch(); 
			if(before_click==up || before_click==down || before_click==left ||before_click==right)
			{
				key=(int)(before_click+click);
				if(key!=234 && key!=197) click=before_click;  
			}
		}
		
		MovingSnake();
		Eating();
		Sleep(speed); 
		
	}while(Judge()); 
	
	Finish();
}

/*****************************************************************************************/


int main()
{
	int input;
	system("color 0B");
	speed=100;
	
	do
	{
		system("cls");
		menu();        
		gotoxy(50,14);
		printf("SELECT:");		
		scanf("%d",&input); 
		
		switch(input)
		{
			case 1:  game(); break;
			case 2:  select_difficulty(); break;
			case 0:  printf("Exit...\n"); break;
			default: printf("Error select!");
		}	
	}while(input);

	return 0;
}
