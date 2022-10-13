#include "DataBase.h"

void DataBase::addCategory(Category& category)
{
	category.setId(++lastId);
	if (category.getIsIncome())
	{
		for (int i = 0; i < categoriesIncome.size(); i++)
		{
			if (category == categoriesIncome[i])
			{
				--lastId;
				return;
			}
		}
		this->categoriesIncome.push_back(category);
	}
	else
	{
		for (int i = 0; i < categoriesExpenses.size(); i++)
		{
			if (category == categoriesExpenses[i])
			{
				--lastId;
				return;
			}
		}
		this->categoriesExpenses.push_back(category);
	}
}

void DataBase::addCategory(std::string name, bool isIncome)
{
	Category newCat(name, isIncome);
	newCat.setId(++lastId);
	if (isIncome)
	{
		for (int i = 0; i < categoriesIncome.size(); i++)
		{
			if (newCat == categoriesIncome[i])
			{
				--lastId;
				return;
			}
		}
		this->categoriesIncome.push_back(newCat);
	}
	else
	{
		for (int i = 0; i < categoriesExpenses.size(); i++)
		{
			if (newCat == categoriesExpenses[i])
			{
				--lastId;
				return;
			}
		}
		this->categoriesExpenses.push_back(newCat);
	}
}

void DataBase::loadCategories(fs::path path, std::vector<Category>& categories)
{
	categories.clear();
	std::ifstream in(path);
	int size = 0;
	in >> size;
	in.ignore(256, '\n');
	for (int i = 0; i < size; i++)
	{
		Category temp;
		in >> temp;
		if (this->lastId < temp.getId())
		{
			this->lastId = temp.getId();
		}
		categories.push_back(temp);
	}
	in.close();
}

void DataBase::loadTransactions(fs::path path, std::vector<Transaction>& transactions)
{
	transactions.clear();
	std::ifstream in(path);
	int size = 0;
	in >> size;
	in.ignore(256, '\n');
	for (int i = 0; i < size; i++)
	{
		Transaction temp;
		in >> temp;
		transactions.push_back(temp);
	}
	in.close();
}

void DataBase::saveCategories(fs::path path, std::vector<Category>& categories)
{
	std::ofstream out(path);
	out << categories.size() << std::endl;
	for (int i = 0; i < categories.size(); i++)
	{
		out << categories[i];
	}
	out.close();
}

void DataBase::saveTransactions(fs::path path, std::vector<Transaction>& transactions)
{
	std::ofstream out(path);
	out << transactions.size() << std::endl;
	for (int i = 0; i < transactions.size(); i++)
	{
		out << transactions[i];
	}
	out.close();
}


std::vector<std::string> DataBase::getCategoryNames(bool isIncome)
{
	std::vector<std::string> names;

	if (isIncome)
	{
		for (int i = 0; i < this->categoriesIncome.size(); i++)
		{
			names.push_back(categoriesIncome[i].getName());
		}

	}
	else
	{
		for (int i = 0; i < this->categoriesExpenses.size(); i++)
		{
			names.push_back(categoriesExpenses[i].getName());
		}
	}
	return names;
}

std::vector<std::string> DataBase::getCurrency()
{
	return this->currency;
}

Category& DataBase::getCategoryById(int id)
{
	for (int i = 0; i < this->categoriesIncome.size(); i++)
	{
		if (this->categoriesIncome[i].getId() == id)
		{
			return categoriesIncome[i];
		}
	}
	for (int i = 0; i < this->categoriesExpenses.size(); i++)
	{
		if (this->categoriesExpenses[i].getId() == id)
		{
			return categoriesExpenses[i];
		}
	}

}

void DataBase::saveAll()
{
	saveCategories(categoryIncomePath, categoriesIncome);
	saveCategories(categoryExpensesPath, categoriesExpenses);
	//saveTransactions(transactionPath, transactions);
	saveAccounts(accountPath, accounts);
	saveCurrency(currencyPath, currency);
}

Category& DataBase::getCategoryByName(std::string name, bool isIncome)
{
	if (isIncome)
	{
		for (int i = 0; i < this->categoriesIncome.size(); i++)
		{
			if (categoriesIncome[i].getName() == name)
			{
				return categoriesIncome[i];
			}
		}

	}
	else
	{
		for (int i = 0; i < this->categoriesExpenses.size(); i++)
		{
			if (categoriesExpenses[i].getName() == name)
			{
				return categoriesExpenses[i];
			}
		}
	}
	return categoriesExpenses[0]; // ??
}

//void DataBase::addTransaction(Transaction& transaction)
//{
//	for (int i = 0; i < transactions.size(); i++)
//	{
//		if (transaction == transactions[i])
//		{
//			return;
//		}
//	}
//	this->transactions.push_back(transaction);
//}


void DataBase::saveAccounts(fs::path path, std::vector<Account>& account)
{
	//fs::path path = this->homePath;
	fs::path mainPath = fs::current_path();
	fs::current_path(path);
	for (int i = 0; i < account.size(); i++)
	{
		std::string name = account[i].getName() + ".txt";
		path /= name;
		std::ofstream ofs;
		ofs.open(name, std::ios::out);
		ofs << account[i];
		ofs.close();
	}
	fs::current_path(mainPath);
}

void DataBase::saveAccount(Account& account)
{
	fs::path mainPath = fs::current_path();
	fs::path p = this->accountPath;
	fs::current_path(p);

	std::string name = account.getName() + ".txt";
	p /= name;
	std::ofstream ofs;
	ofs.open(name, std::ios::out);
	ofs << account;
	ofs.close();

	fs::current_path(mainPath);
}

void DataBase::loadAccounts(fs::path path, std::vector<Account>& accounts)
{
	std::vector <std::string> accNames;
	std::string name;
	for (auto const& dirEntry : fs::directory_iterator{ path })
	{
		if (dirEntry.is_regular_file())
		{
			name = dirEntry.path().filename().string();
			accNames.push_back(name);
		}
	}

	accounts.clear();
	//std::ifstream in(path);
	for (int i = 0; i < accNames.size(); i++)
	{
		Account account;
		std::string accName = accNames[i].substr(0, accNames[i].length() - 4);
		//accName.substr(0, accName.length() - 3);
		account.setName(accName);  //remove '.txt'
		fs::path fullPath = path.string() + accNames[i];
		std::ifstream in(fullPath);
		in >> account;
		accounts.push_back(account);
		accounts[i].sortTransactionsByDate();
		in.close();
	}
}

void DataBase::addAccount(Account& account)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (account == accounts[i])
		{
			return;
		}
	}
	this->accounts.push_back(account);
}

void DataBase::loadCurrency(fs::path path, std::vector<std::string>& currency)
{
	currency.clear();
	std::ifstream in(path);
	std::string text;

	if (in.is_open())
	{
		while (getline(in, text))
		{
			currency.push_back(text);
		}
		in.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}

}

void DataBase::saveCurrency(fs::path path, std::vector<std::string>& currency)
{
	std::ofstream out(path);
	for (int i = 0; i < currency.size(); i++)
	{
		out << currency[i] << std::endl;
	}
	out.close();
}

void DataBase::addCurrency(std::string currency)
{
	for (int i = 0; i < this->currency.size(); i++)
	{
		if (this->currency[i] == currency)
		{
			return;
		}
	}
	this->currency.push_back(currency);
}

void DataBase::updateAccounts(std::vector<Account>& accounts)
{
	this->accounts = accounts;
}