#include <stdio.h>

#define SIZE 64
#define LEN 8
#define COUNT_W 8
#define DOWN_NUM 10

#define SWAP(a,b,t)     t=a;  \
                        a=b;  \
                        b=t;

struct Pos
{
  short int x;
  short int y;
};

struct Pos Pos(short x,short y)
{
  struct Pos temp;
  temp.x = x;
  temp.y = y;
  return temp;
}

short int absolute(short int num)
{
  return (num < 0) ? -num : num;
}

short int chessHorse(struct Pos cur,short int k,short int*chessBoard)
{
  short int i,j,t,count[COUNT_W] = {0};
  struct Pos walks[COUNT_W] = {{-1,-2},{1,-2},
                               {2,-1},{2,1},
                               {1,2},{-1,2},
		                           {-2,1},{-2,-1}};
  struct Pos temp1,temp2;
  chessBoard[cur.y*LEN+cur.x] = k;
  if(k == SIZE) return 1;
/*    --- === Counting === ---    */
  for(i = 0; i < COUNT_W; i++)
  {
    temp1 = Pos(cur.x+walks[i].x,cur.y+walks[i].y);
    if(temp1.x < 0 || temp1.x >= LEN){count[i]=DOWN_NUM;continue;}
    if(temp1.y < 0 || temp1.y >= LEN){count[i]=DOWN_NUM;continue;}
    if(chessBoard[temp1.y*LEN+temp1.x]==0)
    {
      for(j = 0; j < COUNT_W; j++)
      {
        temp2 = Pos(temp1.x+walks[j].x,temp1.y+walks[j].y);
        if(temp2.x < 0 || temp2.x >= LEN) continue;
        if(temp2.y < 0 || temp2.y >= LEN) continue;
        if(chessBoard[temp2.y*LEN+temp2.x]==0)count[i]++;
      }
    }
    else
      count[i] = DOWN_NUM;
  }
/*    --- === Sorting === ---    */
  for(i = 0; i < COUNT_W; i++)
  {
    for(j = 0; j < (COUNT_W - i - 1); j++)
    {
      if(count[j] > count[j+1])
      {
        SWAP(count[j],count[j+1],t)
        SWAP(walks[j],walks[j+1],temp2)
      }
      else if(count[j] == count[j+1])
      {
        temp1 = Pos(cur.x+walks[j].x,cur.y+walks[j].y);
        temp2 = Pos(cur.x+walks[j+1].x,cur.y+walks[j+1].y);

        if((absolute(temp1.x*2-(LEN-1)) + absolute(temp1.y*2-(LEN-1))) < (absolute(temp2.x*2-(LEN-1)) + absolute(temp2.y*2-(LEN-1))))
        {
          SWAP(count[j],count[j+1],t)
          SWAP(walks[j],walks[j+1],temp2)
        }
      }
    }
  }
/*    --- === Main logic === ---    */
  for(i = 0; i < COUNT_W; i++)
  {
    if(count[i] == DOWN_NUM) continue;
    if(chessHorse(Pos(cur.x+walks[i].x,cur.y+walks[i].y),k+1,chessBoard))
      return 1;
  }
  chessBoard[cur.y*LEN+cur.x] = 0;
  return 0;
}

int
main(void)
{
  short int chessBoard[SIZE] = {0};
  short int i=0,j=0;
  printf("Enter the position horse (fomat: a1): ");
  if(scanf("%c%c",(char*)&i,(char*)&j) !=2 )
  {
    printf("BAD input\n");
    return 1;
  }
  i-=97;j-=49;
  if((i<0||i>7) || (j<0||j>7))
  {
    printf("BAD value x = %d;y = %d\n",i,j);
    return 1;
  }
  chessHorse(Pos(i,j),1,chessBoard);

  for(i = 0; i < LEN; i++)
  {
    for(j = 0; j < LEN; j++)
      printf("%02d  ",chessBoard[i*LEN+j]);
    putchar('\n');
  }
  return 0;
}
