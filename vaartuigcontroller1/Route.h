//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : vaartuigcontroller
//  @ File Name : Route.h
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//


#if !defined(_ROUTE_H)
#define _ROUTE_H

#include "Koerslog.h"

class Route : public Koerslog {
public:
	void samenstellen();
	void save();
	void delete();
	void activeerRoute();
	void terugvaren();
private:
	int routenaam;
};

#endif  //_ROUTE_H
