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

void DataBase::loadCategories(fs::path path, std::vector<Category> &categories)
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

void DataBase::saveCategories(fs::path path, std::vector<Category> &categories)
{
	std::ofstream out(path);
	out << categories.size() << std::endl;
	for (int i = 0; i < categories.size(); i++)
	{
		out << categories[i];
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

void DataBase::saveAll()
{
	saveCategories(categoryIncomePath, categoriesIncome);
	saveCategories(categoryExpensesPath, categoriesExpenses);
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