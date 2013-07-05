//
//  @ Project : vaartuigcontroller
//  @ File Name : Stuurautomaat.h
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//

#if !defined(_STUURAUTOMAAT_H)
#define _STUURAUTOMAAT_H

#include <string>
#include "Route.h"
#include "CANcontroller.h"

class Stuurautomaat : public Route 
{ private:
	int volgende_waypoint;
	int vaste_koers;
	int modus;
	string route;
public:
	void bijsturen (int* roerstand, int* afstandWPT, Waypoint* volgendeWPT, bool* alarm, int modus, GPSpositie pos,
	int behouden_koers, int ingestelde_koers, string route );
};

#endif  //_STUURAUTOMAAT_H
