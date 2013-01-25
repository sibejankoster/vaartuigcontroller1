#ifndef LAYOUT_H
#define LAYOUT_H

#include <string>

class Window 
{  private:
     int x1, x2, y1, y2;
	 std::string* A;
public:
	Window(int x1, int x2, int y1, int y2);
	void erase();
	void print(std::string A[]);
};

#endif // LAYOUT_H