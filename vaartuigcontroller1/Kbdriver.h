#ifndef KBDRIVER_H
#define KBDRIVER_H

#include 

namespace Keyboard
{  

	int leesDirect(int modus, int* keuze)
	{  if (modus == 0)
	{  userinput=_getch();
	   keuze=atoi( userinput.c_str() );
	   return 1;
	}

	void leesMutex(void *args)
	{	while(1)
		{	WaitForSingleObject(keybMutex, INFINITE);
			userinput=getch();
			keuze=atoi( userinput.c_str() );
			ReleaseMutex(keybMutex);
		}
	_endthread();
	}	

	}




#endif //KBDRIVER_H