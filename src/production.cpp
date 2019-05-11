#include <iostream>
#include <random>

#include "production.h"
#include "wallet.h"

using namespace std;

/*! Constructor */
Production::Production(){
	priceofWood = 1000;
	priceofGraphite = 1500;

	numberofWood = 1000;
	numberofGraphite = 1000;
}


/*! Function to calculate price of Wood and Graphite. */
void Production::calculatePrices(){
	time_t t;
	time(&t);
	srand((unsigned int) t);
	///Price of Wood and Graphite is a random number between 1000 to 2000.
	priceofWood = 1000 + rand() % ((2000 + 1) - 1000);
	///Price of Graphite is a random number between 1500 to 2500.
	priceofGraphite = 1500 + rand() % ((2500 + 1) - 1500);
}

/*! Function to buy wood if there is enough balance */
void Production::buyWood(){
	if (Wallet::balance < priceofWood){
		 throw std::system_error(std::error_code(), "Not enough bank balance to buy more wood!");
	}else{
		this->numberofWood += 100;
		Wallet::balance -=  priceofWood;
	}
}

/*! Function to buy Graphite if there is enough balance */
void Production::buyGraphite(){
	if (Wallet::balance < priceofGraphite){
		throw std::system_error(std::error_code(), "Not enough bank balance to buy more graphite!");
 }else{
		this->numberofGraphite += 100;
		Wallet::balance -= priceofGraphite;
	}
}

bool Production::disable_buyWood(){
	return (Wallet::balance < priceofWood ? true : false);
}

bool Production::disable_buyGraphite(){
	return (Wallet::balance < priceofGraphite ? true : false);
}

void Production::decreaseWood(){
	this->numberofWood -= 0.20;
}

void Production::decreaseGraphite(){
	this->numberofGraphite-= 0.21;
}

double Production::getWood(){
	return this->numberofWood;
}

void Production::setWood(double newWood){
	numberofWood = newWood;
}

double Production::getGraphite(){
	return this->numberofGraphite;
}

void Production::setGraphite(double newGraphite){
	numberofGraphite = newGraphite;
}

double Production::getPriceofWood(){
	return this->priceofWood;
}
void Production::setPriceofWood(double newPriceofWood){
	priceofWood = newPriceofWood;
}
double Production::getPriceofGraphite(){
	return this->priceofGraphite;
}
void Production::setPriceofGraphite(double newPriceofGraphite){
	priceofGraphite = newPriceofGraphite;
}
