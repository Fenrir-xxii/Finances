#pragma once
//#include "Category.h"
#include <fstream>
#include <filesystem>
#include "Category.h"
#include "Transaction.h"
#include "Account.h"

namespace fs = std::filesystem;

class DataBase
{
private:
	std::vector<Category> categoriesIncome;
	std::vector<Category> categoriesExpenses;
	std::vector<Transaction> transactions;  // temp, should be Account
	std::vector<Account> accounts;
	fs::path categoryIncomePath = fs::current_path().string() + "\\DataBase\\CategoriesIncome.txt";
	fs::path categoryExpensesPath = fs::current_path().string() + "\\DataBase\\CategoriesExpenses.txt";
	fs::path transactionPath = fs::current_path().string() + "\\DataBase\\Transactions.txt";
	fs::path accountPath = fs::current_path().string() + "\\DataBase\\Accounts\\";
	int lastId = 0;
public:
	DataBase()
	{
		loadCategories(categoryIncomePath, categoriesIncome);
		loadCategories(categoryExpensesPath, categoriesExpenses);
		//loadTransactions(transactionPath, transactions);
		loadAccounts(accountPath, accounts);
	}
	
	//void init();
	void addCategory(Category &category);
	void addCategory(std::string name, bool isIncome);
	void removeCategory(Category &category);
	std::vector<std::string> getCategoryNames(bool isIncome);
	Category& getCategoryByName(std::string name, bool isIncome);
	Category& getCategoryById(int id);
	void addTransaction(Transaction& transaction);
	void addAccount(Account& account);
	void loadCategories(fs::path path, std::vector<Category> &categories);
	void saveCategories(fs::path path, std::vector<Category> &categories);
	void loadTransactions(fs::path path, std::vector<Transaction>& transactions);
	void saveTransactions(fs::path path, std::vector<Transaction>& transactions);
	void loadAccounts(fs::path path, std::vector<Account>& accounts);
	void saveAccounts(fs::path path, std::vector<Account>& accounts);

	void saveAll();
};