#if !defined(_CANFORMAT_H)
#define _CANFORMAT_H//
//
//  @ Project : vaartuigcontroller
//  @ File Name : CANFormat.h
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//  in dit geval zijn er maar drie zenders:
//  - alle sensoren zenden in hetzelfde blok met id 0x64
//  - de bedieningsunit zendt met 0x32
//  - de GPS ontvanger zendt met een vrij te kiezen id bv 0x40
//  De indeling van de boodschappen is verschillend per zender. De ontvangers moeten daarom zijn ingesteld

#include <iostream>
#include "Packet.h"
#include "CANFormat.h"
#include "GPS.h"

class Id0x62  //boodschap van sensorcontroller naar centrale vaartuigcontroller
{ public:
   void maak_id0x62(unsigned char* datablock, char olietemp,unsigned char diesel, unsigned char waterSB, unsigned char waterBB,
       bool toplicht, bool ankerlicht, bool stoomlicht, bool navigatielicht, bool deklicht, bool dieptealarm,
       bool navigatiealarm);
   void lees_id0x62(unsigned char* datablock, char olietemp,unsigned char diesel, unsigned char waterSB, unsigned char waterBB,
       bool toplicht, bool ankerlicht, bool stoomlicht, bool navigatielicht, bool deklicht, bool dieptealarm,
       bool navigatiealarm);
  private:
   unsigned int olietemp;
   unsigned int voldiesel;
   unsigned int volwaterSB;
   unsigned int volwaterBB;
   bool toplicht;
   bool ankerlicht;
   bool stoomlicht;
   bool navigatielicht;
   bool deklicht;
   bool dieptealarm;
   bool navigatiealarm;
};

class Id0x40 // GPS zender
{ public:
   void maak_id0x40(unsigned char* datablock, float NBcoord, float OLcoord);
   void lees_id0x40(unsigned char* datablock, float NBcoord, float OLcoord);
  private:
    GPSpositie gpspos;
};

class Id0x32 // boodschap van centrale vaartuigcontroller naar actuators
{ public:
   void maak_id0x32(unsigned char* datablock, int roer, bool toplicht, bool ankerlicht, bool stoomlicht,
       bool navigatielicht, bool deklicht, bool dieptealarm, bool navigatiealarm);
   void lees_id0x32(unsigned char* datablock, int roer, bool toplicht, bool ankerlicht, bool stoomlicht,
       bool navigatielicht, bool deklicht, bool dieptealarm, bool navigatiealarm);
  private:
   int roer;
   bool toplicht;
   bool ankerlicht;
   bool stoomlicht;
   bool navigatielicht;
   bool deklicht;
   bool dieptealarm;
   bool navigatiealarm;
};

#endif  //_CANFORMAT_H
