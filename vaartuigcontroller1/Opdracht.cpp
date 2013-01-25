#include "Opdracht.h" 
#include <stdio.h>
#include <iostream>
#include "Layout.h"
using namespace std;

void Menu::Menukeuze_h(string A[])
{  A[0]="+----------------------+";
   A[1]= "1. Licht schakelen";
   A[2]= "2. GPS invoeren";
   A[3]= "3. Navigatie instellen"; 
   A[4]="+----------------------+";
   A[5]=">>";
   A[6]="einde";
}
void Menu::Menukeuze_l(string A[])
{  A[0]="+------menu 1:verlichting-------+";
   A[1]="1. Toplicht";
   A[2]="2. Ankerlicht";
   A[3]="3. Stoomlicht";
   A[4]="4. Navigatielicht";
   A[5]="5. Deklicht";
   A[6]="6. Terug";
   A[7]="+--------------------------------+";
   A[8]=">>";
   A[9]="einde";
}
void Menu::Menukeuze_g(string A[])
{  A[0]="+---------menu 2: GPS------------+";
   A[1]="1. Huidige positie opslaan";
   A[2]="2. Waypoint_invoeren";
   A[3]="3. Waypoint_verwijderen";
   A[4]="4. Route_maken";
   A[5]="5. Route_wissen";
   A[6]="6. Route loggen aan- en uitzetten";
   A[7]="7. Terug";
   A[8]="+--------------------------------+";
   A[9]=">>";
   A[10]="einde";
}
void Menu::Menukeuze_g1(string A[])
{  A[0]="+-Menu 2.1: Opslaan huidige positie-+";
   A[1]="1. Tijdelijk opslaan (MOB)";
   A[2]="2. Opslaan als Waypoint";
   A[3]="3. Terug               ";
   A[4]="+-----------------------------------+";
   A[5]=">>";
   A[6]="einde";
}

void Menu::Menukeuze_g2(string A[])
{  A[0]="+--Menu 2.2: Waypoint invoeren---+";
   A[1]="1. Naam invoeren";
   A[2]="2. Positie invoeren";
   A[3]="3. Terug          ";
   A[4]="+--------------------------------+";
   A[5]=">>";
   A[6]="einde";
}
void Menu::Menukeuze_g2sub(string A[])
{  A[0]="Voer een naam in voor de waypoint";
   A[1]=">>";
   A[2]="einde";
}
void Menu::Menukeuze_g2sub2(string A[])
{  A[0]="Voer de coordinaten in, gescheiden door";
   A[1]="een komma: bv 54.56, 5.40 (in grad)";    
   A[2]=">>";
   A[3]="einde";
}

void Menu::Menukeuze_g3(string A[])
{  A[0]="+--Menu 2.3: Waypoint wissen-----+";
   A[1]="1. Waypoint kiezen";
   A[2]="2. Bestig wissen";
   A[3]="3. Terug zonder wissen   ";
   A[4]="+--------------------------------+";
   A[5]=">>";
   A[6]="einde";
}
void Menu::Menukeuze_g4(string A[])
{  A[0]="+--Menu 2.4: Route samenstellen--+";
   A[1]="1. Naam route";
   A[2]="2. Waypoint toevoegen";
   A[3]="3. Opslaan   ";
   A[4]="4. Terug ";
   A[5]="+--------------------------------+";
   A[6]=">>";
   A[7]="einde";
}
void Menu::Menukeuze_g5(string A[])
{  A[0]="+--Menu 2.5: Route wissen--------+";
   A[1]="1. Naam route";
   A[2]="2. Bevestig wissen";
   A[3]="3. Terug ";
   A[4]="+--------------------------------+";
   A[5]=">>";
   A[6]="einde";
}

void Menu::Menukeuze_n(string A[])
{  A[0]="+--------menu 3: navigatie--------+";
   A[1]="1. Vaste koers varen";
   A[2]="2. Koers naar waypoint";
   A[3]="3. Route varen";
   A[4]="4. Zelfde route terugvaren";
   A[5]="5. Automaat in- of uitschakelen";
   A[6]="6. Toerenregelaar instellen";
   A[7]="7. Dieptealarm instellen";
   A[8]="8. Roer instellen";
   A[9]="9. Terug";
   A[10]="+--------------------------------+";
   A[11]=">>";
   A[12]="einde";
}

void Menu::Menukeuze_n1(string A[])
{  A[0]="+--Menu 3.1: Vaste koers varen---+";
   A[1]="1. Koers instellen";
   A[2]="2. 1 streep naar bakboord";
   A[3]="3. 1 streep naar sturboord";
   A[4]="4. Automaat uitschakelen ";
   A[5]="5. Terug";
   A[6]="+--------------------------------+";
   A[7]=">>";
   A[8]="einde";
}
void Menu::Menukeuze_n2(string A[])
{  A[0]="+-Menu 3.2.: Koers naar waypoint-+";
   A[1]="1. Waypoint kiezen";
   A[2]="2. Bevestig koersen naar waypoint";
   A[3]="3. Terug";
   A[4]="+--------------------------------+";
   A[5]=">>";
   A[6]="einde";
}
void Menu::Menukeuze_n3(string A[])
{  A[0]="+-----Menu 3.3: Route varen------+";
   A[1]="1. Route kiezen";
   A[2]="2. Bevestig deze route varen";
   A[3]="3. Routevaren uitschakelen";
   A[4]="4. Terug";
   A[5]="+--------------------------------+";
   A[6]=">>";
   A[7]="einde";
}
void Menu::Menukeuze_n4(string A[])
{  A[0]="+---Menu 3.4: Terugvaren---------+";
   A[1]="1. Terugvaren inschakelen";
   A[2]="2. Terugvaren uitschakelen";
   A[3]="3. Vorige menu";
   A[4]="+--------------------------------+";
   A[5]=">>";
   A[6]="einde";
}

