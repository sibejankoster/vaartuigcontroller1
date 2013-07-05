#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     QString tijd;
     void createMenus();
     void laadWaypointLijst();
     void populateWPTLijst();

private slots:
    void on_btn_toplicht_toggled(bool checked);

    void on_btn_aan_uit_toggled(bool checked);

    void on_btn_ankerlicht_toggled(bool checked);

    void on_btn_navigatielicht_toggled(bool checked);

    void on_btn_deklicht_toggled(bool checked);

    void on_btn_sounder_toggled(bool checked);

    void on_btn_alarm_clicked(bool checked);

    void update();

    void openFile();

    void saveFile();

    void editWPT();

    void deleteWPT();

    void nieuwRT();

    void editRT();

    void deleteRT();

    void on_btn_aan_uit_clicked();

    void on_btn_sneller_pressed();

    void on_btn_trager_pressed();

    void on_btn_SB_pressed();

    void on_btn_BB_pressed();

private:
     Ui::MainWindow *ui;
     QTimer *timer;
     QMenu *filemenu;
     QMenu *actionmenu;
     QAction *openAct;
     QAction *saveAct;
     QAction *addAct;
     QAction *editAct;
     QAction *removeAct;
     QAction *insertAct;
     QAction *nieuwWPTAct;
     QAction *editWPTAct;
     QAction *deleteWPTAct;
     QAction *nieuwRTAct;
     QAction *editRTAct;
     QAction *deleteRTAct;
     QString *WPTLijst;
};

#endif // MAINWINDOW_H
