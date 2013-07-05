#ifndef NEWWAYPOINTTAB_H
#define NEWWAYPOINTTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

class NewWaypointTab : public QWidget
{
    Q_OBJECT

public:
    NewWaypointTab(QWidget *parent = 0);

public slots:
    void addEntry();

signals:
    void sendDetails(QString name, QString address);

private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;

};

#endif // NEWWAYPOINTTAB_H
