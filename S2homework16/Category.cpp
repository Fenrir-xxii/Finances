#include "Category.h"

void Category::setId(int id)
{
	this->id = id;
}

std::string Category::getName()
{
	return this->name;
}

bool Category::getIsIncome()
{
	return this->isIncome;
}

int Category::getId()
{
	return this->id;
}
