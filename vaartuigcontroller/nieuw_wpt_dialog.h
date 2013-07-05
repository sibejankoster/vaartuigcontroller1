#ifndef NIEUW_WPT_DIALOG_H
#define NIEUW_WPT_DIALOG_H

#include <QDialog>

namespace Ui {
class Nieuw_WPT_dialog;
}

class Nieuw_WPT_dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Nieuw_WPT_dialog(QWidget *parent = 0);
    ~Nieuw_WPT_dialog();
    
private:
    Ui::Nieuw_WPT_dialog *ui;
};

#endif // NIEUW_WPT_DIALOG_H
