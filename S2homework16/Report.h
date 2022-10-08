#pragma once
#include "DataBase.h"
#include "Time.h"

struct ReportCategory
{
	std::string name;
	double amount;
	bool isIncome;
};


class Report
{
private:
	DataBase dataBase;
	std::vector<Account> accounts;
public:
	//std::vector<Account> getMonthlyReport();
	//std::vector<Account> getLastNDaysReport(int nDays);
	void showMonthlyReport(Account& account, int month);
	void showLastNDaysReport(Account& account, int nDays);
	void showTransactionsByCategory(Account& account, int month);
	void showNBiggestTransactions(Account& account, int qty, bool isIncome);
	void print();

	
};

bool reportCategorySort(ReportCategory& rp1, ReportCategory& rp2);
bool compareTransaction(Transaction& t1, Transaction& t2);