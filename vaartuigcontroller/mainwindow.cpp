#include <QDateEdit>
#include <QtWidgets>
#include <QMenuBar>
#include <QFileDialog>
#include <QAction>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gps.h"
#include "canformat.h"
#include "packet.h"
#include "file.h"
#include "logfile.h"
#include "dynamics.h"
#include "wptlijst.h"


// Sensoren
int toplicht=false;
int aan_uit_schakelaar = true;
int ankerlicht = false;
int navigatielicht =false;
int deklicht = false;
int stoomlicht=false;
int sounder = true;
int dieptealarm=false;
int navigatiealarm=false;
int alarm_reset;
int waterBB=250;
int waterSB=200;
float lichtaccu=12.2;
int diesel=200;
int windrichting=45;
float windsterkte=3;
int VHFkanaal=16;
float logsnelheid=0;
int toeren;
float motoraccu=12.3;
int olietemperatuur =20;
int koelwater = 5;
int *otempp=& olietemperatuur;
int *dieselp =&diesel;
int *waterSBp=&waterSB;
int *waterBBp=&waterBB;
int *tlicht=&toplicht;
int *alicht=&ankerlicht;
int *slicht=&stoomlicht;
int *nlicht=&navigatielicht;
int *dlicht=&deklicht;
int *dalarm=&dieptealarm;
int *nalarm=&navigatiealarm;

//
//GPS, navigatie
GPSpositie gpspos, MOBpositie;
Waypointlijst wptlijst;
Waypointlijst *wptlijstp=&wptlijst;
Logger GPSlog;
float NB, NBnieuw;
float OL, OLnieuw;
float* NBcoordp=&NB;
float* OLcoordp=&OL;
int bearing;
int heading;
float GPSsnelheid;
int koers=0;
int* koersp= &koers;
float snelheid=0;
float *snelheidsp= &snelheid;
int gasstand=0;
int roer=0;
int *roerp=&roer;
int loopteller=0;
//
//CAN
unsigned int id=0;
unsigned char RTR=0, lengte=0;
unsigned int *ptr_id=&id;
unsigned char *ptr_RTR=&RTR;
unsigned char *ptr_lengte=&lengte;
File CANfile, GPSfile;
Id0x62 CANbericht;
Id0x40 GPSbericht;
Packet pack;
L_packet llp;
L_packet* llp_p= &llp;
unsigned char datablock[8];
//
//ui  // geen objecten declareren die al in de Ui zijn geclareerd

//

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{   ui->setupUi(this);
    update();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    gpspos.put(54.2,4.0);
    createMenus();
}

MainWindow::~MainWindow()
{   delete ui;
}

void MainWindow::populateWPTLijst()
{   //new QListWidgetItem (tr("Oak"),WPTLijst);

}

void MainWindow::createMenus()
{   filemenu = menuBar()->addMenu("&Waypoint");
    nieuwWPTAct = new QAction("&Nieuw..", this);
    filemenu->addAction(nieuwWPTAct);
    connect (nieuwWPTAct, SIGNAL(triggered()), this, SLOT (nieuwWPT()));
    editWPTAct = new QAction("&Edit..", this);
    filemenu->addAction(editWPTAct);
    connect (editWPTAct, SIGNAL(triggered()), this, SLOT (editWPT()));
    deleteWPTAct = new QAction("&Delete..", this);
    filemenu->addAction(deleteWPTAct);
    connect (deleteWPTAct, SIGNAL(triggered()), this, SLOT (deleteWPT()));

    filemenu = menuBar()->addMenu("&Route");
    openAct = new QAction("&Open..", this);
    filemenu->addAction(openAct);
    connect (openAct, SIGNAL(triggered()), this, SLOT (openFile()));
    saveAct = new QAction("&Opslaan Als..", this);
    filemenu->addAction(saveAct);
    connect (saveAct, SIGNAL(triggered()), this, SLOT (saveFile()));
    filemenu->addSeparator();
    nieuwRTAct = new QAction("&Nieuw..", this);
    filemenu->addAction(nieuwRTAct);
    connect (nieuwRTAct, SIGNAL(triggered()), this, SLOT (nieuwRT()));
    editRTAct = new QAction("&Edit..", this);
    filemenu->addAction(editRTAct);
    connect (editRTAct, SIGNAL(triggered()), this, SLOT (editRT()));
    deleteWPTAct = new QAction("&Delete..", this);
    filemenu->addAction(deleteWPTAct);
    connect (deleteWPTAct, SIGNAL(triggered()), this, SLOT (deleteWPT()));
}

void MainWindow::laadWaypointLijst()
{   wptlijst.load(wptlijstp);
}

void MainWindow::on_btn_toplicht_toggled(bool checked)
{   toplicht = checked;
}

void MainWindow::on_btn_aan_uit_toggled(bool checked)
{   aan_uit_schakelaar=checked;
}

void MainWindow::on_btn_ankerlicht_toggled(bool checked)
{   ankerlicht=checked;
}

void MainWindow::on_btn_navigatielicht_toggled(bool checked)
{   navigatielicht=checked;
}

void MainWindow::on_btn_deklicht_toggled(bool checked)
{   deklicht = checked;
}

void MainWindow::on_btn_sounder_toggled(bool checked)
{   sounder=checked;
    update();
}

void MainWindow::on_btn_alarm_clicked(bool checked)
{   alarm_reset=checked;
}
void MainWindow::update()  //dit vervult de functie van scheduler
{// Sla sensorwaarden op in 0x62 file
    CANbericht.maak_id0x62(datablock, olietemperatuur, diesel, waterSB, waterBB, toplicht,
                           ankerlicht, stoomlicht, navigatielicht, deklicht,dieptealarm, navigatiealarm);
    pack.maakpacket (&llp, 0x32, 1,6, datablock);
    CANfile.zendbericht(&llp,3);
//
// lees sensorwaarden uit 0x62 file
    CANfile.leesbericht(llp_p);
    pack.leespacket(llp_p, 0x32, 1, 3, datablock);
    CANbericht.lees_id0x62(datablock,*otempp,*dieselp,*waterSBp,*waterBBp,*tlicht,*alicht,*slicht,
                           *nlicht,*dlicht,*dalarm,*nalarm);
//
// GPSlogger //slaat iedere 10 seconden een positie op
    if (loopteller==10)
    {   GPSlog.addpoint(gpspos);
        gpspos.getpos(NBcoordp, OLcoordp);
        loopteller=0;
    }
    loopteller++;
//
//  Opdrachten verwerken
    Dynamics::bereken_koers_en_snelheid(gasstand, roer, snelheidsp, koersp);
    logsnelheid=*snelheidsp;
    GPSsnelheid=snelheid;
//
// positie bijwerken //berekent nieuwe GPS waarden
   Dynamics::berekenpositie(koers, snelheid, NBcoordp, OLcoordp);
//
// update scherm
    this->ui->lcd_waterSB->display(waterSB);
    this->ui->lcd_waterBB->display(waterBB);
    this->ui->lcd_lichtaccu->display(lichtaccu);
    this->ui->lcd_diesel->display(diesel);
    this->ui->lcd_windrichting->display(windrichting);
    this->ui->lcd_windsterkte->display(windsterkte);
    this->ui->lcd_VHF->display(VHFkanaal);
    this->ui->lcd_roerstand->display(roer);
    this->ui->lcd_logsnelheid->display(logsnelheid);
    this->ui->lcd_toeren->display(toeren);
    this->ui->lcd_motoraccu->display(motoraccu);
    this->ui->lcd_olietemperatuur->display(olietemperatuur);
    this->ui->lcd_koelwater->display(koelwater);
    this->ui->lcd_NB->display(NB);
    this->ui->lcd_OL->display(OL);
    this->ui->lcd_bearing->display(bearing);
    this->ui->lcd_heading->display(heading);
    this->ui->lcd_GPSsnelheid->display(GPSsnelheid);
    QTime actuele_tijd=QTime::currentTime();
    tijd = actuele_tijd.toString();
    this->ui->klok->setText(tijd);

}

void MainWindow::on_btn_aan_uit_clicked()
{    close();
}

void MainWindow::on_btn_sneller_pressed()
{   gasstand+=1;
    if (gasstand >10) gasstand=10;
    toeren=gasstand*600;
}

void MainWindow::on_btn_trager_pressed()
{   gasstand-=1;
    if (gasstand <-10)gasstand=-10;
    toeren = gasstand*600;
}

void MainWindow::on_btn_SB_pressed()
{   roer+=15;
    if (roer>90) roer=90;
}

void MainWindow::on_btn_BB_pressed()
{   roer-=15;
    if (roer<-90) roer=-90;
}

void MainWindow::openFile()
{   QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
//        <route->readFromFile(fileName)
        ;
}

void MainWindow::saveFile()
{   QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty())
//        <route->writeToFile(fileName)
        ;
}

void MainWindow::editWPT()
{
}

void MainWindow::deleteWPT()
{}
void MainWindow::nieuwRT()
{}
void MainWindow::editRT()
{}
void MainWindow::deleteRT()
{}








