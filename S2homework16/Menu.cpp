#include "menu.h"

size_t Menu::getMaxItemSize() const
{
	size_t max = 0;
	for (std::string item : options)
	{
		if (item.size() > max) {
			max = item.size();
		}
	}
	return max;
}

size_t Menu::getFrameWidth() const
{
	return getMaxItemSize() + 6;
}

size_t Menu::getFrameHeight() const
{
	return options.size() + 4;
}

Menu::Menu(const std::vector<std::string>& options)
{
	this->options = options;
}

void Menu::drawFrame()
{
	size_t widht = getFrameWidth();
	size_t height = getFrameHeight();
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < widht; x++)
		{
			if (x == 0 || x == widht - 1 || y == 0 || y == height - 1) {
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN_FADE);
				std::cout << ' ';
			}
		}
	}
	SetColor(WHITE, BLACK);
}

void Menu::drawFrame(bool active)
{
	size_t widht = getFrameWidth();
	size_t height = getFrameHeight();

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < widht; x++)
		{
			if (x == 0 || x == widht - 1 || y == 0 || y == height - 1) {
				SetCursorPosition(x, y);
				active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
				std::cout << ' ';
			}
		}
	}

	for (int i = 0; i < widht; i++)
	{
		SetCursorPosition(i, 2);
		active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
		std::cout << ' ';
	}

	SetColor(WHITE, BLACK);
}

void Menu::drawFrame(int cX, int cY)
{
	size_t widht = getFrameWidth() + cX;
	size_t height = getFrameHeight() + cY;
	for (size_t y = cY; y < height; y++)
	{
		for (size_t x = cX; x < widht; x++)
		{
			if (x == cX || x == widht - 1 || y == cY || y == height - 1) {
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE);
				std::cout << ' ';
			}
		}
	}
	SetColor(WHITE, BLACK);
}


void Menu::drawFrame(std::string header, bool active)
{
	size_t headerSize = header.size()+2;
	size_t width = getFrameWidth();
	size_t maxWidth = (width > headerSize) ? width : headerSize;
	size_t height = getFrameHeight();

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < maxWidth; x++)
		{
			if (x == 0 || x == maxWidth-1 || y == 0 || y == height - 1) 
			{
				SetCursorPosition(x, y);
				active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
				std::cout << ' ';
			}
		}
	}
	SetCursorPosition(1, 0);
	active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
	std::cout << header;
	SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}

void Menu::drawFrame(int cX, int cY, std::string header, bool active)
{
	size_t headerSize = header.size() + 2;
	size_t width = getFrameWidth() + cX;
	size_t maxWidth = (width > headerSize) ? width : headerSize;
	size_t height = getFrameHeight() + cY;

	for (size_t y = cY; y < height; y++)
	{
		for (size_t x = cX; x < maxWidth; x++)
		{
			if (x == cX || x == maxWidth - 1 || y == cY || y == height - 1)
			{
				SetCursorPosition(x, y);
				active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
				std::cout << ' ';
			}
		}
	}
	SetCursorPosition(cX+1, 0);
	active ? SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE) : SetColor(ConsoleColor::WHITE, ConsoleColor::GRAY);
	std::cout << header;
	SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}

void Menu::drawOptions() 
{
	int startX = 3;
	int startY = 2;
	int max = getMaxItemSize();
	for (size_t i = 0; i < options.size(); i++)
	{
		SetCursorPosition(startX, startY + i);
		if (activeOption == i) 
		{
			SetColor(RED, WHITE);
		}
		else 
		{
			SetColor(WHITE, BLACK);
		}
		auto item = options[i];
		item.append(std::string(max - item.size(), ' '));
		std::cout << item;
	}
	SetColor(WHITE, BLACK);
}

void Menu::drawOptions(int cX, int cY) 
{
	int startX = cX+3;
	int startY = cY;
	int max = getMaxItemSize();
	for (size_t i = 0; i < options.size(); i++)
	{
		SetCursorPosition(startX, startY + i);
		if (activeOption == i) 
		{
			SetColor(RED, WHITE);
		}
		else 
		{
			SetColor(WHITE, BLACK);
		}
		auto item = options[i];
		item.append(std::string(max - item.size(), ' '));
		std::cout << item;
	}
	SetColor(WHITE, BLACK);
}

void Menu::drawOptions2(int size, int currentLine, int previousLine)
{
	int startX = 3;
	int startY = 2;
	int max = getMaxItemSize();

	int upperEdge = 0;
	int lowerEdge = size;

	int start = 0;

	if (currentLine >= size)
	{
		start = currentLine - size + 1;
		//start = currentLine - size+1;
		//start++;
	}
	/*if (currentLine < previousLine)
	{
		start = previousLine - size;
	}*/
	int end = start + size;

	for (size_t i = start; i < end; i++)
	{
		if (i <= end)
		{
			SetCursorPosition(startX, startY + i-start);
			if (activeOption == i)
			{
				SetColor(RED, WHITE);
			}
			else
			{
				SetColor(WHITE, BLACK);
			}
			auto item = options[i];
			item.append(std::string(max - item.size(), ' '));
			std::cout << item;
		}
	}
	SetColor(WHITE, BLACK);
}

void Menu::drawTransaction(Transaction& transaction)
{
	this->options.clear();
	this->options.push_back(transaction.getName());
	this->options.push_back(std::to_string(transaction.getAmount()));
	this->options.push_back(transaction.getCategory()->getName());
	this->options.push_back(timeToString(transaction.getDate()));
	drawOptions();
}

void Menu::drawMessageFrame(std::string message)
{
	system("cls");
	SetCursorPosition(0, 0);

	for (size_t coordY = 0; coordY < 10; coordY++)
	{
		for (size_t coordX = 0; coordX < 50; coordX++)
		{
			if (coordX == 0 || coordX == 50 - 1 || coordY == 0 || coordY == 10 - 1) 
			{
				SetCursorPosition(coordX, coordY);
				SetColor(ConsoleColor::WHITE, ConsoleColor::BLUE_FADE);
				std::cout << ' ';
			}
		}
	}
	SetCursorPosition(1, 0);
	std::cout << message << std::endl;
	SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	SetCursorPosition(1, 2);

}

void Menu::down() 
{
	activeOption++;
	if (activeOption >= options.size()) 
	{
		activeOption = 0;
	}
}

void Menu::up() 
{
	activeOption--;
	if (activeOption < 0) 
	{
		activeOption = options.size() - 1;
	}
}

int Menu::getSelectedOption() const 
{
	return activeOption;
}

void Menu::setActiveOption(int idx)
{
	activeOption = idx;
}






size_t MultiPageMenu::getMaxItemSize() const
{
	size_t max = 0;
	for (std::string item : options)
	{
		if (item.size() > max)
		{
			max = item.size();
		}
	}
	return max;
}

size_t MultiPageMenu::getFrameWidth() const
{
	return getMaxItemSize() + 6;
}

size_t MultiPageMenu::getFrameHeight() const
{
	return rows + 4;
}

void MultiPageMenu::drawFrame()
{
	size_t width = getFrameWidth();
	size_t height = getFrameHeight();
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
			{
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN);
				std::cout << ' ';
			}
		}
	}
	SetColor(WHITE, BLACK);
}

void MultiPageMenu::drawFrame2()
{
	size_t width = 80;
	size_t height = 5;
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
			{
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN);
				std::cout << ' ';
			}
		}
	}

	for (size_t y = 1; y < height-1; y++)
	{
		for (size_t x = width-25; x < width; x++)
		{
			if (x == width - 25 or x == width - 7)
			{
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN);
				std::cout << ' ';
			}
		}
	}

	SetColor(WHITE, BLACK);
}

void MultiPageMenu::drawFrame2(int cX, int cY)
{
	size_t width = 80;
	size_t height = 25;
	for (size_t y = cY; y < height; y++)
	{
		for (size_t x = cX; x < width; x++)
		{
			if (x == cX || x == width - 1 || y == cY || y == height - 1)
			{
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN);
				std::cout << ' ';
			}
		}
	}

	for (size_t x = cX; x < width; x++)  // headers line (horizontal)
	{
		SetCursorPosition(x, cY+2);
		SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN);
		std::cout << ' ';
	}

	for (size_t y = cY; y < height; y++)
	{
		for (size_t x = cX+11; x < width; x++)
		{
			if (x == cX+11 or x == cX + 41 or x == cX + 57 or x == width - 12)
			{
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN);
				std::cout << ' ';
			}
		}
	}
	

	SetColor(WHITE, BLACK);
}

void MultiPageMenu::drawOptions()
{
	int startX = 3;
	int startY = 2;
	int max = getMaxItemSize();

	for (size_t i = beginRow; i < endRow; i++)
	{
		if (i >= options.size())
		{
			SetCursorPosition(startX, startY + (i - beginRow));
			SetColor(WHITE, BLACK);
			std::cout << std::string(max, ' ');
			continue;
		}
		SetCursorPosition(startX, startY + (i - beginRow));
		if (activeOption == i)
		{
			SetColor(RED, WHITE);
		}
		else
		{
			SetColor(WHITE, BLACK);
		}
		auto item = options[i];
		item.append(std::string(max - item.size(), ' '));
		std::cout << item;
	}
}

void MultiPageMenu::drawOptions(std::vector < AccountData > &accountData)
{
	int startX = 3;
	int startY = 1;
	int max = getMaxItemSize();

	for (size_t i = beginRow; i < endRow; i++)
	{
		if (i >= accountData.size())
		{
			SetCursorPosition(startX, startY + (i - beginRow));
			SetColor(WHITE, BLACK);
			std::cout << std::string(max, ' ');
			continue;
		}
		SetCursorPosition(startX, startY + (i - beginRow));
		if (activeOption == i)
		{
			SetColor(RED, WHITE);
		}
		else
		{
			SetColor(WHITE, BLACK);
		}
		auto item = accountData[i].name;
		item.append(std::string(max - item.size(), ' '));
		std::cout << item;
	}

	for (size_t i = beginRow; i < endRow; i++)
	{
		SetCursorPosition(56, i+1);
		std::cout << accountData[i].balance;
		SetCursorPosition(74, i+1);
		std::cout << accountData[i].currency;
	}
	std::cout << std::endl;

}

void MultiPageMenu::drawOptions(std::vector < Transaction >& transactions)
{
	SetCursorPosition(1, 5);
	std::cout << "date";
	SetCursorPosition(12, 5);
	std::cout << "description";
	SetCursorPosition(42, 5);
	std::cout << "category";
	SetCursorPosition(58, 5);
	std::cout << "debit";
	SetCursorPosition(69, 5);
	std::cout << "credit";
	SetCursorPosition(0, 35);
}

void MultiPageMenu::down() {
	activeOption++;
	if (activeOption >= options.size())
	{
		activeOption = 0;
		beginRow = 0;
		endRow = rows;
	}
	if (activeOption >= endRow)
	{
		beginRow++;
		endRow++;
	}
}

void MultiPageMenu::up()
{
	activeOption--;
	if (activeOption < 0) {
		activeOption = options.size() - 1;
		beginRow = options.size() - rows;
		endRow = options.size();
	}
	if (activeOption < beginRow)
	{
		beginRow--;
		endRow--;
	}
}

int MultiPageMenu::getSelectedOption() const
{
	return activeOption;
}
