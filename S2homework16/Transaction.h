#pragma once
#include <string>
#include <chrono>
#include "Category.h"

class Transaction
{
private:
	double amount;
	std::string name;
	std::chrono::time_point<std::chrono::system_clock> date;
	Category category;
	//bool isIncome;
public:
	Transaction() {}
	Transaction(double amount, Category category, std::string name, std::chrono::time_point<std::chrono::system_clock> date)
	{
		this->amount = amount;
		this->category = category;
		this->name = name;
		this->date = date;

	}
	void setAmount(double amount);
	void setName(std::string name);
	void setTime(std::chrono::time_point<std::chrono::system_clock> date);
	void setCategory(Category &category);
	double getAmount();
	std::string getName();
	std::chrono::time_point<std::chrono::system_clock> getDate();
	Category* getCategory();
	bool isIncome();

};
