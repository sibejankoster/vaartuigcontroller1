//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : vaartuigcontroller
//  @ File Name : Toestand.h
//  @ Date : 6-12-2012
//  @ Author : S.J. Koster
//
//

#if !defined(_TOESTAND_H)
#define _TOESTAND_H

class Toestand {
public:
	void toplicht_schakelen();
	void ankerlicht_schakelen();
	void stoomlicht_schakelen();
	void navigatielicht_schakelen();
	void deklicht_schakelen();
	void navigatiealarm_schakelen();
	void wateralarm_schakelen();
	double bericht_ID_ophogen(double bericht_ID);
	void zet_OL(int* graden_OL, int* minuten_OL);
	void zet_NB(int* graden_NB, int* minuten_NB);
	void zet_roerstand(int graden);
	int get_roerstand();

private:
	bool toplicht_aan;
	bool ankerlicht_aan;
	bool stoomlicht_aan;
	bool navigatielicht_aan;
	bool deklicht_aan;
	bool navigatiealarm_aan;
	bool wateralarm_aan;
	double bericht_ID;
	int graden_OL;
	int minuten_OL;
	int graden_NB;
	int minuten_NB;
	int roerstand;
};

#endif  //_TOESTAND_H
