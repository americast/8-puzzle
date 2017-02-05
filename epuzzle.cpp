#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
using namespace std;
int no=0;
struct puzzle
{
    int mat[3][3];
    puzzle *next;
}*start;

void display (puzzle *ptr)
{
    cout<<endl;
    for (int i=0;i<3;i++)
    {
      for (int j=0;j<3;j++)
        cout<<" "<<ptr->mat[i][j]<<" ";
      cout<<endl;
    }
}

int distance (int acx, int acy, int x, int y)
{
    return (int)(pow(acx-x,2)+pow(acy-y,2));
}

int goal(puzzle *ptr)
{
    int dist=0, count=1;
    while(count<=8)
    {
        int x,y;
        for (int i=0;i<3;i++)
          for (int j=0;j<3;j++)
            if((ptr)->mat[i][j]==count) {x=i;y=j; break;}
        int acx,acy,cnow=0;
         for (int i=0;i<3;i++)
          for (int j=0;j<3;j++)
            if (count==cnow++) {acx=i;acy=j; break;}
        dist+=distance(acx,acy,x,y);
        count++;
    }
    return dist;
}

int check(puzzle *ptr)
{
    puzzle *ptrtemp=start,*prevptr;
    int flag, tempcount=0;
    while(1)
    {
        if (ptrtemp==NULL)  break;
        flag=1;
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
              if (ptr->mat[i][j]!=ptrtemp->mat[i][j]) {flag=0;break;}
        if (flag==1)
        {
            if (tempcount!=0)
              prevptr->next=NULL;
            else
              start=NULL;
            if (tempcount<no)
              no=tempcount;
            return 0;
        }
        else
        {
            tempcount++;
            prevptr=ptrtemp;
            ptrtemp=ptrtemp->next;
        }
    }
    return 1; // 1 means it had not appeared before...
}

/*int howmuch(int x, int y)
{
    if ((x==0 && y==0) || (x==0 && y==2) || (x==2 && y==2) || (x==2 && y==0)) return 2;
    else if (x==1 && y==1) return 4;
    else return 3;
}*/

void place (puzzle *newp, puzzle *ptr)
{
       for (int i=0;i<3;i++)
          for (int j=0;j<3;j++)
            newp->mat[i][j]=ptr->mat[i][j];
}

void compute (puzzle *ptr)
{
    no++;
    if (goal(ptr)==0)
    {
        puzzle *ptr=start;
        while(1)
        {
            if (ptr==NULL)  break;
            display(ptr);
            ptr=ptr->next;
        }
        cout<<"\nGoal reached! No. of steps: "<<no-1<<endl; exit(0);
    }
    int posx,posy;
    for (int i=0;i<3;i++)
      for (int j=0;j<3;j++)
        if (ptr->mat[i][j]==0) {posx=i;posy=j;break;}
   //int howmuch=where(posx,posy);
    puzzle newp[4], *nowptr=(puzzle*)malloc(sizeof(puzzle)); int count=-1,mind=100;
    if (posx-1>=0 && posx-1<=2)
    {
        count++;
        place(&newp[count],ptr);
        int temp=newp[count].mat[posx][posy];
        newp[count].mat[posx][posy]=newp[count].mat[posx-1][posy];
        newp[count].mat[posx-1][posy]=temp;
        if (goal(&newp[count])<mind && check(&newp[count])!=0)
        {mind=goal(&newp[count]); place(nowptr,&newp[count]);}
    }
    if (posx+1>=0 && posx+1<=2)
    {
        count++;
        place(&newp[count],ptr);
        int temp=newp[count].mat[posx][posy];
        newp[count].mat[posx][posy]=newp[count].mat[posx+1][posy];
        newp[count].mat[posx+1][posy]=temp;
        if (goal(&newp[count])<mind && check(&newp[count])!=0)
        {mind=goal(&newp[count]); place(nowptr,&newp[count]);}
    }
        if (posy-1>=0 && posy-1<=2)
    {
        count++;
        place(&newp[count],ptr);
        int temp=newp[count].mat[posx][posy];
        newp[count].mat[posx][posy]=newp[count].mat[posx][posy-1];
        newp[count].mat[posx][posy-1]=temp;
        if (goal(&newp[count])<mind && check(&newp[count])!=0)
        {mind=goal(&newp[count]); place(nowptr,&newp[count]);}
    }
        if (posy+1>=0 && posy+1<=2)
    {
        count++;
        place(&newp[count],ptr);
        int temp=newp[count].mat[posx][posy];
        newp[count].mat[posx][posy]=newp[count].mat[posx][posy+1];
        newp[count].mat[posx][posy+1]=temp;
        if (goal(&newp[count])<mind && check(&newp[count])!=0)
        {mind=goal(&newp[count]); place(nowptr,&newp[count]);}
    }
    if (mind==100)  
    {
        puzzle *ptr=start;
        while(1)
        {
            if (ptr==NULL)  break;
            display(ptr);
            ptr=ptr->next;
        }
        cout<<"No solution. No of steps: "<<no-1<<endl;exit(0);
    }
    /*for (int k=0;k<howmuch;k++)
      for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
          puzzle[k].mat[i][j]=ptr->mat[i][j];*/
    ptr=start;
    while(1)
    {
        if ((ptr->next)==NULL)  break;
        ptr=ptr->next;
    }
    ptr->next=nowptr;
    ptr=ptr->next;
    ptr->next=NULL;
    compute(ptr);
}

int main()
{
    start=(puzzle*)malloc(sizeof(puzzle));
    start->next=NULL;
    for (int i=0;i<3;i++)
      for (int j=0;j<3;j++)
        cin>>start->mat[i][j];
    compute(start);
}