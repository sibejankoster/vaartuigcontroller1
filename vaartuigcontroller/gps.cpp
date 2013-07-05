#include "GPS.h"
#include <sstream>
#include <string>
#include <iostream>

void GPSpositie::getpos(float* NBcoord, float* OLcoord)
{  *NBcoord=NB;
   *OLcoord=OL;
}
float GPSpositie::getNB()
{   return NB;
}

float GPSpositie::getOL()
{   return OL;
}

void GPSpositie::zetNB(float NBreedte)
{   NB=NBreedte;
}

void GPSpositie::zetOL(float OLengte)
{   OL=OLengte;
}


void GPSpositie::put(float NBcoord, float OLcoord)
{  NB=NBcoord;
   OL=OLcoord;
}

int Waypointlijst::add(string naam, GPSpositie gpspos)
{   waypoints.insert(pair<string, GPSpositie>(naam,gpspos));
    return 1;
}

string Waypointlijst::zoek(string naam)
{	map<string, GPSpositie>::iterator itr;
    itr=waypoints.find(naam);
    return itr->first ;
}

int Waypointlijst::save()
{	std::ofstream filestream("Waypoint_file");
    map<string, GPSpositie>::iterator itr;
    itr=waypoints.begin();
    do
    {	filestream <<itr->first<<', '<<itr->second.getNB()<<', '<<itr->second.getOL()<<endl;
        itr++;
    }
    while (itr != waypoints.end());
    filestream.close();
    return 1;
}

int  Waypointlijst::load(Waypointlijst* wptlstp)
{	std::ifstream in_stream ("Waypoint_file");
    string naam;
    string temp;
    stringstream sst;
    float F;
    GPSpositie coordinaten;
    char letter=NULL;
    if (in_stream.is_open());
    {	do
        {	letter= in_stream.get();
            while (letter != ',')
            {	naam+=letter;
                letter= in_stream.get();
            }
            while (letter != ',')
            {	temp+=letter;
                letter= in_stream.get();
            }
            sst<<temp;              //testen !
            sst >> F;
            coordinaten.zetNB(F);
            letter= in_stream.get();
            while (letter != 10 )				//line feed
            {	temp+=letter;
                letter= in_stream.get();
            }
            sst<<temp;              //testen !
            sst >>F;
            coordinaten.zetOL(F);
            wptlstp->waypoints.insert (pair<string, GPSpositie>(naam, coordinaten));
        } while (!EOF);
    }
    in_stream.close();
    return 1;
}

int Waypointlijst::extract()
{

}

void Route::zoek_volgende_punt(int richting, string vorige_punt)
{
}
bool Route::waypoint_bereikt()
{
    return true;
}
