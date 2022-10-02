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
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN_FADE);
				std::cout << ' ';
			}
		}
	}
	SetColor(WHITE, BLACK);
}


void Menu::drawFrame(std::string header)
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
				SetColor(ConsoleColor::WHITE, ConsoleColor::GREEN_FADE);
				std::cout << ' ';
			}
		}
	}
	SetCursorPosition(1, 0);
	SetColor(ConsoleColor::BLACK, ConsoleColor::GREEN_FADE);
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
	int startX = cX;
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