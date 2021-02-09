#ifndef _SNAKE_H_
#define _SNAKE_H_


#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'





/****************************************************************************************************/
//������һ���µı�������snake�����Ǹ��ṹ���������������Ԫ�� 
typedef struct Snakes{
	int x;
	int y;
	struct Snakes* next;
} snake;


/****************************************************************************************************/
//ȫ�ֱ���
char name[20];
struct Food{    //ʳ��Ľṹ�壬��������������� 
	int x;
	int y;
} food;
snake* head;    //�����ߵ�����ı�ͷ 
int score; 
char click;
int speed;

/****************************************************************************************************/
//�������� 
void gotoxy(int x,int y);  //��ת��ӡ��� 
void menu();  //��ʼ����
void select_difficulty();
void game();  //��Ϸ���к��� 
void goto_print(int x,int y);  //��ת��ӡ 
void creatgraph(); //����Χǽ
void creatsnake(); //����һ����
void creatfood(); //����ʳ��
void MovingSnake(); //�ߵ��ƶ� 
void Eating(); //�Ե�ʳ�� 
int Judge();   //�ж���Ϸ�Ƿ���� 
void Finish();








#endif

