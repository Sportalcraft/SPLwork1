#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"

using namespace std;

class Customer {
public:
	Customer(string c_name, int c_id);
	Customer(const Customer& Other);
	Customer(Customer&& Other);
	virtual ~Customer();
	//Customer* operator=(const Customer& other);
	//Customer* operator=(Customer&& other);
	virtual vector<int> order(const vector<Dish> &menu) = 0;
	virtual string toString() const = 0;
	virtual Customer* clone() const = 0;
	string getName() const;
	int getId() const;
protected:
	vector<Dish> orders;
private:
	const string name;
	const int id;
};


class VegetarianCustomer : public Customer {
public:
	VegetarianCustomer(string name, int id);
	VegetarianCustomer(const VegetarianCustomer& Other);
	VegetarianCustomer(VegetarianCustomer&& Other);
	virtual ~VegetarianCustomer();
	//VegetarianCustomer* operator=(const VegetarianCustomer& other);
	//VegetarianCustomer* operator=(VegetarianCustomer&& other);
	vector<int> order(const vector<Dish> &menu);
	string toString() const;
	virtual Customer* clone() const;
private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(string name, int id);
	CheapCustomer(const CheapCustomer& Other);
	CheapCustomer(CheapCustomer&& Other);
	virtual ~CheapCustomer();
	//CheapCustomer* operator=(const CheapCustomer& other);
	//CheapCustomer* operator=(CheapCustomer&& other);
	vector<int> order(const vector<Dish> &menu);
	string toString() const;
	virtual Customer* clone() const;
private:
};


class SpicyCustomer : public Customer {
public:
	SpicyCustomer(string name, int id);
	SpicyCustomer(const SpicyCustomer& Other);
	SpicyCustomer(SpicyCustomer&& Other);
	virtual ~SpicyCustomer();
	//SpicyCustomer* operator=(const SpicyCustomer& other);
	//SpicyCustomer* operator=(SpicyCustomer&& other);
	vector<int> order(const vector<Dish> &menu);
	string toString() const;
	virtual Customer* clone() const;
private:
};


class AlchoholicCustomer : public Customer {
public:
	AlchoholicCustomer(string name, int id);
	AlchoholicCustomer(const AlchoholicCustomer& Other);
	AlchoholicCustomer(AlchoholicCustomer&& Other);
	virtual ~AlchoholicCustomer();
	//AlchoholicCustomer* operator=(const AlchoholicCustomer& other);
	//AlchoholicCustomer* operator=(AlchoholicCustomer&& other);
	vector<int> order(const vector<Dish> &menu);
	string toString() const;
	virtual Customer* clone() const;
private:
	bool sorted;

	void sortOrders(const vector<Dish> &menu);
	bool wayToSort(Dish& d1, Dish& d2) const;
};


#endif