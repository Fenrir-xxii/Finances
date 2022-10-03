#include "Transaction.h"

void Transaction::setAmount(double amount)
{
	this->amount = amount;
}

void Transaction::setName(std::string name)
{
	this->name = name;
}

void Transaction::setTime(std::chrono::time_point<std::chrono::system_clock> date)
{
	this->date = date;
}

void Transaction::setCategory(Category &category)
{
	this->category = category;
}

double Transaction::getAmount()
{
	return this->amount;
}

std::string Transaction::getName()
{
	return this->name;
}

std::chrono::time_point<std::chrono::system_clock> Transaction::getDate()
{
	return this->date;
}

Category* Transaction::getCategory()
{
	return &(this->category);
}

bool Transaction::isIncome()
{
	return this->category.getIsIncome();
}