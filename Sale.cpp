#include <cstdio>
#include <sstream>
#include <utility>

#include "Sale.h"

Sale::Sale() {
	//std::printf("Inside constructor without parameters\n");
}

Sale::Sale
(
	std::string _date, std::string _ticker,
	float _purchasePrice, float _sellingPrice,
	uint16_t _volume
):
	date(std::move(_date)), ticker(std::move(_ticker)),
	purchasePrice(_purchasePrice), sellingPrice(_sellingPrice),
	volume(_volume)
{
	//std::printf("Inside constructor with 7 (seven) parameters\n");

	this->resultPerOneShare = this->sellingPrice - this->purchasePrice;
	this->resultInCurrency = this->resultPerOneShare * this->volume;
	this->resultInPercents = this->resultPerOneShare / this->purchasePrice * 100;
}

Sale::Sale(const std::string &s)
{
	//std::printf("Inside constructor from formatted string\n");

	std::istringstream iss(s);

	iss >> this->date;
	iss >> this->ticker;
	iss >> this->purchasePrice;
	iss >> this->sellingPrice;
	iss >> this->volume;

	this->resultPerOneShare = this->sellingPrice - this->purchasePrice;
	this->resultInCurrency = this->resultPerOneShare * this->volume;
	this->resultInPercents = this->resultPerOneShare / this->purchasePrice * 100;
}

Sale::Sale(Sale &&other):
	date { std::move(other.date) }, ticker { std::move(other.ticker) },
	purchasePrice { std::move(other.purchasePrice) },
	sellingPrice { std::move(other.sellingPrice) },
	volume { std::move(other.volume) }
{
	//std::printf("Inside move constructor\n");

	this->resultPerOneShare = this->sellingPrice - this->purchasePrice;
	this->resultInCurrency = this->resultPerOneShare * this->volume;
	this->resultInPercents = this->resultPerOneShare / this->purchasePrice * 100;
}