#include "adddialog.h"
#include "waypointwidget.h"

#include <QtWidgets>

WaypointWidget::WaypointWidget(QWidget *parent)
    : QDialog(parent)
{
    tabel = new TabelModel(this);
    newWaypointTab = new NewWaypointTab(this);
    connect(newWaypointTab, SIGNAL(sendDetails(QString, QString)),
        this, SLOT(addEntry(QString, QString)));



    setupTabel();
}

void WaypointWidget::addEntry()
{
    AddDialog aDialog;

    if (aDialog.exec()) {
        QString name = aDialog.nameText->text();
        QString waypoint = aDialog.waypointText->toPlainText();

        addEntry(name, waypoint);
    }
}

void WaypointWidget::addEntry(QString name, QString waypoint)
{
    QList<QPair<QString, QString> >list = tabel->getList();
    QPair<QString, QString> pair(name, waypoint);

    if (!list.contains(pair)) {
        tabel->insertRows(0, 1, QModelIndex());

        QModelIndex index = tabel->index(0, 0, QModelIndex());
        tabel->setData(index, name, Qt::EditRole);
        index = tabel->index(0, 1, QModelIndex());
        tabel->setData(index, waypoint, Qt::EditRole);
        }
        else {
        QMessageBox::information(this, tr("Dubbele naam"),
            tr("De naam \"%1\" bestaat al.").arg(name));
    }
}

void WaypointWidget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    QString name;
    QString waypoint;
    int row = -1;

    foreach (QModelIndex index, indexes) {
        row = proxy->mapToSource(index).row();
        QModelIndex nameIndex = tabel->index(row, 0, QModelIndex());
        QVariant varName = tabel->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex waypointIndex = tabel->index(row, 1, QModelIndex());
        QVariant varAddr = tabel->data(waypointIndex, Qt::DisplayRole);
        waypoint = varAddr.toString();
    }

    AddDialog aDialog;
    aDialog.setWindowTitle(tr("Edit een waypoint"));

    aDialog.nameText->setReadOnly(true);
    aDialog.nameText->setText(name);
    aDialog.waypointText->setText(waypoint);

    if (aDialog.exec()) {
        QString newwaypoint = aDialog.waypointText->toPlainText();
        if (newwaypoint != waypoint) {
            QModelIndex index = tabel->index(row, 1, QModelIndex());
            tabel->setData(index, newwaypoint, Qt::EditRole);
        }
    }
}

void WaypointWidget::verwijderEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
        int row = proxy->mapToSource(index).row();
        tabel->removeRows(row, 1, QModelIndex());
    }

    if (tabel->rowCount(QModelIndex()) == 0) {
        insertTab(0, newWaypointTab, "Waypoints");
    }
}

void WaypointWidget::setupTabel()
{
    QStringList groups;
    groups << "ABC" << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VW" << "XYZ";

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(tabel);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);
        tableView->setSortingEnabled(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        QString newStr = QString("^[%1].*").arg(str);

        proxyModel->setFilterRegExp(QRegExp(newStr, Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(0);
        proxyModel->sort(0, Qt::AscendingOrder);

        connect(tableView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SIGNAL(selectionChanged(QItemSelection)));

        }
}

void WaypointWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Kan file niet openen"),
            file.errorString());
        return;
    }

    QList<QPair<QString, QString> > pairs = tabel->getList();
    QDataStream in(&file);
    in >> pairs;

    if (pairs.isEmpty()) {
        QMessageBox::information(this, tr("Geen waypoints ingevoerd"),
                                 tr("De file bevat geen waypoints."));
    } else {
        for (int i=0; i<pairs.size(); ++i) {
            QPair<QString, QString> p = pairs.at(i);
            addEntry(p.first, p.second);
        }
    }
}

void WaypointWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Kan file niet openen"), file.errorString());
        return;
    }

    QList<QPair<QString, QString> > pairs = tabel->getList();
    QDataStream out(&file);
    out << pairs;
}
