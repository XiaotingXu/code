#include "Date.h"
#include "general.h"
#include <iomanip>
#include <iostream>
using namespace std;

namespace oop244{

	// returns a uniqe value out of date
	// this value is used to compare two dates
	int Date::value()const{
		return _year * 372 + _mon * 31 + _day;
	}
	
	// validate(), this is an optional private function to write
	// for validation logic and setting the _readErrorCode.
	// see the read() funciton description for more detail
	void Date::validate(){
		if(_year <= MAX_YEAR && _year>=MIN_YEAR){
			if( _mon >= 1 && _mon <= 12 ){
				if(_day <= mdays() && _day >=0){
					errCode(NO_ERROR);
				}
				else{
					errCode(DAY_ERROR);			
				}
			}
			else{
				errCode(MON_ERROR);
			}
		}
		else{
			errCode(YEAR_ERROR);
		}
	}

	// mday():
	// returns the day of the month.
	// _mon value must be set for this to work
	// if _mon is invalid, this function returns -1
	// leap years are considered in this logic
	int Date::mdays()const{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
	}
	
	// constructors
	Date::Date(){
		_year=0;
		_mon=0;
		_day=0;
		errCode(NO_ERROR);
	}
		
	Date::Date(int y,int m,int d){
		_year=y;
		_mon=m;
		_day=d;
		errCode(NO_ERROR);
	}
	
	// member fucntions
	void Date::errCode(int errorCode){
		switch(errorCode){
			case 1:
				_readErrorCode=1;
				break;
			case 2:
				_readErrorCode=2;
				break;
			case 3:
				_readErrorCode=3;
				break;
			case 4:
				_readErrorCode=4;
				break;
			default:
				_readErrorCode=0;
		}
	}
	
	int Date::errCode()const{
		return _readErrorCode;
	}

	bool Date::bad()const{
		if (_readErrorCode!=0){
			return true;
		}
		else{
			return false;
		}
	}

	// operators
	bool Date::operator==(const Date& D)const{
	if (value()==D.value()){
		return true;
	}
	else{
		return false;
	}
}

	bool Date::operator!=(const Date& D)const{
		if (value()!=D.value()){
			return true;
		}
		else{
			return false;
		}
	}

	bool Date::operator<(const Date& D)const{
		if (value()<D.value()){
			return true;
		}
		else{
			return false;
		}
	}

	bool Date::operator>(const Date& D)const{
		if (value()>D.value()){
			return true;
		}
		else{
			return false;
		}
	}

	bool Date::operator<=(const Date& D)const{
		if (value()<=D.value()){
			return true;
		}
		else{
			return false;
		}
	}

	bool Date::operator>=(const Date& D)const{
		if (value()>=D.value()){
			return true;
		}
		else{
			return false;
		}
	}

	// IO funtions
	std::istream& Date::read(std::istream& istr){	
		char a;
		
		istr >> _year >> a >> _mon >> a >> _day;
		validate();
		
		if(istr.fail()){
			errCode(CIN_FAILED);
		}
		
		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr)const{
		ostr << _year << "/" << _mon << "/" << _day ;
		return ostr;
	}

	// non-memeber operator overloads
	std::istream& operator>>(std::istream& istr, Date& D){
		D.read(istr);
		return istr;
	}

	std::ostream& operator<<(std::ostream& ostr,const Date& D){
		D.write(ostr);
		return ostr;
	}
}
