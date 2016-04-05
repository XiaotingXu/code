#include <iostream>
#include <string>
#include <iomanip>
#include "Item.h"
#include "ItemOrder.h"

ItemOrder::ItemOrder(const std::string& _name){
	filled = false;
	code = 0;
	if(_name != "")
		name = _name;
}

bool ItemOrder::asksFor(const Item& item) const{
	if(item.empty())
		return false;
	else
		return true;
}

bool ItemOrder::isFilled() const{
	if(filled)
		return true;
	else
		return false;
}

void ItemOrder::fill(const unsigned int c){
	code = c;
	filled = true;
}

void ItemOrder::clear(){
	filled = false;
	code = 0;
}

const std::string& ItemOrder::getName() const{
	return name;
}

void ItemOrder::display(std::ostream& os) const{
	size_t CODE_WIDTH = 5;
	if(!filled)
		os << " - ";
	else
		os << " + ";
	os << "[" << std::right << std::setfill('0') << std::setw(CODE_WIDTH) << code << std::setfill(' ') << "] " << name << std::endl;
}