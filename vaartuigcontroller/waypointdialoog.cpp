#include <QtGui>
#include "waypointdialoog.h"

Waypointdialoog::Waypointdialoog(QWidget *parent): QDialog(parent)
{   lbl_naam = new QLabel (tr("Naam"));
    lne_naam = new QLineEdit;
    lbl_naam->setBuddy(lne_naam);

    lbl_NB = new QLabel (tr("NB xx.xxxxx"));
    lne_NB = new QLineEdit;
    lbl_NB->setBuddy(lne_NB);

    lbl_OL = new QLabel (tr("OL xx.xxxxx"));
    lne_OL = new QLineEdit;
    lbl_OL->setBuddy(lne_OL);

    btn_OK = new QPushButton("OK");
}
