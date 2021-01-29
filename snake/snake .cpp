#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define R 7
#define r 7
#define u 100
#define Long 700
#define wide 560

void snake(int *pc,int horizontal[],int vretical[],int g)
{
	for(int i=1;i<=*pc;i++)
	{
		setfillcolor(RED);
		setlinecolor(WHITE);
		fillrectangle(horizontal[g-*pc+i]-r,vretical[g-*pc+i]-r,horizontal[g-*pc+i]+r,vretical[g-*pc+i]+r);
	}
}
void clean_snake(int *pc,int horizontal[],int vretical[],int g)
{
	clearrectangle(horizontal[g-*pc]-r,vretical[g-*pc]-r,horizontal[g-*pc]+r,vretical[g-*pc]+r);
}
void lose()
{
	cleardevice();
	settextstyle(Long/4, 0, _T("宋体"));
    outtextxy(Long/4, wide/4, _T("失败"));
}
void win()
{
	cleardevice();
    settextstyle(Long/4, 0, _T("宋体"));
    outtextxy(Long/4, wide/4, _T("成功"));
}
void horizontal_move(int horizontal[],int vretical[],int g,int m,int *pc,int*pe,int*pf,int *pp)
{
	horizontal[g]=horizontal[g-1]+m;
	vretical[g]=vretical[g-1];
	if(fabs(horizontal[g]-*pe)<r&&fabs(vretical[g]-*pf)<r)
	{
		*pc=*pc+1;
    	*pe=rand()%((Long-4*r)/(2*r))+1;
        *pe=*pe*2*r-r;
	    *pf=rand()%((wide-4*r)/(2*r))+1;
       	*pf=*pf*2*r-r;
        setfillcolor(RED);
        solidcircle(*pe,*pf,R);
	}
	if(horizontal[g]>Long-r||horizontal[g]<r||vretical[g]>wide-r||vretical[g]<r)
	{
	     *pp+=1;
	}
	for(int i=1;i<*pc;i++)
	{
		if(horizontal[g]==horizontal[g-i]&&vretical[g]==vretical[g-i])
		{
			*pp+=1;
		}
	}
	if(*pc>25)
	{
		*pp+=2;
	}
    snake(pc, horizontal,vretical,g);
}
void vretical_move(int horizontal[],int vretical[],int g,int m,int *pc,int*pe,int*pf,int *pp)
{
	horizontal[g]=horizontal[g-1];
	vretical[g]=vretical[g-1]+m;
	if(fabs(horizontal[g]-*pe)<r&&fabs(vretical[g]-*pf)<r)
	{
		*pc=*pc+1;
    	*pe=rand()%((Long-4*r)/(2*r))+1;
        *pe=*pe*2*r-r;
	    *pf=rand()%((wide-4*r)/(2*r))+1;
       	*pf=*pf*2*r-r;
        setfillcolor(RED);
        solidcircle(*pe,*pf,R);
	}
	if(horizontal[g]>Long-r||horizontal[g]<r||vretical[g]>wide-r||vretical[g]<r)
	{
	     *pp+=1;
	}
	for(int i=1;i<*pc;i++)
	{
		if(horizontal[g]==horizontal[g-i]&&vretical[g]==vretical[g-i])
		{
			*pp+=1;
		}
	}
	if(*pc>25)
	{
		*pp+=2;
	}
    snake(pc,horizontal, vretical,g);
}
void main()
{
	initgraph(Long,wide);
	int a,b,e,f,g,n,t=0,c=1,p=1;
	int horizontal[100000],vretical[100000];
	char direction[10000];
	srand((unsigned)time(NULL));
	a=rand()%((Long/2-4*r)/(2*r))+1;
	a=a*2*r-r;
	b=rand()%((wide/2-4*r)/(2*r))+1;
	b=b*2*r-r;
	e=rand()%((Long-4*r)/(2*r))+1;
	e=e*2*r-r;
	f=rand()%((wide-4*r)/(2*r))+1;
	f=f*2*r-r;
	setfillcolor(RED);
	solidcircle(e,f,R);
	horizontal[0]=a;
	vretical[0]=b;
    snake(&c, horizontal,vretical,0);
	for(g=1;;g++)
	{
		horizontal_move(horizontal,vretical,g,2*r,&c,&e,&f,&p);
		if(p>1)
			break;
		clean_snake(&c, horizontal,vretical, g);
		Sleep(u);
		if(kbhit())
		{
			direction[t]=getch();
			if(direction[t]=='s'||direction[t]=='w'||direction[t]==27)
			{}
			else
			{
				continue;
			}
			for(;;)
			{   
			if(direction[t]=='a')
			{
				for(n=g+1;;n++)
				{
					horizontal_move(horizontal,vretical,n,-2*r,&c,&e,&f,&p);
					if(p>1)
			            break;
	            	clean_snake(&c, horizontal,vretical, n);
					Sleep(u);
					if(kbhit())
					{
						t=t+1;
						direction[t]=getch();
						if(direction[t]=='s'||direction[t]=='w'||direction[t]==27)
						{
							g=n;
						    break;
						}
						continue;
					}
				}
				if(p>1)
			            break;
			}
			if(direction[t]=='d')
			{
				for(n=g+1;;n++)
				{	
					horizontal_move(horizontal,vretical,n,2*r,&c,&e,&f,&p);
					if(p>1)
			            break;
	            	clean_snake(&c, horizontal,vretical, n);
					Sleep(u);
					if(kbhit())
					{
						t=t+1;
						direction[t]=getch();
						if(direction[t]=='s'||direction[t]=='w'||direction[t]==27)
						{
							g=n;
						    break;
						}
			            continue;
					}

				}
				if(p>1)
			            break;
			}
			if(direction[t]=='w')
			{
				for(n=g+1;;n++)
				{
					vretical_move(horizontal,vretical,n,-2*r,&c,&e,&f,&p);
					if(p>1)
			            break;
	            	clean_snake(&c, horizontal, vretical, n);
					Sleep(u);
					if(kbhit())
					{
						t=t+1;
						direction[t]=getch();
						if(direction[t]=='a'||direction[t]=='d'||direction[t]==27)
						{
							g=n;
						    break;
						}
						continue;
						
					}
				}
				if(p>1)
			            break;
			}
			if(direction[t]=='s')
			{
				for(n=g+1;;n++)
				{
					vretical_move(horizontal,vretical,n,2*r,&c,&e,&f,&p);
					if(p>1)
			            break;
	            	clean_snake(&c,horizontal,vretical, n);
					Sleep(u);
					if(kbhit())
					{
						t=t+1;
						direction[t]=getch();
						if(direction[t]=='a'||direction[t]=='d'||direction[t]==27)
						{
							g=n;
						    break;
						}
					    continue;
						
					}
				}
				if(p>1)
			        break;
			}
			}
			if(direction[t]==27)
			    break;
	    	if(p>1)
	            break;
		}
	}
	if(p==2)
        lose();
	if(p==3)
		win();
	getch();
	closegraph();
}
