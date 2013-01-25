#ifndef GPS_H
#define GPS_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class GPSpositie
{  private:
   float NB, OL; 
	
public:
	void berekenpositie(int koers, int snelheid, float* NBcoord, float* OLcoord);
	void getpos(float* NB, float* OL);
	void put(float NB,float OL);
};

class Waypoint: public GPSpositie
{  private:
	   std::string naam;
	   float NB, OL;
   public:
	   void aanmaken(std::string naam, float NB, float OL);
	   void edit(std::string naam, float* NB, float* OL);
	   void wissen();
	   void load();
	   void save();
};

class Waypointlijst
{  private:
    multimap<std::string, std::string> waypoints;
public:
	int add(string naam, float NB, float OL);
	int remove (string naam);
	string zoek (string naam);
	int save ();
	int load ();
};

#endif //GPS_H