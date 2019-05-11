#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <QMessageBox>
#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "unistd.h"
#include "mainwindow.h"


Pencil::Pencil()
{
    this->numberofPencil = 0;
    this->priceofPencil = 1.00;
    this->rateofPencil = 1;
    this->totalnumberofPencil = 0;

    this->valueofMarketing = 0;
    this->priceofMarketing = 500;
    this->unlockedMarketing = false; //Check if marketing is unlocked or not.

    this->numberofApm = 0;
    this->rateofApm = 0; ///Rate of apm is only used as a label for the ui
    this->priceofApm = 150;
    this->standardrateofApm = 120;
    this->upgradeApm50 = false; ///APM upgrade possible if intelligence >= 50
    this->upgradeApm5000 = false; ///APM upgrade possible if intelligence >= 5000
    this->finishedUpgrade50 = false; ///Check if APM has already been upgraded once
    this->finishedUpgrade5000 = false; ///Check if APM has been already been upgraded twice
}

void Pencil::producePencil(){
    if(Production::numberofWood < .21 || Production::numberofGraphite < .20){
        return;
    }
    else{
        this->numberofPencil++;
        /* Total number of pencils shouldn't be more than 25000
         */
        if(totalnumberofPencil < 25000){
            this->totalnumberofPencil++;
        }
        else {
            /* Game-Over Pop-up
             */
            QMessageBox msgBox;
            msgBox.setText("GAME OVER");
            msgBox.setInformativeText("Do you want to save your changes?");
            msgBox.setStandardButtons(QMessageBox::Discard| QMessageBox::Save |QMessageBox::Retry |QMessageBox::Close);
            MainWindow s;
            MainWindow r;
            int ret = msgBox.exec();
            switch (ret) {
                case QMessageBox::Save:
                    s.save();
                    break;
                case QMessageBox::Discard:
                    break;
                case QMessageBox::Close:
                    QApplication::quit();
                    break;
                case QMessageBox::Retry:
                    r.reset();
                    break;
                default:
                    // should never be reached
                    break;
            }
        }
        Production::decreaseWood();
        Production::decreaseGraphite();
    }
}

double Pencil::getInventory(){
    return this->numberofPencil;
}

void Pencil::increasePrice(){
	this->priceofPencil += 0.05;
}

void Pencil::decreasePrice(){
	this->priceofPencil -= 0.05;
}

/*! Function to round doubles to two decimal places */
double Pencil::round(double var)
{
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
}

/*! Function to calculate rate of a pencil every fraction of a second */
void Pencil::newRate(){
    this->rateofPencil = round((1 / this->priceofPencil) * pow(1.1, this->valueofMarketing));
}

/*! Sell pencils (according to rate) every second   */
void Pencil::sell(){
    if(this->numberofPencil == 0 ){
        return;
    }
    else{
        Wallet::balance += this->priceofPencil;
        this->numberofPencil--;
    }
}

/*! Function to produced two pencils each second for every APM */
void Pencil::producePencilApm(){ ///Rate of pencil production changes of Apm only if the rate is a mulitple of standardrateofApm
double currentnewRate = floor(this->rateofApm/this->standardrateofApm);
  for (int i = 0; i < numberofApm * currentnewRate; i++){
    producePencil();
    producePencil();
  }
}

/*! Function to buy APM and increase its price by 10% after every purchase */
void Pencil::buyApm(){
  if (Wallet::balance < this->priceofApm){
    throw std::system_error(std::error_code(), "Not enough bank balance to buy more APM's!");
  }else if(numberofApm < 10){
      this->numberofApm++;
      Wallet::balance -= this->priceofApm;

      this->priceofApm = this->priceofApm + (0.10 * this->priceofApm);
      this->rateofApm += 120;
  }
}

/*!Function to upgrade APM, increase its rate of pencil production */
void Pencil::upgradeApm(){
  if (Wallet::intelligence >= 50 && this->upgradeApm50 == true && this->finishedUpgrade50 == false){
    this->rateofApm = this->rateofApm + (0.1 * this->rateofApm);
    Wallet::intelligence -= 50;
    this->finishedUpgrade50 = true;
  }
  if (Wallet::intelligence >= 200 && this->totalnumberofPencil >= 5000 && this->upgradeApm5000 == true && this->finishedUpgrade5000 == false){
    this->rateofApm = this->rateofApm + (0.1 * this->rateofApm);
    Wallet::intelligence -= 200;
    this->finishedUpgrade5000 = true;
  }
}

//Pencil Setters & Getters
void Pencil::setPriceofPencil(double newPrice){
  priceofPencil = newPrice;
}
double Pencil::getPriceofPencil(){
  return this->priceofPencil;
}
void Pencil::setNumberofPencil(double newNumber){
  numberofPencil = newNumber;
}
double Pencil::getNumberofPencil(){
  return this->numberofPencil;
}
void Pencil::setTotalNumberofPencil(double newTotalnumberofPencil){
  totalnumberofPencil = newTotalnumberofPencil;
}
double Pencil::getTotalNumberofPencil(){
  return this->totalnumberofPencil;
}
void Pencil::setRateOfPencil(double value){
    rateofPencil = value;
}
double Pencil::getRateOfPencil(){
    return this->rateofPencil;
}

//APM Setters & Getters
void Pencil::setNumberofAPM(double newAPM){
  numberofApm = newAPM;
}
double Pencil::getNumberofAPM(){
  return this->numberofApm;
}
void Pencil::setPriceofAPM(double newPrice){
  priceofApm = newPrice;
}
double Pencil::getPriceofAPM(){
  return this->priceofApm;
}
void Pencil::setRateofAPM(double newRate){
  rateofApm = newRate;
}
double Pencil::getRateofAPM(){
  return this->rateofApm;
}

/*!Marketing functions */

/*! Function that upgrades Marketing */
void Pencil::upgradeMarketing(){
  if (Wallet::balance >= this->priceofMarketing){
    this->valueofMarketing += 1;
    Wallet::balance -= this->priceofMarketing;
    this->priceofMarketing = this->priceofMarketing + (0.1 * this->priceofMarketing);
  }
}

/*! Function that unlocks Marketing */
void Pencil::unlockMarketing(){
  if (Wallet::intelligence >= 100 && this->unlockedMarketing == false){
    this->unlockedMarketing = true;
    Wallet::intelligence -= 100;
  }
}
