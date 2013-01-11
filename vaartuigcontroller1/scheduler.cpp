//
//
//  @ Project : vaartuigcontroller
//  @ File Name : main.h
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
//#include <boost/thread.hpp>
#include "File.h"
#include "Packet.h"
#include "Opdracht.h"
#include "CANFormat.h"

void gotoxy( int x, int y )
{ COORD p = { x, y };
  SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

void clrwindow(int x1, int y1, int x2, int y2)
{  int i,j;
   for (i=x1;i<=x2;i++)
   {  for (j=y1; j<=y2; j++)
	  {  gotoxy(i,j);
         std::cout<<" ";
      }
   }
   gotoxy(x1,y1);
}

void framewindow(int x1, int y1, int x2, int y2)
{  int i;
   gotoxy(x1,y1);
   for (i=x1;i<=x2;i++) std::cout <<"-";  
   gotoxy(x1,y2);
   for (i=x1;i<=x2;i++) std::cout <<"-";  
   gotoxy(x1,y1); 
}

void windowprint (int window[4], std::string A[])
{  int i;
   std::string header, regel;
   header = "+" + std::string((window[3]-window[0]), '-') + "+";
   gotoxy (window[0],window[1]);
   std::cout <<header;
   for (i=window[1]+1;i<window[3];i++)
   {  regel = "|"+A[i-1]+std::string((window[2]-window[0]-sizeof(A[i-1])," ")) +"|";
      gotoxy(window[0],i);
	  std::cout << regel;
   }
   gotoxy(window[0], window[3]);
   std::cout <<header;
}

void main()
{ int menuwindow[] = {0,0,35,10};
  int outputwindow[]={40,0,75,10};
  std::string A[40];
  unsigned int id=0;
  unsigned char RTR=0, lengte=0;
  unsigned int *ptr_id;
  unsigned char *ptr_RTR;
  unsigned char *ptr_lengte;
  ptr_id=&id;
  ptr_RTR=&RTR;
  ptr_lengte = &lengte;
  File CANfile, GPSfile;
  CANfile.init("CANin.txt");
  //->> init GPS file
  int menutoestand=0;
  Menu _menu;
  int olietemp=0;
  int diesel =0;
  int waterSB =0;
  int waterBB = 0;
  bool toplicht=false, ankerlicht=false, stoomlicht =false, navigatielicht=false, deklicht=false;
  bool dieptealarm = true, navigatiealarm=false;
  bool* tlicht, *alicht, *slicht, *nlicht, *dlicht, *dalarm, *nalarm;
  tlicht=&toplicht;
  alicht=&ankerlicht;
  slicht=&stoomlicht;
  nlicht=&navigatielicht;
  dlicht=&deklicht;
  dalarm=&dieptealarm;
  nalarm=&navigatiealarm;
  Id0x32 CANOpdracht;
  Id0x40 GPSbericht;
  Packet pack;
  L_packet llp;
  L_packet* llp_p;
  llp_p=&llp;
  unsigned char datablock[8];
  int NBG=54;
  int NBM=0;
  int OLG=5;
  int OLM=50;

  while (1)
  { clrwindow(0,0,40,9);
	switch(menutoestand)
	{	case 0:
			_menu.Menukeuze_h();
			break;
		case 1:
			_menu.Menukeuze_l();
			break;
		case 2:
			_menu.Menukeuze_n();
			break;
		case 11:
			if (toplicht==true) toplicht =false;
			else toplicht =true;
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 12: 
			if (ankerlicht==true) ankerlicht =false;
			else ankerlicht =true;
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 13:
			if (stoomlicht==true) stoomlicht =false;
			else stoomlicht =true;
			menutoestand=0;
			clrwindow(0,0,20,10);
			_menu.Menukeuze_h();
			break;
		case 14:
			if (navigatielicht==true) navigatielicht =false;
			else navigatielicht =true;
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 15:
			if (deklicht==true) deklicht =false;
			else deklicht =true;
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 16:
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 21:
			//positie_invoeren(); //etc
			break;
		default:
			fflush(stdin);
			menutoestand=0;
			break;
	}
  char userinput=0;
  if (!std::cin.eof())
  {  userinput = std::cin.get();
	 if (userinput >='0' && userinput <= '9')
	 {  if (menutoestand ==0) menutoestand =userinput-'0';
		else if (menutoestand ==1) menutoestand =userinput-'0'+10;
		else if (menutoestand ==2) menutoestand =userinput-'0'+20;
     }
	 userinput=0;
	 fflush(stdin);
	
  }
  //-->>verwerk opdrachten in file
  //deze worden later ingevuld
  int roer=19, *roerp;
  roerp=&roer;
  //<<
  CANOpdracht.maak_id0x32(datablock, roer, toplicht, ankerlicht, stoomlicht, 
	   navigatielicht, deklicht, dieptealarm, navigatiealarm);
  pack.maakpacket(&llp, 0x32, 1, 3, datablock);
  CANfile.zendbericht(&llp, 3);
  
  //-->>file teruglezen
  CANfile.leesbericht(llp_p);
  pack.leespacket(llp_p, 0x32, 1, 3, datablock);
  CANOpdracht.lees_id0x32(datablock, *roerp, *tlicht, *alicht, *slicht,*nlicht, *dlicht, *dalarm, *nalarm);
   
  //print terugmelding
  framewindow(0,10,40,24);
  clrwindow(0,11,40,23);
  std::cout<<"roer    \t"<<*roerp <<std::endl<<"toplicht \t"<<*tlicht<<std::endl<<"ankerlicht \t"<<*alicht<<std::endl;
  std::cout<<"stoomlicht \t"<<*slicht <<std::endl<<"navigatielicht \t"<<*nlicht<<std::endl<<"deklicht \t"<<*dlicht<<std::endl;
  std::cout<<"dieptealarm \t"<<*dalarm <<std::endl<<"navigatiealarm \t"<<*nalarm<<std::endl;
  std::cout<< "olietemp\t" <<std::endl<<"diesel\t" <<std::endl << "waterSB \t" <<std::endl <<"waterBB \t"<<std::endl;
 
  //hier eventueel GPS positie inlezen uit bestaande file
  //oude GPS positie opslaan
  GPSbericht.maak_id0x40(datablock, NBG, NBM, OLG, OLM);
  pack.maakpacket(&llp, 0x40, 1, 4, datablock);
  GPSfile.logbericht(&llp, 4);
  
  //werk positie bij
  // koers= koers + roerstand
  // positie NB = NB + snelheid *cos alfa
  // positie OL = OL + snelheid *sin alfa
  // save nieuwe positie
  // storingen simuleren ?
  // geef alarmen
  // loop
  // routes instellen
  }
   
  

}