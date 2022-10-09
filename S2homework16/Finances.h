#pragma once
#include <vector>
#include "Account.h"
#include "Enum.h"
#include "DataBase.h"

//struct AccountData
//{
//	std::string name;
//	double balance;
//	std::string currency;
//};

class Finances
{
private:
	std::vector<Account> accounts;
	DataBase dataBase;
	fs::path accountPath = fs::current_path().string() + "\\DataBase\\Accounts\\";
public:
	Finances()
	{
		//dataBase.load
		dataBase.loadAccounts(accountPath, accounts);
	}

	void showMainMenu();
	void showMyAccounts();
};
