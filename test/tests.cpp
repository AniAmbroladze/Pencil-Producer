/**
* @file tests.h
* @brief This header file made for Unit Testing
*
*/
#include <QApplication>
#include <iostream>
#include "src/mainwindow.h"
#include "src/pencil.h"
#include "src/pencil.cpp"
#include "src/production.h"
#include "src/production.cpp"
#include "src/wallet.h"
#include "src/wallet.cpp"
#include <gtest/gtest.h>

/*! Unit Testing for the pencil class */
TEST(PencilProduce, pencilMake){
    Pencil P;

    ASSERT_EQ(0, P.numberofPencil);
    P.producePencil();
    ASSERT_EQ(1, P.numberofPencil);

    ASSERT_EQ(0, P.numberofApm);
    ASSERT_EQ(1, P.rateofPencil);
    ASSERT_EQ(1, P.rateofPencil);

    P.increasePrice();
    ASSERT_EQ(1.05, P.priceofPencil);

    P.newRate();
    ASSERT_EQ(.95, P.rateofPencil);

    P.decreasePrice();
    ASSERT_EQ(1.00, P.priceofPencil);

    ASSERT_EQ(1, P.getInventory());

    EXPECT_ANY_THROW(P.buyApm(););

    P.setIntelligence(200);
    P.unlockMarketing();
    ASSERT_EQ(true, P.unlockedMarketing);

    ASSERT_EQ(0, P.valueofMarketing);
    P.setBalance(1000);
    P.upgradeMarketing();
    ASSERT_EQ(1, P.valueofMarketing);

    P.setIntelligence(3000);
    P.totalnumberofPencil = 6000;
    P.upgradeApm5000 = true;
    P.finishedUpgrade5000 = false;
    P.upgradeApm();
    ASSERT_EQ(true, P.finishedUpgrade5000);

    P.setIntelligence(200);
    P.upgradeApm50 = true;
    P.finishedUpgrade50 = false;
    P.upgradeApm();
    ASSERT_EQ(true, P.finishedUpgrade50);

}

/*! Unit Testing for the wallet class */
TEST(WalletTest, WalletMake){
  Wallet W;

  ASSERT_EQ(145.00, W.balance);

  W.setBalance(150.00);

  ASSERT_EQ(150.00, W.balance);

  ASSERT_EQ(0, W.intelligence);
  W.increaseIntelligence();
  ASSERT_EQ(1, W.intelligence);

}

/*! Unit Testing for the production class */
TEST(ProductionTest, ProductionMake){
  Production P;

  ASSERT_EQ(P.numberofWood, 1000);
  ASSERT_EQ(P.numberofGraphite, 1000);
  P.decreaseWood();

  ASSERT_EQ(P.numberofWood, 999.8);
  P.decreaseGraphite();
  ASSERT_EQ(P.numberofGraphite, 999.79);

  ///Check whether it is possible to buy Wood and Graphite or not with current
  ///balance.
  EXPECT_ANY_THROW(P.buyWood(););
  EXPECT_ANY_THROW(P.buyGraphite(););

  bool testwoodButton;
  testwoodButton =  P.disable_buyWood();
  ASSERT_EQ(testwoodButton, true);

  bool testgraphiteButton;
  testgraphiteButton = P.disable_buyGraphite();
  ASSERT_EQ(testgraphiteButton, true);
}

int main(int argc, char *argv[]){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
