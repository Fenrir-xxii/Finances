#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "console.h"
#include "Transaction.h"
#include "Time.h"
#include "Enum.h"


class Menu {
private:
	int activeOption = 0;
	std::vector<std::string> options;
	size_t getMaxItemSize() const;
	size_t getFrameWidth() const;
	size_t getFrameHeight() const;
public:
	Menu(const std::vector<std::string>& options);
	Menu() {};
	void drawFrame();
	void drawFrame(bool active);
	void drawFrame(int cX, int xY);
	void drawFrame(std::string header, bool active);
    void drawFrame(std::string header, bool active, ConsoleColor color);
	void drawFrame(int cX, int cY, std::string header, bool active);
    void drawFrame(int cX, int cY, std::string header, bool active, ConsoleColor color);
	void drawOptions();
	void drawOptions(int cX, int cY);
	void drawOptions2(int size, int currentLine, int previousLine);
	void drawTransaction(Transaction& transaction);
	void down();
	void up();
	int getSelectedOption() const;
	void setActiveOption(int idx);
	void drawMessageFrame(std::string message);
    void drawMessageFrame(std::string message, ConsoleColor color);
    void drawMessageFrame(std::string message, int width, int height);
    void drawText(int cX, int cY, std::string text, ConsoleColor textColor, ConsoleColor backgroundColor);
};




class MultiPageMenu {
private:
    int activeOption = 0;
    int beginRow;
    int endRow;
    int rows;
    std::vector<std::string> options;
    size_t getMaxItemSize() const;
    size_t getFrameWidth() const;
    size_t getFrameHeight() const;
public:
    MultiPageMenu(const std::vector<std::string>& options, int rows) 
    {
        this->options = options;
        this->rows = rows;
        beginRow = 0;
        endRow = rows;
        activeOption = 0;
    }
    MultiPageMenu(const std::vector<AccountData>& accountData, int rows)
    {
        for (int i = 0; i < accountData.size(); i++)
        {
            this->options.push_back(accountData[i].name);
        }
        this->rows = rows > accountData.size() ? accountData.size() : rows;
        beginRow = 0;
        endRow = rows > accountData.size() ? accountData.size() : rows;
        activeOption = 0;
    }
    MultiPageMenu(std::vector<Transaction>& transactions, int rows)
    {
        for (int i = 0; i < transactions.size(); i++)
        {
            this->options.push_back(transactions[i].getName());
        }
        this->rows = rows > transactions.size() ? transactions.size() : rows;
        beginRow = 0;
        endRow = rows > transactions.size() ? transactions.size() : rows;
        activeOption = 0;
    }
    MultiPageMenu(MultiPageMenu& m)
    {
        this->options = m.options;
        this->activeOption = m.activeOption;
        this->beginRow = m.beginRow;
        this->endRow = m.endRow;
        this->rows = m.rows;
    }

    void drawFrame();
	void drawFrame2();
    void drawFrame2(int cX, int cY);
    void drawOptions();
	void drawOptions(std::vector < AccountData > &accountData);
    void drawOptions(std::vector < Transaction >& transactions, int rows);
    void clearOptions(int rows);
    void down();
    void up();
	int getSelectedOption() const;

    MultiPageMenu& operator=(MultiPageMenu& m)
    {
        this->options = m.options;
        this->activeOption = m.activeOption;
        this->beginRow = m.beginRow;
        this->endRow = m.endRow;
        this->rows = m.rows;
        return *this;
    }

};