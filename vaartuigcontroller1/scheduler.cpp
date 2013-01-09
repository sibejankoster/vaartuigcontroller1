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
#include "File.h"
#include "Packet.h"
#include "Opdracht.h"

void main()
{ unsigned char data[8];
  unsigned int id=0;
  unsigned char RTR=0, lengte=0;
  unsigned int *ptr_id;
  unsigned char *ptr_RTR;
  unsigned char *ptr_lengte;
  ptr_id=&id;
  ptr_RTR=&RTR;
  ptr_lengte = &lengte;
  File in_file;
  in_file.init("CANin.txt");
  //->> init GPS file
  int menutoestand=0;
  Menu _menu;
  int toplicht=0, ankerlicht=0, stoomlicht =0, navigatielicht=0; 
  while (1)
  {  switch(menutoestand)
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
			if (toplicht==1) toplicht =0;
			else toplicht =1;
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 12: 
			if (ankerlicht==1) ankerlicht =0;
			else ankerlicht =1;
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 13:
			if (stoomlicht==1) stoomlicht =0;
			else stoomlicht =1;
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 14:
			if (navigatielicht==1) navigatielicht =0;
			else navigatielicht =1;
			menutoestand=0;
			_menu.Menukeuze_h();
			break;
		case 15:
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
  in_file.zendbericht("CAN_in.txt", id, RTR, lengte, data);
  //-->>lees sensoren (lees file)
  in_file.leesbericht("CAN_in.txt", &id, &RTR, &lengte, data);
  std::cout<<"sensoren gelezen"<<std::endl;
  
  //print toestand
  //werk positie bij
  //save positie
  //geef alarmen
  //loop
  }
   
  /*
  in_file.leesbericht("CANin.txt", ptr_id, ptr_RTR, ptr_lengte, data);
  printf ("id %d RTR  %d lengte %d \n",id,RTR,lengte);
  printf ("temperatuur %d\ndiesel %d\nwaterSB %d\nwaterBB %d\n",data[0],data[1],data[2],data[3]); 
  printf ("data4 %d\ndat 5 %d\ndata 6 %d\ndata 7 %d\n",data[4],data[5],data[6],data[7]);
  */


}