#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Sale.h"

std::vector<Sale> sales;
std::set<std::string> years;

float resultByYear(const std::string &year) {
	float res { 0.0f };

	std::vector<Sale> salesByYear;

	std::for_each(sales.cbegin(), sales.cend(), [year, &salesByYear](const Sale &sale){
		if (sale.date.find(year) != std::string::npos) {
			salesByYear.emplace_back(sale.date, sale.ticker, sale.purchasePrice, sale.sellingPrice, sale.volume);
		}
	});

	res = std::accumulate(salesByYear.cbegin(), salesByYear.cend(), 0.0f, [](float a, const Sale &b){
		return a + b.resultInCurrency;
	});

	return res;
}

int main(int argc, char* argv[])
{
	std::printf("%s\n", "Welcome to Sales Calculator");
	std::printf("%s\n", "Release Date: Jan 31, 2021");

	std::ifstream ifs("D:\\Arthur\\Sales\\Sales.txt");

	if (!ifs.is_open()) {
		std::printf("Error occured during file \"%s\" opening", "Sales.txt");
		return 1;
	}

	std::string line;
	
	sales.reserve(16);

	while (std::getline(ifs, line)) {
		sales.push_back(std::move(Sale(line)));
	}

	ifs.close();

	//sales.shrink_to_fit();

	std::printf("\n");

	for (const Sale &s: sales) {
		std::printf(
			"%10s %8s %6.2f %6.2f %4i %+6.2f %+7.2f$ %+6.2f\%\n",
			s.date.c_str(), s.ticker.c_str(), s.purchasePrice, s.sellingPrice,
			s.volume, s.resultPerOneShare, s.resultInCurrency, s.resultInPercents);
	}

	std::printf("\n");

	float allTimeResult { 0.0f };

	allTimeResult = std::accumulate(sales.cbegin(), sales.cend(), 0.0f, [](float a, const Sale &b){
		return a + b.resultInCurrency;
	});

	std::printf("Total result by all the time: %+8.2f$\n", allTimeResult);

	std::printf("\n");

	std::for_each(sales.cbegin(), sales.cend(), [](const Sale &sale){
		years.emplace(sale.date.substr(0, 4));
	});

	std::printf("Results by years:\n");

	for (const std::string &s: years) { std::printf("\t%4s: %+9.2f$\n", s.c_str(), resultByYear(s)); }

	std::printf("\n");

	std::printf("Press any key to finish Sales Calculator...\n");

	std::cin.get();

	return 0;
}