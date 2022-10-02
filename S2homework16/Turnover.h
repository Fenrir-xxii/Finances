#pragma once
#include <string>
#include <chrono>

class Turnover
{
private:
	double amount;
	std::string name;
	std::chrono::time_point<std::chrono::system_clock> date;
	int category;
	bool isIncome;
public:
	Turnover() {}
	Turnover(double amount, bool isIncome, int category, std::string name, std::chrono::time_point<std::chrono::system_clock> date)
	{
		this->amount = amount;
		this->isIncome = isIncome;
		this->category = category;
		this->name = name;
		this->date = date;

	}
	void setAmount(double amount);
	void setName(std::string name);
	void setTime(std::chrono::time_point<std::chrono::system_clock> date);
	void setCategory(int category);
	void setIsIncome(bool isIncome);
	double getAmount();
	std::string getName();
	std::chrono::time_point<std::chrono::system_clock> getDate();
	int getCategory();
	bool getIsIncome();


};
