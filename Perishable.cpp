
// includes go here
#include <iostream>
#include <fstream>
#include "Perishable.h"
#include <iomanip>

namespace oop244{
  // constructor
	Perishable::Perishable(){
		qtyNeeded(1);
		taxed(false);
		_unit[0] = '\0';
	}

  // Setters and getters
	const Date& Perishable::expiry() const{
		return _expiry;
	}

	void Perishable::expiry(const Date& value){
		_expiry = value;
	}

	const char* Perishable::unit() const{
		return _unit;
	}

	void Perishable::unit(const char* value){
		strncpy(_unit,value,11);
	}

  // fstream& Perishable::store(fstream& file)const
	std::fstream& Perishable::store(std::fstream& file)const{
		if (!file.is_open()) {
			std::cerr << "File is not open" << std::endl;
		}
		else{
			file << "P," << upc() << "," << name()<< ","  << price() << ","  << unit() << ","<< quantity() << ","<< qtyNeeded() << ","<< expiry()<< std::endl;
		}
		return file;
	}
  //fstream& Perishable::load(fstream& file)
    std::fstream& Perishable::load(std::fstream& file){
        char upc_[MAX_UPC_LEN + 1];
        char name_[21];
        char unit[11];
        double price_;
        int quantity_;
        int qtyNeeded_;
        char comma;
		int year,month,day;
        if(file.is_open() && file.good()){
                file.getline(upc_,MAX_UPC_LEN + 1,',');
                file.getline(name_,21,',');
				file >> price_;
				file.ignore();
                file.getline(unit,11,',');
				file >> quantity_ ;
				file.ignore();
				file >> qtyNeeded_ ;
				file.ignore();
                file >> year >> comma >> month >> comma >> day;
				file.ignore(2000,'\n');
        }

        upc(upc_);
        name(name_);
        price(price_);
        quantity(quantity_);
        qtyNeeded(qtyNeeded_);
        strncpy(_unit,unit,11);
		Date expiry(year,month,day);
		_expiry=expiry;
        return file;
}
  //ostream& Perishable::display(ostream& os, bool linear)const
    std::ostream& Perishable::display(std::ostream& ostr, bool linear)const{
        if(!_err.isClear())
            return ostr << _err.message();
        else{
            if(linear){
                ostr << std::setw(MAX_UPC_LEN) << std::left << upc() << "|" << std::setw(20) << std::left << name() << "|" << std::fixed << std::right << std::setw(7) << std::setprecision(2) << cost() << "|";
                ostr << std::right << std::setw(4) << quantity() << "|" << std::right << std::setw(4) << qtyNeeded() << "|" << std::left << std::setw(10) << _unit << "|" << _expiry;
            }
            else
                ostr << "Upc:" << upc() << std::endl << "Name:" << name() << std::endl << "Price:" << price() << std::endl << "Price after tax:" << cost() << std::endl << "Quantity On Hand: " << quantity() << std::endl << "Quantity Needed: " << qtyNeeded() << std::endl << "Unit: " << _unit << std::endl << "Expiry date: " << _expiry <<std::endl;
        }

        return ostr;
    }
  // istream& Perishable::conInput(istream& is)
    std::istream& Perishable::conInput(std::istream& istr){
    char upc_[MAX_UPC_LEN + 1];
    char name_[21];
    double price_;
    int quantity_;
    int qtyNeeded_;
	char unit[11];
	int invalid=0;
	Date expiry_;
	_err.clear();
	istr.clear();
	std::cout << "Perishable Item Entry:" << std::endl << "Upc: ";
	istr >> upc_;
	istr.ignore(2000,'\n');
    std::cout << "Name: ";
    istr >> name_;
	istr.ignore(2000,'\n');
    std::cout << "Price: ";
    istr >> price_;
	if(istr.fail()){
        _err.message("Invalid Price Entry");
        istr.ignore(2000,'\n');
		invalid++;
    }
	else{
	    std::cout << "Quantity On Hand: ";
    	istr >> quantity_;
    	if(istr.fail()){
        	_err.message("Invalid Quantity Entry");
        	istr.ignore(2000,'\n');
			invalid++;
    	}
		else{
    		std::cout << "Quantity Needed: ";
    		istr >> qtyNeeded_;
	   		if(istr.fail()){
        		_err.message("Invalid Quantity Needed Entry");
        		istr.ignore(2000,'\n');
				invalid++;
    		}
			else{
				std::cout << "Unit: ";
				istr >> unit;
				istr.ignore(2000,'\n');	
				std::cout << "Expiry date (YYYY/MM/DD) : ";
				istr >> expiry_;
				istr.ignore(2000,'\n');	
				if(expiry_.bad()){
					invalid++;
					istr.setstate(std::ios::failbit);
				}
				if(expiry_.errCode() == 1)
					_err.message("Invalid Date Entry");
				else if(expiry_.errCode() == 2)
						_err.message("Invalid Year in Date Entry");
					else if(expiry_.errCode() == 3)
							_err.message("Invalid Month in Date Entry");
							else if(expiry_.errCode() == 4)
								_err.message("Invalid Day in Date Entry");
								else {
									_expiry = expiry_;
								}
				}
		}
	}
	if(!invalid){
		upc(upc_);
        name(name_);
        price(price_);
        quantity(quantity_);
        qtyNeeded(qtyNeeded_);
		strncpy(_unit,unit,11);
		
	}
	return istr;
    }
}

