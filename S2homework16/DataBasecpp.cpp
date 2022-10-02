#include "DataBase.h"

void DataBase::addCategory(Category& category)
{
	this->categories.push_back(category);
}

void DataBase::addCategory(std::string name, bool isIncome)
{
	Category newCat(name, isIncome);
	newCat.setId(++lastId);
	this->categories.push_back(newCat);
	
}

void DataBase::loadCategories()
{
	this->categories.clear();
	std::ifstream in(this->categoryPath);
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
		this->categories.push_back(temp);
	}
	in.close();
}

void DataBase::saveCategories()
{
	std::ofstream out(this->categoryPath);
	out << categories.size() << std::endl;
	for (int i = 0; i < categories.size(); i++)
	{
		out << categories[i];
	}
	out.close();
}