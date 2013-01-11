#include "Opdracht.h" 
#include <stdio.h>
#include <iostream>

using namespace std;

void Menu::Menukeuze_h()
{  int menutoestand;
   cout <<"----------------------------------"<<endl;
   cout << "1. Licht schakelen" <<endl;
   cout << "2. GPS invoeren" << endl;
   cout <<"----------------------------------"<<endl;
   cout << ">> ";
   return;
}

void Menu::Menukeuze_l()
{  int keuze;
   cout <<"---------menu verlichting---------"<<endl;
   cout << "1. Toplicht" <<endl;
   cout << "2. Ankerlicht" <<endl;
   cout << "3. Stoomlicht" <<endl;
   cout << "4. Navigatielicht" <<endl;
   cout << "5. Deklicht"<<endl;
   cout << "6. Terug"<<endl;
   cout <<"----------------------------------"<<endl;
   cout << ">> ";
   return;  //1.x = keuze submenu 'licht'
}
void Menu::Menukeuze_n()
{  int keuze;
   cout <<"----------menu navigatie-----------"<<endl;
   cout << "1. Positie_invoeren" <<endl;
   cout << "2. Waypoint_opslaan" << endl;
   cout << "3. Waypoint_verwijderen" << endl;
   cout << "4. Route_maken" << endl;
   cout << "5. Route_wissen" << endl;
   cout << "6. Terug" << endl;
   cout <<"----------------------------------"<<endl;
   cout << ">> ";
   return; //  2.x = keuze submenu 'navigatie'
}

