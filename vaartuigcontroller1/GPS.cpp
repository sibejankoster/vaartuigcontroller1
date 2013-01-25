#include "GPS.h"
#include <cmath>
#include <sstream>

void GPSpositie::getpos(float* NBcoord, float* OLcoord)
{  *NBcoord=NB;
   *OLcoord=OL;
}

void GPSpositie::put(float NBcoord, float OLcoord)
{  NB=NBcoord;
   OL=OLcoord;
}

#define PI 3.14159265
void GPSpositie::berekenpositie(int koers, int snelheid, float* NBcoord, float* OLcoord)
{  *NBcoord += snelheid*std::cos (koers*2*PI/360)/120;  //dit hangt af van de kloksnelheid
   *OLcoord += snelheid*std::sin (koers*2*PI/360)/120;  //1 graad = 60 nautische mijl (NB)
   // geen grootcirkelberekeningen
}

void Waypoint::aanmaken(std::string naam, float NB, float OL)
{  
}

int Waypointlijst::add(string naam, float NB, float OL)
{   string coordinaten;
	stringstream sstr;
	multimap<string, string>::iterator itr;
	sstr << NB <<", "<<OL<<endl;
	coordinaten=sstr.str();	
	//if (itr != waypoints.end()) //naam wordt al gebruikt // dit gaat fout bij een nog lege file !
	//{ return 0;
	//}
	//else 
	waypoints.insert(pair<string, string>(naam, coordinaten));
	return 1;
}

int Waypointlijst::remove(string naam)
{   string coordinaten;
	bool succes;
	multimap<string, string>::iterator itr;
	itr=waypoints.find(naam);
	if (itr != waypoints.end())
	{  waypoints.erase(itr);
	   succes=true; 	
	}
	else succes = false;
	return succes;
}

string Waypointlijst::zoek(string naam)
{	multimap<string, string>::iterator itr;
	
	itr=waypoints.find(naam);
	return itr->second ;
}

int Waypointlijst::save()
{	std::ofstream filestream("Waypoint_file");
	multimap<string, string>::iterator itr;
	itr=waypoints.begin();
	do 
	{	filestream <<itr++->first<<", "<<itr->second;
	}
	while (itr != waypoints.end());
	filestream.close();
	return 1;
}

int  Waypointlijst::load()
{	std::ifstream in_stream ("Waypoint_file");
	string naam, coordinaten;
	char letter=NULL;
	bool succes;
	if (in_stream.is_open());
	{	do
		{	letter= in_stream.get();
			while (letter != ',')
			{	naam+=letter;
				letter= in_stream.get();
 			}
			letter= in_stream.get();
			while (letter != 10 )				//line feed
			{	coordinaten+=letter;
				letter= in_stream.get();
 			}
			waypoints.insert(pair<string, string>(naam, coordinaten));
		} while (!EOF);
	}
	in_stream.close();
	return 1;
}

