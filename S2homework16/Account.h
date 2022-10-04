#pragma once
#include <vector>
#include "Transaction.h"
#include "menu.h"
#include "DataBase.h"

class Account
{
private:
	std::string name;
	double balance;
	std::vector<Transaction> debit;
	std::vector<Transaction> credit;
	DataBase dataBase;
public:
	Account() {};
	Account(std::string name, double balance)
	{
		this->name = name;
		this->balance = balance;
	}

	//std::string timeToString(std::chrono::system_clock::time_point tp);
	//std::chrono::system_clock::time_point fromString(const std::string& dateStr, const std::string& format);
	void addTransaction(Transaction& transaction);
	void removeTransaction(int idx, bool isIncome);
	void editTransaction(Transaction& transaction);
	void editDebitTransaction(int idx);
	void editCreditTransaction(int idx);
	void load();
	void save();
};
