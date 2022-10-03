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
	/*options.push_back(transaction.getName());
	options.push_back(std::to_string(transaction.getAmount()));
	options.push_back(transaction.getCategory()->getName());
	options.push_back(timeToString(transaction.getDate()));*/
	Menu menu;
	menu.drawTransaction(transaction);
	//menu.drawMessageFrame("Pick field you want to edit");
	int key = 0;
	int num = 0;
	bool work = true;
	std::string newName;
	std::string newDate;
	double newAmount = 0;
	menu.drawMessageFrame("Pick field you want to edit");
	menu.drawFrame(1, 1);
	menu.drawOptions(3, 3);
	do
	{
		key = getKey();
		switch (key)
		{
		case UP_ARROW:
			menu.up();
			menu.drawOptions(3, 3);
			break;
		case DOWN_ARROW:
			menu.down();
			menu.drawOptions(3, 3);
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
				menu.drawFrame(1, 1);
				menu.drawOptions(3, 3);
				
				break;
			case 1:
				std::cin >> newAmount;
				transaction.setAmount(newAmount);
				menu.drawTransaction(transaction);
				menu.drawMessageFrame("Pick field you want to edit");
				menu.drawFrame(1, 1);
				menu.drawOptions(3, 3);
				break;
			case 2:

				break;
			case 3:
				std::cin >> newDate;
				transaction.setTime(fromString(newDate, "%d.%m.%Y"));
				menu.drawTransaction(transaction);
				menu.drawMessageFrame("Pick field you want to edit");
				menu.drawFrame(1, 1);
				menu.drawOptions(3, 3);
				break;
			}
			//system("cls");
			//work = false;
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