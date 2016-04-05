#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include "Task.h"
#include "Utilities.h"

char Task::delimiter;
size_t Task::field_width;

Task::Task(const std::string& record){
	slots = "1";
	pNextTask[0] = pNextTask[1] = nullptr;
	std::string record_remain = record;
	record_remain.erase(0,record_remain.find_first_not_of(' ')); //trim the leading whitespaces
	record_remain.erase(record_remain.find_last_not_of(' ') + 1); //trim the trailing whitespaces
	size_t next_pos = 0;
	std::string task[4];
	Utilities utility;
	unsigned i = 0;
	bool more = true;
	std::string msg;
	while(i < 4 && !record_remain.empty()){
		record_remain = utility.Utilities::nextToken(record_remain, next_pos, more);	
		task[i] = record_remain.substr(0,next_pos);
		task[i].erase(0,task[i].find_first_not_of(' ')); //trim the leading whitespaces
		task[i].erase(task[i].find_last_not_of(' ') + 1); //trim the trailing whitespaces
		i++;
	}
	if(task[0]==""){
		msg = record + " <-- *** no token found before the delimiter ***";
		throw msg;
	}
	else{
		name = task[0];
		if(task[1] != ""){	
			slots = task[1];
			if(task[2] != ""){
				nextTask[0] = task[2];
					if(task[3] != "")
						nextTask[1] = task[3];
			}
		}
		if(field_width < utility.Utilities::getFieldWidth())
			field_width = utility.Utilities::getFieldWidth() + 2;  //2 is for "[]"
	}
}

const std::string& Task::getName() const{
	return name;
}

unsigned int Task::getSlots() const{
	return atoi(slots.c_str());
}
bool Task::validate(const Task& task){
	bool valid = false;
	if(*this == task){
		return valid;
	}
	if(nextTask[0] == task.getName()){
		pNextTask[0] = &task;
	}
	if(nextTask[1] == task.getName()){
		pNextTask[1] = &task;
	}
	if(nextTask[0] != "" && nextTask[1] != "" && pNextTask[0] && pNextTask[1])
		valid = true;
	if(nextTask[0] != "" && nextTask[1] == "" && pNextTask[0])
		valid = true;
	if(nextTask[0] == "" && nextTask[1] != "" && pNextTask[1])
		valid = true;
	if(nextTask[0] == "" && nextTask[1] == "" && !pNextTask[0] && !pNextTask[1])
		valid = true;
	return valid;
}

const Task* Task::getNextTask(Quality quality) const{
	std::string msg;
	if(quality == passed){
		if(pNextTask[0])
			return pNextTask[0];
		else{
			msg = "Validate [" + nextTask[0] + "] @ [" + name + "]***";
			throw msg;
		}
	}
	else{ 
		if(pNextTask[1])
			return pNextTask[1];
		else{
			msg = "Validate [" + nextTask[1] + "] @ [" + name + "]***";
			throw msg;
		}
	}
}

void Task::display(std::ostream& os) const{
	std::string _name = "[" + name + "]";
	std::string _slots = "[" + slots + "]";
	if(!name.empty()){
		os << "Task Name    : " << std::left << std::setw(field_width) << _name << " " << _slots << std::right << std::endl;
		if(!nextTask[0].empty()){
			if(!pNextTask[0]){
				std::string _continue = "[" + nextTask[0] + "]";
				os << " Continue to : " << std::left <<std::setw(field_width) << _continue << std::right<< " ***to be validated***" << std::endl;			
			}
			else{
				std::string _continue = "[" +getNextTask(passed)->name + "]";
				os << " Continue to : " << std::left << std::setw(field_width) << _continue << std::endl;
			}
		}
		if(!nextTask[1].empty()){
			if(!pNextTask[1]){
				std::string _redirect = "[" + nextTask[1] + "]";
				os << " Redirect to : " << std::left << std::setw(field_width) << _redirect << std::right << " ***to be validated***" << std::endl;
			}
			else{
				std::string _redirect = "[" + getNextTask(redirect)->name + "]";
				os << " Redirect to : " << std::left << std::setw(field_width) << _redirect << std::endl;
			}
		}
	}
}

void Task::setDelimiter(const char c){
	delimiter = c;
}

size_t Task::getFieldWidth(){
	return field_width;
}

 bool operator==(const Task& t1, const Task& t2){
	 if(t1.getName() == t2.getName() )
		 return true;
	 else
		 return false;
 }
