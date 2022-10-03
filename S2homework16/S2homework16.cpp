#include <iostream>
#include "DataBase.h"
#include "Transaction.h"
#include "Account.h"

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
    ShowConsoleCursor(false);
    DataBase dataBase;
    /*dataBase.addCategory("Food", false);
    dataBase.addCategory("Salary", true);
    dataBase.saveCategories();*/
    //dataBase.loadCategories();



    auto timeNow = std::chrono::system_clock::now();
    Category category("Food", false);
    Transaction transaction(203.50, category, "Potatoes", timeNow);
    Account account;
    account.addTransaction(transaction);
    account.editCreditTransaction(0);

}
