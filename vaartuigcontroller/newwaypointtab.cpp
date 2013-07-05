#include "adddialog.h"
#include "newwaypointtab.h"

#include <QtWidgets>

NewWaypointTab::NewWaypointTab(QWidget *parent)
{
    Q_UNUSED(parent);

    descriptionLabel = new QLabel(tr("Er zij nog geen waypoints ingevoerd. "
                                      "\nKlik op 'Toevoegen'."));

    addButton = new QPushButton(tr("Toevoegen"));

    connect(addButton, SIGNAL(clicked()), this, SLOT(addEntry()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}

void NewWaypointTab::addEntry()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString address = aDialog.waypointText->toPlainText();

        emit sendDetails(name, address);
    }
}
