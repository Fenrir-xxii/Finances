#include "Turnover.h"

void Turnover::setAmount(double amount)
{
	this->amount = amount;
}

void Turnover::setName(std::string name)
{
	this->name = name;
}

void Turnover::setTime(std::chrono::time_point<std::chrono::system_clock> date)
{
	this->date = date;
}

void Turnover::setCategory(int category)
{
	this->category = category;
}

void Turnover::setIsIncome(bool isIncome)
{
	this->isIncome = isIncome;
}