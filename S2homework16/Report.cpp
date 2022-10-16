#include "Report.h"

bool reportCategorySort(ReportCategory& rp1, ReportCategory& rp2)
{
	return rp1.amount > rp2.amount;
}

bool compareTransaction(Transaction& t1, Transaction& t2)
{
	return t1.getAmount() > t2.getAmount();
}

void Report::showMonthlyReport(Account& account, int month)
{
	// creating timePoint with parameter 'month'
	std::string strMonth = std::to_string(month);
	if (month < 0 or month>12)
	{
		return;
	}
	if (month < 10)
	{
		strMonth = "0" + std::to_string(month);
	}

	std::string date = "01." + strMonth + ".2022";

	auto tp = fromString(date, "%d.%m.%Y");

	auto dp = floor<std::chrono::days>(tp);
	std::chrono::year_month_day ymd{ dp };

	auto m = ymd.month();

	int lastDay = getLastDayOfMonth(month, 2022);
	std::string lastDateString = std::to_string(lastDay) + "." + std::to_string(month) + "." + "2022";
	auto tp2 = fromString(lastDateString, "%d.%m.%Y");

	double initialBalance = account.getBalanceByDate(tp);
	double finalBalance = account.getBalanceByDate(tp2);

	std::vector<Transaction> debit = account.getTransactions(true);
	std::vector<Transaction> credit = account.getTransactions(false);

	Account temp;
	temp.setCurrency(account.getCurrency());

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
	SetColor(BLACK, YELLOW_FADE);
	std::cout << "Monthly report for month #" << month;
	SetColor(WHITE, BLACK);
	std::cout << std::endl << std::endl;
	printReport(temp, initialBalance, finalBalance, date, lastDateString);

	//std::cout << "Initial balance: " << initialBalance << std::endl;
	//std::cout << "Final balance: " << finalBalance << std::endl;
	//std::cout << temp << std::endl;
	////std::cout << "Month: " << m << std::endl;
}

void Report::showLastNDaysReport(Account& account, int nDays)
{
	std::chrono::system_clock::time_point timeEnd = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point timeStart = timeEnd - std::chrono::hours(24 * nDays);

	std::string timeEndString = timeToString(timeEnd);
	std::string timeStartString = timeToString(timeStart);

	std::vector<Transaction> debit = account.getTransactions(true);
	std::vector<Transaction> credit = account.getTransactions(false);

	double initialBalance = account.getBalanceByDate(timeStart);
	double finalBalance = account.getBalanceByDate(timeEnd);

	Account temp;
	temp.setCurrency(account.getCurrency());

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

	SetColor(BLACK, YELLOW_FADE);
	std::cout << "Monthly report for last " << nDays << " day(s)";
	SetColor(WHITE, BLACK);
	std::cout << std::endl << std::endl;

	printReport(temp, initialBalance, finalBalance, timeStartString, timeEndString);

	//std::cout << temp << std::endl;
}

void Report::showTransactionsByCategory(Account& account, int month)
{
	std::vector <Category> categoriesIncome;
	std::vector <Category> categoriesExpenses;
	this->dataBase.loadCategories(fs::current_path().string() + "\\DataBase\\CategoriesIncome.txt", categoriesIncome);
	this->dataBase.loadCategories(fs::current_path().string() + "\\DataBase\\CategoriesExpenses.txt", categoriesExpenses);
	std::vector<Transaction> debit = account.getTransactions(true);
	std::vector<Transaction> credit = account.getTransactions(false);

	std::string strMonth = std::to_string(month);
	if (month < 0 or month>12)
	{
		return;
	}
	if (month < 10)
	{
		strMonth = "0" + std::to_string(month);
	}

	std::string date = "01." + strMonth + ".2022";
	auto tp = fromString(date, "%d.%m.%Y");
	auto dp = floor<std::chrono::days>(tp);
	std::chrono::year_month_day ymd{ dp };
	auto m = ymd.month();

	std::vector<ReportCategory> results;

	for (int cat = 0; cat < categoriesIncome.size(); cat++)
	{
		ReportCategory temp;
		temp.name = categoriesIncome[cat].getName();
		double sum = 0;
		for (int i = 0; i < debit.size(); i++)
		{
			auto dp2 = floor < std::chrono::days>(debit[i].getDate());
			std::chrono::year_month_day ymd2{ dp2 };
			auto m2 = ymd2.month();
			if (m2 == m)
			{
				Category* c = debit[i].getCategory();
				if ((*c) == categoriesIncome[cat])
				{
					sum += debit[i].getAmount();
				}
			}
		}
		temp.amount = sum;
		temp.isIncome = true;
		temp.currency = account.getCurrency();
		results.push_back(temp);
	}
	for (int cat = 0; cat < categoriesExpenses.size(); cat++)
	{
		ReportCategory temp;
		temp.name = categoriesExpenses[cat].getName();
		double sum = 0;
		for (int i = 0; i < credit.size(); i++)
		{
			auto dp2 = floor < std::chrono::days>(credit[i].getDate());
			std::chrono::year_month_day ymd2{ dp2 };
			auto m2 = ymd2.month();
			if (m2 == m)
			{
				Category* c = credit[i].getCategory();
				if ((*c) == categoriesExpenses[cat])
				{
					sum += credit[i].getAmount();
				}
			}
		}
		temp.amount = sum;
		temp.isIncome = false;
		temp.currency = account.getCurrency();
		results.push_back(temp);
	}

	std::sort(results.begin(), results.end(), reportCategorySort);

	SetColor(BLACK, YELLOW_FADE);
	std::cout << "Report by categories for month #" << month;
	SetColor(WHITE, BLACK);
	std::cout << std::endl << std::endl;
	printCategoryReport(results);

	/*for (int i = 0; i < results.size(); i++)
	{
		std::cout << "Category: " << results[i].name << "(isIncome?) '" << results[i].isIncome << "' - ";
		std::cout << "amount: " << results[i].amount << std::endl;
	}*/

}

void Report::showNBiggestTransactions(Account& account, int qty, bool isIncome)
{
	std::vector<Transaction> debit = account.getTransactions(true);
	std::vector<Transaction> credit = account.getTransactions(false);

	int quantity = qty;

	if (isIncome)
	{
		if (qty > debit.size())
		{
			quantity = debit.size();
		}
	}
	else
	{
		if (qty > credit.size())
		{
			quantity = credit.size();
		}
	}

	std::sort(debit.begin(), debit.end(), compareTransaction);
	std::sort(credit.begin(), credit.end(), compareTransaction);

	SetColor(BLACK, YELLOW_FADE);
	if (isIncome)
	{
		std::cout << "Report for " << quantity << " biggest INCOME transaction(s)";
	}
	else
	{
		std::cout << "Report for " << quantity << " biggest EXPENSE transaction(s)";
	}
	SetColor(WHITE, BLACK);
	std::cout << std::endl << std::endl;
	for (int i = 0; i < quantity; i++)
	{
		if (isIncome)
		{
			std::cout << "Transaction";
			SetColor(GREEN, BLACK);
			std::cout << " #" << (i + 1);
			SetColor(WHITE, BLACK);
			std::cout << ":" << std::endl;
			std::cout << timeToString(debit[i].getDate()) << " ";
			std::cout << debit[i].getName() << " ";
			SetColor(GREEN, BLACK);
			std::cout << debit[i].getAmount();
			SetColor(WHITE, BLACK);
			std::cout << " " << account.getCurrency() << std::endl;
		}
		else
		{
			std::cout << "Transaction";
			SetColor(RED, BLACK);
			std::cout << " #" << (i + 1) << ":";
			SetColor(WHITE, BLACK); 
			std::cout << ":" << std::endl;
			std::cout << timeToString(credit[i].getDate()) << " ";
			std::cout << credit[i].getName() << " ";
			SetColor(RED, BLACK);
			std::cout << credit[i].getAmount();
			SetColor(WHITE, BLACK);
			std::cout << " " << account.getCurrency() << std::endl;
		}
		SetColor(WHITE, BLACK);
	}
	std::cout << std::endl;
}

void Report::printReport(Account& account, double& initBalance, double& finalBalance, std::string initDate, std::string finalDate)
{
	std::vector<Transaction> transactions = account.getTransactions(true);
	std::vector<Transaction> temp = account.getTransactions(false);
	double debit = 0;
	double credit = 0;
	for (int i = 0; i < temp.size(); i++)
	{
		transactions.push_back(temp[i]);
	}
	std::sort(transactions.begin(), transactions.end());

	int coordXDebit = 43;
	int coordXCredit = 50;
	std::string s1 = "Transactions:";
	std::string s2 = "Debit";
	std::string s3 = "Credit";
	std::string s4 = "Total";
	std::string s0((coordXCredit + s3.size()), '-');
	int setWidthDebit = coordXDebit - s1.size();
	int setWidthCredit = coordXCredit - coordXDebit + s2.length();
	std::string date;
	std::string name;

	std::cout << "Initial balance for " << initDate << " is ";
	SetColor(BLACK, GRAY);
	std::cout << initBalance;
	SetColor(WHITE, BLACK);
	std::cout << " " << account.getCurrency() << std::endl << std::endl;
	std::cout << s0 << std::endl;
	SetColor(WHITE, BLACK);
	std::cout << s1 << std::right << std::setw(setWidthDebit);
	SetColor(GREEN, BLACK);
	std::cout << s2 << std::right << std::setw(setWidthCredit);
	SetColor(RED, BLACK);
	std::cout << s3 << std::endl;
	SetColor(WHITE, BLACK);
	std::cout << s0 << std::endl;
	for (int i = 0; i < transactions.size(); i++)
	{
		date = timeToString(transactions[i].getDate());
		name = transactions[i].getName();
		std::cout << date << " " << name;
		if (transactions[i].isIncome())
		{
			SetColor(GREEN, BLACK);
			std::cout << std::right << std::setw(coordXDebit - date.size() - name.size() - 1) << transactions[i].getAmount() << std::endl;
			debit += transactions[i].getAmount();
		}
		else
		{
			SetColor(RED, BLACK);
			std::cout << std::right << std::setw(coordXCredit - date.size() - name.size() - 1+ s2.size()) << transactions[i].getAmount() << std::endl;
			credit += transactions[i].getAmount();
		}
		SetColor(WHITE, BLACK);
	}
	std::cout << s0 << std::endl;
	std::cout << s4 << std::right << std::setw(coordXDebit - s4.size());
	SetColor(GREEN, BLACK);
	std::cout << debit << std::right << std::setw(coordXCredit - coordXDebit + s4.length());
	SetColor(RED, BLACK);
	std::cout  << credit << std::endl;
	SetColor(WHITE, BLACK);
	std::cout << s0 << std::endl;
	std::cout << std::endl << "Final balance for " << finalDate << " is ";
	SetColor(BLACK, GRAY);
	std::cout << finalBalance;
	SetColor(WHITE, BLACK);
	std::cout << " " << account.getCurrency() << std::endl << std::endl;
}

void Report::printCategoryReport(std::vector <ReportCategory> &results)
{
	double totalIncome = 0;
	double totalExpenses = 0;
	for (int j = 0; j < results.size(); j++)
	{
		if (results[j].isIncome)
		{
			totalIncome += results[j].amount;
		}
		else
		{
			totalExpenses += results[j].amount;
		}
	}

	int size = 0;

	SetColor(BLACK, GRAY);
	std::cout << "Income Categories:\n";
	SetColor(WHITE, BLACK);
	for (int i = 0; i < results.size(); i++)
	{
		if (results[i].amount > 0 and results[i].isIncome)
		{
			size = results[i].amount / totalIncome * 100;
			std::cout << results[i].name << ":\n";
			SetColor(BLACK, GREEN_FADE);
			std::cout << std::string(size, ' ');
			SetColor(WHITE, BLACK);
			std::cout << " " << size << "%" << std::endl;
			std::cout << "Amount: " << results[i].amount << " " << results[i].currency << std::endl << std::endl;
		}
	}
	SetColor(BLACK, GRAY);
	std::cout << "TOTAL INCOME: " << totalIncome << " " << results[0].currency << std::endl;
	SetColor(WHITE, BLACK);
	std::cout << std::endl;
	std::cout << std::string(100, '-') << std::endl << std::endl;

	SetColor(BLACK, GRAY);
	std::cout << "Expenses Categories:\n";
	SetColor(WHITE, BLACK);
	for (int i = 0; i < results.size(); i++)
	{
		if (results[i].amount > 0 and !results[i].isIncome)
		{
			size = results[i].amount / totalExpenses * 100;
			std::cout << results[i].name << ":\n";
			SetColor(BLACK, RED_FADE);
			std::cout << std::string(size, ' ');
			SetColor(WHITE, BLACK);
			std::cout << " " << size << "%" << std::endl;
			std::cout << "Amount: " << results[i].amount << " " << results[i].currency << std::endl << std::endl;
		}
	}
	SetColor(BLACK, GRAY);
	std::cout << "TOTAL EXPENSES: " << totalExpenses << " " << results[0].currency << std::endl;
	SetColor(WHITE, BLACK);
	std::cout << std::endl;
}