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
   //enum Menu_h { licht_schakelen, GPS_invoeren, terugh} h_menu;
   //enum Menu_l { toplicht, ankerlicht, stoomlicht, navigatielicht, deklicht, terugl} l_menu;
   //enum Menu_n { positie_invoeren, waypoint_opslaan, waypoint_verwijderen, route_maken, route_wissen, terugn} n_menu;
   void Menukeuze_h();
   void Menukeuze_l();
   void Menukeuze_n();
};


#endif //OPDRACHT_H