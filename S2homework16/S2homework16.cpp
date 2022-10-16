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

int main()
{
    ShowConsoleCursor(false);

    Finances finances;
    finances.showMainMenu();

    return 0;
}