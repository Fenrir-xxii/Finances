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
    std::vector<Transaction> transactions; //todo (pick account, then load it transactions)

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
    menu.drawFrame2(0, 4);
    menu.drawOptions(transactions);
    system("pause");
}