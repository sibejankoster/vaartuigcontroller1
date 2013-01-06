#include "Opdracht.h" 
#include <stdio.h>
#include <iostream>

using namespace std;

int Menu::Menukeuze_h()
{  int keuze;
   cout <<"----------------------------------"<<endl;
   cout << "1. Licht_schakelen" <<endl;
   cout << "2. GPS_invoeren" << endl;
   cout << "3. Terug" <<endl ;
   cout <<"----------------------------------"<<endl;
   cout << ">> ";
   cin>>keuze;
   return keuze;
}

int Menu::Menukeuze_l()
{  int keuze;
   cout <<"----------------------------------"<<endl;
   cout << "1. Toplicht" <<endl;
   cout << "2. Ankerlicht" <<endl;
   cout << "3. Stoomlicht" <<endl;
   cout << "4. Navigatielicht" <<endl;
   cout << "5. Terug"<<endl;
   cout <<"----------------------------------"<<endl;
   cout << ">> ";
   cin>>keuze;
   return keuze;
}
int Menu::Menukeuze_n()
{  int keuze;
   cout <<"----------------------------------"<<endl;
   cout << "1. Positie_invoeren" <<endl;
   cout << "2. Waypoint_opslaan" << endl;
   cout << "3. Waypoint_verwijderen" << endl;
   cout << "4. Route_maken" << endl;
   cout << "5. Route_wissen" << endl;
   cout << "6. Terug" << endl;
   cout <<"----------------------------------"<<endl;
   cout << ">> ";
   cin>>keuze;  return keuze;
}

