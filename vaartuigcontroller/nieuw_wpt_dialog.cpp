#include "nieuw_wpt_dialog.h"
#include "ui_nieuw_wpt_dialog.h"

Nieuw_WPT_dialog::Nieuw_WPT_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nieuw_WPT_dialog)
{
    ui->setupUi(this);
}

Nieuw_WPT_dialog::~Nieuw_WPT_dialog()
{
    delete ui;
}
