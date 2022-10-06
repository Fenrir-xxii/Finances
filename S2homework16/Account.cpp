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
	}
	else
	{
		credit.push_back(transaction);
	}
}

void Account::removeTransaction(int idx, bool isIncome)
{
	if ((idx < 0) or (isIncome and idx > debit.size()-1) or ((!isIncome and idx > credit.size() - 1))) // test
	{
		return;
	}

	if (isIncome)
	{
		debit.erase(debit.begin() + idx);
	}
	else
	{
		credit.erase(debit.begin() + idx);
	}
}

void Account::editTransaction(Transaction& transaction)
{
	//menu
	std::vector<std::string> options;
	//std::vector<std::string> categoryNamesIncome = dataBase.getCategoryNames(true);
	//std::vector<std::string> categoryNamesExpenses = dataBase.getCategoryNames(false);
	std::vector<std::string> categoryNamesIncome;
	std::vector<std::string> categoryNamesExpenses;

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
				menu.drawFrame();
				menu.drawOptions();
				
				break;
			case 1:
				std::cin >> newAmount;
				transaction.setAmount(newAmount);
				menu.drawTransaction(transaction);
				menu.drawMessageFrame("Pick field you want to edit");
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
					case ENTER:
						//TODO
						if (leftActive)
						{
							num = menuCategoryExpenses.getSelectedOption();
							//transaction.setCategory(dataBase.getCategoryByName(categoryNamesExpenses[num], false));
							work2 = false;
						}
						else
						{
							num = menuCategoryIncome.getSelectedOption();
							//transaction.setCategory(dataBase.getCategoryByName(categoryNamesIncome[num], true));
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
				menu.drawFrame();
				menu.drawOptions();
				break;
			case 3:
				std::cin >> newDate;
				transaction.setDate(fromString(newDate, "%d.%m.%Y"));
				menu.drawTransaction(transaction);
				menu.drawMessageFrame("Pick field you want to edit");
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

void Account::save()
{

}

std::string Account::getName()
{
	return this->name;
}

double Account::getBalance()
{
	return this->balance;
}

void Account::setName(std::string name)
{
	this->name = name;
}

void Account::setBalance(double balance)
{
	this->balance = balance;
}