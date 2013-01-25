//
//  @ Project : vaartuigcontroller
//  @ File Name : CANFormat.cpp
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//

#include "CANFormat.h"
void Id0x62::maak_id0x62(unsigned char* datablock, char olietemp,unsigned char diesel, unsigned char waterSB, unsigned char waterBB, 
	   bool toplicht, bool ankerlicht, bool stoomlicht, bool navigatielicht, bool deklicht, bool dieptealarm,
	   bool navigatiealarm)
{  datablock[0]=olietemp;
   datablock[1]=diesel;
   datablock[2]=waterSB;
   datablock[3]=waterBB;
   datablock[4]=(toplicht<<8)+(ankerlicht<<7)+(stoomlicht<<6)+(navigatielicht<<5)+(deklicht<<4);
   datablock[5]=(dieptealarm<<8)+(navigatiealarm<<7);
}

void Id0x62::lees_id0x62(unsigned char* datablock, char olietemp,unsigned char diesel, unsigned char waterSB, unsigned char waterBB, 
	   bool toplicht, bool ankerlicht, bool stoomlicht, bool navigatielicht, bool deklicht, bool dieptealarm,
	   bool navigatiealarm)
{  olietemp=datablock[0];
   diesel=datablock[1];
   waterSB=datablock[2];
   waterBB=datablock[3];
   toplicht=datablock[4]&0x80;
   ankerlicht=datablock[4]&0x40;
   stoomlicht=datablock[4]&0x20;
   navigatielicht=datablock[4]&0x10;
   deklicht=datablock[4]&0x08;
   dieptealarm =datablock[5]&0x80;
   navigatiealarm = datablock[5]&0x40;
}  

void Id0x40::maak_id0x40(unsigned char* datablock, float NBcoord, float OLcoord)
{  char NBG=char(NBcoord);
   char NBM1= char (NBcoord*100);
   char NBM2= char (NBcoord*10000);
   char OLG=char(OLcoord);
   char OLM1= char (OLcoord*100);
   char OLM2= char (OLcoord*10000);
	datablock[0]= NBG;
   datablock[1]= NBM1;
   datablock[2]= NBM2;
   datablock[3]= OLG;
   datablock[4]= OLM1;
   datablock[5]= OLM2;
}

void Id0x32::lees_id0x32(unsigned char* datablock, int roer, bool toplicht, bool ankerlicht, bool stoomlicht, 
	   bool navigatielicht, bool deklicht, bool dieptealarm, bool navigatiealarm)
{  roer=datablock[0];
   toplicht=datablock[2]&0x80;
   ankerlicht =datablock[2]&0x40;
   stoomlicht =datablock[2]&0x20;
   navigatielicht =datablock[2]&0x10;
   deklicht =datablock[2]&0x08;
   dieptealarm =datablock[2]&0x04;
   navigatiealarm =datablock[2]&0x02;
}

void Id0x32::maak_id0x32(unsigned char* datablock, int roer, bool toplicht, bool ankerlicht, bool stoomlicht, 
	   bool navigatielicht, bool deklicht, bool dieptealarm, bool navigatiealarm)
{  datablock[0]=roer;
   datablock[1]=0;
   datablock[2]=(toplicht<<7)+(ankerlicht<<6)+(stoomlicht<<5)+(navigatielicht<<4)+(deklicht<<3)+(dieptealarm<<2)+(navigatiealarm<<1);
}

