#if !defined(DYNAMICS_H)
#define DYNAMICS_H

/* Sumuleren van de beweging van het vaartuig
*/

namespace Dynamics
{   void berekenpositie(int koers, int snelheid, float* NBcoord, float* OLcoord);
    void bereken_koers_en_snelheid(int gasstand, int roerstand, float* snelheid, int* koers);
};


#endif //DYNAMICS_H
