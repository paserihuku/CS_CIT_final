#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define m 12   //マス目の数
#define n 50   //上限手数
#define win 4  //勝利条件となる箱数

void gameflow(int **board);
void attack(int **board, int count_turn);
int playerturn(void);
int computer1turn(void);
void widthjudge(int **board, int i, int j ,int pawn);
void heightjudge(int **board, int i, int j ,int pawn);
void Soaring(int **board, int i, int j, int pawn);
void unSoaring(int **board, int i, int j, int pawn);
void showboard(int **board);
void reachsearch(int **check, int **board, int pawn);
void winplayer(int pawn, int **board);


int main(void)
{
  int i,j=0;
  srand((unsigned)time(NULL));

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
      for(j=0;j<=m-1;j++){
        if(abs(board[x][j])!=1){
          board[x][j]=pawn;
          widthjudge(board ,x ,j ,pawn);
          heightjudge(board, x, j ,pawn);
          Soaring(board ,x ,j ,pawn);
          unSoaring(board ,x ,j ,pawn);
          return;
          }
        }
      printf("ERROR!! この列はもう入力できません。\n");
      }
    else
      printf("ERROR!! 0~9,A(a),B(b)までを入力してください。\n");
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
  i=rand()%11;
  printf("%d\n",i);
  return i;
}


void widthjudge(int **board, int i, int j, int pawn)
{
  int connect=pawn;
  int x=0;
  int **check;
  check = (int **)calloc(win,sizeof(int *));
  for(x=0;x<win;x++)
  check[x] = (int *)calloc(3,sizeof(int));
  //右
  for(x=1;x<=win-1;x++){
    i+=x;
    if(i<=m-1){
      if(board[i][j]==-pawn)
        break;
      connect-=check[x][0];
      check[x][0]=board[i][j];
      check[x][1]=i;
      check[x][2]=j;
      connect+=check[x][0];
      if(connect==pawn*4)
        winplayer(pawn,board);
      if(connect==pawn*3)
        reachsearch(check,board,pawn);
    }
    i-=x;
  }
  //左
  for(x=1;x<=win-1;x++){
    i-=x;
    if(0<=i){
      if(board[i][j]==-pawn)
        break;
      connect-=check[win-x][0];
      check[win-x][0]=board[i][j];
      check[win-x][1]=i;
      check[win-x][2]=j;
      connect+=check[win-x][0];
      if(connect==pawn*4)
        winplayer(pawn,board);
      if(connect==pawn*3)
        reachsearch(check,board,pawn);

    }
    i+=x;
  }
  for(x=0;x<win;x++)
    free(check[x]);
  free(check);
  return;
}


void heightjudge(int **board, int i, int j, int pawn)
{
  int connect=pawn;
  int y=0;
  int **check;
  check = (int **)calloc(win,sizeof(int *));
  for(y=0;y<win;y++)
  check[y] = (int *)calloc(3,sizeof(int));
  //下
  for(y=1;y<=win-1;y++){
    j-=y;
    if(0<=j){
      if(board[i][j]==-pawn)
        break;
      connect-=check[y][0];
      check[y][0]=board[i][j];
      check[y][1]=i;
      check[y][2]=j;
      connect+=check[y][0];
      if(connect==pawn*4)
        winplayer(pawn,board);
      if(connect==pawn*3)
        reachsearch(check,board,pawn);
    }
    j+=y;
  }
  for(y=0;y<win;y++)
    free(check[y]);
  free(check);
  return;
}


void Soaring(int **board, int i, int j, int pawn)
{
  int connect=pawn;
  int x=0;
  int **check;
  check = (int **)calloc(win,sizeof(int *));
  for(x=0;x<win;x++)
  check[x] = (int *)calloc(3,sizeof(int));
  //右上
  for(x=1;x<=win-1;x++){
    i+=x;
    j+=x;
    if(i<=m-1&j<=m-1){
      if(board[i][j]==-pawn)
        break;
      connect-=check[x][0];
      check[x][0]=board[i][j];
      check[x][1]=i;
      check[x][2]=j;
      connect+=check[x][0];
      if(connect==pawn*4)
        winplayer(pawn,board);
      if(connect==pawn*3)
        reachsearch(check,board,pawn);
    }
    i-=x;
    j-=x;
  }
  //左下
  for(x=1;x<=win-1;x++){
    i-=x;
    j-=x;
    if(0<=i&&0<=j){
      if(board[i][j]==-pawn)
        break;
      connect-=check[win-x][0];
      check[win-x][0]=board[i][j];
      check[win-x][1]=i;
      check[win-x][2]=j;
      connect+=check[win-x][0];
      if(connect==pawn*4)
        winplayer(pawn,board);
      if(connect==pawn*3)
        reachsearch(check,board,pawn);

    }
    i+=x;
    j+=x;
  }
  for(x=0;x<win;x++)
    free(check[x]);
  free(check);
  return;
}


void unSoaring(int **board, int i, int j, int pawn)
{
  int connect=pawn;
  int x=0;
  int **check;
  check = (int **)calloc(win,sizeof(int *));
  for(x=0;x<win;x++)
  check[x] = (int *)calloc(3,sizeof(int));
  //右下
  for(x=1;x<=win-1;x++){
    i+=x;
    j-=x;
    if(i<=m-1&&0<=j){
      if(board[i][j]==-pawn)
        break;
      connect-=check[x][0];
      check[x][0]=board[i][j];
      check[x][1]=i;
      check[x][2]=j;
      connect+=check[x][0];
      if(connect==pawn*4)
        winplayer(pawn,board);
      if(connect==pawn*3)
        reachsearch(check,board,pawn);
    }
    i-=x;
    j+=x;
  }
  //左上
  for(x=1;x<=win-1;x++){
    i-=x;
    j+=x;
    if(0<=i&&j<=m-1){
      if(board[i][j]==-pawn)
        break;
      connect-=check[win-x][0];
      check[win-x][0]=board[i][j];
      check[win-x][1]=i;
      check[win-x][2]=j;
      connect+=check[win-x][0];
      if(connect==pawn*4)
        winplayer(pawn,board);
      if(connect==pawn*3)
        reachsearch(check,board,pawn);

    }
    i+=x;
    j-=x;
  }
  for(x=0;x<win;x++)
    free(check[x]);
  free(check);
  return;
}

void reachsearch(int **check, int **board, int pawn)
{
  int i,j,x;
  for(x=1;x<=win-1;x++){
    if(check[x][0]==0)
      board[check[x][1]][check[x][2]]=pawn*10;
  }
  return;
}


void showboard(int **board)
{
  int i,j=0;
  for(j=m-1;j>=0;j--){
    printf("%x ",j);
    for(i=0;i<m;i++){
      printf("|");
      if(board[i][j]==0)
        printf(" _ ");
      if(board[i][j]==1)
        printf(" ● ");
      if(board[i][j]==10)
          printf(" ◎ ");
      if(board[i][j]==-1)
        printf(" × ");
      if(board[i][j]==-10)
        printf(" ※ ");
      }
      printf("|");
      printf("\n");
    }
  printf("   ");
  for(i=0;i<m;i++){
    printf(" %x",i);
    printf("  ");
  }
  printf("\n");
  return;
}


void winplayer(int pawn, int **board)
{
  printf("******************************************************\n");
  showboard(board);
  if(pawn==1){
    printf("先手の勝利です！\n");
    }
  if(pawn==-1){
    printf("後手の勝利です！\n");
    }
  exit(1);
}
