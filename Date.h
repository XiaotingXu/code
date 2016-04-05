#ifndef __244_DATE_H__
#define __244_DATE_H__
// header file includes
#include <iostream>

namespace oop244{
	// Error code values gos here
	#define NO_ERROR   0  //No error the date is valid
	#define CIN_FAILED 1  //istream failed when entering information
	#define YEAR_ERROR 2  //Year value is invalid
	#define MON_ERROR  3  //Month value is invalid
	#define DAY_ERROR  4  //Day value is invalid
	
	class Date{
		
		private:
		// private member variables
		int _year;
		int _mon;
		int _day;
		int _readErrorCode;
		// privaet memeber functions and setters
		int value()const;
		void errCode(int errorCode);
		
		public:
		// constructors
		Date();
		Date(int,int,int);
		// operator overloads	
		bool operator==(const Date& D)const;
		bool operator!=(const Date& D)const;
		bool operator<(const Date& D)const;
		bool operator>(const Date& D)const;
		bool operator<=(const Date& D)const;
		bool operator>=(const Date& D)const;
		// IO member funcions
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		// public member fucntions and getters
		int errCode()const;
		bool bad()const;
		int mdays()const;
		void validate();
	
	};
	// operator << and >> overloads prototypes for ostream and istream go here
	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&,const Date&);
}
#endif
