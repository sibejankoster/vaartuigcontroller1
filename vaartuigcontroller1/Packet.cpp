#include "Packet.h"
#include <iostream>

void Packet::maakpacket(L_packet* llp, int id, char RTR, char lengte, unsigned char data[])
{  unsigned int tmp;
   unsigned char highb, lowb;   
   tmp = lengte + (RTR<<4) + (id<<5);
   lowb= tmp&0x00FF;
   highb=(tmp>>8)&0x00FF;
   llp->id_block1=highb;
   llp->id_block2=lowb;
   int i=0;
   do
   { llp->datablock[i]=data[i];
     i++;
   }
   while (i<lengte);
}

