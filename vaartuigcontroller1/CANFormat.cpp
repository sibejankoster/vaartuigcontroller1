//
//  @ Project : vaartuigcontroller
//  @ File Name : CANFormat.cpp
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//

#include "CANFormat.h"
void Id0x62::maak_id0x62(L_packet* llp, char olietemp,unsigned char diesel, unsigned char waterSB, unsigned char waterBB, 
	   bool toplicht, bool ankerlicht, bool stoomlicht, bool navigatielicht, bool deklicht, bool dieptealarm,
	   bool navigatiealarm)
{  llp->datablock[0]=olietemp;
   llp->datablock[1]=diesel;
   llp->datablock[2]=waterSB;
   llp->datablock[3]=waterBB;
   llp->datablock[4]=toplicht<<8+ankerlicht<<7+stoomlicht<<6+navigatielicht<<5+deklicht<<4;
   llp->datablock[5]=dieptealarm<<8+navigatiealarm<<7;
}

void Id0x62::lees_id0x62(L_packet* llp, char olietemp,unsigned char diesel, unsigned char waterSB, unsigned char waterBB, 
	   bool toplicht, bool ankerlicht, bool stoomlicht, bool navigatielicht, bool deklicht, bool dieptealarm,
	   bool navigatiealarm)
{  olietemp=llp->datablock[0];
   diesel=llp->datablock[1];
   waterSB=llp->datablock[2];
   waterBB=llp->datablock[3];
   toplicht= llp->datablock[4]&0x80;
   ankerlicht= llp->datablock[4]&0x40;
   stoomlicht= llp->datablock[4]&0x20;
   navigatielicht= llp->datablock[4]&0x10;
   deklicht= llp->datablock[4]&0x08;
   dieptealarm = llp->datablock[5]&0x80;
   navigatiealarm = llp->datablock[5]&0x40;
}  

void Id0x40::maak_id0x40(L_packet* llp, int graden_NB, unsigned int decimaal_NB, int graden_OL, unsigned int decimaal_OL)
{  llp->datablock[0]=graden_NB;
   llp->datablock[1]=decimaal_NB;
   llp->datablock[2]=graden_OL;
   llp->datablock[3]=decimaal_OL;
}

void Id0x32::maak_id0x32(L_packet* llp, int roer_act, bool toplicht_act, bool ankerlicht_act, bool stoomlicht_act, 
	   bool navigatielicht_act, bool deklicht_act, bool dieptealarm_act, bool navigatiealarm_act)
{
}

void Id0x32::lees_id0x32(L_packet* llp, int roer_act, bool toplicht_act, bool ankerlicht_act, bool stoomlicht_act, 
	   bool navigatielicht_act, bool deklicht_act, bool dieptealarm_act, bool navigatiealarm_act)
{ llp->datablock[0]=roer_act;
  llp->datablock[1]=0;
  llp->datablock[2]=toplicht_act<<8+ankerlicht_act<<7+stoomlicht_act<<6+navigatielicht_act<<5+deklicht_act<<4+
	  dieptealarm_act<<4+navigatiealarm_act<<3;
}