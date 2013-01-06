//
//
//  @ Project : vaartuigcontroller
//  @ File Name : main.h
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "File.h"
#include "Packet.h"

void main()
{ unsigned char data[8];
  unsigned int id=0;
  unsigned char RTR=0, lengte=0;
  unsigned int *ptr_id;
  unsigned char *ptr_RTR;
  unsigned char *ptr_lengte;
  ptr_id=&id;
  ptr_RTR=&RTR;
  ptr_lengte = &lengte;
  File in_file;
  in_file.init("CANin.txt");
  in_file.leesbericht("CANin.txt", ptr_id, ptr_RTR, ptr_lengte, data);
  printf ("id %d RTR  %d lengte %d \n",id,RTR,lengte);
  printf ("temperatuur %d\ndiesel %d\nwaterSB %d\nwaterBB %d\n",data[0],data[1],data[2],data[3]); 
  printf ("data4 %d\ndat 5 %d\ndata 6 %d\ndata 7 %d\n",data[4],data[5],data[6],data[7]);



}