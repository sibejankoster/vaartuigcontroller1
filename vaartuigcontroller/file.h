//
//
//  @ Project : vaartuigcontroller
//  @ File Name : File.h
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//

#if !defined (FILE_H)
#define FILE_H

#include <stdio.h>
#include <string>
#include "Packet.h"

class File
{ public:
   void init(std::string filenaam);
   void leesbericht(L_packet* llp_p);
   void zendbericht(L_packet* llp, char lengte);
private:
   std::string s;
};


#endif  //FILE_H
