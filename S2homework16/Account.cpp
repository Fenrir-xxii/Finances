#include "Account.h"

void Account::addTransaction(Transaction& transaction)
{
	if (transaction.isIncome())
	{
		debit.push_back(transaction);
		this->balance += transaction.getAmount();
	}
	else
	{
		credit.push_back(transaction);
		this->balance -= transaction.getAmount();
	}
}

void Account::removeTransaction(int idx, bool isIncome)
{
	if ((idx < 0) or (isIncome and idx > debit.size()-1) or ((!isIncome and idx > credit.size() - 1))) // test
	{
		return;
	}
	double temp;
	if (isIncome)
	{
		temp = debit[idx].getAmount();
		debit.erase(debit.begin() + idx);
		this->balance -= temp;
	}
	else
	{
		temp = credit[idx].getAmount();
		credit.erase(credit.begin() + idx);
		this->balance += temp;
	}
}

std::vector<std::string> Account::getCategoryNames(bool isIncome)
{
	std::vector<std::string> categoryNames;
	fs::path categoryIncomePath = fs::current_path().string() + "\\DataBase\\CategoriesIncome.txt";
	fs::path categoryExpensesPath = fs::current_path().string() + "\\DataBase\\CategoriesExpenses.txt";

	fs::path path = isIncome ? categoryIncomePath : categoryExpensesPath;
	std::ifstream in(path);
	int size = 0;
	in >> size;
	in.ignore(256, '\n');
	for (int i = 0; i < size; i++)
	{
		Category temp;
		in >> temp;
		categoryNames.push_back(temp.getName());
	}
	in.close();

	return categoryNames;
}

void Account::editTransaction(Transaction& transaction, int idx)		// привести в порядок 
{
	std::vector<std::string> options;
	std::vector<std::string> categoryNamesIncome = getCategoryNames(true);
	std::vector<std::string> categoryNamesExpenses = getCategoryNames(false);

	double amountBeforeEdit = transaction.getAmount();
	double amountAfterEdit = transaction.getAmount();
	bool isIncomeBeforeEdit = transaction.isIncome();
	bool isIncomeAfterEdit = transaction.isIncome();

	int maxWidth = 0;
	for (int i = 0; i < categoryNamesExpenses.size(); i++)
	{
		if (categoryNamesExpenses[i].length() > maxWidth)
		{
			maxWidth = categoryNamesExpenses[i].length();
		}
	}
	maxWidth += 6;
	Menu menu;
	menu.drawTransaction(transaction);
	Menu menuCategoryIncome(categoryNamesIncome);
	Menu menuCategoryExpenses(categoryNamesExpenses);
	int key = 0;
	int num = 0;
	bool choosingFieldToEdit = true;
	bool choosingCategory = true;
	bool menuExpensesActive = true;
	bool isDateValid = false;
	bool isValueCorrect = false;
	std::string newName;
	std::string newDate;
	double newAmount = 0;
	menu.drawFrame();
	menu.drawOptions();
	do
	{
		key = getKey();
		switch (key)
		{
		case UP_ARROW:
			menu.up();
			menu.drawOptions();
			break;
		case DOWN_ARROW:
			menu.down();
			menu.drawOptions();
			break;
		case ENTER:
			menu.drawMessageFrame("Enter new parameter");
			num = menu.getSelectedOption();
			switch (num)
			{
			case 0 :
				std::getline(std::cin, newName);
				transaction.setName(newName);
				system("cls");
				menu.drawFrame();
				menu.drawTransaction(transaction);
				break;
			case 1:
				do
				{
					menu.drawMessageFrame("Enter new parameter");
					std::cin >> newAmount;
					if (std::cin.fail())
					{
						isValueCorrect = false;
					}
					else
					{
						isValueCorrect = true;
					}
					std::cin.clear();
					std::cin.ignore(1000, '\n');

				} while (!isValueCorrect);
				transaction.setAmount(newAmount);
				amountAfterEdit = newAmount;
				system("cls");
				menu.drawFrame();
				menu.drawTransaction(transaction);
				break;
			case 2:
				system("cls");
				menuCategoryExpenses.drawFrame("Expenses", menuExpensesActive, ConsoleColor::RED_FADE);
				menuCategoryExpenses.drawOptions();
				menuCategoryIncome.drawFrame(maxWidth,0, "Income", !menuExpensesActive, ConsoleColor::GREEN_FADE);
				menuCategoryIncome.drawOptions(maxWidth,2);
				while (choosingCategory)
				{
					key = getKey();
					switch (key)
					{
					case UP_ARROW:
						menuExpensesActive ? menuCategoryExpenses.up() : menuCategoryIncome.up();
						menuCategoryExpenses.drawOptions();
						menuCategoryIncome.drawOptions(maxWidth, 2);
						break;
					case DOWN_ARROW:
						menuExpensesActive ? menuCategoryExpenses.down() : menuCategoryIncome.down();
						menuCategoryExpenses.drawOptions();
						menuCategoryIncome.drawOptions(maxWidth, 2);
						break;
					case TAB:
						menuExpensesActive = !menuExpensesActive;
						break;
					case ENTER:
						if (menuExpensesActive)
						{
							num = menuCategoryExpenses.getSelectedOption();
							transaction.setCategory(transaction.getCategoryByName(categoryNamesExpenses[num], false));
							choosingCategory = false;
						}
						else
						{
							num = menuCategoryIncome.getSelectedOption();
							transaction.setCategory(transaction.getCategoryByName(categoryNamesIncome[num], true));
							choosingCategory = false;
						}
						system("cls");
						break;
					case ESC:
						system("cls");
						choosingCategory = false;
						break;
					}
				}
				system("cls");
				menu.drawFrame();
				menu.drawTransaction(transaction);
				break;
			case 3:
				do
				{
					menu.drawMessageFrame("Enter new parameter");
					std::cin >> newDate;
					try
					{
						transaction.setDate(fromString(newDate, "%d.%m.%Y"));
						isDateValid = true;
					}
					catch (const char* e)
					{
						system("cls");
						std::cout << e << std::endl << "Try again" << std::endl;
						system("pause");
					}
				} while (!isDateValid);
				system("cls");
				menu.drawFrame();
				menu.drawTransaction(transaction);
				break;
			}
			break;
		case ESC:
			choosingFieldToEdit = false;
		default:
			break;
		}

	} while (choosingFieldToEdit);

	isIncomeAfterEdit = transaction.isIncome();
	// change balance and/or category debit/credit
	if (isIncomeBeforeEdit != isIncomeAfterEdit)
	{
		if (!isIncomeAfterEdit)
		{
			this->balance -= (amountBeforeEdit + amountAfterEdit);
			this->credit.push_back(transaction);
			this->debit.erase(debit.begin() + idx);
		}
		else
		{
			this->balance += (amountBeforeEdit + amountAfterEdit);
			this->debit.push_back(transaction);
			this->credit.erase(credit.begin() + idx);
		}
	}
	else if (amountBeforeEdit != amountAfterEdit)
	{
		if (!transaction.isIncome())
		{
			this->balance += (amountBeforeEdit - amountAfterEdit);
		}
		else
		{
			this->balance -= (amountBeforeEdit - amountAfterEdit);
		}
	}

}

void Account::editDebitTransaction(int idx)
{
	if (idx < 0 or idx > debit.size() - 1)
	{
		return;
	}

	editTransaction(debit[idx], idx);
}

void Account::editCreditTransaction(int idx)
{
	if (idx < 0 or idx > credit.size() - 1)
	{
		return;
	}

	editTransaction(credit[idx], idx);
}

std::string Account::getName()
{
	return this->name;
}

std::string Account::getCurrency()
{
	return this->currency;
}

double Account::getBalance()
{
	return this->balance;
}

void Account::setName(std::string name)
{
	this->name = name;
}

void Account::setCurrency(std::string currency)
{
	this->currency = currency;
}

void Account::setBalance(double balance)
{
	this->balance = balance;
}

double Account::getBalanceByDate(std::chrono::time_point<std::chrono::system_clock> date)
{
	double res = this->balance;

	for (int i = debit.size() - 1; i >= 0; i--)
	{
		if (debit[i].getDate() >= date)
		{
			res -= debit[i].getAmount();
		}
	}
	for (int i = credit.size() - 1; i >= 0; i--)
	{
		if (credit[i].getDate() >= date)
		{
			res += credit[i].getAmount();
		}
	}

	return res;
}

void Account::sortTransactionsByDate()
{
	std::sort(this->debit.begin(), this->debit.end());
	std::sort(this->credit.begin(), this->credit.end());
}

bool Account::compareDate(Transaction &transaction1, Transaction &transaction2)
{
	return transaction1.getDate() > transaction2.getDate();
}

std::vector<Transaction> Account::getTransactions(bool isIncome)
{
	if (isIncome)
	{
		return this->debit;
	}
	else
	{
		return this->credit;
	}
}

Transaction& Account::getTransactionByIdx(int idx, bool isIncome)
{
	if (isIncome)
	{
		return this->debit[idx];
	}
	else
	{
		return this->credit[idx];
	}
}