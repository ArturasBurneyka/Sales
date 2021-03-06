#pragma once
#include <cstdint>
#include <string>

class Sale {

public:
	std::string date;
	std::string ticker;
	float purchasePrice;
	float sellingPrice;
	uint16_t volume;
	float resultPerOneShare;
	float resultInCurrency;
	float resultInPercents;

	Sale();
	Sale (
		std::string _date, std::string _ticker,
		float _purchasePrice, float _sellingPrice,
		uint16_t _volume
	);
	/* Construstor from formatted string */
	Sale(const std::string &s);
	/* Copy constructor and copy assign operator */
	Sale(const Sale &other) = delete;
	Sale& operator=(const Sale &other) = delete;
	/* Move constructor and move assign operator */
	Sale(Sale &&other);
};