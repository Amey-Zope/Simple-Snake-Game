#include<process.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>


//constants for	keys
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESC 1
#define __CPPARGS

char c,y,n;
struct SnakeParts
{
	int x;
	int y;
}box[50],target;  //snake size and targeted food

//void exitConfirm();
void snake(int ,int);
void initialize(int,int);
void interrupt (*prev)(__CPPARGS);
void interrupt our(__CPPARGS);
void snakeb();
int check();
void Rectangle(int,int,int,int);

int stop=0,blocks=4,direction=2,size=10,hit=1,snake_color=2,bk=13,target_color=4;
int stage=1,speed=100,point=0,k,i;

void main()
{
	char msg[50];
	int gd=DETECT,gm,x=100,y=100,i=0,j=0,x11=1,y11=25;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

	//code for moving text

	while(1)
	{
		clrscr();
		gotoxy(x11,y11);
		setcolor(1);
		settextstyle(1,0,4);
		outtextxy(x11,y11,"Welcome to SNAKE GAME");
		delay(30);
		x11++;

		if(x11>105)
		{
			break;
		}
	}

	sprintf(msg,"S/s: START");
	setcolor(1);
	settextstyle(1,HORIZ_DIR,3);
	outtextxy(250,220,msg);
	sprintf(msg,"Q/q: QUIT");
	setcolor(1);
	settextstyle(1,HORIZ_DIR,3);
	outtextxy(250,270,msg);

	scanf("%c",&c);
	cleardevice();


	switch(c)
	{
		case 's':
		case 'S':
			prev=getvect(9);//interrupt function pointer to save the old keybord routine in old key
			initialize(x,y);
			while(1)
			{
				switch(direction)
				{
					case 0: j=j-size;
							break;

					case 1: j=j+size;
							break;

					case 2:	i=i+size;
							break;

					case 3: i=i-size;
							break;
				}
				setcolor(snake_color);
				snake(x+i,y+j);
				delay(speed);
				setcolor(bk);
				snakeb();
				setvect(9,our); //replace the original keyboard functionaliry with new one
				if(stop==1)
				{
					break;
				}
				if(check())
				{
					break;
				}
				if(hit==1)
				{
					hit=0;
					target.x=size+size*random(30);
					target.y=size+size*random(30);
					setcolor(target_color);
					setfillstyle(SOLID_FILL,target_color);
					circle(target.x+size/2,target.y+size/2,size/2-1);
					floodfill(target.x+size/2,target.y+size/2,target_color);
				}
				setfillstyle(SOLID_FILL,target_color);
				setcolor(2);
				circle(target.x+size/2,target.y+size/2,size/2-1);
				floodfill(target.x+size/2,target.y+size/2,2);
				gotoxy(65,3);
				printf("SCORE = %3d",point);
				setcolor(1);
				settextstyle(6,HORIZ_DIR,1);
				sprintf(msg,"Use Esc to Exit");
				outtextxy(500,420,msg);
				sprintf(msg,"Use directional keys to navigate");
				outtextxy(375,445,msg);
				setcolor(0);
				sprintf(msg,"STAGE: %d",stage);
				outtextxy(50,445,msg);
			}
			break;
		case 'q':
		case 'Q':
				exit(1);
				break;
		}

		closegraph();
}

void interrupt our(__CPPARGS)
{
		  switch(inportb(0x60))
		  {
				 case UP: if(direction==1)break;direction=0;break;
				 case DOWN: if(direction==0)break;direction=1;break;
				 case RIGHT: if(direction==3)break;direction=2;break;
				 case LEFT: if(direction==2)break;direction=3;break;
				 case ESC:	stop=1;
							break;
		   }

		  (*prev)();
}

void snake(int x1,int y1)
{
		 int k=0;
		 for(k=blocks;k>0;k--)
		 {
			box[k].x=box[k-1].x;
			box[k].y=box[k-1].y;
		 }
		 box[0].x=x1;
		 box[0].y=y1;
		 for(k=0;k<blocks;k++)
		 {
				 Rectangle(box[k].x,box[k].y,box[k].x+size,box[k].y+size);

		 }

}

void snakeb()
{
		 for(k=0;k<blocks;k++)
		 {
				 Rectangle(box[k].x,box[k].y,box[k].x+size,box[k].y+size);
		 }
}

void initialize(int x,int y)
{
		 setcolor(bk);
		 rectangle(0,0,639,479);
		 setfillstyle(SOLID_FILL,bk);
		 floodfill(250,250,bk);
		 box[0].x=x;
		 box[0].y=y;
		 for(i=1;i<blocks;i++)
		 {
				 box[i].x=x-size*i;
				 box[i].y=y;
		 }
}

int check()
{
		 int i;
		 char msg[50];
		 //	condition when snake reches the wall
		 if(!(box[0].x>=0 && box[0].x<=639 && box[0].y>=0 && box[0].y<=479))
		 {
				 for(i=100;i<900;i+=100)
				 {
					sound(i);
					delay(100);
					nosound();
				 }
				 sprintf(msg,"GAME OVER");
				 setcolor(4);
				 settextstyle(1,HORIZ_DIR,6);
				 outtextxy(150,200,msg);
				 delay(3000);
				 cleardevice();
				 return 1;
		 }
		 for(i=1;i<blocks;i++)
		 {
				 if(box[0].x==box[i].x && box[0].y==box[i].y)
				 {
					for(i=900;i>=100;i-=100)
					{
						sound(i);
						delay(100);
						nosound();
					}
					sprintf(msg,"GAME OVER");
					setcolor(4);
					settextstyle(1,HORIZ_DIR,6);
					outtextxy(150,200,msg);
					delay(3000);
					cleardevice();
					return 1;
				 }
		 }
		 if(box[0].x==target.x && box[0].y==target.y)
		 {
				 sound(500); //sound after getting the food
				 delay(100);
				 nosound();
				 blocks++;
				 point++;
				 hit=1;
				 setcolor(bk);
				 setfillstyle(SOLID_FILL,bk);
				 setcolor(bk);
				 circle(target.x+size/2,target.y+size/2,size/2-1);
				 floodfill(target.x+size/2,target.y+size/2,bk);
		 }
		 if(blocks==30)
		 {
				 stage++;
				 blocks=4;
				 sprintf(msg,"STAGE %d CLEARED",stage-1);
				 outtextxy(120,200,msg);
				 setcolor(4);
				 settextstyle(1,HORIZ_DIR,6);
				 outtextxy(150,200,msg);
				 delay(2000);
				 cleardevice();
				 initialize(100,100);
				 speed=100/stage;    //will decrese the delay
		 }
		 return 0;
}

void Rectangle(int x1,int y1,int x2,int y2)
{
		 for(i=0;i<size/2;i++)
				 rectangle(x1+i,y1+i,x2-i,y2-i);
}