#include "dynamics.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

#define PI 3.14159265
void Dynamics::berekenpositie(int koers, int snelheid, float* NBcoord, float* OLcoord)
{  *NBcoord += snelheid*std::cos (koers*2*PI/360)/1200;  //dit hangt af van de kloksnelheid
   *OLcoord += snelheid*std::sin (koers*2*PI/360)/1200;  //1 graad = 60 nautische mijl (NB)
   // geen grootcirkelberekeningen
}
void Dynamics::bereken_koers_en_snelheid(int gasstand, int roerstand, float* snelheidsp, int* koersp)
{	*koersp += roerstand/10;								//veranderstelde reactiesnelheid op roer
    int snelheid = *snelheidsp;
    snelheid = gasstand;	//kwadratische weerstand //--> controleren of dit binnen int past
    *snelheidsp=snelheid;
}
