#include <iostream>
#include <string>
#include <algorithm>
#include "OrderManager.h"
#include "ItemManager.h"
#include "CustomerOrder.h"
#include "Item.h"


void OrderManager::push_back(CustomerOrder&& src){
	customerOrders.push_back(std::move(src) );
}

CustomerOrder&& OrderManager::extract(){
	return std::move(customerOrders.back());
}

void OrderManager::pop(){
	customerOrders.pop_back();
}

bool OrderManager::empty() const{
	if(customerOrders.empty())
		return true;
	else
		return false;
}

std::vector<CustomerOrder>::iterator OrderManager::begin(){
	return customerOrders.begin();
}

std::vector<CustomerOrder>::iterator OrderManager::end(){
	return customerOrders.end();
}

const std::vector<CustomerOrder>::const_iterator OrderManager::cbegin() const{
	return customerOrders.cbegin();
}

const std::vector<CustomerOrder>::const_iterator OrderManager::cend() const{
	return customerOrders.cend();
}

void OrderManager::display(std::ostream& os) const{
	for(auto it = customerOrders.cbegin(); it != customerOrders.cend(); ++it){
		it->display(os);
	}
}

void validate(const OrderManager& order, const ItemManager& item, std::ostream& os){
	//bool found = false;
	for(auto it_order = order.cbegin(); it_order != order.cend(); ++it_order){
		for(auto i = 0; i < it_order->noOrders(); ++i){
			if(std::find_if(item.cbegin(), item.cend(), [=](Item pItem)->bool{return (*it_order)[i] == pItem.getName();}) == item.cend())
				os << (*it_order)[i] << " is unavailable" << std::endl;	
				/*for(auto it_item = item.cbegin(); it_item != item.cend(); ++it_item){
				if((*it_order)[i] == it_item->getName())
					found = true;
				if(found)
					break;
			}
			if(!found)
				os << (*it_order)[i] << " is unavailable" << std::endl;
			else 
				found = false;*/
		}
	}
}
