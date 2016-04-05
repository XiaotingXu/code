#include <iostream>
#include <string>
#include <iomanip>
#include <iostream>
#include "Item.h"
#include "Utilities.h"

char Item::delimiter;
size_t Item::field_width;

Item::Item(const std::string& record){
	details = "no detailed description";
	code = 1;
	if(record!=""){
		Utilities utility;
		std::string item[5];
		unsigned i = 0;
		size_t next_pos = 0;
		bool more = true;
		std::string msg;
		std::string record_remain = record;
		record_remain.erase(0,record_remain.find_first_not_of(' ')); //trim the leading whitespaces
		record_remain.erase(record_remain.find_last_not_of(' ') + 1); //trim the trailing whitespaces
		while(i < 5 && record_remain != ""){
			record_remain = utility.Utilities::nextToken(record_remain, next_pos, more);			
			item[i] = record_remain.substr(0,next_pos);
			item[i].erase(0,item[i].find_first_not_of(' ')); //trim the leading whitespaces
			item[i].erase(item[i].find_last_not_of(' ') + 1); //trim the trailing whitespaces
			i++;
		}
		if(item[0] == ""){
			msg = record + " <-- *** no token found before the delimiter ***";
			throw msg;
		}
		else if(item[1] == ""){
			msg = record + " <-- *** no name of the source task found ***";
			throw msg;
		}
		else if(item[2] == ""){
			msg = record + " <-- *** no name of the destination task found ***";
			throw msg;			
		}
		else{ //The first three fields are required, and the fourth as well as the fifth is  optional.
			name = item[0];
			source = item[1];
			destination = item[2];
			if(item[3] != ""){
				code = atoi(item[3].c_str());
				if(item[4] != "")
					details = item[4];
			}
			if(field_width < utility.Utilities::getFieldWidth())
				field_width = utility.Utilities::getFieldWidth();
		}
	}
}

bool Item::empty() const{
		if(details == "no detailed description" && code == 1)  //safe empty state
			return true;
		else
			return false;
}

void Item::operator++(int){
	code++;
}

unsigned int Item::getCode() const{
	return code;
}

const std::string& Item::getName() const{
	return name;
}

const std::string& Item::getSource() const{
	return source;
}

const std::string& Item::getDestination() const{
	return destination;
}

void Item::display(std::ostream& os, bool full) const{
	size_t CODE_WIDTH = 5;
	os << std::left << std::setw(field_width) << name << "[" << std::right << std::setw(CODE_WIDTH) << std::setfill('0') << code << "] " << std::setfill(' ');
	if(full){
		os << "From " << std::left << std::setw(field_width) << source << " To " << destination  << '\n' << std::right << std::setfill(' ') << std::setw(field_width + CODE_WIDTH + 2) << ":" << " " << std::left << details;
	}
	os << std::endl;
}	

void Item::setDelimiter(const char c){
	delimiter = c;	
}

size_t Item::getFieldWidth(){
	return field_width;	
}