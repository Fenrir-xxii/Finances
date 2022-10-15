#include "Transaction.h"

void Transaction::setAmount(double amount)
{
	this->amount = amount;
}

void Transaction::setName(std::string name)
{
	this->name = name;
}

void Transaction::setDate(std::chrono::time_point<std::chrono::system_clock> date)
{
	this->date = date;
}

void Transaction::setCategory(Category &category)
{
	this->category = category;
}

double Transaction::getAmount()
{
	return this->amount;
}

std::string Transaction::getName()
{
	return this->name;
}

std::chrono::time_point<std::chrono::system_clock> Transaction::getDate()
{
	return this->date;
}

Category* Transaction::getCategory()
{
	return &(this->category);
}

bool Transaction::isIncome()
{
	return this->category.getIsIncome();
}

void Transaction::loadCategories(fs::path path, std::vector<Category>& categories)
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
		categories.push_back(temp);
	}
	in.close();
}

Category& Transaction::getCategoryByName(std::string name, bool isIncome)
{
	/*loadCategories(categoryIncomePath, categoriesIncome);
	loadCategories(categoryExpensesPath, categoriesExpenses);*/
	
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
}

void Transaction::updateCategories(std::vector<Category> categoriesIncome, std::vector<Category> categoriesExpenses)
{
	this->categoriesIncome = categoriesIncome;
	this->categoriesExpenses = categoriesExpenses;
}