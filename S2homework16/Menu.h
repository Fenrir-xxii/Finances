#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "console.h"
#include "Transaction.h"
#include "Time.h"


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

	void drawFrame(int cX, int xY, std::string header, bool active);

	void drawOptions();

	void drawOptions(int cX, int cY);

	void drawTransaction(Transaction& transaction);

	void down();

	void up();

	int getSelectedOption() const;

	void setActiveOption(int idx);

	void drawMessageFrame(std::string message);
};