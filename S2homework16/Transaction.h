#pragma once
#include <string>
#include <chrono>
#include "Category.h"
//#include "DataBase.h"
#include "Time.h"

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
	void setDate(std::chrono::time_point<std::chrono::system_clock> date);
	void setCategory(Category &category);

	double getAmount();
	std::string getName();
	std::chrono::time_point<std::chrono::system_clock> getDate();
	Category* getCategory();
	bool isIncome();

	friend std::ofstream& operator <<(std::ofstream& out, Transaction& transaction)
	{
		out << transaction.amount << std::endl;
		out << transaction.category << std::endl;
		out << transaction.name << std::endl;
		out << timeToString(transaction.date) << std::endl;
		return out;
	}

	friend std::ifstream& operator >>(std::ifstream& in, Transaction& transaction)
	{
		in >> transaction.amount;
		in.ignore(256, '\n');
		in >> transaction.category;
		//in.ignore(256, '\n');
		/*DataBase db;
		transaction.setCategory(db.getCategoryById(categoryId));*/
		getline(in, transaction.name);
		std::string date;
		getline(in, date);
		transaction.setDate(fromString(date, "%d.%m.%Y"));

		return in;
	}

	bool operator==(Transaction& transaction)
	{
		return this->name == transaction.name and this->amount == transaction.amount and this->category == transaction.category and this->date == transaction.date;
	}
};
