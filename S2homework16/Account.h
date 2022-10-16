#pragma once
#include <vector>
#include "Transaction.h"
#include "menu.h"
#include <filesystem>

namespace fs = std::filesystem;


class Account
{
private:
	std::string name;
	double balance;
	std::string currency;
	std::vector<Transaction> debit;
	std::vector<Transaction> credit;
public:
	Account() {};
	Account(std::string name, double balance, std::string currency)
	{
		this->name = name;
		this->balance = balance;
		this->currency = currency;
	}

	std::string getName();
	std::string getCurrency();
	double getBalance();
	void setName(std::string name);
	void setCurrency(std::string currency);
	void setBalance(double balance);
	void addTransaction(Transaction& transaction);
	void removeTransaction(int idx, bool isIncome);
	void editTransaction(Transaction& transaction, int idx);
	void editDebitTransaction(int idx);
	void editCreditTransaction(int idx);
	std::vector<std::string> getCategoryNames(bool isIncome);
	double getBalanceByDate(std::chrono::time_point<std::chrono::system_clock> date);
	void sortTransactionsByDate();
	bool compareDate(Transaction& transaction1, Transaction& transaction2);
	std::vector<Transaction> getTransactions(bool isIncome);
	Transaction& getTransactionByIdx(int idx, bool isIncome);

	friend std::ofstream& operator <<(std::ofstream& out, Account& account)
	{
		out << account.name << std::endl;
		out << account.currency << std::endl;
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
		getline(in, account.name);
		getline(in, account.currency);
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

	friend std::ostream& operator <<(std::ostream& out, Account& account)
	{
		out << "Account name: " << account.name << std::endl;
		out << "Account currency: " << account.currency << std::endl;
		out << "Balance: " << account.balance << std::endl;
		out << "Debit operations: " << account.debit.size() << std::endl;
		out << "Credit operations: " << account.credit.size() << std::endl;
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

};