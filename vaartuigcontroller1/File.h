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
   void leesbericht(std::string filenaam, unsigned int* id, unsigned char* RTR, unsigned char* lengte, unsigned char data[]);
   void zendbericht(std::string filenaam, unsigned int id, unsigned char RTR, unsigned char lengte, unsigned char data[]);
  private:
   std::string s;
};


#endif  //FILE_H