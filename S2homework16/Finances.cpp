#include "Finances.h"

void Finances::showMainMenu()
{
    std::vector<std::string> mainMenuOptions({ "My Accounts", "Account Settings", "Exit" });
    Menu menu(mainMenuOptions);
    int key = -1;
    int selection = -1;

    while (key != ESC)
    {
        menu.drawFrame();
        menu.drawOptions();
        key = getKey();

        switch (key)
        {
        case UP_ARROW:
            menu.up();
            break;
        case DOWN_ARROW:
            menu.down();
            break;
        case ENTER:
            selection = menu.getSelectedOption();
            if (selection == MAIN_MENU_OPTIONS::MY_ACCOUNTS)
            {
                system("cls");
                showMyAccounts();
            }
            else if (selection == MAIN_MENU_OPTIONS::ACCOUNT_OPTIONS)
            {

            }
            else if (selection == MAIN_MENU_OPTIONS::EXIT)
            {
                system("cls");
                key = ESC;
            }
            break;
        case ESC:
            system("cls");
            break;
        default:
            break;
        }
    }
}

void Finances::showMyAccounts()
{
    std::vector < AccountData > accountData;
    std::vector<Transaction> transactions;// = this->accounts[0].getTransactions(false); //todo (pick account, then load it transactions)
    std::vector<Transaction> transactionsIncome;// = this->accounts[0].getTransactions(true);
    std::vector<Transaction> transactionsExpenses;
    /*for (int j = 0; j < transactions2.size(); j++)
    {
        transactions.push_back(transactions2[j]);
    }
    std::sort(transactions.begin(), transactions.end());*/

    for (int i = 0; i < accounts.size(); i++)
    {
        AccountData temp;
        temp.name = accounts[i].getName();
        temp.balance = accounts[i].getBalance();
        temp.currency = accounts[i].getCurrency();
        accountData.push_back(temp);
    }
    MultiPageMenu menu(accountData, 3);
    menu.drawFrame2();
    menu.drawOptions(accountData);
    MultiPageMenu menu2(transactions, 15);
    menu2.drawFrame2(0, 4);
    menu2.drawOptions(transactions,15);
    Menu text;
    std::vector <std::string> v({ "Yes", "No" });
    Menu yesNo(v);

    std::vector<std::string> categoryNamesIncome = this->dataBase.getCategoryNames(true);
    std::vector<std::string> categoryNamesExpenses = this->dataBase.getCategoryNames(false);
    Menu menuCategoryIncome(categoryNamesIncome);
    Menu menuCategoryExpenses(categoryNamesExpenses);
    int maxWidth = 0;
    for (int i = 0; i < categoryNamesExpenses.size(); i++)
    {
        if (categoryNamesExpenses[i].length() > maxWidth)
        {
            maxWidth = categoryNamesExpenses[i].length();
        }
    }
    maxWidth += 6;

    Transaction t(200.88, this->dataBase.getCategoryByName("Shoping", false), "Hat", std::chrono::system_clock::now()); // delete

    int key = -1;
    int selection = -1;
    int selection2 = -1;
    bool upperMenuActive = true;
    bool work = true;
    bool work2 = true;
    bool isIncome = true;
    bool leftActive = true;
    bool accountChosen = false;
    int num = 0;
    std::string temp;
    Transaction newTransaction;
    double newAmount = 0;
    while (key != ESC)
    {
        menu.drawFrame2();
        menu.drawOptions(accountData);
        menu2.drawFrame2(0, 4);
        menu2.drawOptions(transactions,15);
        key = getKey();

        switch (key)
        {
        case UP_ARROW:
            upperMenuActive ? menu.up() : menu2.up();
            break;
        case DOWN_ARROW:
            upperMenuActive ? menu.down() : menu2.down();
            break;
        case ENTER:
            if (upperMenuActive)
            {
                selection = menu.getSelectedOption();
                transactions.clear();
                /*transactionsExpenses = this->accounts[selection].getTransactions(false);
                transactionsIncome = this->accounts[selection].getTransactions(true);
                transactions = transactionsExpenses;
                for (int j = 0; j < transactionsIncome.size(); j++)
                {
                    transactions.push_back(transactionsIncome[j]);
                }
                std::sort(transactions.begin(), transactions.end());*/
                transactions = getAllTransactions(this->accounts[selection]);
                menu2.clearOptions(15);
                menu2.drawOptions(transactions,15);
                accountChosen = true;
            }
            else
            {
                //selection = menu2.getSelectedOption();
            }
           
            break;
        case TAB:
            upperMenuActive = !upperMenuActive;
            break;
        case SPACE:
            selection = menu.getSelectedOption();
            showReportMenu(this->accounts[selection]);
            break;
        case CREATE_TRANSACTION_1:
            system("cls");
            if (accountChosen)
            {
                //system("cls");
                selection = menu.getSelectedOption();
                text.drawMessageFrame("Create new transaction?", 5, 6);
                yesNo.drawOptions(2, 2);
                work = true;
                do
                {
                    //std::cin.ignore(256, '\n');
                    key = getKey();
                    switch (key)
                    {
                    case UP_ARROW:
                        yesNo.up();
                        yesNo.drawOptions(2, 2);
                        break;
                    case DOWN_ARROW:
                        yesNo.down();
                        yesNo.drawOptions(2, 2);
                        break;
                    case ENTER:
                        num = yesNo.getSelectedOption();
                        if (num == YES_NO_MENU::YES)
                        {
                            text.drawMessageFrame("Enter transaction's description");
                            std::getline(std::cin, temp);
                            newTransaction.setName(temp);
                            text.drawMessageFrame("Enter transaction's amount");
                            std::cin >> newAmount;
                            newTransaction.setAmount(newAmount);

                            system("cls");
                            menuCategoryExpenses.drawFrame("Expenses", true);
                            menuCategoryExpenses.drawOptions();
                            menuCategoryIncome.drawFrame(maxWidth, 0, "Income", false);
                            menuCategoryIncome.drawOptions(maxWidth, 2);
                            key = 0;
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
                                    if (leftActive)
                                    {
                                        num = menuCategoryExpenses.getSelectedOption();
                                        newTransaction.setCategory(newTransaction.getCategoryByName(categoryNamesExpenses[num], false));
                                        work2 = false;
                                    }
                                    else
                                    {
                                        num = menuCategoryIncome.getSelectedOption();
                                        newTransaction.setCategory(newTransaction.getCategoryByName(categoryNamesExpenses[num], true));
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
                            text.drawMessageFrame("Enter transaction's date (dd.mm.yyyy)");
                            std::cin >> temp;
                            system("cls");
                            newTransaction.setDate(fromString(temp, "%d.%m.%Y"));
                            this->accounts[selection].addTransaction(newTransaction);
                            transactions.push_back(newTransaction);
                            std::sort(transactions.begin(), transactions.end());
                            menu2.clearOptions(15);
                            menu2.drawOptions(transactions, 15);
                        }
                        else if (num == YES_NO_MENU::NO)
                        {
                            work = false;
                        }
                        system("cls");
                        //work = false;
                        break;
                    default:
                        break;
                    }

                } while (work);
            }
            else
            {
                text.drawMessageFrame("Pick an account first!\n", ConsoleColor::RED_FADE);
                system("pause");
                system("cls");
            }
            break;
        case EDIT_TRANSACTION_2:
            system("cls");
            // EDIT METHOD editTransaction()
            if (accountChosen)
            {
                selection2 = menu2.getSelectedOption();
                isIncome = transactions[selection2].isIncome();
                //newTransaction = this->accounts[selection].getTransactionByIdx(selection2, isIncome);
                this->accounts[selection].editTransaction(this->accounts[selection].getTransactionByIdx(selection2, isIncome));
                transactions = getAllTransactions(this->accounts[selection]);
                system("cls");
                menu2.clearOptions(15);
                menu2.drawOptions(transactions, 15);
            }
            else
            {
                text.drawMessageFrame("Pick an account first!\n", ConsoleColor::RED_FADE);
                system("pause");
                system("cls");
            }
            break;
        case DELETE_TRANSACTION_3:
            system("cls");
            if (accountChosen)
            {
                selection2 = menu2.getSelectedOption();
                isIncome = transactions[selection2].isIncome();
                this->accounts[selection].removeTransaction(selection2, isIncome);
                transactions = getAllTransactions(this->accounts[selection]);
                system("cls");
                menu2.clearOptions(15);
                menu2.drawOptions(transactions, 15);

            }
            else
            {
                text.drawMessageFrame("Pick an account first!\n", ConsoleColor::RED_FADE);
                system("pause");
                system("cls");
            }

            break;
        case ESC:
            system("cls");
            break;
        default:
            break;
        }
    }

    //system("pause");
}

void Finances::showReportMenu(Account& account)
{
    std::vector<std::string> reportMenuOptions({ "Last N days report", "Monthly report", "Category report", "N biggest transactions", "Go Back"});
    Menu menu(reportMenuOptions);
    int key = -1;
    int selection = -1;
    system("cls");

    while (key != ESC)
    {
        menu.drawFrame();
        menu.drawOptions();
        key = getKey();

        switch (key)
        {
        case UP_ARROW:
            menu.up();
            break;
        case DOWN_ARROW:
            menu.down();
            break;
        case ENTER:
            selection = menu.getSelectedOption();
            system("cls");
            if (selection == REPORTS_MENU_OPTIONS::LAST_N_DAYS_REPORT)
            {
                this->report.showLastNDaysReport(account, 30);
            }
            else if (selection == REPORTS_MENU_OPTIONS::MONTHLY_REPORT)
            {
                this->report.showMonthlyReport(account, 10);
            }
            else if (selection == REPORTS_MENU_OPTIONS::CATEGORY_REPORT)
            {
                this->report.showTransactionsByCategory(account, 10);
            }
            else if (selection == REPORTS_MENU_OPTIONS::N_BIGGEST_TRANSACTIONS)
            {
                this->report.showNBiggestTransactions(account, 3 ,false);
            }
            else if (selection == REPORTS_MENU_OPTIONS::GO_BACK)
            {
                system("cls");
                key = ESC;
            }
            system("pause");
            system("cls");
            break;
        case ESC:
            system("cls");
            break;
        default:
            break;
        }
    }
}

std::vector<Transaction> Finances::getAllTransactions(Account& account)
{
    std::vector<Transaction> result;
    
    std::vector<Transaction> transactionsExpenses = account.getTransactions(false);
    std::vector<Transaction> transactionsIncome = account.getTransactions(true);
    result = transactionsExpenses;

    for (int j = 0; j < transactionsIncome.size(); j++)
    {
        result.push_back(transactionsIncome[j]);
    }
    std::sort(result.begin(), result.end());

    return result;
}