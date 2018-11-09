#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"
using namespace std;

class Customer {
public:
	Customer(string c_name, int c_id);
	virtual vector<int> order(const vector<Dish> &menu) = 0;
	virtual string toString() const = 0;
	string getName() const;
	int getId() const;
private:
	const string name;
	const int id
};


class VegetarianCustomer : public Customer {
public:
	VegetarianCustomer(string name, int id);
	vector<int> order(const vector<Dish> &menu);
	string toString() const;
private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(string name, int id);
	vector<int> order(const vector<Dish> &menu);
	string toString() const;
private:
};


class SpicyCustomer : public Customer {
public:
	SpicyCustomer(string name, int id);
	vector<int> order(const vector<Dish> &menu);
	string toString() const;
private:
};


class AlchoholicCustomer : public Customer {
public:
	AlchoholicCustomer(string name, int id)
	vector<int> order(const vector<Dish> &menu);
	string toString() const;
private:
};


#endif