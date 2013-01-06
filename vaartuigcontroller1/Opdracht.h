#ifndef OPDRACHT_H
#define OPDRACHT_H

class Opdracht
{ public:
   void licht_schakelen();
   void GPS_invoeren();
  private:
};

class Menu
{ private:
   unsigned int keuze;

  public:
   enum Menu_h { licht_schakelen, GPS_invoeren, terugh} h_menu;
   enum Menu_l { toplicht, ankerlicht, stoomlicht, navigatielicht, deklicht, terugl} l_menu;
   enum Menu_n { positie_invoeren, waypoint_opslaan, waypoint_verwijderen, route_maken, route_wissen, terugn} n_menu;
   int Menukeuze_h();
   int Menukeuze_l();
   int Menukeuze_n();

};

//toon hoofdmenu
//toon submenu GPS invoeren of verlichting
//invoeren waypoits = code 0x40
//schakelen verlichting = code 0x32
//terugmelding status = code 0x64






#endif //OPDRACHT_H