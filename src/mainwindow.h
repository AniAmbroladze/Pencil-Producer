#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTimer>

#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "scores.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "unistd.h"

/**
 * \brief Getting MainWondow class from Ui namespace
 *
 */

namespace Ui {
    class MainWindow;
}
/*
 * \brief class MainWindow extending from QMainWindow
 * uses Q_OBJECT macro defined in QMainWindow header
 *
 */

class MainWindow : public QMainWindow, public Pencil
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer = new QTimer(this);
    QTimer *pencilSeller = new QTimer(this);
    QTimer *timerFast = new QTimer(this);
    void load();
    void reset();
    void upload();
    void save();
    string getlink();

private slots:
    void on_makePencil_clicked();
    void runner();
    void seller();
    void apm2Seller();
    void calculatePrices();
    void generateIntelligence();

    void on_buyWood_clicked();
    void on_buyGraphite_clicked();
    void on_buyApm_clicked();
    void on_upgradeApm_clicked();

    void checkbuttons();
    void check_upgradeApm();

    void on_increasePencil_clicked();
    void on_decreasePencil_clicked();

    void on_saveState_clicked();
    void on_loadState_clicked();

    void on_debugBalance_clicked();
    void on_debugPencils_clicked();
    void on_debugTotalPencils_clicked();
    void on_debugWoodGraphite_clicked();
    void on_upgradeMarketing_clicked();
    void on_pushButton_clicked();

    void on_incINT_clicked();
    void on_incMAR_clicked();
    void on_info_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void quitClicked();

};

#endif // MAINWINDOW_H
