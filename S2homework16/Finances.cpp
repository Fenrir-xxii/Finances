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
                system("cls");
                showOptions();
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
    this->dataBase.updateAccounts(this->accounts);
    this->dataBase.saveAll();
}

void Finances::showMyAccounts()
{
    std::vector<AccountData> accountData = getAllAccountsData();
    std::vector<Transaction> transactions;
    std::vector<Transaction> transactionsIncome;
    std::vector<Transaction> transactionsExpenses;
    
    MultiPageMenu accountMenu(accountData, 3);
    accountMenu.drawFrame2();
    accountMenu.drawOptions(accountData);
    int multiMenuSize = 17;
    MultiPageMenu transactionMenu(transactions, multiMenuSize);
    transactionMenu.drawFrame2(0, 4);
    transactionMenu.drawOptions(transactions, multiMenuSize);
    Menu text;
    //std::vector <std::string> v({ "Yes", "No" });
    Menu yesNo({ "Yes", "No" });

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

    //Transaction t(200.88, this->dataBase.getCategoryByName("Shoping", false), "Hat", std::chrono::system_clock::now()); // delete

    int key = -1;
    int accountSelection = -1;
    int transactionSelection = -1;
    bool accountMenuActive = true;
    bool creatingNewTransaction = true;
    bool choosingCategory = true;
    bool isIncome = true;
    bool menuCategoryExpensesActive = true;
    bool accountChosen = false;
    int num = 0;
    int indexOfTransaction = -1;
    std::string temp;
    std::string activeAcc;
    Transaction newTransaction;
    double newAmount = 0;

    accountMenu.drawFrame2();
    accountMenu.drawOptions(accountData);
    transactionMenu.drawFrame2(0, 4);
    transactionMenu.drawOptions(transactions, multiMenuSize);
    while (key != ESC)
    {
        key = getKey();

        switch (key)
        {
        case UP_ARROW:
            accountMenuActive ? accountMenu.up() : transactionMenu.up();
            accountMenuActive ? accountMenu.drawOptions(accountData) : transactionMenu.drawOptions(transactions, multiMenuSize);
            break;
        case DOWN_ARROW:
            accountMenuActive ? accountMenu.down() : transactionMenu.down();
            accountMenuActive ? accountMenu.drawOptions(accountData) : transactionMenu.drawOptions(transactions, multiMenuSize);
            break;
        case ENTER:     // choosing account
            if (accountMenuActive)
            {
                accountSelection = accountMenu.getSelectedOption();
                activeAcc = accountData[accountSelection].name + " chosen";
                accountMenu.drawFrame2();
                text.drawText(3, 0, activeAcc, ConsoleColor::BLACK, ConsoleColor::GRAY);
                transactions.clear();

                transactionsExpenses = this->accounts[accountSelection].getTransactions(false);
                transactionsIncome = this->accounts[accountSelection].getTransactions(true);
                transactions = getAllTransactions(this->accounts[accountSelection]);
                MultiPageMenu temp(transactions, multiMenuSize);
                transactionMenu.clearOptions(multiMenuSize);
                transactionMenu = temp;
                transactionMenu.drawOptions(transactions, multiMenuSize);
                accountChosen = true;
            }
            break;
        case TAB:    // switch between account menu and transaction menu
            accountMenuActive = !accountMenuActive;
            break;
        case SPACE:  // report menu
            accountSelection = accountMenu.getSelectedOption();
            showReportMenu(this->accounts[accountSelection]);
            break;
        case CREATE_TRANSACTION_1:
            system("cls");
            if (accountChosen)
            {
                accountSelection = accountMenu.getSelectedOption();
                text.drawMessageFrame("Create new transaction?", 5, 6);
                yesNo.drawOptions(2, 2);
                creatingNewTransaction = true;
                do
                {
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
                            std::cin.ignore(256, '\n');
                            newTransaction.setAmount(newAmount);

                            system("cls");
                            menuCategoryExpenses.drawFrame("Expenses", true);
                            menuCategoryExpenses.drawOptions();
                            menuCategoryIncome.drawFrame(maxWidth, 0, "Income", false);
                            menuCategoryIncome.drawOptions(maxWidth, 2);
                            key = 0;
                            choosingCategory = true;
                            while (choosingCategory)
                            {
                                key = getKey();
                                switch (key)
                                {
                                case UP_ARROW:
                                    menuCategoryExpensesActive ? menuCategoryExpenses.up() : menuCategoryIncome.up();
                                    menuCategoryExpenses.drawFrame("Expenses", true);
                                    menuCategoryExpenses.drawOptions();
                                    menuCategoryIncome.drawFrame(maxWidth, 0, "Income", false);
                                    menuCategoryIncome.drawOptions(maxWidth, 2);
                                    break;
                                case DOWN_ARROW:
                                    menuCategoryExpensesActive ? menuCategoryExpenses.down() : menuCategoryIncome.down();
                                    menuCategoryExpenses.drawFrame("Expenses", true);
                                    menuCategoryExpenses.drawOptions();
                                    menuCategoryIncome.drawFrame(maxWidth, 0, "Income", false);
                                    menuCategoryIncome.drawOptions(maxWidth, 2);
                                    break;
                                case TAB:
                                    menuCategoryExpensesActive = !menuCategoryExpensesActive;
                                    break;
                                case ENTER:
                                    if (menuCategoryExpensesActive)
                                    {
                                        num = menuCategoryExpenses.getSelectedOption();
                                        newTransaction.setCategory(newTransaction.getCategoryByName(categoryNamesExpenses[num], false));
                                        choosingCategory = false;
                                    }
                                    else
                                    {
                                        num = menuCategoryIncome.getSelectedOption();
                                        newTransaction.setCategory(newTransaction.getCategoryByName(categoryNamesIncome[num], true));
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
                            text.drawMessageFrame("Enter transaction's date (dd.mm.yyyy)");
                            std::cin >> temp;
                            std::cin.ignore(256, '\n');
                            system("cls");
                            newTransaction.setDate(fromString(temp, "%d.%m.%Y"));
                            this->accounts[accountSelection].addTransaction(newTransaction);
                            transactions.push_back(newTransaction);
                            std::sort(transactions.begin(), transactions.end());
                            //transactionMenu.clearOptions(multiMenuSize);
                            //transactionMenu.drawOptions(transactions, multiMenuSize);
                            MultiPageMenu temp(transactions, multiMenuSize);
                            transactionMenu = temp;
                            accountData = getAllAccountsData();
                            creatingNewTransaction = false;
                        }
                        else if (num == YES_NO_MENU::NO)
                        {
                            creatingNewTransaction = false;
                        }
                        system("cls");
                        break;
                    default:
                        break;
                    }

                } while (creatingNewTransaction);
            }
            else
            {
                text.drawMessageFrame("Choose an account first!\n", ConsoleColor::RED_FADE);
                system("pause");
                system("cls");
            }
            accountMenu.drawFrame2();
            accountMenu.drawOptions(accountData);
            /*MultiPageMenu temp(transactions, multiMenuSize);
            transactionMenu = temp;*/
            transactionMenu.drawFrame2(0, 4);
            text.drawText(3, 0, activeAcc, ConsoleColor::BLACK, ConsoleColor::GRAY);
            transactionMenu.drawOptions(transactions, multiMenuSize);
            break;
        case EDIT_TRANSACTION_2:
            system("cls");
            if (accountChosen)
            {
                indexOfTransaction = -1;
                transactionSelection = transactionMenu.getSelectedOption();
                isIncome = transactions[transactionSelection].isIncome();
                if (isIncome)
                {
                    for (int i = 0; i < transactionsIncome.size(); i++)
                    {
                        if (transactionsIncome[i] == transactions[transactionSelection])
                        {
                            indexOfTransaction = i;
                            break;
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < transactionsExpenses.size(); i++)
                    {
                        if (transactionsExpenses[i] == transactions[transactionSelection])
                        {
                            indexOfTransaction = i;
                            break;
                        }
                    }
                }
                //this->accounts[accountSelection].editTransaction(this->accounts[accountSelection].getTransactionByIdx(indexOfTransaction, isIncome), indexOfTransaction);
                if (isIncome)
                {
                    this->accounts[accountSelection].editDebitTransaction(indexOfTransaction);
                }
                else
                {
                    this->accounts[accountSelection].editCreditTransaction(indexOfTransaction);
                }

                transactions = getAllTransactions(this->accounts[accountSelection]);
                accountData = getAllAccountsData();
                transactionsExpenses = this->accounts[accountSelection].getTransactions(false);
                transactionsIncome = this->accounts[accountSelection].getTransactions(true);
                system("cls");
                accountMenu.drawFrame2();
                accountMenu.drawOptions(accountData);
                transactionMenu.clearOptions(multiMenuSize);
                transactionMenu.drawFrame2(0, 4);
                text.drawText(3, 0, activeAcc, ConsoleColor::BLACK, ConsoleColor::GRAY);
                transactionMenu.drawOptions(transactions, multiMenuSize);
            }
            else
            {
                text.drawMessageFrame("Choose an account first!\n", ConsoleColor::RED_FADE);
                system("pause");
                system("cls");
            }
            break;
        case DELETE_TRANSACTION_3:
            system("cls");
            if (accountChosen)
            {
                indexOfTransaction = -1;
                transactionSelection = transactionMenu.getSelectedOption();
                isIncome = transactions[transactionSelection].isIncome();

                if (isIncome)
                {
                    for (int i = 0; i < transactionsIncome.size(); i++)
                    {
                        if (transactionsIncome[i] == transactions[transactionSelection])
                        {
                            indexOfTransaction = i;
                            break;
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < transactionsExpenses.size(); i++)
                    {
                        if (transactionsExpenses[i] == transactions[transactionSelection])
                        {
                            indexOfTransaction = i;
                            break;
                        }
                    }
                }

                this->accounts[accountSelection].removeTransaction(indexOfTransaction, isIncome);
                transactions = getAllTransactions(this->accounts[accountSelection]);
                transactionsExpenses = this->accounts[accountSelection].getTransactions(false);
                transactionsIncome = this->accounts[accountSelection].getTransactions(true);
                //system("cls");
                accountData = getAllAccountsData();
                accountMenu.drawFrame2();
                accountMenu.drawOptions(accountData);
                MultiPageMenu temp(transactions, multiMenuSize);
                transactionMenu = temp;
                transactionMenu.clearOptions(multiMenuSize);
                transactionMenu.drawFrame2(0, 4);
                text.drawText(3, 0, activeAcc, ConsoleColor::BLACK, ConsoleColor::GRAY);
                transactionMenu.drawOptions(transactions, multiMenuSize);
                //accountData = getAllAccountsData();
            }
            else
            {
                text.drawMessageFrame("Choose an account first!\n", ConsoleColor::RED_FADE);
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

void Finances::showOptions()
{
    std::vector<std::string> settingsMenuOptions({ "Open new account", "Close account", "Return" });
    Menu menu(settingsMenuOptions);
    Menu text;
    Menu yesNo({ "Yes", "No" });
    std::vector<std::string> currencyNames = this->dataBase.getCurrency();
    Menu currencyMenu(currencyNames);
    bool openingAccount = true;
    bool choosingCurrency = true;
    int num = -1;
    int key = -1;
    int selection = -1;
    std::string temp;
    Account newAcc;

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
            if (selection == ACCOUNT_SETTINGS_OPTIONS::CREATE)
            {
                system("cls");
                text.drawMessageFrame("Do You want to open a new account?", 5, 6);
                yesNo.drawOptions(2, 2);
                openingAccount = true;
                do
                {
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
                            text.drawMessageFrame("Enter name for your account");
                            std::getline(std::cin, temp);
                            newAcc.setName(temp);
                            text.drawMessageFrame("Pick currency of account");
                    
                            system("cls");
                            currencyMenu.drawFrame();
                            currencyMenu.drawOptions();
                            key = 0;
                            while (choosingCurrency)
                            {
                                key = getKey();
                                switch (key)
                                {
                                case UP_ARROW:
                                    currencyMenu.up();
                                    currencyMenu.drawOptions();
                                    break;
                                case DOWN_ARROW:
                                    currencyMenu.down();
                                    currencyMenu.drawOptions();
                                    break;
                                case ENTER:
                                    num = currencyMenu.getSelectedOption();
                                    newAcc.setCurrency(currencyNames[num]);
                                    newAcc.setBalance(0);
                                    this->dataBase.addAccount(newAcc);
                                    this->accounts.push_back(newAcc);
                                    system("cls");
                                    return;
                                case ESC:
                                    system("cls");
                                    choosingCurrency = false;
                                    break;
                                }
                            }
                        }
                        else if (num == YES_NO_MENU::NO)
                        {
                            openingAccount = false;
                        }
                        system("cls");
                        break;
                    default:
                        break;
                    }

                } while (openingAccount);
            }
            else if (selection == ACCOUNT_SETTINGS_OPTIONS::REMOVE)
            {

            }
            else if (selection == ACCOUNT_SETTINGS_OPTIONS::RETURN)
            {
                system("cls");
                return;
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

std::vector <AccountData> Finances::getAllAccountsData()
{
    std::vector<AccountData> result;
    for (int i = 0; i < accounts.size(); i++)
    {
        AccountData temp;
        temp.name = accounts[i].getName();
        temp.balance = accounts[i].getBalance();
        temp.currency = accounts[i].getCurrency();
        result.push_back(temp);
    }

    return result;
}

void Finances::showAddNewCategoryMenu()
{
    Menu text;
    Menu yesNo({ "Yes", "No" });

    system("cls");
    text.drawMessageFrame("Do You want to add a new category?", 5, 6);
    yesNo.drawOptions(2, 2);
    bool addingCategory = true;
    bool isIncomeCategory = true;
    int key = -1;
    int num = -1;
    std::string temp;

    do
    {
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
                text.drawMessageFrame("Enter name of category");
                std::getline(std::cin, temp);
                text.drawMessageFrame("Is this category an income?", 5, 6);
                yesNo.drawOptions(2, 2);
                do
                {
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
                            this->dataBase.addCategory(temp, true);
                        }
                        else
                        {
                            this->dataBase.addCategory(temp, false);
                        }
                        isIncomeCategory = false;
                        return;
                    case ESC:
                        system("cls");
                        isIncomeCategory = false;
                        break;
                    }
                } while (isIncomeCategory);
            }
            else if (num == YES_NO_MENU::NO)
            {
                addingCategory = false;
            }
            system("cls");
            break;
        case ESC:
            system("cls");
            addingCategory = false;
            break;
        default:
            break;
        }

    } while (addingCategory);
}



//int Finances::getIdxOfTransaction(bool isIncome)
//{
//
//}