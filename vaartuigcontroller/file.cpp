#include "File.h"
#include <fstream>
#include <iostream>

//** Maakt een CAN file aan als deze nog niet bestaat **//
void File::init(std::string filenaam)
{ L_packet llpacket;
  L_packet* ptr_llp;
  ptr_llp=&llpacket;
  Packet p;
}

void File::leesbericht(L_packet* llp_p)
{ int lengte;
  unsigned char datablock[8];
  std::string s;
  std::ifstream in_stream ("CANfile");
  if (in_stream.is_open())
  { llp_p->id_block1 =in_stream.get();
    llp_p->id_block2= in_stream.get();
    lengte=(char)llp_p->id_block2&0x000F;
    int i=0;
    do
    {  llp_p->datablock[i]=in_stream.get();
    }
    while(++i<3); //lengte);
 }
 in_stream.close();
}

void File::zendbericht(L_packet* llp, char lengte)
{ std::ofstream filestream("CANfile");
  filestream<<llp->id_block1<<llp->id_block2;
  int i=0;
  do
  {  filestream<<llp->datablock[i];
  }
  while(++i<lengte);
  filestream<<std::endl;
  filestream.close();
}

