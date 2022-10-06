#pragma once
#include <vector>
#include "Account.h"


class Finances
{
private:
	std::vector<Account> accounts;
	DataBase dataBase;
public:
	Finances()
	{
		//dataBase.load
	}
};
