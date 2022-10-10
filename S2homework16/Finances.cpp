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
    std::vector<Transaction> transactions2;// = this->accounts[0].getTransactions(true);

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

    Transaction t(200.88, this->dataBase.getCategoryByName("Shoping", false), "Hat", std::chrono::system_clock::now()); // delete

    int key = -1;
    int selection = -1;
    bool upperMenuActive = true;

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
                transactions = this->accounts[selection].getTransactions(false);
                transactions2 = this->accounts[selection].getTransactions(true);
                for (int j = 0; j < transactions2.size(); j++)
                {
                    transactions.push_back(transactions2[j]);
                }
                std::sort(transactions.begin(), transactions.end());
                menu2.clearOptions(15);
                menu2.drawOptions(transactions,15);
            }
            else
            {
                selection = menu2.getSelectedOption();
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
            // TO DO
            selection = menu.getSelectedOption();
            //Transaction t(200.88, this->dataBase.getCategoryByName("Shoping", false), "Hat", std::chrono::system_clock::now());
            this->accounts[selection].addTransaction(t);
            transactions.push_back(t);
            std::sort(transactions.begin(), transactions.end());
            menu2.clearOptions(15);
            menu2.drawOptions(transactions, 15);
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