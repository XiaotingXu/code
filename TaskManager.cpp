#include <iostream>
#include <vector>
#include <algorithm>
#include "Task.h"
#include "ItemManager.h"
#include "TaskManager.h"
#include "Utilities.h"
#include "Item.h"


void TaskManager::push_back(Task&& src){
	tasks.push_back(std::move(src));
}

std::vector<Task>::iterator TaskManager::begin(){
	return tasks.begin();
}

std::vector<Task>::iterator TaskManager::end(){
	return tasks.end();
}

const std::vector<Task>::const_iterator TaskManager::cbegin() const{
	return tasks.cbegin();
}

const std::vector<Task>::const_iterator TaskManager::cend() const{
	return tasks.cend();
}

void TaskManager::validate(std::ostream& os){
	bool valid = true;
	for(auto i = 0; i < tasks.size() && valid; ++i){
		bool invalid = true;
		for(auto j = 0; j < tasks.size() && invalid; ++j){
			 if (tasks[i].validate(tasks[j]))
                invalid = false;
		}
		valid = !invalid;
	}
	if(!valid)
       std::cerr << "*** Not all Tasks have been validated ***\n";
}

void TaskManager::display(std::ostream& os) const{
	for(auto it = tasks.begin(); it != tasks.end(); ++it){
		it->display(os);
	}
}

void validate(const TaskManager& task, const ItemManager& item, std::ostream& os){
	bool source_found = false;
	bool destination_found = false;
	for(auto it_item = item.cbegin(); it_item != item.cend(); ++it_item){
		for(auto it_task = task.cbegin(); it_task != task.cend() && !source_found && !destination_found; ++ it_task){
			if(it_task->getName() == it_item->getSource())
				source_found = true;
			if(it_task->getName() == it_item->getDestination())
				destination_found = true;
		}
		if(!source_found){
			os << it_item->getSource() << " is unavailable" << std::endl;
		}
		else
			source_found = false;
		if(!destination_found){
			os << it_item->getDestination() << " is unavailable" << std::endl;
		}
		else
			destination_found = false;
	}
	
}