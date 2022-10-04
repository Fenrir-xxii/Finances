#pragma once
#include "Category.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class DataBase
{
private:
	std::vector<Category> categoriesIncome;
	std::vector<Category> categoriesExpenses;
	fs::path categoryIncomePath = fs::current_path().string() + "\\DataBase\\CategoriesIncome.txt";
	fs::path categoryExpensesPath = fs::current_path().string() + "\\DataBase\\CategoriesExpenses.txt";
	int lastId = 0;
public:
	DataBase()
	{
		loadCategories(categoryIncomePath, categoriesIncome);
		loadCategories(categoryExpensesPath, categoriesExpenses);
	}
	
	//void init();
	void addCategory(Category &category);
	void addCategory(std::string name, bool isIncome);
	void removeCategory(Category &category);
	std::vector<std::string> getCategoryNames(bool isIncome);
	Category& getCategoryByName(std::string name, bool isIncome);
	void loadCategories(fs::path path, std::vector<Category> &categories);
	void saveCategories(fs::path path, std::vector<Category> &categories);
	void saveAll();
};