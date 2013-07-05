//
//  @ Project : vaartuigcontroller
//  @ File Name : Stuurautomaat.cpp
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//
#include "Stuurautomaat.h"
#include "GPS.h"

#define PI 3.14159265

int koers_naar_waypoint(Waypoint waypnt, GPSpositie pos)
{   float NBdiff, OLdiff, *NB, *OL, *NBWPT, *OLWPT;
    int koers;
	pos.getpos(NB, OL);
	waypnt.getpos(NBWPT, OLWPT);
	//afgezien van de overgang van OL naar WL bij 180 OL
	NBdiff= *NB-*NBWPT;
	OLdiff= *OL -*OLWPT;
	//afgezien van grootcirkelberekeningen
	koers=atan( NBdiff/(OLdiff*cos(*NB*2*PI/360)));
	return koers;
}

void bijsturen (int* roerstand, int* afstandWPT, Waypoint* volgendeWPT, bool* alarm, int modus, GPSpositie pos,
	int behouden_koers, int ingestelde_koers, string route )
{	switch (modus)
	{case 0:				//uitgeschakeld, doe niets
		break;
	 case 1:				//vaste koers aanhouden
		*roerstand += *roerstand +(behouden_koers - ingestelde_koers)/10;  //P-regelaar, niet te abrupt reageren
		break;
	 case 2:				//naar waypoint varen
		koers_naar_waypoint;
		 *roerstand += *roerstand + (behouden_koers -koers_naar_waypoint(*volgendeWPT,pos))/10;
		break;
	 default:
	    break;
	}
	return;
}