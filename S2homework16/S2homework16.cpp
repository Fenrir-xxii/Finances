#include <iostream>
#include "DataBase.h"
#include "Transaction.h"
#include "Account.h"
#include "Report.h"
#include "Finances.h"

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main5()
{
    ShowConsoleCursor(false);
    //DataBase dataBase;
    Finances finances;
    finances.showMainMenu();
    //dataBase.saveAll();


    return 0;
}

int main()
{
    ShowConsoleCursor(false);
  /*  DataBase dataBase;
    dataBase.addCurrency("UAH");
    dataBase.addCurrency("EUR");
    dataBase.addCurrency("USD");
    dataBase.addCurrency("UAH");
    dataBase.saveAll();*/

    Finances fin;
    fin.showAddNewCategoryMenu();

    return 0;
}

int main1()
{
    ShowConsoleCursor(false);
    //DataBase dataBase;
    /*dataBase.addCategory("Food", false);
    dataBase.addCategory("Salary", true);
    dataBase.saveCategories();*/
    //dataBase.loadCategories();



    auto timeNow = std::chrono::system_clock::now();
    Category category("Food", false);
    Category category2("Salary", true);
    Category category3("Fuel", false);
    Category category4("Shoping", false);
    Category category5("Sales", true);
    DataBase dataBase;
    dataBase.addCategory(category);
    dataBase.addCategory(category2);
    dataBase.addCategory(category3);
    dataBase.addCategory(category4);
    dataBase.addCategory(category5);
    dataBase.saveAll();

    Transaction transaction(203.50, category, "Potatoes", timeNow);

    //Account account;
    //account.addTransaction(transaction);
    //account.editCreditTransaction(0);


    //auto timeNow = std::chrono::system_clock::now();
    std::string time = "10.10.2022";
    auto timeT = fromString(time, "%d.%m.%Y");
    time = "01.09.2022";
    auto timeT2 = fromString(time, "%d.%m.%Y");
    time = "07.10.2022";
    auto timeT3 = fromString(time, "%d.%m.%Y");
    time = "22.09.2022";
    auto timeT4 = fromString(time, "%d.%m.%Y");
    time = "10.10.2022";
    auto timeT5 = fromString(time, "%d.%m.%Y");

    //Category category("Food", false);
    //Transaction transaction(203.50, category, "Potatoes", timeT);
    Transaction transaction2(23.80, category, "Juice", timeT);
    Transaction transaction3(1245.99, category4, "Jacket", timeT2);
    Transaction transaction4(12600, category2, "Salary", timeT3);
    Transaction transaction5(100.09, category4, "Toy", timeT4);
    Transaction transaction6(1600, category2, "Premium", timeT5);
    //DataBase dataBase;
    //dataBase.addTransaction(transaction);
    //dataBase.addTransaction(transaction2);
    //dataBase.saveAll();

    Account main("main", 2300, "UAH");
    main.addTransaction(transaction);
    main.addTransaction(transaction2);
    main.addTransaction(transaction3);
    main.addTransaction(transaction4);
    Account sub("sub", 150.60, "EUR");
    sub.addTransaction(transaction5);
    sub.addTransaction(transaction6);

    dataBase.addAccount(main);
    dataBase.addAccount(sub);

    //main.editCreditTransaction(0);

    dataBase.saveAll();

    std::cout << main << std::endl;

    main.sortTransactionsByDate();

    std::cout << "AFTER SORTING:\n" << main << std::endl;


    std::string timeS = "07.10.2022";
    auto timeST = fromString(timeS, "%d.%m.%Y");

    std::cout << "Balance for main: " << main.getBalanceByDate(timeST) << std::endl;
    std::cout << "Balance for sub: " << sub.getBalanceByDate(timeST) << std::endl;
    std::cout << std::endl;

    Report report;

    report.showLastNDaysReport(main, 30);
    report.showMonthlyReport(main, 10);
    report.showTransactionsByCategory(main, 10);
    report.showNBiggestTransactions(main, 3, true);
    report.showNBiggestTransactions(main, 3, false);
    report.showMonthlyReport(sub, 10);

    return 0;
}

int main2()
{
    std::vector <std::string> some;
    for (int i = 0; i < 12; i++)
    {
        some.push_back("Some option " + std::to_string(i));
    }
    Menu menu(some);

    bool work = true;
    int key = 0;
    int size = 5;
    int line = 0;
    int previousLine = 0;
    menu.drawOptions2(size, 0, previousLine);

    
	do
	{
		key = getKey();
		switch (key)
		{
		case UP_ARROW:
			menu.up();
            line = menu.getSelectedOption();
			menu.drawOptions2(size, line, previousLine);
            previousLine = line;
			break;
		case DOWN_ARROW:
			menu.down();
            line = menu.getSelectedOption();
			menu.drawOptions2(size, line, previousLine);
            previousLine = line;
			break;
		case ESC:
			work = false;
		default:
			break;
		}

	} while (work);
    
    return 0;
}