#pragma once

enum MAIN_MENU_OPTIONS
{
	MY_ACCOUNTS = 0, ACCOUNT_OPTIONS, EXIT
};

struct AccountData
{
	std::string name;
	double balance;
	std::string currency;
};