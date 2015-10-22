#include <stdio.h>
#include <stdlib.h>

#define m 12   //マス目の数
#define n 50   //上限手数
#define win 4  //勝利条件となる箱数

void gameflow(int **board);
void attack(int **board, int count_turn);
int playerturn(void);
int computer1turn(void);
void showboard(int **board);
void autojudge(int **board,int i,int j);
void widthjudge(int **board, int i, int j ,int pawn);
void heightjudge(int **board, int i, int j ,int pawn);
void Soaring(int **board, int i, int j, int pawn);
void unSoaring(int **board, int i, int j, int pawn);
void winplayer(int pawn);


int main(void)
{
  int i,j=0;

  int **board;
  board = malloc(sizeof(int *)*m);
  for(i=0;i<m;i++)
    board[i] = malloc(sizeof(int)*m);

  for(i=0;i<m;i++){
    for(j=0;j<m;j++)
      board[i][j]=0;
    }
  gameflow(board);
  return 0;
}

void gameflow(int **board)
{
  int i,j=0;
  int count_turn=0;
  while(1){
    if(count_turn >= n){
      printf("上限手数に達したため引き分けとします！\n" );
      exit(0);
      }
    count_turn++;
    printf("******************************************************\n");
    printf("%dターン目です。\n",count_turn);
    showboard(board);
    attack(board,count_turn);
    }
  return;
  }


void attack(int **board , int count_turn)
{
  int x=0;
  int j=0;
  int pawn=0;

  if(count_turn%2==1){
    printf("先手の番です。\n");
    pawn=1;
    }else{
    printf("後手の番です。\n");
    pawn=-1;
    }
  while (1) {
    printf("箱を置く列を指定してください。　：" );
    x=playerturn();
    if(0<=x && x<=11){
      for(j=m-1;j>=0;j--){
        if(board[x][j]==0){
          board[x][j]=pawn;
          widthjudge(board ,x ,j ,pawn);
          heightjudge(board, x, j ,pawn);
          return;
          }
        }
      printf("ERROR!! この列はもう入力できません。\n");
      }
    else
      printf("ERROR!! 0~9,A,Bまでを入力してください。\n");
      }
    }


int playerturn(void)
{
  int i;
  scanf("%x",&i);
  return i;
}


int computer1turn(void)
{
  int i;
  return i;
}


void showboard(int **board)
{
  int i,j=0;
  for(j=0;j<m;j++){
    for(i=0;i<m;i++){
      printf("|");
      if(board[i][j]==0)
        printf(" _ ");
      if(board[i][j]==1)
        printf(" ● ");
      if(board[i][j]==-1)
        printf(" × ");
      }
      printf("|");
      printf("\n");
    }
    return;
}


void widthjudge(int **board, int i, int j, int pawn)
{
  int connect=0;
  //右
  int x=i;
  while(x<i+4){
    if(board[x][j]==pawn)
      connect++;
    x++;
    if(x>=m-1) break;
    if(connect>=win)
      winplayer(pawn);
  }
  //左
  x=i;
  while(x>i-4) {
    if(board[x][j]==pawn)
      connect++;
    x--;
    if(x<=0) break;
  if(connect>=win)
    winplayer(pawn);
  }
  return;
}


void heightjudge(int **board, int i, int j, int pawn)
{
  int connect=0;
  //下
  int y=j;
  while(y<j+4){
    if(board[i][y]==pawn)
      connect++;
    y++;
    if(y>=m-1) break;
    if(connect>=win)
      winplayer(pawn);
  }
  return;
}


void Soaring(int **board, int i, int j, int pawn)
{
  int connect=0;
  //右上
  int x=i;
  int y=j;
  while(x<i+4){
    if(board[x][j]==pawn)
      connect++;
    x++;
    j++;
    if(x>=m-1 || y>=m-1) break;
    if(connect>=win)
      winplayer(pawn);
  }
  //左下
  x=i;
  y=j;
  while(x>i-4) {
    if(board[x][j]==pawn)
      connect++;
    x--;
    y--;
    if(x<=0 || y<=0) break;
    if(connect>=win)
      winplayer(pawn);
  }
  return;
}


void unSoaring(int **board, int i, int j, int pawn)
{
  int connect=0;
  //右下
  int x=i;
  int y=j;
  while(x<i+4){
    if(board[x][j]==pawn)
      connect++;
    x++;
    y--;
    if(x>=m-1 || y<=0) break;
    if(connect>=win)
      winplayer(pawn);
  }
  //左上
  x=i;
  y=j;
  while(x>i-4) {
    if(board[x][j]==pawn)
      connect++;
    x--;
    y++;
    if(x<=0 || y>=m-1) break;
  if(connect>=win)
    winplayer(pawn);
  }
  return;
}


void winplayer(int pawn)
{
  if(pawn==1){
    printf("先手の勝利です！\n");
    }
  if(pawn==-1){
    printf("後手の勝利です！\n");
    }
  exit(1);
}
