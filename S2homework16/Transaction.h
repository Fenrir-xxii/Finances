#pragma once
#include <string>
#include <chrono>
#include "Category.h"
#include <filesystem>
#include <iomanip>
#include "Time.h"

namespace fs = std::filesystem;


class Transaction
{
private:
	double amount;
	std::string name;
	std::chrono::time_point<std::chrono::system_clock> date;
	Category category;
	std::vector<Category> categoriesIncome;
	std::vector<Category> categoriesExpenses;
	fs::path categoryIncomePath = fs::current_path().string() + "\\DataBase\\CategoriesIncome.txt";
	fs::path categoryExpensesPath = fs::current_path().string() + "\\DataBase\\CategoriesExpenses.txt";
public:
	Transaction() 
	{
		loadCategories(categoryIncomePath, categoriesIncome);
		loadCategories(categoryExpensesPath, categoriesExpenses);
	}
	Transaction(double amount, Category category, std::string name, std::chrono::time_point<std::chrono::system_clock> date)
	{
		this->amount = amount;
		this->category = category;
		this->name = name;
		this->date = date;
		loadCategories(categoryIncomePath, categoriesIncome);
		loadCategories(categoryExpensesPath, categoriesExpenses);
	}
	void setAmount(double amount);
	void setName(std::string name);
	void setDate(std::chrono::time_point<std::chrono::system_clock> date);
	void setCategory(Category &category);
	void loadCategories(fs::path path, std::vector<Category>& categories);
	Category& getCategoryByName(std::string name, bool isIncome);

	double getAmount();
	std::string getName();
	std::chrono::time_point<std::chrono::system_clock> getDate();
	Category* getCategory();
	bool isIncome();
	void updateCategories(std::vector<Category> categoriesIncome, std::vector<Category> categoriesExpenses);

	friend std::ofstream& operator <<(std::ofstream& out, Transaction& transaction)
	{
		out << transaction.amount << std::endl;
		out << transaction.category; // << std::endl;
		out << transaction.name << std::endl;
		out << timeToString(transaction.date) << std::endl;
		return out;
	}

	friend std::ifstream& operator >>(std::ifstream& in, Transaction& transaction)
	{
		in >> transaction.amount;
		in.ignore(256, '\n');
		in >> transaction.category;
		getline(in, transaction.name);
		std::string date;
		getline(in, date);
		transaction.setDate(fromString(date, "%d.%m.%Y"));

		return in;
	}

	bool operator==(Transaction& transaction)
	{
		return this->name == transaction.name and this->amount == transaction.amount and this->category == transaction.category and this->date == transaction.date;
	}

	bool operator<(Transaction& transaction)
	{
		return date < transaction.date;
	}


	friend std::ostream& operator <<(std::ostream& out, Transaction& transaction)
	{
		out << "Transaction's amount: " << transaction.amount << std::endl;
		out << "Transaction's category: " << transaction.category;
		out << "Transaction's name: " << transaction.name << std::endl;
		out << "Transaction's date: " << timeToString(transaction.date) << std::endl;
		return out;
	}
};
