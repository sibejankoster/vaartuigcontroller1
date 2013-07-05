#ifndef GPS_H
#define GPS_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
using namespace std;

class GPSpositie
{  private:
   float NB, OL;

public:
   void getpos(float* NBcoord, float* OLcoord);
   float getNB();
   float getOL();
   void zetNB(float NBreedte);
   void zetOL(float OLengte);
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
{  public:
    std::map<string, GPSpositie> waypoints;
public:
    int add(string naam, GPSpositie gpspos);
    int remove (string naam);
    int extract();
    string zoek (string naam);
    int save ();
    int load (Waypointlijst* wptlst);
};

class Route: public Waypointlijst
{ private:
    string naam;
    int richting;
  public:
    void zoek_volgende_punt(int richting, string vorige_punt);
    bool waypoint_bereikt();
};

#endif //GPS_H
