#include "Packet.h"
#include <iostream>

void Packet::maakpacket(L_packet* llp, int id, char RTR, char lengte, unsigned char* datablock)
{  unsigned int tmp;
   unsigned char highb, lowb;   
   tmp = lengte + (RTR<<4) + (id<<5);
   lowb= tmp&0x00FF;
   highb=(tmp>>8)&0x00FF;
   llp->id_block1=highb;
   llp->id_block2=lowb;
   int i=0;
   do
   { llp->datablock[i]=datablock[i];
     i++;
   }
   while (i<lengte);
}

void Packet::leespacket(L_packet* llp_p, int id, char RTR, char lengte, unsigned char* datablock)
{ lengte=static_cast<char>(llp_p->id_block2&0x000F);
  RTR=(llp_p->id_block2>>4)&0x0001;
  id= (llp_p->id_block1<<7)+(llp_p->id_block2>>5)*16;
  int i=0;
  do
  {  datablock[i]=llp_p->datablock[i];
  }
  while(++i<lengte);
}