#pragma once
#include "DataBase.h"
#include "Time.h"

struct ReportCategory
{
	std::string name;
	double amount;
	bool isIncome;
	std::string currency;
};


class Report
{
private:
	DataBase dataBase;
	std::vector<Account> accounts;
public:
	void showMonthlyReport(Account& account, int month);
	void showLastNDaysReport(Account& account, int nDays);
	void showTransactionsByCategory(Account& account, int month);
	void showNBiggestTransactions(Account& account, int qty, bool isIncome);
	void printReport(Account & account, double &initBalance, double &finalBalance, std::string initDate, std::string finalDate);
	void printCategoryReport(std::vector <ReportCategory> &results);
};

bool reportCategorySort(ReportCategory& rp1, ReportCategory& rp2);
bool compareTransaction(Transaction& t1, Transaction& t2);