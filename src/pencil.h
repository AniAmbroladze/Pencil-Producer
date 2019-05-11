/**
* @file pencil.h
* @brief this header file contains the functionalities for
* buying and selling pencil and the Auto Pencil Machine (APM).
*
*/

#ifndef PENCIL_H
#define PENCIL_H
#include "production.h"
#include "wallet.h"

class Pencil : public Production
{
public:
    Pencil();

    ///Pencil variables and functions

    double priceofPencil;
    double rateofPencil;
    double numberofPencil;
    double totalnumberofPencil;

    void increasePrice();
    void decreasePrice();
    void sell();
    void newRate();
    double getInventory();
    void producePencil();

    void setPriceofPencil(double);
    void setNumberofPencil(double);
    void setTotalNumberofPencil(double);
    void setRateOfPencil(double);
    double getRateOfPencil();
    double getNumberofPencil();
    double getPriceofPencil();
    double getTotalNumberofPencil();

    ///APM variables and functions
    double numberofApm;
    double priceofApm;
    double rateofApm;
    double standardrateofApm;

    void buyApm();
    void producePencilApm(); ///Each APM produces two pencils every second
    void upgradeApm();
    bool upgradeApm50;
    bool upgradeApm5000;
    bool finishedUpgrade50;
    bool finishedUpgrade5000;

    void setNumberofAPM(double);
    double getNumberofAPM();
    void setPriceofAPM(double);
    double getPriceofAPM();
    void setRateofAPM(double);
    double getRateofAPM();

    ///Marketing variables and functions

    double valueofMarketing;
    double priceofMarketing;
    bool unlockedMarketing;

    void upgradeMarketing();
    void unlockMarketing();

    ///Function to round number to 2 decimal places
    double round(double var);
};

#endif // PENCIL_H
