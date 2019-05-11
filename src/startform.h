#ifndef STARTFORM_H
#define STARTFORM_H

#include <QWidget>
#include "mainwindow.h"
#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "startform.h"
#include "scores.h"

namespace Ui {
class StartForm;
}

class StartForm : public QWidget, public Pencil
{
    Q_OBJECT

public:
    explicit StartForm(QWidget *parent = nullptr);
    ~StartForm();

private slots:

    void goBack();

    void on_playGame_clicked();

    void on_highScore_clicked();

    void on_loadGame_clicked();

    void on_info1_clicked();

private:
    scores scoreboard;
    MainWindow game;
    Ui::StartForm *ui;
};

#endif // STARTFORM_H
