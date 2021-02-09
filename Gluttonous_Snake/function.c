#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<process.h>
#include<windows.h>
#include<conio.h>
#include"snakegame.h"

/****************************************************************************************************/
//���ع��
void HideCursor()  
{
	HANDLE OUTPUT=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor={1,0};
	SetConsoleCursorInfo(OUTPUT,&cursor);
} 


/****************************************************************************************************/
//��ת���
void gotoxy(int x,int y)  
{
	COORD POS;   //windows���涨��Ľṹ�壬��ʾ������� 
	POS.X=x;
	POS.Y=y;
	HANDLE OUTPUT=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(OUTPUT,POS);   //���ƹ��λ�ã������ʽ 
} 


/****************************************************************************************************/
//��ʼ����
void menu()  
{
	system("title ̰���ߣ�����̨�棩[�˵���]"); 
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
	printf("����Ӣ�����뷨�²�����������ƣ�w=up, a=left, s=right, d=down, p��ͣ");
}


/****************************************************************************************************/
//��ת��ӡ���� 
void goto_print(int x,int y)
{
	gotoxy(x,y);
	printf("��");
}


/****************************************************************************************************/

void select_difficulty()
{
	system("title ̰���ߣ�����̨�棩[��Ϸ�Ѷ�ѡ��]"); 
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
//����Χǽ 
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
//����һ���ߣ��õ������������� 
void creatsnake()
{
	snake* p=(snake*)malloc(sizeof(snake));  //������ͷ 
	head=p;   //��headָ����ͷ
	 
	srand((unsigned)time(NULL));
	head->y=(rand()%20)+5;
	head->x=(rand()%45)+10;
	if(head->x%2!=0) //x�������Ƿ�ż��ʱҪ���ż�� 
	{
		head->x+=1;
	}
	head->next=NULL; 
	click=left;
} 


/****************************************************************************************************/
//����ʳ��
void creatfood()
{
	int flag=0;
	
	while(!flag) //ͨ��ѭ��ɸѡ�����ʵ�ʳ������� 
	{
		flag=1;
		
		srand((unsigned)time(NULL)); //�������һ��ʳ�����꣬��ȥ�ж��Ƿ���� 
		food.y=rand()%25+1;
		food.x=rand()%53+2;
		
		if(food.x%2!=0)      // 1. Ҫ�� x Ϊż�� 
		{
			food.x+=1;
		} 
		
		snake* body=head;    // 2.�ж�ʳ�ﲻ�����ߵ�������
		while(body) //ѭ�����������ǵ�������ĩ�� 
		{
			if(food.x==body->x && food.y==body->y)
			{
				flag=0; //���겻�ϸ�
				break;  //�˳���ǰѭ������ѭ���� 
			}
			body=body->next; //��ָ��ָ����һ������ 
		} 
	}
	
	gotoxy(food.x,food.y); printf("��");
} 



/****************************************************************************************************/
// �ߵ��ƶ� 
void MovingSnake()
{
	snake *p,*p_front;
		
//1.�����ƶ�����Ҳ���Ǹı���ͷ���� 
	int x=head->x;
	int y=head->y;  //�����ͷ����
	switch(click)  
	{
		case up: y-=1; break;
		case down: y+=1; break;
		case left: x-=2; break;
		case right: x+=2; break;
		default: break; 
	}
	
//2.���µķ����ϣ�����һ���µ���ͷ 
	if(x!=head->x || y!=head->y);  //���Ͻ����ж��Ƿ���������ȷ���ƶ�ָ�� 
	{
		p=head;
		snake* new_head=(snake*)malloc(sizeof(snake));
		head=new_head;
		head->x=x;
		head->y=y;    //���µ�ͷ�������head�� 
		head->next=p; //����ͷ��nextָ��ָ���ͷ
		goto_print(head->x,head->y); //���µ�ͷ��ӡ���� 
	} 
	
//3.ɾ����β,free�� 
	p_front=NULL,p=head;  //�˴���head���µ�ͷ�����滹���žɵ�ͷ�������������ڣ�����Ҫ����ֻ��һ�� 
	 
	while(p->next)  //��pָ����β  
	{
		p_front=p;
		p=p->next;  //pָ�����һ����p_frontָ�����ڶ��� 
	}	
	gotoxy(p->x,p->y);
	printf("  ");      //����β�ķ��鸲�ǵ� 

	free(p);           //�ͷ�����ڵ� 
	p_front->next=NULL;
	
	HideCursor(); 
} 


/****************************************************************************************************/
//�Ե�ʳ��
void Eating()
{
	if(head->x==food.x && head->y==food.y) //��ͷ��ʳ��������ص� 
	{
		//1.�����µ�ʳ�� 
		creatfood();
		
		//2.�ߵ�����䳤(Ϊ��������һ��)
		snake* newbody=(snake*)malloc(sizeof(snake));
		snake* p=head;
		while(1) //��pָ�����β
		{
			if(!p->next) break;
			p=p->next;
		}
		p->next=newbody;    //��������ߵ����һ������ 
		newbody->next=NULL;
		
		//3.����������β��ӡ���� 
		switch(click) //�����˶�����ȷ������β�����꣬������������ģ����ܺ������غϰ� 
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
//�ж���Ϸ�Ƿ���� 
int Judge()
{
	int ret=1;  //����ֵ 
	
	// 1.��ͷ������ǽ��
	if(head->x==0 || head->x==56 || head->y==0 || head->y==26)  
	{
		ret=0;
		return ret;
	}
	
    // 2.��ͷ��������ײ
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
//�������� 
void Finish()
{
	system("title ��Ϸ����");
	gotoxy(18,14);
	printf("GAME OVER");
	gotoxy(20,16);
	printf("Your score is %d\n\n\n",score);
	
	snake *p,*q; //�ͷ�����ռ�  
	for(p=head;p;p=q)
	{
		q=p->next;
		free(p);
	}
	
	system("pause"); 
} 
