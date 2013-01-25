#ifndef OPDRACHT_H
#define OPDRACHT_H
#include <string>

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
   void Menukeuze_h(std::string* A);
   void Menukeuze_l(std::string* A);
   void Menukeuze_g(std::string* A);
   void Menukeuze_n(std::string* A);
   void Menukeuze_n1(std::string* A);
   void Menukeuze_g1(std::string* A);
   void Menukeuze_g2(std::string* A);
   void Menukeuze_g2sub(std::string* A);
   void Menukeuze_g2sub2(std::string* A);
   void Menukeuze_g3(std::string* A);
   void Menukeuze_g4(std::string* A);
   void Menukeuze_g5(std::string* A);
   void Menukeuze_n2(std::string* A);
   void Menukeuze_n3(std::string* A);
   void Menukeuze_n4(std::string* A);
};


#endif //OPDRACHT_H