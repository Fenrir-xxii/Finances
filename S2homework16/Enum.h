#pragma once

enum MAIN_MENU_OPTIONS
{
	MY_ACCOUNTS = 0, ACCOUNT_OPTIONS, EXIT
};

enum REPORTS_MENU_OPTIONS
{
	LAST_N_DAYS_REPORT = 0, MONTHLY_REPORT, CATEGORY_REPORT, N_BIGGEST_TRANSACTIONS, GO_BACK
};

struct AccountData
{
	std::string name;
	double balance;
	std::string currency;
};