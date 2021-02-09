#define WIN 5
#define SIZE 10
#define DEBUG 0 


void initgame(char board[SIZE][SIZE],int x,int y);

int row(char board[SIZE][SIZE],int x,int y);
int column(char board[SIZE][SIZE],int x,int y);
int diagonal(char board[SIZE][SIZE],int x,int y);
int back_diagonal(char board[SIZE][SIZE],int x,int y);
char referee(char board[SIZE][SIZE],int x,int y);

void display(char board[SIZE][SIZE],int x,int y);
char turn(int cont);

