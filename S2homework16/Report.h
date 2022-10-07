#pragma once
#include "DataBase.h"
#include "Time.h"

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
	void print();

	
};