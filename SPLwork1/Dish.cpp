#include "Dish.h"




Dish::Dish(int d_id, std::string d_name, int d_price, DishType d_type) : id(d_id), name(d_name), price(d_price), type(d_type)
{
}

Dish::Dish(const Dish & Other) : id(Other.id), name(Other.name), price(Other.price), type(Other.type)
{
}

Dish::Dish(const Dish&& Other) : id(Other.id), name(Other.name), price(Other.price), type(Other.type)
{
}

Dish * Dish::operator=(const Dish & other)
{
	return this;
}

Dish * Dish::operator=(const Dish&& other)
{
	return this;
}

Dish::~Dish()
{
}

int Dish::getId() const
{
	return id;
}

std::string Dish::getName() const
{
	return name;
}

int Dish::getPrice() const
{
	return price;
}

DishType Dish::getType() const
{
	return type;
}
