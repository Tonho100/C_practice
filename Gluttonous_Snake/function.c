#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<process.h>
#include<windows.h>
#include<conio.h>
#include"snakegame.h"

/****************************************************************************************************/
//隐藏光标
void HideCursor()  
{
	HANDLE OUTPUT=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor={1,0};
	SetConsoleCursorInfo(OUTPUT,&cursor);
} 


/****************************************************************************************************/
//跳转光标
void gotoxy(int x,int y)  
{
	COORD POS;   //windows里面定义的结构体，表示光标坐标 
	POS.X=x;
	POS.Y=y;
	HANDLE OUTPUT=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(OUTPUT,POS);   //控制光标位置，输出格式 
} 


/****************************************************************************************************/
//开始界面
void menu()  
{
	system("title 贪吃蛇（控制台版）[菜单栏]"); 
	gotoxy(25,2);
	printf("/----------------------------------------------------------------/");
	gotoxy(25,17);
	printf("/----------------------------------------------------------------/");
	gotoxy(40,5);
	printf("WELCOME TO THE GAME OF RETRO SNAKE");
	gotoxy(50,8);
	printf("1.START GAME\n");
	gotoxy(50,10);
	printf("2.Select the difficulty");
	gotoxy(50,12);
	printf("0.QIUT");
	gotoxy(35,16);
	printf("请在英文输入法下操作，方向控制：w=up, a=left, s=right, d=down, p暂停");
}


/****************************************************************************************************/
//跳转打印方块 
void goto_print(int x,int y)
{
	gotoxy(x,y);
	printf("■");
}


/****************************************************************************************************/

void select_difficulty()
{
	system("title 贪吃蛇（控制台版）[游戏难度选择]"); 
	int choice;
	system("cls");
	gotoxy(50,8);
	printf("Select the difficulty:");
	gotoxy(50,10);
	printf("1.EASY *");
	gotoxy(50,12);
	printf("2.NORMAL * *");
	gotoxy(50,14);
	printf("3.DIFFICULT * * *");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: speed=400; break;
		case 2: speed=200; break;
		case 3: speed=50;  break;
		default:speed=400; break;
	}
	
} 


/****************************************************************************************************/
//创造围墙 
void creatgraph()
{
	int i;
	for(i=0;i<58;i+=2)
	{
		goto_print(i,0);
		goto_print(i,26);
	}
	for(i=1;i<26;i++)
	{
		goto_print(0,i);
		goto_print(56,i);
	}	
} 


/****************************************************************************************************/
//创造一条蛇，用到链表（单向链表） 
void creatsnake()
{
	snake* p=(snake*)malloc(sizeof(snake));  //创造蛇头 
	head=p;   //把head指向蛇头
	 
	srand((unsigned)time(NULL));
	head->y=(rand()%20)+5;
	head->x=(rand()%45)+10;
	if(head->x%2!=0) //x的坐标是非偶数时要变成偶数 
	{
		head->x+=1;
	}
	head->next=NULL; 
	click=left;
} 


/****************************************************************************************************/
//创造食物
void creatfood()
{
	int flag=0;
	
	while(!flag) //通过循环筛选出合适的食物的坐标 
	{
		flag=1;
		
		srand((unsigned)time(NULL)); //先随机出一组食物坐标，再去判断是否合适 
		food.y=rand()%25+1;
		food.x=rand()%53+2;
		
		if(food.x%2!=0)      // 1. 要求 x 为偶数 
		{
			food.x+=1;
		} 
		
		snake* body=head;    // 2.判断食物不能在蛇的身体上
		while(body) //循环结束条件是到达链表末端 
		{
			if(food.x==body->x && food.y==body->y)
			{
				flag=0; //坐标不合格
				break;  //退出当前循环（内循环） 
			}
			body=body->next; //把指针指向下一节蛇身 
		} 
	}
	
	gotoxy(food.x,food.y); printf("⊙");
} 



/****************************************************************************************************/
// 蛇的移动 
void MovingSnake()
{
	snake *p,*p_front;
		
//1.控制移动方向，也就是改变蛇头坐标 
	int x=head->x;
	int y=head->y;  //标记蛇头坐标
	switch(click)  
	{
		case up: y-=1; break;
		case down: y+=1; break;
		case left: x-=2; break;
		case right: x+=2; break;
		default: break; 
	}
	
//2.在新的方向上，增加一个新的蛇头 
	if(x!=head->x || y!=head->y);  //更严谨，判断是否输入了正确的移动指令 
	{
		p=head;
		snake* new_head=(snake*)malloc(sizeof(snake));
		head=new_head;
		head->x=x;
		head->y=y;    //把新的头坐标放入head中 
		head->next=p; //让新头的next指针指向旧头
		goto_print(head->x,head->y); //把新的头打印出来 
	} 
	
//3.删除蛇尾,free掉 
	p_front=NULL,p=head;  //此处的head是新的头，后面还接着旧的头，所以最少两节，不需要考虑只有一节 
	 
	while(p->next)  //把p指向蛇尾  
	{
		p_front=p;
		p=p->next;  //p指向最后一个，p_front指向倒数第二个 
	}	
	gotoxy(p->x,p->y);
	printf("  ");      //将蛇尾的方块覆盖掉 

	free(p);           //释放链表节点 
	p_front->next=NULL;
	
	HideCursor(); 
} 


/****************************************************************************************************/
//吃到食物
void Eating()
{
	if(head->x==food.x && head->y==food.y) //当头与食物的坐标重叠 
	{
		//1.创造新的食物 
		creatfood();
		
		//2.蛇的身体变长(为链表后面加一项)
		snake* newbody=(snake*)malloc(sizeof(snake));
		snake* p=head;
		while(1) //将p指向旧蛇尾
		{
			if(!p->next) break;
			p=p->next;
		}
		p->next=newbody;    //将其加入蛇的最后一节链表 
		newbody->next=NULL;
		
		//3.将新增的蛇尾打印出来 
		switch(click) //根据运动方向确定新蛇尾的坐标，这种是有问题的：可能和蛇身重合啊 
		{
			case    up: newbody->x=p->x; newbody->y=p->y+1; break;
			case  down: newbody->x=p->x; newbody->y=p->y-1; break;
			case  left: newbody->x=p->x+1; newbody->y=p->y; break;
			case right: newbody->x=p->x-1; newbody->y=p->y; break;
		} 
		goto_print(newbody->x ,newbody->y); 
		
		
		score+=10; 
	} 
}


/****************************************************************************************************/
//判断游戏是否结束 
int Judge()
{
	int ret=1;  //返回值 
	
	// 1.蛇头碰到了墙壁
	if(head->x==0 || head->x==56 || head->y==0 || head->y==26)  
	{
		ret=0;
		return ret;
	}
	
    // 2.蛇头和蛇身相撞
	snake* p=head->next;
	while(1)
	{
		if(p==NULL) break;
		if(head->x==p->x && head->y==p->y)  
		{
			ret=0;
			return ret; 
		}
		p=p->next;
		
	}
	
	return ret;
}



/****************************************************************************************************/
//结束画面 
void Finish()
{
	system("title 游戏结束");
	gotoxy(18,14);
	printf("GAME OVER");
	gotoxy(20,16);
	printf("Your score is %d\n\n\n",score);
	
	snake *p,*q; //释放链表空间  
	for(p=head;p;p=q)
	{
		q=p->next;
		free(p);
	}
	
	system("pause"); 
} 
