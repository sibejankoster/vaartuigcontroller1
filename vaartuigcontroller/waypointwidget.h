#ifndef WAYPOINTWIDGET_H
#define WAYPOINTWIDGET_H

#include <QItemselection>
#include <QTabWidget>
#include <QString>

#include "newwaypointtab.h"
#include "tabelmodel.h"

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

class WaypointWidget: public QDialog
{
Q_OBJECT
public:
    WaypointWidget(QWidget *parent = 0);
    void readFromFile (const QString &filenaam);
    void writeToFile (const QString &filenaam);

public slots:
    void addEntry();
    void addEntry(QString naam, QString waypoint);
    void editEntry();
    void verwijderEntry();

signals:
    void selectionChanged (const QItemSelection &selected);
private:
    void setupTabel();
    TabelModel *tabel;
    NewWaypointTab *newWaypointTab;
    QSortFilterProxyModel *proxyModel;
};

#endif // WAYPOINTWIDGET_H
