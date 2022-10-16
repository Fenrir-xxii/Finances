#pragma once
#include <vector>
#include "Account.h"
#include "Enum.h"
#include "DataBase.h"
#include "Report.h"

class Finances
{
private:
	std::vector<Account> accounts;
	DataBase dataBase;
	fs::path accountPath = fs::current_path().string() + "\\DataBase\\Accounts\\";
	Report report;
public:
	Finances()
	{
		dataBase.loadAccounts(accountPath, accounts);
	}

	void showMainMenu();
	void showMyAccounts();
	void showReportMenu(Account& account);
	void showOptions();
	void showAddNewCategoryMenu();
	void removeAccount(int idx);
	std::vector<Transaction> getAllTransactions(Account& account);
	std::vector <AccountData> getAllAccountsData();
};
