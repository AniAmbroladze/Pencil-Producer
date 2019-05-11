#include <iostream>
#include "wallet.h"

/*! Constructor */
Wallet::Wallet(){
	this->balance = 145.00;
	this->intelligence = 0.00;
}

/*! Setter for balance */
void Wallet::setBalance(double newBalance){
	this->balance = newBalance;
}

/*! Getter for balance */
double Wallet::getBalance(){
	return this->balance;
}

/*! Method to increment intelligence */
void Wallet::increaseIntelligence(){
	if (this->intelligence <= 200){
            this->intelligence += 1;
	}
}

/*! Setter for intelligence */
void Wallet::setIntelligence(double newIntelligence){
	this->intelligence = newIntelligence;
}

/*! Getter for intelligence */
double Wallet::getIntelligence(){
	return this->intelligence;
}
