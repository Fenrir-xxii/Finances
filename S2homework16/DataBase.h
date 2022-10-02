#pragma once
#include "Category.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class DataBase
{
private:
	std::vector<Category> categories;
	fs::path categoryPath = fs::current_path().string() + "\\DataBase\\Categories.txt";
	int lastId = 0;
public:
	void addCategory(Category &category);
	void addCategory(std::string name, bool isIncome);
	void removeCategory(Category &category);

	void loadCategories();
	void saveCategories();

};