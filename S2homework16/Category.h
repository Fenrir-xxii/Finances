#pragma once
#include <string>
#include <vector>
#include <fstream>

class Category
{
private:
	std::string name;
	int id = 0;
	bool isIncome;
public:
	Category() {}

	Category(std::string name, bool isIncome)
	{
		this->name = name;
		this->isIncome = isIncome;
	}
	void setId(int id);
	std::string getName();
	bool getIsIncome();
	int getId();

	friend std::ofstream& operator <<(std::ofstream& out, Category& category)
	{
		out << category.id << std::endl;
		out << category.name << std::endl;
		out << category.isIncome;// << std::endl;
		return out;
	}

	friend std::ifstream& operator >>(std::ifstream& in, Category& category)
	{
		in >> category.id;
		in.ignore(256, '\n');
		getline(in, category.name);
		in >> category.isIncome;
		in.ignore(256, '\n');
		return in;
	}

	bool operator==(Category& category)
	{
		return this->name == category.name and this->isIncome == category.isIncome;
	}

};