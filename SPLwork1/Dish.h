#ifndef DISH_H_
#define DISH_H_
#include <string>
using namespace std;

enum DishType {
	VEG, SPC, BVG, ALC
};

class Dish {
public:
	Dish(int d_id, std::string d_name, int d_price, DishType d_type);
	Dish(const Dish& Other);
	Dish(Dish&& Other);
	~Dish();
	//Dish* operator=(const Dish& other);
	//Dish* operator=(Dish&& other);
	int getId() const;
	string getName() const;
	int getPrice() const;
	DishType getType() const;
private:
	const int id;
	const string name;
	const int price;
	const DishType type;
};


#endif