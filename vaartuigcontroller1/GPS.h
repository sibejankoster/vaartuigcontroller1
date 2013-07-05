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
	void getpos(float* NB, float* OL);
	void put(float NB,float OL);
};

class Waypoint: public GPSpositie
{  private:
	   std::string naam;
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

class Route: public Waypointlijst
{ private:
	string naam;
	int richting;
	int act_positie;
  public:
	void zoek_volgende_punt(int richting, string vorige_punt);
	bool waypoint_bereikt();
};

#endif //GPS_H