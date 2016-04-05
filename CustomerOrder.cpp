#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Utilities.h"
#include "Item.h"
#include "ItemOrder.h"
#include "CustomerOrder.h"

int MAX_ORDER_NUM = 10;
char CustomerOrder::delimiter;
size_t CustomerOrder::field_width;

CustomerOrder::CustomerOrder(const std::string& record){
	nOrders = 0;
	order = nullptr;
	std::string record_remain = record;
	record_remain.erase(0,record_remain.find_first_not_of(' ')); //trim the leading whitespaces
	record_remain.erase(record_remain.find_last_not_of(' ') + 1); //trim the trailing whitespaces
	Utilities utility;
	size_t next_pos = 0;
	bool more = true;
	std::string cust_order[MAX_ORDER_NUM];
	std::string msg;
	int i = 0;
	if(record!=""){
		while(i< MAX_ORDER_NUM && !record_remain.empty()){
			record_remain =  utility.Utilities::nextToken(record_remain, next_pos, more);
			cust_order[i] = record_remain.substr(0,next_pos);
			cust_order[i].erase(0,cust_order[i].find_first_not_of(' ')); //trim the leading whitespaces
			cust_order[i].erase(cust_order[i].find_last_not_of(' ') + 1); //trim the trailing whitespaces
			i++;
		}
		i = i-1; // for the last i++
		if(cust_order[0] == ""){
			msg = record + " <-- *** no token found before the delimiter ***";
			throw msg;
		}
		else if(cust_order[1] == ""){
			msg = record + "<-- *** no customer name found ***";
			throw msg;
		}
		else if(cust_order[2] == ""){
			msg = record + "<-- *** no product name found ***";
			throw msg;
		}
		else if(cust_order[3] == ""){
			msg = record + "<-- *** no item ordered ***";
			throw msg;
		}
		else{
			name = cust_order[0];
			product = cust_order[1];
			nOrders = i - 2;
			order = new ItemOrder[nOrders];
			for(int j=0; j < nOrders; j++){
				std::string str = cust_order[j+2];
				order[j]= ItemOrder(str);
			}
			if(field_width < utility.Utilities::getFieldWidth())
				field_width = utility.Utilities::getFieldWidth(); 
		}
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& src){
	std::string msg = "Cannot call copy constructor because duplicate customer orders are forbid.";
	throw msg;
}

CustomerOrder::CustomerOrder(CustomerOrder&& src){
	name = src.name;
	product = src.product;
	nOrders = src.nOrders;
	order = src.order;
	src.order = nullptr;
	src.nOrders = 0;
}

CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& src){
	if(this != &src){
		name = src.name;
		product = src.product;
		nOrders = src.nOrders;
		order = src.order;
		src.order = nullptr;
		src.nOrders = 0;
	}
	return std::move(*this);
}

CustomerOrder::~CustomerOrder(){
	delete [] order;
}

unsigned int CustomerOrder::noOrders() const{
	return nOrders;
}

const std::string& CustomerOrder::operator[](unsigned int i) const{
		std::string msg = "*** Error! This customer only has " + std::to_string(nOrders) + " orders. ***";
		if(i < nOrders){
			return order[i].getName();
		}
		else 
			throw msg;
}

void CustomerOrder::fill(Item& item){
	for(unsigned i = 0; i < nOrders; i++){
		if(item.getName() == order[i].getName()){
			order[i].fill(item.getCode());
			item++;
		}
	}
}

void CustomerOrder::remove(Item& item){
	for(unsigned i = 0; i < nOrders; i++){
		if(item.getName() == order[i].getName() && order[i].isFilled()){
			order[i].clear();
		}
	}
}

bool CustomerOrder::empty() const{
	if(!nOrders && !order) // if the current object is in safe empty state
		return true;
	else
		return false;
}

void CustomerOrder::display(std::ostream& os) const{
	os << std::left << std::setw(field_width) << name << ": " << std::setw(field_width) << product << std::endl;
	for(unsigned i = 0; i < nOrders; i++){
		order[i].display(os);
	}
}

void CustomerOrder::setDelimiter(const char c){
	delimiter = c;
}
