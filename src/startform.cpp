#include "startform.h"
#include "ui_startform.h"
#include <iostream>
#include "mainwindow.h"
#include "scores.h"
#include <QMessageBox>
#include <QRect>
#include <QPushButton>

using namespace std;

StartForm::StartForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartForm)
{
    ui->setupUi(this);

    ui->stackedWidget->insertWidget(1, &scoreboard);
    ui->stackedWidget->insertWidget(2, &game);

    connect(&scoreboard, SIGNAL(backClicked()), this, SLOT(goBack()));
    connect(&game, SIGNAL(quitClicked()), this, SLOT(goBack()));

}

StartForm::~StartForm()
{
    delete ui;
}

void StartForm::goBack(){
    ui->stackedWidget->setCurrentIndex(0);
}

void StartForm::on_playGame_clicked()
{
    game.reset();
    ui->stackedWidget->setCurrentIndex(2);
}

void StartForm::on_highScore_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartForm::on_loadGame_clicked()
{
    game.load();
    ui->stackedWidget->setCurrentIndex(2);
}

/* Information Button Pop-up*/

void StartForm::on_info1_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("MORE ABOUT THE BUTTONS:\n\n"
                   "\n'Play Game' - starts the game.\n"
                   "\n'High Scores' - displays top users with highest scores.\n"
                   "\n'Load Game' - loads saved data.");
    msgBox.setStandardButtons(QMessageBox::Cancel);
    if(QMessageBox::Cancel){
        msgBox.exec();
    }

}
