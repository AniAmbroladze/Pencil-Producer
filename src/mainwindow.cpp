#include <iostream>
#include <stdio.h>
#include <fstream>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QCheckBox>
#include <QAbstractButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pencil.h"
#include "production.h"
#include "wallet.h"

using namespace std;

/* Start: Initialization */

/// Mainwindow constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /// Label is set to display as soon as the MainWindow class is constructed
    ui->setupUi(this);

    /// Timer initialization
    connect(timer, SIGNAL(timeout()), this, SLOT(apm2Seller()));
    connect(timer, SIGNAL(timeout()), this, SLOT(generateIntelligence()));
    connect(timer, SIGNAL(timeout()), this, SLOT(check_upgradeApm()));
    timer->start(1000);

    connect(pencilSeller, SIGNAL(timeout()), this, SLOT(seller()));
    pencilSeller->start(200);

    connect(timerFast, SIGNAL(timeout()), this, SLOT(runner()));

    timerFast->start(100);

    ///This timer is used for calculating prices of graphite and wood every 5 sec.
    QTimer *timer5s = new QTimer(this);
    connect(timer5s, SIGNAL(timeout()), this, SLOT(calculatePrices()));
    timer5s->start(5000);

    ///Buttons and labels to be hidden initially
    ui->intelligence->setHidden(true);
    ui->intelligenceLabel->setHidden(true);

    ui->upgradeMarketing->setHidden(true);
    ui->valueofMarketing->setHidden(true);

    ui->debugBalance->setHidden(true);
    ui->debugPencils->setHidden(true);
    ui->debugTotalPencils->setHidden(true);
    ui->debugWoodGraphite->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* End: Initialization */

/* Start: Functions running every second */

///Function to calculate prices of graphite and wood every 5 second
void MainWindow::calculatePrices(){
  Production::calculatePrices();
}
/// Function that updates ui labels every fraction of a second
void MainWindow::runner()
{
    checkbuttons();
    ui->inventory->setText(QString::number(Pencil::numberofPencil));
    ui->wood->setText(QString::number(Production::numberofWood));
    ui->graphite->setText(QString::number(Production::numberofGraphite));
    ui->priceofWood->setText("$ " + QString::number( Production::priceofWood));
    ui->priceofGraphite->setText("$ "+QString::number(Production::priceofGraphite));

    ui->balance->setText("$ " + QString::number(Wallet::balance));
    ui->intelligence->setText(QString::number(Wallet::intelligence));

    ui->pencilPrice->setText("$ " + QString::number(Pencil::priceofPencil));
    ui->publicDemand->setText(QString::number(Pencil::rateofPencil));
    ui->totalinventory->setText(QString::number(Pencil::totalnumberofPencil));

    ui->numberofApm->setText(QString::number(Pencil::numberofApm));
    ui->priceofApm->setText("$ " + QString::number(Pencil::priceofApm));
    ui->rateofApm->setText(QString::number(Pencil::rateofApm) + " pencils/min");
    ui->valueofMarketing->setText(QString::number(Pencil::valueofMarketing));
    ui->unlockedMarketing->setText(QString::number(Pencil::unlockedMarketing));

    checkbuttons();
}

//! Function to check which buttons need to be disabled. */
/* setEnabled(0) = disable button, setEnabled(1) = enable button */
void MainWindow::checkbuttons(){
  if (Wallet::balance < Production::priceofGraphite){
    ui->buyGraphite->setEnabled(0);
  }else{
    ui->buyGraphite->setEnabled(1);
  }

  if (Wallet::balance < Production::priceofWood){
    ui->buyWood->setEnabled(0);
  }else{
    ui->buyWood->setEnabled(1);
  }

  if (Wallet::balance < Pencil::priceofApm){
    ui->buyApm->setEnabled(0);
  }else{
    ui->buyApm->setEnabled(1);
  }

  ///Prevent the user from setting the price lower than 0
  if (Pencil::priceofPencil <= 0.1){
    ui->decreasePencil->setEnabled(0);
  }else{
    ui->decreasePencil->setEnabled(1);
  }

  if (Pencil::upgradeApm50 == false && Pencil::upgradeApm5000 == false){
    ui->upgradeApm->setEnabled(0);
  }else if (Pencil::finishedUpgrade50 == true && Pencil::finishedUpgrade5000 == false){
    ui->upgradeApm->setEnabled(0);
  }else if (Pencil::finishedUpgrade50 == true && Pencil::finishedUpgrade5000 == true){
    ui->upgradeApm->setEnabled(0);
  }else{
    ui->upgradeApm->setEnabled(1);
  }

  if (ui->debugtool->isChecked()){
    ui->debugBalance->setHidden(false);
    ui->debugPencils->setHidden(false);
    ui->debugTotalPencils->setHidden(false);
    ui->debugWoodGraphite->setHidden(false);
    ui->incINT->setHidden(false);
    ui->incMAR->setHidden(false);
  }else{
    ui->debugBalance->setHidden(true);
    ui->debugPencils->setHidden(true);
    ui->debugTotalPencils->setHidden(true);
    ui->debugWoodGraphite->setHidden(true);
    ui->incINT->setHidden(true);
    ui->incMAR->setHidden(true);
  }


}
/*! Function to sell pencils continuously according to rate */
void MainWindow::seller(){
    Pencil::sell();
    pencilSeller->start(200/Pencil::getRateOfPencil());
}

/*Function to produce pencils continuously every second according to number of APM's and rate */
void MainWindow::apm2Seller(){
    Pencil::producePencilApm();
}

/*Function to generate 1 intelligence every second */

void MainWindow::generateIntelligence(){
    if (Pencil::totalnumberofPencil >= 3000 && Wallet::intelligence <= 200 ){ ///Start generating intelligence after
                                                                            /// total pencils manafactured reaches 3000
         Wallet::increaseIntelligence();
         ui->intelligence->setHidden(false);
         ui->intelligenceLabel->setHidden(false);

         ui->upgradeMarketing->setHidden(false); ///Marketing unlocks when intelligence does.
         ui->valueofMarketing->setHidden(false);
    }
}

void MainWindow::check_upgradeApm(){
  if (Wallet::intelligence >= 50 && Pencil::upgradeApm50 == false && Pencil::finishedUpgrade50 == false){
    Pencil::upgradeApm50 = true;
  }
  if (Wallet::intelligence >= 100 && Pencil::totalnumberofPencil >= 5000 && Pencil::upgradeApm5000 == false  && Pencil::finishedUpgrade5000 == false){
    Pencil::upgradeApm5000 = true;
  }
}

/* End : Functions running every second */

/* Start: Buttons and their functionalities */

void MainWindow::on_saveState_clicked(){
    save();
    upload();
}

void MainWindow::on_loadState_clicked(){
  load();
}

void MainWindow::on_buyWood_clicked()
{
    Production::buyWood();
    checkbuttons();
}

void MainWindow::on_buyGraphite_clicked()
{
    Production::buyGraphite();
    checkbuttons();
}

void MainWindow::on_makePencil_clicked()
{
    Pencil::producePencil();
}

void MainWindow::on_increasePencil_clicked()
{
    Pencil::increasePrice();
    Pencil::newRate();
}

void MainWindow::on_decreasePencil_clicked()
{
    Pencil::decreasePrice();
    Pencil::newRate();
}

void MainWindow::on_buyApm_clicked(){
  Pencil::buyApm();
  checkbuttons();
}

void MainWindow::on_upgradeApm_clicked(){
  Pencil::upgradeApm();
  checkbuttons();
}

void MainWindow::on_upgradeMarketing_clicked(){
  if (Pencil::unlockedMarketing == false){
    Pencil::unlockMarketing();
    checkbuttons();
  }else if (Pencil::unlockedMarketing == true){
    Pencil::upgradeMarketing();
    checkbuttons();
  }

}

///Debug Tool Buttons

void MainWindow::on_debugBalance_clicked(){
  Wallet::balance += 1000;
}

void MainWindow::on_debugPencils_clicked(){
  Pencil::numberofPencil += 1000;
  /* Total number of pencils shouldn't be more than 25000
   */
  if(  Pencil::totalnumberofPencil <= 24000){
        Pencil::totalnumberofPencil += 1000;
  }
  else {
      /* Game-Over Pop-up
       */
      QMessageBox msgBox;
      msgBox.setText("GAME OVER");
      msgBox.setInformativeText("Do you want to save your changes?");
      msgBox.setStandardButtons(QMessageBox::Discard| QMessageBox::Save | QMessageBox::Retry |QMessageBox::Close);
      int ret = msgBox.exec();
      switch (ret) {
        case QMessageBox::Save:
            save();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Close:
            QApplication::quit();
            break;
        case QMessageBox::Retry:
            reset();
            break;
        default:
            // should never be reached
            break;
      }
  }
}

void MainWindow::on_debugTotalPencils_clicked(){
    if(  Pencil::totalnumberofPencil <= 24000){
          Pencil::totalnumberofPencil += 1000;
    }
    else {
        /* Game-Over Pop-up
         */
          QMessageBox msgBox;
          msgBox.setText("GAME OVER");
          msgBox.setInformativeText("Do you want to save your changes?");
          msgBox.setStandardButtons(QMessageBox::Discard| QMessageBox::Save | QMessageBox::Retry |QMessageBox::Close);
          int ret = msgBox.exec();
          switch (ret) {
            case QMessageBox::Save:
                save();
                break;
            case QMessageBox::Discard:
                break;
            case QMessageBox::Close:
                QApplication::quit();
                break;
            case QMessageBox::Retry:
                reset();
                break;
            default:
                // should never be reached
                break;
          }
    }
}

void MainWindow::on_debugWoodGraphite_clicked(){
  Production::numberofGraphite += 10;
  Production::numberofWood += 10;
}

void MainWindow::on_incINT_clicked()
{
    /* Total number of pencils should be equal or more than 3000
     */
    if (Pencil::totalnumberofPencil >= 3000){
        /* Intelligence shouldn't be more than 200
         */
        if(Wallet::intelligence <= 190){
            Wallet::intelligence += 10;
        }
        else {

            /* Intelligence Warning Pop-up
            */
            QMessageBox msgBox;
            msgBox.setText("You can't increase intelligence anymore.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            if(QMessageBox::Cancel){
                msgBox.exec();
            }
        }
    }
    else {
            /* Intelligence Warning Pop-up
            */
            QMessageBox msgBox;
            msgBox.setText("You can't increase Intelligence yet.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            if(QMessageBox::Cancel){
            msgBox.exec();
            }
    }
}

void MainWindow::on_incMAR_clicked()
{
    /* Marketing should be unlocked
     */
    if (Pencil::unlockedMarketing == true){
        /* Marketing shouldn't be more than 30
         */
        if(Pencil::valueofMarketing <= 27){
            Pencil::valueofMarketing += 3;
        }
        else {
            /* Marketing Warning Pop-up
             */
            QMessageBox msgBox;
            msgBox.setText("You can't increase Marketing anymore.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            if(QMessageBox::Cancel){
                msgBox.exec();
            }
        }

    }
    else {
            /* Marketing Warning Pop-up
            */
            QMessageBox msgBox;
            msgBox.setText("You can't upgrade Marketing yet.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            if(QMessageBox::Cancel){
            msgBox.exec();
        }
    }
}
/* End: Buttons and their functionalities */

/* Start: Saving and loading functionalities */
void MainWindow::save(){
    ofstream myfile;
    double valIds[19] ={
        Pencil::numberofPencil,
        Production::numberofGraphite,
        Production::numberofWood,
        Production::priceofGraphite,
        Wallet::balance,
        Wallet::intelligence,
        Pencil::priceofPencil,
        Pencil::rateofPencil,
        Pencil::numberofApm,
        Pencil::numberofApm,
        Pencil::rateofApm,
        Pencil::totalnumberofPencil,
        Pencil::valueofMarketing,
        Pencil::priceofMarketing,
        (double) Pencil::upgradeApm50,
        (double) Pencil::upgradeApm5000,
        (double) Pencil::finishedUpgrade50,
        (double) Pencil::finishedUpgrade5000,
        (double) Pencil::unlockedMarketing
    };
    myfile.open ("saveGame.save");
        for (int i = 0; i < 12; i++){
            myfile << valIds[i] << endl;
        }
        myfile.close();
}

void MainWindow::load(){
    ifstream myfile("./saveGame.save");
            if(myfile.is_open()){
                int arrSize = 0;
                double arr[10000];

                while(true){
                    double x;
                    myfile >> x;
                    if(myfile.eof()){break;}
                    arr[arrSize++] = x;
                }
                Pencil::numberofPencil = arr[0];
                Production::numberofGraphite = arr[1];
                Production::numberofWood = arr[2];
                Production::priceofGraphite = arr[3];
                Wallet::balance = arr[4];
                Wallet::intelligence = arr[5];
                Pencil::priceofPencil = arr[6];
                Pencil::rateofPencil = arr[7];
                Pencil::numberofApm = arr[8];
                Pencil::numberofApm = arr[9];
                Pencil::rateofApm = arr[10];
                Pencil::totalnumberofPencil = arr[11];
                Pencil::valueofMarketing = arr[12];
                Pencil::priceofMarketing = arr[13];
                Pencil::upgradeApm50 = (bool)arr[14];
                Pencil::upgradeApm5000 = (bool)arr[15];
                Pencil::finishedUpgrade50 = (bool)arr[16];
                Pencil::finishedUpgrade5000 = (bool)arr[17];
                Pencil::unlockedMarketing = (bool)arr[18];
            }
            else{
                cout << "Error" <<  endl;
            }
}
/* End: Saving and loading functionalities */

void MainWindow::reset(){
    Pencil::numberofPencil = 0;
    Production::numberofGraphite = 1000;
    Production::numberofWood = 1000;
    Production::priceofGraphite = 0;
    Wallet::balance = 145;
    Wallet::intelligence = 0;
    Pencil::priceofPencil = 1;
    Pencil::rateofPencil = 1;
    Pencil::numberofApm = 0;
    Pencil::numberofApm = 0;
    Pencil::rateofApm = 0;
    Pencil::totalnumberofPencil = 0;
    Pencil::valueofMarketing = 0;
    Pencil::priceofMarketing = 500;
    Pencil::upgradeApm50 = false;
    Pencil::upgradeApm5000 = false;
    Pencil::finishedUpgrade50 = false;
    Pencil::finishedUpgrade5000 = false;
    Pencil::unlockedMarketing = false;

 /* Hiding Marketing, Inteligence & Debug Tools */

    ui->upgradeMarketing->setHidden(true);
    ui->valueofMarketing->setHidden(true);
    ui->intelligence->setHidden(true);
    ui->intelligenceLabel->setHidden(true);
    ui->debugtool->setChecked(false);

}

void MainWindow::upload(){
    json j;
    const char* jacobs_id = std::getenv("JACOBS_ID");
    const char* se_token = std::getenv("SE_TOKEN");
    const char* game_username = std::getenv("GAME_USERNAME");
    j["jacobs-id"] = jacobs_id;
    j["se-token"] = se_token;
    j["game-username"] = game_username;
    j["score"] = Pencil::totalnumberofPencil;

    string link = getlink();

    /* CURL perform POST request to the server to upload score to the server */
    struct curl_slist *headers = NULL;
    CURL* curl = curl_easy_init();
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, j.dump().c_str());
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

std::size_t writecallback(const char* in, std::size_t size, std::size_t num, std::string* out){
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

string MainWindow::getlink()
{
    //Performing GET request to get link of the server
    const std::string url("https://matiusulung.com/se.json");
    string link;
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &link);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    json obj = json::parse(link);
    link = obj["link"];
    link.append("/uploadscore");
    return link;
}

/* Quit button that takes one back to the welcome page */
void MainWindow::on_pushButton_clicked()
{
    emit quitClicked();
}

/* Information Button Pop-up*/

void MainWindow::on_info_clicked()
{
    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{min-width: 700px;}");
    msgBox.setText("MORE ABOUT BUTTONS:\n"
                   
                   "\n'Make Pencil'- adds one pencil to the inventory (Consumes 0.21 m of wood & 0.20 m of graphite\n"
                   "\n'+' & '-' - increases & decreases the price of 1 pencil by an increment of $0.05\n"
                   "\n'Buy APM'- increases the 2000-series APM in the inventory by 1 & debits the current price of 1 (one) 2000-series APM from the bank balance\n"
                   "\n'Buy Wood' - adds 100.00 m of wood to the inventory & Debits the current price of wood fom the bank balance\n"
                   "\n'Buy Graphite' - adds 100.00 m of graphite to the inventory & debits the current price of graphite fom the bank balance\n"
                   "\n'UPGRADE' - increases the rate of pencil production of the APM by 10% each time it is purchased\n"
                   "\n'Upgrade Marketing' - increase the value of M & debits the current price of it from the bank balance\n"
                   "\n'Debug tool' - enables below listed tools\n"
                   "\n'Bank Balance +1000' - increases Bank balance by $1000\n"
                   "\n'Pecnicls Produced +1000' - increases Pencils Produced by 1000\n"
                   "\n'Total Pencils Prod. +1000' - increases Total Pencils Produced by 1000\n"
                   "\n'Wood+10, Graphite +10' - increases Wood and Graphite by 10\n"
                   "\n'Increase Intelligence +10' - increases Intelligence by 10\n"
                   "\n'Increase Marketing +3' - increases Marketing by 3\n"
                   "\n'SAVE' - saves data to the file\n"
                   "\n'LOAD' - loads saved data\n"
                   "\n'QUIT' - goes back to the main page\n"
                   "-------------------------------------------------"
                   "\nPOP-UPS:"

                   "    \n'Save' - saves the data and closes the pop-up."
                   "    \n'Close' - quits the game."
                   "    \n'Don't Save' - discards the pop-up."
                   "    \n'Retry' - resets the game."
                   "    \n'Cancel' - closes the pop-up.");
    
    msgBox.setStandardButtons(QMessageBox::Cancel);
    if(QMessageBox::Cancel){
        msgBox.exec();
    }
}
