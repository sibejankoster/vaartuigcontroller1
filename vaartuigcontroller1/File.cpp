#include "File.h"
#include <fstream>
#include <iostream>

//** Maakt een CAN file aan als deze nog niet bestaat **//
void File::init(std::string filenaam)
{ L_packet llpacket;
  L_packet* ptr_llp;
  ptr_llp=&llpacket;
  Packet p;
  
  unsigned char data[] = {20,200,150,150,0,0};
  int id=0x64;
  std::fstream in_stream;
  in_stream.open (filenaam, std::fstream::in);
  
  if (in_stream.good())
  {  in_stream.close();  //file bestaat, gebruik bestaande file
  }
  else                   // demo file wordt aangemaakt
  {  in_stream.open(filenaam, std::fstream::out);
     int lengte = sizeof(data)/sizeof(char);
     p.maakpacket(ptr_llp, id,1,lengte,data);
	 in_stream<<llpacket.id_block1<<llpacket.id_block2;
	 int i=0;
	 do
	 {  in_stream<<llpacket.datablock[i];
	 }
	 while(++i<lengte);
	 in_stream<<std::endl;
	 std::cout<<"File aangemaakt";
  }
}

void File::leesbericht(std::string filenaam, unsigned int* id, unsigned char* RTR, unsigned char* lengte, unsigned char data[])
{ L_packet llp;
  std::string s;
  std::fstream in_stream;
  in_stream.open (filenaam, std::fstream::in);
  llp.id_block1 =in_stream.get();
  llp.id_block2= in_stream.get();
  *lengte=(char)llp.id_block2&0x000F;
  *RTR=(llp.id_block2>>4)&0x0001;
  *id= (llp.id_block1<<7)+(llp.id_block2>>5)*16;
  int i=0;
  do
  {  data[i]=in_stream.get();
  }
  while(++i<*lengte);
  in_stream.close();
}

void File::zendbericht(std::string filenaam, unsigned int id, unsigned char RTR, unsigned char lengte, unsigned char data[])
{ L_packet llpacket;
  L_packet* ptr_llp;
  ptr_llp=&llpacket;
  Packet p;
  const std::string uitfile ="CAN_uit";
  std::fstream in_stream;
  in_stream.open (uitfile, std::fstream::in);
  
  if (in_stream.good())
  {  in_stream.close();            //file bestaat, gebruik bestaande file
  }
  else                             // demo file wordt aangemaakt
  {  in_stream.open(uitfile, std::fstream::out);
     int lengte = sizeof(data)/sizeof(char);
     p.maakpacket(ptr_llp, id,1,lengte,data);
	 in_stream<<llpacket.id_block1<<llpacket.id_block2;
	 int i=0;
	 do
	 {  in_stream<<llpacket.datablock[i];
	 }
	 while(++i<lengte);
	 in_stream<<std::endl;
  }
}

