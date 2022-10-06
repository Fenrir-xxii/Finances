#pragma once
#include <vector>
#include "Transaction.h"
#include "menu.h"
//#include "DataBase.h"

class Account
{
private:
	std::string name;
	double balance;
	std::vector<Transaction> debit;
	std::vector<Transaction> credit;
	//DataBase dataBase;
public:
	Account() {};
	Account(std::string name, double balance)
	{
		this->name = name;
		this->balance = balance;
	}

	//std::string timeToString(std::chrono::system_clock::time_point tp);
	//std::chrono::system_clock::time_point fromString(const std::string& dateStr, const std::string& format);
	std::string getName();
	double getBalance();
	void setName(std::string name);
	void setBalance(double balance);
	void addTransaction(Transaction& transaction);
	void removeTransaction(int idx, bool isIncome);
	void editTransaction(Transaction& transaction);
	void editDebitTransaction(int idx);
	void editCreditTransaction(int idx);
	void load();
	void save();

	friend std::ofstream& operator <<(std::ofstream& out, Account& account)
	{
		out << account.balance << std::endl;
		out << account.debit.size() << std::endl;
		out << account.credit.size() << std::endl;
		for (int i = 0; i < account.debit.size(); i++)
		{
			out << account.debit[i] << std::endl;
		}
		for (int i = 0; i < account.credit.size(); i++)
		{
			out << account.credit[i] << std::endl;
		}
		return out;
	}

	friend std::ifstream& operator >>(std::ifstream& in, Account& account)
	{
		in >> account.balance;
		in.ignore(256, '\n');
		int debitSize = 0;
		int creditSize = 0;
		in >> debitSize;
		in.ignore(256, '\n');
		in >> creditSize;
		in.ignore(256, '\n');
		for (int i = 0; i < debitSize; i++)
		{
			Transaction transaction;
			in >> transaction;
			account.debit.push_back(transaction);
		}
		for (int i = 0; i < creditSize; i++)
		{
			Transaction transaction;
			in >> transaction;
			account.credit.push_back(transaction);
		}

		return in;
	}

	bool operator==(Account& account)
	{
		return this->name == account.name and this->balance == account.balance;
	}

};

// write in file:
// name of account = FileName
// balance
// debit
// credit