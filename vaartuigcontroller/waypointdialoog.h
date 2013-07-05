#ifndef WAYPOINTDIALOOG_H
#define WAYPOINTDIALOOG_H
#include <QtGui>

#include "waypointwidget.h"

class Waypointdialoog: public QDialog
{
    Q_OBJECT

public:
    Waypointdialoog(QWidget*parent =0);
signals:
    void accept(const QString &str);

private slots:
    void OKClicked();

private:
    QLabel *lbl_naam, *lbl_NB, *lbl_OL;
    QLineEdit *lne_naam, *lne_NB, *lne_OL;
    QPushButton *btn_OK;
};

#endif // WAYPOINTDIALOOG_H
