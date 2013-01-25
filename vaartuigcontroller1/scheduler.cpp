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
#include <process.h>
#include <iostream>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/xtime.hpp>
#include "File.h"
#include "Packet.h"
#include "Opdracht.h"
#include "CANFormat.h"
#include "GPS.h"
#include "Layout.h"

#define CHECK_INTERVAL 2000
#define MENUMODUS 1

HANDLE keybMutex;
std::string userinput; 
int keuze;

int keybmodus=MENUMODUS;
void inputThread(void *args)
{ printf("thread started\n");
  while(1)
  {	WaitForSingleObject(keybMutex, INFINITE);
	
	if (keybmodus=MENUMODUS)
	{   userinput=_getch();
		keuze=atoi(userinput.c_str());
	}
	else std::cin >> userinput;
	ReleaseMutex(keybMutex);
  }
  _endthread();
}

int main()
{ 
  // keyboard mutex
  keybMutex = CreateMutex(NULL, 0 ,NULL);
  _beginthread(inputThread,0,NULL);
  //
  // windows
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
  float NBcoord, OLcoord;
  float *NBcoordp, *OLcoordp;
  NBcoordp=&NBcoord;
  OLcoordp=&OLcoord;
  GPSpositie gpspos, MOBpositie;
  gpspos.put(54.0, 4.0);						//uitgangspositie
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
  Id0x32 CANOpdracht;
  Id0x40 GPSbericht;
  Packet pack;
  L_packet llp;
  L_packet* llp_p;
  llp_p=&llp;
  unsigned char datablock[8];
  //
  // sensorwaarden
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
  int snelheid=10;
  int gasstand=10;
  int roer=19, *roerp;
  roerp=&roer;

  fflush(stdin);

  while (1)
  { //1. Sla default sensorwaarden op in 0x62 file
	//2. Verwerk opdrachten in sensorwaarden (simulatie vaartuig)
	CANOpdracht.maak_id0x32(datablock, roer, toplicht, ankerlicht, stoomlicht, 
			navigatielicht, deklicht, dieptealarm, navigatiealarm);
	pack.maakpacket(&llp, 0x32, 1, 3, datablock);
	CANfile.zendbericht(&llp, 3);
  
//1. Lees sensorwaarden uit 0x62 file en beeld af op scherm
	CANfile.leesbericht(llp_p);
	pack.leespacket(llp_p, 0x32, 1, 3, datablock);
	CANOpdracht.lees_id0x32(datablock, *roerp, *tlicht, *alicht, *slicht,*nlicht, *dlicht, *dalarm, *nalarm);
	std::ostringstream hulps; 
	
	hulps << "roer      \t"<< *roerp;			A[0]= hulps.str(); hulps.str("");
	hulps << "toplicht \t" <<*tlicht;			A[1]=hulps.str();hulps.str("");
	hulps << "ankerlicht \t" <<*alicht;		A[2]=hulps.str();hulps.str("");
	hulps << "navigatielicht \t" <<*nlicht;	A[3]=hulps.str();hulps.str("");
	hulps << "deklicht \t" <<*dlicht;			A[4]=hulps.str();hulps.str("");
	hulps << "dieptealarm \t" <<*dalarm;		A[5]=hulps.str();hulps.str("");
	hulps << "navigatiealarm \t" <<*nalarm;	A[6]=hulps.str();hulps.str("");
	hulps << "olietemperatuur \t" <<*otempp;	A[7]=hulps.str();hulps.str("");
	hulps << "diesel       \t" <<*dieselp;	A[8]=hulps.str();hulps.str("");
	hulps << "water SB     \t" <<*waterSBp;	A[9]=hulps.str();hulps.str("");
	hulps << "water BB     \t" <<*waterBBp;	A[10]=hulps.str();hulps.str("");
	hulps << "              \t";				A[11]=hulps.str();hulps.str("");
// de volgende zijn geen sensorwaarden, maar instellingen
	hulps << "automaat     \t" <<*waterBBp;	A[12]=hulps.str();hulps.str("");
	hulps << "route        \t" <<*waterBBp;	A[13]=hulps.str();hulps.str("");
	hulps << "routelogger  \t" <<*waterBBp;	A[14]=hulps.str();hulps.str("");
	hulps << "toeren       \t" <<*waterBBp;	A[15]=hulps.str();hulps.str("");
	hulps << "einde";							A[16]=hulps.str();hulps.str("");
	toestandwindow.print(A);

// GPS logger in de vorm van 0x40 berichten
	gpspos.getpos(NBcoordp, OLcoordp);
	GPSbericht.maak_id0x40(datablock, NBcoord, OLcoord);
	pack.maakpacket(&llp, 0x40, 1, 4, datablock);
	GPSfile.logbericht(&llp, 4);
    
//-->werk positie bij en beeld af op scherm
	koers += *roerp/10;							//veranderstelde reactiesnelheid op roer
	snelheid += gasstand -0.1*snelheid*snelheid;	//kwadratische weerstand //--> controleren of dit binnen int past
	gpspos.berekenpositie(koers, snelheid, NBcoordp, OLcoordp);
  
	hulps << "Noorderbreedte   \t"<< NBcoord;				A[0]= hulps.str(); hulps.str("");
	hulps << "Oosterlengte    \t" << OLcoord;				A[1]=hulps.str();hulps.str("");
	hulps << "Snelheid        \t" << snelheid;			A[2]=hulps.str();hulps.str("");
	hulps << "Behouden koers  \t" << koers;				A[3]=hulps.str();hulps.str("");
	hulps << "einde";										A[4]=hulps.str();hulps.str("");
	GPSwindow.print(A);

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

	if (keybmodus==MENUMODUS)
	{	if(WaitForSingleObject(keybMutex,CHECK_INTERVAL)==WAIT_TIMEOUT) {}
		else									//er is user input binnengekomen (string of char +return)
		{   if (menutoestand ==0) menutoestand=keuze;
			else if (menutoestand ==1) menutoestand =keuze+10;
			else if (menutoestand ==2) menutoestand =keuze+20;
			else if (menutoestand ==3) menutoestand =keuze+30;
			else if (menutoestand==21) menutoestand =keuze+210;
			else if (menutoestand==22) menutoestand =keuze+220;
			userinput="";
			ReleaseMutex(keybMutex);
		}
	}

  // roer veranderen !
  // storingen simuleren ?
  // geef alarmen
  // routes instellen
  }
}   
  

