#include "logfile.h"

int Logger::addpoint(GPSpositie wpt) //file wordt telkens vernietigd bij afsluiten
{	struct tm *nu;
    time_t now;
    float NBpos, OLpos;
    float *NBposp, *OLposp;
    NBposp=&NBpos;
    OLposp=&OLpos;
    time(&now);
    nu = localtime(&now);
    std::ofstream filestream("Logfile", fstream::app);
    wpt.getpos(NBposp, OLposp);
    cout.unsetf(ios::floatfield);            // floatfield not set
    cout.precision(5);
    filestream << setprecision(6)<< nu->tm_hour <<":"<<nu->tm_min<<", "<<NBpos<<", "<<OLpos<<endl;
    cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
    filestream.close();
    return 1;
}

int Logger::save_voor_terugvaren()
{	//file wordt opgeslagen als route met naam 'Route0'
    ifstream source("Logfile", ios::binary);
    ofstream dest("Route0", ios::binary);
    istreambuf_iterator<char> begin_source(source);
    istreambuf_iterator<char> end_source;
    ostreambuf_iterator<char> begin_dest(dest);
    copy(begin_source, end_source, begin_dest);
    source.close();
    dest.close();
    return 1;
}

void Logger::wissen()
{  std::ofstream filestream("Logfile", fstream::out);
   filestream << "";
   filestream.close();
}
