#include <iostream>
#include <vector>
#include "ItemManager.h"
#include "Item.h"

void ItemManager::push_back(Item&& src){
	items.push_back(std::move(src));
}

std::vector<Item>::iterator ItemManager::begin(){
	return items.begin();
}

std::vector<Item>::iterator ItemManager::end(){
	return items.end();
}

const std::vector<Item>::const_iterator ItemManager::cbegin() const{
	return items.cbegin();
}

const std::vector<Item>::const_iterator ItemManager::cend() const{
	return items.cend();
}

void ItemManager::display(std::ostream& os, bool full) const{
	for(auto it = items.begin(); it != items.end(); ++it){
		it->display(os, full);
	}
}