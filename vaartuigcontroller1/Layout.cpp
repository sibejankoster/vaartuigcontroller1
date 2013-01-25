#include "Layout.h"
#include "Opdracht.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>

void gotoxy( int x, int y )
{ COORD p = { x, y };
  SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

Window::Window(int x1, int y1, int x2, int y2)
	: x1(x1), y1(y1),x2(x2),y2(y2)
{}

void Window::erase()
{  int i,j;
   gotoxy(x1,y1);
   std::cout<<"+";
   for (i=x1;i<=x2;i++) std::cout<<"-"; //bovenkader 
   std::cout<<"+";
   for (j=y1;j<y2;j++)
   { gotoxy(x1,j+1);
     std::cout<<"|";
     for (i=x1;i<=x2;i++) std::cout<<" "; //body 
     std::cout<<"|";
   }
   gotoxy(x1,y2);
   std::cout<<"+";
   for (i=x1;i<=x2;i++) std::cout<<"-"; //onderkader 
   std::cout<<"+";
}

void Window::print(std::string* A)
{  Window::erase();
   for (int i=0;i<=(y2-y1)&&A[i]!= "einde";i++) // aan het einde van iedere outputarray moet "einde" staan
   {  gotoxy(x1+2,y1+i+2); 
	  std::cout<<A[i];
   }
}

