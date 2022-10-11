#include "Account.h"

//std::string Account::timeToString(std::chrono::system_clock::time_point tp) {
//
//	std::stringstream ss;
//	ss << format("{:%d.%m.%Y}", tp);
//	return ss.str();
//}
//
//std::chrono::system_clock::time_point Account::fromString(const std::string& dateStr, const std::string& format) {
//	std::stringstream ss{ dateStr };
//	std::chrono::system_clock::time_point tp;
//	ss >> std::chrono::parse(format, tp);
//	if (ss.fail()) {
//		throw "Can`t parse date";
//	}
//	return tp;
//}

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
		credit.erase(debit.begin() + idx);
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

void Account::editTransaction(Transaction& transaction)
{
	//menu
	std::vector<std::string> options;
	//std::vector<std::string> categoryNamesIncome = dataBase.getCategoryNames(true);
	//std::vector<std::string> categoryNamesExpenses = dataBase.getCategoryNames(false);
	std::vector<std::string> categoryNamesIncome = getCategoryNames(true);
	std::vector<std::string> categoryNamesExpenses = getCategoryNames(false);

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
	bool work = true;
	bool work2 = true;
	bool leftActive = true;
	std::string newName;
	std::string newDate;
	double newAmount = 0;
	//menu.drawMessageFrame("Pick field you want to edit");
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
				menu.drawTransaction(transaction);
				menu.drawMessageFrame("Pick field you want to edit");
				system("cls");
				menu.drawFrame();
				menu.drawOptions();
				
				break;
			case 1:
				std::cin >> newAmount;
				transaction.setAmount(newAmount);
				system("cls");
				//menu.drawTransaction(transaction);
				menu.drawMessageFrame("Pick field you want to edit");
				menu.drawTransaction(transaction);
				//system("cls");
				menu.drawFrame();
				menu.drawOptions();
				break;
			case 2:
				system("cls");
				menuCategoryExpenses.drawFrame("Expenses", true);
				menuCategoryExpenses.drawOptions();
				menuCategoryIncome.drawFrame(maxWidth,0, "Income", false);
				menuCategoryIncome.drawOptions(maxWidth,2);
				while (work2)
				{
					key = getKey();
					switch (key)
					{
					case UP_ARROW:
						leftActive ? menuCategoryExpenses.up() : menuCategoryIncome.up();
						menuCategoryExpenses.drawFrame("Expenses", true);
						menuCategoryExpenses.drawOptions();
						menuCategoryIncome.drawFrame(maxWidth, 0, "Income", false);
						menuCategoryIncome.drawOptions(maxWidth, 2);
						break;
					case DOWN_ARROW:
						leftActive ? menuCategoryExpenses.down() : menuCategoryIncome.down();
						menuCategoryExpenses.drawFrame("Expenses", true);
						menuCategoryExpenses.drawOptions();
						menuCategoryIncome.drawFrame(maxWidth, 0, "Income", false);
						menuCategoryIncome.drawOptions(maxWidth, 2);
						break;
					case TAB:
						leftActive = !leftActive;
						break;
					case ENTER:
						//TODO
						if (leftActive)
						{
							num = menuCategoryExpenses.getSelectedOption();
							//transaction.setCategory(dataBase.getCategoryByName(categoryNamesExpenses[num], false));
							transaction.setCategory(transaction.getCategoryByName(categoryNamesExpenses[num], false));
							work2 = false;
						}
						else
						{
							num = menuCategoryIncome.getSelectedOption();
							//transaction.setCategory(dataBase.getCategoryByName(categoryNamesIncome[num], true));
							transaction.setCategory(transaction.getCategoryByName(categoryNamesExpenses[num], true));
							work2 = false;
						}
						system("cls");
						break;
					case ESC:
						system("cls");
						work2 = false;
						break;
					}
				}
				menu.drawTransaction(transaction);
				menu.drawMessageFrame("Pick field you want to edit");
				system("cls");
				menu.drawFrame();
				menu.drawOptions();
				break;
			case 3:
				std::cin >> newDate;
				transaction.setDate(fromString(newDate, "%d.%m.%Y"));
				menu.drawTransaction(transaction);
				menu.drawMessageFrame("Pick field you want to edit");
				system("cls");
				menu.drawFrame();
				menu.drawOptions();
				break;
			}
			break;
		case ESC:
			work = false;
		default:
			break;
		}

	} while (work);

}

void Account::editDebitTransaction(int idx)
{
	if (idx < 0 or idx > debit.size() - 1)
	{
		return;
	}

	editTransaction(debit[idx]);
}

void Account::editCreditTransaction(int idx)
{
	if (idx < 0 or idx > credit.size() - 1)
	{
		return;
	}

	editTransaction(credit[idx]);
}

//void Account::save()
//{
//
//}

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
	/*std::sort(this->debit.begin(), this->debit.end(), &Account::compareDate);
	std::sort(this->credit.begin(), this->credit.end(), &Account::compareDate);*/

	std::sort(this->debit.begin(), this->debit.end());
	std::sort(this->credit.begin(), this->credit.end());
}

bool Account::compareDate(Transaction &transaction1, Transaction &transaction2)
{
	//return transaction1.getAmount() > transaction2.getAmount();
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