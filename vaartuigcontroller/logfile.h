#ifndef LOGFILE_H
#define LOGFILE_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <time.h>
#include "gps.h"

class Logger
{private:

public:
    int addpoint(GPSpositie gpspos);
    int save_voor_terugvaren();
    void wissen();
};

#endif // LOGFILE_H
