#if !defined(PACKET_H)
#define PACKET_H
//
//  @ Project : vaartuigcontroller
//  @ File Name : Packet.h
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//

class L_packet
{  public:
	unsigned char id_block1;
	unsigned char id_block2;
    unsigned char datablock[8];
};

class Packet
{ public:
  int id;
  char RTR;
  char lengte;
  char data[8];
  void maakpacket(L_packet* llp,int id, char RTR, char lengte, unsigned char* data);
};

#endif // PACKET_H