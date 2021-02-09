#ifndef _SNAKE_H_
#define _SNAKE_H_


#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'





/****************************************************************************************************/
//声明了一种新的变量叫作snake，这是个结构体变量（单向链表单元） 
typedef struct Snakes{
	int x;
	int y;
	struct Snakes* next;
} snake;


/****************************************************************************************************/
//全局变量
char name[20];
struct Food{    //食物的结构体，包含了事物的坐标 
	int x;
	int y;
} food;
snake* head;    //代表蛇的链表的表头 
int score; 
char click;
int speed;

/****************************************************************************************************/
//函数声明 
void gotoxy(int x,int y);  //跳转打印光标 
void menu();  //开始界面
void select_difficulty();
void game();  //游戏进行函数 
void goto_print(int x,int y);  //跳转打印 
void creatgraph(); //创造围墙
void creatsnake(); //创造一条蛇
void creatfood(); //创造食物
void MovingSnake(); //蛇的移动 
void Eating(); //吃到食物 
int Judge();   //判断游戏是否结束 
void Finish();








#endif

