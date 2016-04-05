#include <string>
#include <algorithm>
#include "Utilities.h"

char Utilities::delimiter;
size_t Utilities::field_width;
 	
Utilities::Utilities(size_t minimum_field_width){
	field_width = minimum_field_width;
}

void Utilities::setFieldWidth(size_t fw){
	field_width = fw;
}

size_t Utilities::getFieldWidth() const{
	return field_width;
}

const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more){
	size_t fw;
	std::string str_tmp = str;
	std::string thisToken;
	thisToken = str_tmp.substr(0,next_pos);	//extract the current token
	thisToken.erase(0,thisToken.find_first_not_of(' ')); //trim the leading whitespaces
	thisToken.erase(thisToken.find_last_not_of(' ') + 1);	//trim the trailing whitesapces
	fw = thisToken.size();
	if(fw > field_width)
		field_width = fw;
	if(more){
		if(next_pos != 0)
			str_tmp = str_tmp.substr(next_pos+1); //cut the current token
		if(str_tmp.find_first_of(getDelimiter()) != std::string::npos){ //determine whether there are more tokens or not
			next_pos = str_tmp.find_first_of(getDelimiter());
			more = true;
		}
		else{
			next_pos = std::string::npos;
			more = false;
		}
	}
	else //after extracting last token
		str_tmp = "";
	return str_tmp;
}

void Utilities::setDelimiter(const char c){
	delimiter = c;
}

const char Utilities::getDelimiter(){
	return delimiter;
}