//includes go here
#include <iostream>
#include <fstream>
#include <iomanip>
#include "NFI.h"
#include "general.h"

namespace oop244{
  // constructor
	NFI::NFI(){
		qtyNeeded(1);
		taxed(1);
	}

  // fstream& NFI::store(fstream& file)const
	std::fstream& NFI::store(std::fstream& file) const{
		if (file.is_open()){
			file << "N," << upc() << "," << name()<< ","  << price() << "," << quantity() << "," << qtyNeeded() << std::endl;
		}
		return file;
	}

  // fstream& NFI::load(fstream& file)
	std::fstream& NFI::load(std::fstream& file){
		char upc_[MAX_UPC_LEN+1];
		char name_[21];
		double price_;
		int quantity_;
		int qtyNeeded_;
		
		if(file.is_open() && file.good()){
			file.getline(upc_,MAX_UPC_LEN + 1, ',');
			file.getline(name_, 21, ',');  
			file >> price_;
			file.ignore(); 
			file >> quantity_;
			file.ignore();  
			file >> qtyNeeded_;
		}
		upc(upc_);
		name(name_);
		price(price_);
		quantity(quantity_);
		qtyNeeded(qtyNeeded_);
		return file;  
	}

  // ostream& NFI::display(ostream& ostr, bool linear)const
	std::ostream& NFI::display(std::ostream& ostr, bool linear) const{
		if(!_err.isClear()){
			return ostr << _err.message();
		}
		else{
			if(linear){
				ostr << std::setw(MAX_UPC_LEN) << std::left << upc() << "|" << std::setw(20) << std::left << name() << "|" << std::fixed << std::right << std::setw(7) << std::setprecision(2) << cost() << "|" << std::right << std::setw(4) << quantity() << "|" << std::right << std::setw(4) << qtyNeeded();
			}
			else{
				ostr << "Upc: " << upc() << '\n' << "Name: " << name() << '\n' << "Price: " << price() << '\n' << "Price after tax: " << cost() << '\n' << "Quantity On Hand: " << quantity() << '\n' << "Quantity Needed: " << qtyNeeded() << std::endl;
			}
		}
		return ostr;
	}

  // istream& NFI::conInput(istream& istr)
	 std::istream& NFI::conInput(std::istream& istr){
		char upc_[MAX_UPC_LEN+1];
		char name_[21];
		double price_;
		int quantity_;
		int qtyNeeded_;
		int invalid=0;

		_err.clear();
		istr.clear();

		std::cout << "Non-Food Item Entry:" << '\n' << "Upc: ";
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
			}
		}

		if(!invalid){
			upc(upc_);
			name(name_);
			price(price_);
			quantity(quantity_);
			qtyNeeded(qtyNeeded_);
		}

		return istr;
	 }
}
