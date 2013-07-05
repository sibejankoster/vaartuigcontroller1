//
//  @ Project : vaartuigcontroller
//  @ File Name : scheduler.cpp
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>				//gotoxy screen coord
#include <conio.h>					//_getch() user input no wait
#include <sstream>
#include <string>
#include <iomanip>
#include <iomanip>
#include <locale>
#include <iostream>
#include "File.h"
#include "Packet.h"
#include "Opdracht.h"
#include "CANFormat.h"
#include "GPS.h"
#include "Layout.h"
#include "logfile.h"
#include "Dynamics.h"

//getinput
bool getInput(char *c)
{	if (kbhit())
	{	*c=getch();
		return true;
	}
	return false;
}

int main()
{ 
  // dialoog
  int keuze=0;
  	
	// tijd
  struct tm *nu;
  time_t now;
  //
  // output vensters
  Window menuwindow(0,0,40,15);
  Window GPSwindow(0,17,40,26);
  Window toestandwindow(45,0,75,26);
  std::string A[40];
  int menutoestand=0;
  Menu _menu;
  //
  // GPS
  Waypointlijst wptlijst;
  wptlijst.load();
  Logger GPSlog;
  GPSlog.wissen();
  float NBcoord, OLcoord;
  float *NBcoordp, *OLcoordp;
  NBcoordp=&NBcoord;
  OLcoordp=&OLcoord;
  GPSpositie gpspos, MOBpositie;
  gpspos.put(54.2, 4.0);						//uitgangspositie
  int loopteller=0;
  //
  //Navigatie
  int afstandWPT;
  int* afstandWPTp;
  afstandWPTp=&afstandWPT;
  int koersWPT;
  int* koersWPTp;
  koersWPTp=&koersWPT;
  bool alarm;
  bool* alarmp;
  alarmp=&alarm;
  //
  // CAN
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
  Id0x62 CANbericht;
  Id0x40 GPSbericht;
  Packet pack;
  L_packet llp;
  L_packet* llp_p;
  llp_p=&llp;
  unsigned char datablock[8];
  //
  // sensoren
  int olietemp=0, diesel =0, waterSB =0, waterBB = 0;
  int *otempp, *dieselp, *waterSBp, *waterBBp;
  otempp=&olietemp;
  dieselp = &diesel;
  waterSBp=&waterSB;
  waterBBp=&waterBB;
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
  int koers=0;
  int* koersp;
  koersp=&koers;
  int snelheid=10;
  int *snelheidsp;
  snelheidsp=&snelheid;
  int gasstand=10;
  int roer=19, *roerp;
  roerp=&roer;
  //
  // simulatie
  Dynamics simulatie;
  //
  fflush(stdin);

  while (1)
  { //1. Tijd
    time(&now);
	nu = localtime(&now);

//  Sla default sensorwaarden op in 0x62 file
//  Sommige variabelen worden per loop bijgewerkt door methods in Dynamics (simulatie vaartuig)
	CANbericht.maak_id0x62(datablock, olietemp, diesel, waterSB, waterBB, toplicht, ankerlicht, stoomlicht, 
			navigatielicht, deklicht, dieptealarm, navigatiealarm);
	pack.maakpacket(&llp, 0x32, 1, 6, datablock);
	CANfile.zendbericht(&llp, 3);
//	  
//  Lees sensorwaarden uit 0x62 file (simulatie CAN bericht)
	CANfile.leesbericht(llp_p);
	pack.leespacket(llp_p, 0x32, 1, 3, datablock);
	CANbericht.lees_id0x62(datablock, *otempp, *dieselp, *waterSBp, *waterBBp, *tlicht, *alicht, *slicht,*nlicht, *dlicht, *dalarm, *nalarm);
	std::ostringstream hulps; 
//
//  Beeld af op scherm	
	hulps << "roer      \t"<< *roerp;			A[0]= hulps.str(); hulps.str("");
	hulps << "toplicht \t" <<*tlicht;			A[1]=hulps.str();hulps.str("");
	hulps << "ankerlicht \t" <<*alicht;			A[2]=hulps.str();hulps.str("");
	hulps << "navigatielicht \t" <<*nlicht;		A[3]=hulps.str();hulps.str("");
	hulps << "deklicht \t" <<*dlicht;			A[4]=hulps.str();hulps.str("");
	hulps << "dieptealarm \t" <<*dalarm;		A[5]=hulps.str();hulps.str("");
	hulps << "navigatiealarm \t" <<*nalarm;		A[6]=hulps.str();hulps.str("");
	hulps << "olietemperatuur \t" <<*otempp;	A[7]=hulps.str();hulps.str("");
	hulps << "diesel       \t" <<*dieselp;		A[8]=hulps.str();hulps.str("");
	hulps << "water SB     \t" <<*waterSBp;		A[9]=hulps.str();hulps.str("");
	hulps << "water BB     \t" <<*waterBBp;		A[10]=hulps.str();hulps.str("");
	hulps << "temp koelwater  \t" <<"90";		A[11]=hulps.str();hulps.str("");
	hulps << "Motorbelasting \t" <<"- ";		A[12]=hulps.str();hulps.str("");
	hulps << "Motoraccu      \t" <<"13";		A[13]=hulps.str();hulps.str("");
	hulps << "Lichtaccu      \t" <<"12";		A[14]=hulps.str();hulps.str("");
	hulps << "Windrichting   \t" <<"-";			A[15]=hulps.str();hulps.str("");
	hulps << "Windstrekte    \t" <<"4";			A[16]=hulps.str();hulps.str("");
	hulps << "VHF kanaal     \t" <<"16";		A[17]=hulps.str();hulps.str("");
	hulps << "              \t";				A[18]=hulps.str();hulps.str("");

	hulps << "automaat     \t" <<*waterBBp;	A[19]=hulps.str();hulps.str("");
	hulps << "route        \t" <<*waterBBp;	A[20]=hulps.str();hulps.str("");
	hulps << "routelogger  \t" <<*waterBBp;	A[21]=hulps.str();hulps.str("");
	hulps << "toeren       \t" <<*waterBBp;	A[22]=hulps.str();hulps.str("");
	hulps << "einde";						A[23]=hulps.str();hulps.str("");
	toestandwindow.print(A);
//
// GPS logger (slaat iedere loop (2 to 10 seconden de actuele positie op)
   GPSlog.addpoint(gpspos);
//	
//  Werk positie bij met Dynamics en beeld af op scherm
	simulatie.bereken_koers_en_snelheid(gasstand, roer, snelheidsp, koersp);
    simulatie.berekenpositie(koers, snelheid, NBcoordp, OLcoordp);  

	hulps << "Noorderbreedte   \t"<< NBcoord;			A[0]= hulps.str(); hulps.str("");
	hulps << "Oosterlengte    \t" << OLcoord;			A[1]=hulps.str();hulps.str("");
	hulps << "Snelheid        \t" << snelheid;			A[2]=hulps.str();hulps.str("");
	hulps << "Behouden koers  \t" << koers;				A[3]=hulps.str();hulps.str("");
	hulps << "Tijd          \t"<< nu->tm_hour<<":"<< nu->tm_min; A[4]=hulps.str();hulps.str("");

	hulps << "einde";									A[5]=hulps.str();hulps.str("");
	GPSwindow.print(A);
//
//  Bijsturen
	void bijsturen (int* roerstand, int modus, string route, int* afstandWPTp, int* koersWPTp, bool* alarm);
	if (alarm=true); //BEEP

// Verwerking menukeuze (van de vorige loop)
	switch(menutoestand)
	{	case 0:
			_menu.Menukeuze_h(A); 
			menuwindow.print(A);
			break;
		case 1:
			_menu.Menukeuze_l(A);
			menuwindow.print(A);
			break;
		case 2:
			_menu.Menukeuze_g(A);
			menuwindow.print(A);
			break;
		case 3:
			_menu.Menukeuze_n(A);
			menuwindow.print(A);
			break;
		case 11:
			_menu.Menukeuze_l(A);
			menuwindow.print(A);
			if (toplicht==true) toplicht =false;
			else toplicht =true;
			menutoestand=0;
			break;
		case 12: 
			_menu.Menukeuze_l(A);
			menuwindow.print(A);
			if (ankerlicht==true) ankerlicht =false;
			else ankerlicht =true;
			menutoestand=0;
			break;
		case 13:
			_menu.Menukeuze_l(A);
			menuwindow.print(A);
			if (stoomlicht==true) stoomlicht =false;
			else stoomlicht =true;
			menutoestand=0;
			break;
		case 14:
			_menu.Menukeuze_l(A);
			menuwindow.print(A);
			if (navigatielicht==true) navigatielicht =false;
			else navigatielicht =true;
			menutoestand=0;
			break;
		case 15:
			_menu.Menukeuze_l(A);
			menuwindow.print(A);
			if (deklicht==true) deklicht =false;
			else deklicht =true;
			menutoestand=0;
			break;
		case 16:   //"terug"
			_menu.Menukeuze_l(A);
			menuwindow.print(A);
			menutoestand=0;
			break;
		case 21:
			_menu.Menukeuze_g1(A);
			menuwindow.print(A);
			break;
		case 22:
		    _menu.Menukeuze_g2(A);
			menuwindow.print(A);
			break;
		case 23:
		    _menu.Menukeuze_g3(A);
			menuwindow.print(A);
			break;
		case 24:
		    _menu.Menukeuze_g4(A);
			menuwindow.print(A);
			break;
		case 25:
		    _menu.Menukeuze_g(A);  
			menuwindow.print(A);
			break;
		case 26:
		    _menu.Menukeuze_g4(A);
			menuwindow.print(A);
			break;
		case 27:
		    _menu.Menukeuze_g(A);  //terug
			menuwindow.print(A);
			break;
		case 31:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 32:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 33:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 34:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 35:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 36:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 37:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 38:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 39:
		    _menu.Menukeuze_n(A);  //terug
			menuwindow.print(A);
			break;
		case 211:
			_menu.Menukeuze_g1(A);
			menuwindow.print(A);
			MOBpositie=gpspos;
			menutoestand=2;
			break;
		case 212:
			_menu.Menukeuze_g1(A);
			menuwindow.print(A);
			menutoestand=22;
			break;
		case 213:
			_menu.Menukeuze_g1(A);
			menuwindow.print(A);
			menutoestand = 2;
			break;
		case 221:
		    _menu.Menukeuze_g2sub(A);
			menuwindow.print(A);
			menutoestand = 222;
			break;

		default:
			fflush(stdin);
			menutoestand=0;
			_menu.Menukeuze_h(A); 
			menuwindow.print(A);
			break;
	}
	//std::cin>>keuze;
	if (menutoestand ==0) menutoestand=keuze;
	else if (menutoestand ==1) menutoestand =keuze+10;
	else if (menutoestand ==2) menutoestand =keuze+20;
	else if (menutoestand ==3) menutoestand =keuze+30;
	else if (menutoestand==21) menutoestand =keuze+210;
	else if (menutoestand==22) menutoestand =keuze+220;
	}
}   
  

