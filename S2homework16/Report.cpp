#include "Report.h"

void Report::showMonthlyReport(Account& account, int month)
{
	// create date with month
	//std::string date = "01." + month + ".2022";

	//auto tp = fromString("01.09.2022", "%d.%m.%Y");
	std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

	auto dp = floor<std::chrono::days>(timeNow);
	std::chrono::year_month_day ymd{ dp };

	auto m = ymd.month();

	std::vector<Transaction> debit = account.getTransactions(true);
	std::vector<Transaction> credit = account.getTransactions(false);

	Account temp;

	for (int i = 0; i < debit.size(); i++)
	{
		auto dp2 = floor < std::chrono::days>(debit[i].getDate());
		std::chrono::year_month_day ymd2{ dp2 };
		auto m2 = ymd2.month();
		if (m2==m)
		{
			temp.addTransaction(debit[i]);
		}
	}
	for (int i = 0; i < credit.size(); i++)
	{
		auto dp2 = floor < std::chrono::days>(credit[i].getDate());
		std::chrono::year_month_day ymd2{ dp2 };
		auto m2 = ymd2.month();
		if (m2 == m)
		{
			temp.addTransaction(credit[i]);
		}
	}

	std::cout << temp << std::endl;
	//std::cout << "Month: " << m << std::endl;
}

void Report::showLastNDaysReport(Account& account, int nDays)
{
	std::chrono::system_clock::time_point timeEnd = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point timeStart = timeEnd - std::chrono::hours(24 * nDays);

	std::vector<Transaction> debit = account.getTransactions(true);
	std::vector<Transaction> credit = account.getTransactions(false);

	Account temp;
	
	for (int i = 0; i < debit.size(); i++)
	{
		if (debit[i].getDate() >= timeStart and debit[i].getDate() <= timeEnd)
		{
			temp.addTransaction(debit[i]);
		}
	}
	for (int i = 0; i < credit.size(); i++)
	{
		if (credit[i].getDate() >= timeStart and credit[i].getDate() <= timeEnd)
		{
			temp.addTransaction(credit[i]);
		}
	}

	std::cout << temp << std::endl;

}


void Report::print()
{

}