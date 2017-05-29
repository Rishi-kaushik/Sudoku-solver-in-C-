//*****************************************************************
//*********** This program inputs a sudoku puzzle and  ************
//***********   gives out its solution. This is the    ************
//*********** final version of the program so it can   ************
//*********** solve even the hardest 9*9 sudoku puzzle ************
//*****************************************************************
//*******************                           *******************
//*******************  MADE BY - RISHI KAUSHIK  *******************
//*******************  rishik1234@hotmail.com   *******************
//*******************---------------------------*******************
//*******************    Start - 9 march 2015   *******************
//*******************   Finish - 25 march 2015  *******************
//*****************************************************************
//******* This is an open source program you may use, edit ********
//*****************************************************************

#include<iostream.h>
#include<math.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>


//-----------------------------------------(global variables)
unsigned char bord[10][37][19];
int flag;
int diff;
int x,y,z,X,Y;
int count;
int biginer=1,hilight=1,dice=1,boo=1,boom=-1;

//-----------------------------------------(functions)

int clear();   // <--- clear useless possibilities
int slice();   // <--- Slice & dice (human simulated)
int bcr();     // <--- Block Row Collum check (suduko definiung rule)
int solve();   // <--- Solve ahead (fill nums)
int ghost();   // <--- Ghost number (human simulated)
int force();   // <--- last resort ie. brute force(program is reluctant to use it)

//-----------------------------------------(main function)
void main()
{
clrscr();
unsigned char input,load=219; //---variables
int px=18,py=9,lx=px,ly=py;
cout<<"\n\n\n\n\n\n\n";
cout<<"                         *******************************\n";
cout<<"                         ******* PROJECT SUDOKU ********\n";
cout<<"                         *******************************";
cout<<"\n\n\n";
for(x=0;x<80;++x)
{
	delay(20);
	cout<<load;
}
clrscr();
for(;input!=13;)
{
	if(input==27 ||input==8)exit(0);
	clrscr();
	cout<<"\n\n\n______________________________________________________________________________\n\n";
	cout<<"\n\n              1)  Sudoku's defining rule                  ";
	if(biginer==1)cout<<"Use";
	else cout<<"Don't Use";
	cout<<"\n\n              2)  Slice n' Dice                           ";
	if(dice==1)cout<<"Use";
	else cout<<"Don't Use";
	cout<<"\n\n              3)  Ghost number method                     ";
	if(boo==1)cout<<"Use";
	else cout<<"Don't Use";
	cout<<"\n\n              4)  Brute Force                             ";
	if(boom==1)cout<<"Use";
	else cout<<"Don't Use";
	cout<<"\n\n              5)  Highlight initial values                ";
	if(hilight==1)cout<<"Use";
	else cout<<"Don't Use";
	cout<<"\n\n\n______________________________________________________________________________\n\n";
	cout<<"                 Press respictive number to change settings\n\n";
	input=getch();
	if(input=='1')biginer=-biginer;
	if(input=='2')dice=-dice;
	if(input=='3')boo=-boo;
	if(input=='4')boom=-boom;
	if(input=='5')hilight=-hilight;
}
for(y=0;y<19;y++)                 //---making bord layout
{
	for(x=0;x<37;x++)
	{
		bord[0][x][y]=' ';
		if(x%4==0)bord[0][x][y]=179;
		if(y%2==0)bord[0][x][y]=196;
		if(y%6==0)bord[0][x][y]=205;
		if(x%12==0)bord[0][x][y]=186;
		if(x%4==0 && y%2==0)bord[0][x][y]=197;
		if(x%12==0 && y%6==0)bord[0][x][y]=206;
		if(x%12!=0 && x%4==0 && y%6==0)bord[0][x][y]=216;
		if(x%12==0 && y%6!=0 && y%2==0)bord[0][x][y]=215;
		if(y==0 && x%4==0)bord[0][x][y]=209;
		if(y==18 && x%4==0)bord[0][x][y]=207;
		if(y%2==0 && x==0)bord[0][x][y]=199;
		if(y%2==0 && x==36)bord[0][x][y]=182;
		if(y==0 && x%12==0)bord[0][x][y]=203;
		if(y==18 && x%12==0)bord[0][x][y]=202;
		if(y%6==0 && x==0)bord[0][x][y]=204;
		if(y%6==0 && x==36)bord[0][x][y]=185;
	}
}
bord[0][0][0]=201;     //---corners
bord[0][36][18]=188;
bord[0][36][0]=187;
bord[0][0][18]=200;
for(;;)
{
	clrscr();
	if((ly-1)%6==0)bord[0][lx][ly-1]=205;
	else bord[0][lx][ly-1]=196;
	if((ly+1)%6==0)bord[0][lx][ly+1]=205;
	else bord[0][lx][ly+1]=196;
	if((lx+2)%12==0)bord[0][lx+2][ly]=186;
	else bord[0][lx+2][ly]=179;
	if((lx-2)%12==0)bord[0][lx-2][ly]=186;
	else bord[0][lx-2][ly]=179;
	lx=px;
	ly=py;
	bord[0][px][py-1]=30;
	bord[0][px+2][py]=16;
	bord[0][px-2][py]=17;
	bord[0][px][py+1]=31;
//-------------------------------------------(Display)
	cout<<"\n\n		      ";
	for(y=0;y<19;y++)
	{
		for(x=0;x<37;x++)
		{
			cout<<bord[0][x][y];
		}
		cout<<"\n                      ";
	}
//------------------------------------------(input)
	input=getch();
	if(input==72)   py-=2;
	if(input==75)   px-=4;
	if(input==77)   px+=4;
	if(input==80)   py+=2;
	if(input==27 || input==8)exit(0);
	if(input=='x')bord[0][px][py]=' ';
	if(input>48 && input<58)bord[0][px][py]=input;
	if(input==13)break;
	if(px<0 || px>36 || py<0 || py>18)
	{
		px=lx;
		py=ly;
	}
}
if(hilight==1)
{
	for(y=1;y<19;y+=2)
	{
		for(x=2;x<37;x+=4)
		{
			if(bord[0][x][y]!=' ')
			{
				bord[0][x+1][y]=')';
				bord[0][x-1][y]='(';
			}
		}
	}
}
//--------------------- SOLVING BOARD -----------------------
for(y=1;y<19;y+=2)
{
	for(x=2;x<37;x+=4)
	{
		for(z=1;z<10;++z)
		{
			bord[z][x][y]=1;
		}
	}
}
flag=1;
for(;flag==1;)
{
	for(;flag==1;) // <--- go through the bord many times (till we get new things)
	{
		diff++;
		flag=0;       // <--- flag that if we found anything new? (0 = no)
		/*solving process*/
		clear();
		if(biginer==1)bcr();
		solve();
		clear();
		if(dice==1)slice();
		clear();
		if(boo==1)ghost();
		solve();
	}
	for(y=1;y<19;y+=2)
	{
		for(x=2;x<37;x+=4)
		{
			if(bord[0][x][y]==' ')
			{
				flag=1;
			}
		}
	}
	if(flag==1)
	{
		flag=0;
		if(boom==1)force();
	}
}
clrscr();     // <--- now we display what we calculated
if((py-1)%6==0)bord[0][px][py-1]=205;
else bord[0][px][py-1]=196;
if((py+1)%6==0)bord[0][px][py+1]=205;
else bord[0][px][py+1]=196;
if((px+2)%12==0)bord[0][px+2][py]=186;
else bord[0][px+2][py]=179;
if((px-2)%12==0)bord[0][px-2][py]=186;
else bord[0][px-2][py]=179;
cout<<"\n\n		      ";
for(y=0;y<19;y++)
{
	for(x=0;x<37;x++)
	{
		cout<<bord[0][x][y];
	}
	cout<<"\n                      ";
}
cout<<"\n                                 Difficulty ="<<diff;
getch();
}    // <---------------------- MAIN ENDES --------------------

int clear()
{
	int X,Y,z;
	for(Y=1;Y<19;Y+=2)   // <--- one time travel the bord
	{
		for(X=2;X<37;X+=4)
		{
			if(bord[0][X][Y]!=' ')// <--- if the cell is filled
			{
				for(z=1;z<10;++z)
				{
					if(z!=(bord[0][X][Y]-48))
					{
						bord[z][X][Y]=0;
					}
				}
			}
		}
	}
	return 0;
}

int bcr()
{
	int pres[10];
	for(y=1;y<19;y+=2)   // <--- one time travel the bord
	{
		for(x=2;x<37;x+=4)
		{
			if(bord[0][x][y]==' ')      // <--- if the cell (display)
			{         //      is empty (to be filled)
				for(X=2;X<37;X+=4)
				{
					if(bord[0][X][y]!=' ' && bord[bord[0][X][y]-48][x][y]==1)
					{
						z=bord[0][X][y]-48;
						bord[z][x][y]=0;
						flag=1;
					}
				}
				for(Y=1;Y<19;Y+=2)
				{
					if(bord[0][x][Y]!=' ' && bord[bord[0][x][Y]-48][x][y]==1)
					{
						z=bord[0][x][Y]-48;
						bord[z][x][y]=0;
						flag=1;
					}
				}
			}
		}
	}
	for(x=2;x<37;x+=12)
	{
		for(y=1;y<19;y+=6)
		{
			for(X=0;X<10;X++)
			{
				pres[X]=0;
			}
			for(X=x;X<x+12;X+=4)
			{
				for(Y=y;Y<y+6;Y+=2)
				{
					if(bord[0][X][Y]!=' ')
					{
						pres[bord[0][X][Y]-48]=1;
					}
				}
			}
			for(z=1;z<10;z++)
			{
				if(pres[z]==1)
				{
					for(X=x;X<x+12;X+=4)
					{
						for(Y=y;Y<y+6;Y+=2)
						{
							if(bord[z][X][Y]==1 && bord[0][X][Y]==' ')
							{
								bord[z][X][Y]=0;
								flag=1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

int solve()
{
	for(y=1;y<19;y+=2)   // <--- fill with the knowledge of what we cant fill
	{
		for(x=2;x<37;x+=4)
		{
			if(bord[0][x][y]==' ')
			{
				for(Y=0,z=1;z<10;++z)
				{
					if(bord[z][x][y]==1)
					{
						Y++; // <--- from here on 'Y' is the no of possible enteries
					}
				}
				if(Y==1)   // <--- if only one possible entery (found one!!!)
				{
					for(z=1;z<10;++z)  // <--- now what was the entery?
					{
						if(bord[z][x][y]==1)   // <--- this one!!!
						{
							bord[0][x][y]=z+48;
							flag=1; // <--- set the flag because we found some thing new
						}               // <--- this means its worth checking again
					}
				}
			}
		}
	}
	return 0;
}

int slice()
{
	for(y=1;y<19;y+=2)   // <--- one time travel the bord
	{
		for(z=1;z<10;z++)
		{
			count=0;
			for(x=2;x<37;x+=4)
			{
				if(bord[z][x][y]==1)
				{
					count+=1;
				}
			}
			if(count==1)
			{
				for(x=2;x<37;x+=4)
				{
					if(bord[z][x][y]==1 && bord[0][x][y]==' ')
					{
						bord[0][x][y]=z+48;
						flag=1;
						break;
					}
				}
			}
		}
	}
	for(x=2;x<37;x+=4)   // <--- one time travel the bord
	{
		for(z=1;z<10;z++)
		{
			count=0;
			for(y=1;y<19;y+=2)
			{
				if(bord[z][x][y]==1)
				{
					count+=1;
				}
			}
			if(count==1)
			{
				for(y=1;y<19;y+=2)
				{
					if(bord[z][x][y]==1 && bord[0][x][y]==' ')
					{
						bord[0][x][y]=z+48;
						flag=1;
						break;
					}
				}
			}
		}
	}
	for(x=2;x<37;x+=12)
	{
		for(y=1;y<19;y+=6)
		{
			for(z=1;z<10;z++)
			{
				count=0;
				for(X=x;X<x+12;X+=4)
				{
					for(Y=y;Y<y+6;Y+=2)
					{
						if(bord[z][X][Y]==1)
						{
							count++;
						}
					}
				}
				if(count==1)
				{
					for(X=x;X<x+12;X+=4)
					{
						for(Y=y;Y<y+6;Y+=2)
						{
							if(bord[z][X][Y]==1 && bord[0][X][Y]==' ')
							{
								bord[0][X][Y]=z+48;
								flag=1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

int ghost()
{
int hori,vert;
	for(x=2;x<37;x+=12)
	{
		for(y=1;y<19;y+=6)
		{
			for(z=1;z<10;z++)
			{
				hori=0;
				vert=0;
				for(X=x;X<x+12;X+=4)
				{
					if(bord[z][X][y]==1 || bord[z][X][y+2]==1 || bord[z][X][y+4]==1)
					{
						vert++;
					}
				}
				for(Y=y;Y<y+6;Y+=2)
				{
					if(bord[z][x][Y]==1 || bord[z][x+4][Y]==1 || bord[z][x+8][Y]==1)
					{
						hori++;
					}
				}
				if(hori==1)
				{
					for(Y=y;Y<y+6;Y+=2)
					{
						if(bord[z][x][Y]==1 || bord[z][x+4][Y]==1 || bord[z][x+8][Y]==1)
						{
							for(X=2;X<37;X+=4)
							{
								if(X!=x && X!=x+4 && X!=x+8 && bord[z][X][Y]==1)
								{
									bord[z][X][Y]=0;
									flag=1;
								}
							}
						}
					}
				}
				if(vert==1)
				{
					for(X=x;X<x+12;X+=4)
					{
						if(bord[z][X][y]==1 || bord[z][X][y+2]==1 || bord[z][X][y+4]==1)
						{
							for(Y=1;Y<19;Y+=2)
							{
								if(Y!=y && Y!=y+2 && Y!=y+4 && bord[z][X][Y]==1)
								{
									bord[z][X][Y]=0;
									flag=1;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

int force()
{
int c,mflag=0,tot;
unsigned char copy[9][10][9][9],backup[10][9][9];
	for(z=0;z<10;z++)
	{
		for(y=0;y<9;y++)
		{
			for(x=0;x<9;x++)
			{
				backup[z][x][y]=bord[z][(x*4)+2][(y*2)+1];
				for(c=0;c<9;c++)
				{
					copy[c][z][x][y]=backup[z][x][y];
				}
			}
		}
	}
	for(y=0;y<9;y++)
	{
		for(x=0;x<9;x++)
		{
			if(backup[0][x][y]==' ')
			{
				tot=0;
				for(z=1;z<10;z++)
				{
					if(backup[z][x][y]==1)
					{
						copy[tot][0][x][y]=z+48;
						tot++;
					}
				}
				for(c=0;c<tot;++c)
				{
					for(z=0;z<10;z++)
					{
						for(Y=0;Y<9;Y++)
						{
							for(X=0;X<9;X++)
							{
								bord[z][(X*4)+2][(Y*2)+1]=copy[c][z][X][Y];
							}
						}
					}
					for(flag=1;flag==1;) // <--- go through the bord many times (till we get new things)
					{
						++diff;
						flag=0;       // <--- flag that if we found anything new? (0 = no)
						  clear();
						if(biginer==1)bcr();
						  solve();
						  clear();
						if(dice==1)slice();
						  clear();
						if(boo==1)ghost();
						  solve();
						  clear();
					}
					for(z=0;z<10;z++)
					{
						for(Y=0;Y<9;Y++)
						{
							for(X=0;X<9;X++)
							{
								copy[c][z][X][Y]=bord[z][(X*4)+2][(Y*2)+1];
							}
						}
					}
				}
				for(Y=0;Y<9;Y++)
				{
					for(X=0;X<9;X++)
					{
						for(z=1;z<10;z++)
						{
							count=0;
							for(c=0;c<tot;c++)
							{
								if(copy[c][z][X][Y]!=0)count=1;
							}
							if(count==0 && backup[z][X][Y]==1)
							{
								backup[z][X][Y]=0;
								mflag=1;
							}
						}
					}
				}
			}
		}
	}
	for(z=0;z<10;z++)
	{
		for(y=0;y<9;y++)
		{
			for(x=0;x<9;x++)
			{
				bord[z][(x*4)+2][(y*2)+1]=backup[z][x][y];
			}
		}
	}
	flag=mflag;
	return 0;
}