#include "Report.h"

bool reportCategorySort(ReportCategory& rp1, ReportCategory& rp2)
{
	return rp1.amount > rp2.amount;
}

bool compareTransaction(Transaction& t1, Transaction& t2)
{
	
	return t1.getAmount() > t2.getAmount();
	
	
	/*switch (option)
	{
	case 0:
		return t1.getAmount() > t2.getAmount();
	case 1:
		return t1.getDate() > t2.getDate();
	dafault:
		break;
	}*/
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
	//std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

	auto dp = floor<std::chrono::days>(tp);
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
				//std::shared_ptr<Category> c = std::make_shared<>;
				if ((*c) == categoriesIncome[cat])
				{
					sum += debit[i].getAmount();
				}
			}
		}
		temp.amount = sum;
		temp.isIncome = true;
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
				//std::shared_ptr<Category> c;
				if ((*c) == categoriesExpenses[cat])
				{
					sum += credit[i].getAmount();
				}
			}
		}
		temp.amount = sum;
		temp.isIncome = false;
		results.push_back(temp);
	}

	std::sort(results.begin(), results.end(), reportCategorySort);

	for (int i = 0; i < results.size(); i++)
	{
		std::cout << "Category: " << results[i].name << "(isIncome?) '" << results[i].isIncome << "' - ";
		std::cout << "amount: " << results[i].amount << std::endl;
	}

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

	for (int i = 0; i < quantity; i++)
	{
		if (isIncome)
		{
			std::cout << "INCOME transaction #" << (i+1)  << "\n" << debit[i] << std::endl;
		}
		else
		{
			std::cout << "EXPENSE transaction #" << (i + 1) << "\n" << credit[i] << std::endl;
		}
	}
}

void Report::print()
{

}