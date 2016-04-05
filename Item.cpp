
// header file includes
#include "Item.h"
#include <cstring>
namespace oop244{

  // constructors
    Item::Item(){
        _upc[0]='\0';
        _name=nullptr;
        _price=0;
        _quantity=0;
        _qtyNeeded=0;
        _taxed=true;
    }

	Item::Item(const char* upc,const char* name,double price,int qtyNeeded,bool taxed){
        strncpy(_upc,upc,MAX_UPC_LEN+1);
		_name = new char[strlen(name)+1];
		strcpy(_name,name);
		_price = price;
		_quantity = 0;
		_qtyNeeded = qtyNeeded;
		_taxed = taxed;
	}


	Item::Item(const Item& src){
		upc(src._upc);
		if(src._name != nullptr){
			_name = new char[strlen(src._name)+1];
			name(src._name);
		}
		else{
			_name=nullptr;
		}
		price(src._price);
		qtyNeeded(src._qtyNeeded);
		taxed(src._taxed);
        quantity(0);
	}

  // operator=
	Item& Item::operator=(const Item& src){
	    if(this != &src){
            upc(src._upc);
            name(src._name);
            price(src._price);
            qtyNeeded(src._qtyNeeded);
            taxed(src._taxed);
            quantity(0);

	    }
		return *this;
	}



  // setters
	void Item::upc(const char* upc){
        strncpy(_upc,upc,MAX_UPC_LEN+1);
	}

	void Item::price(double price){
		_price = price;
	}

	void Item::name(const char* name){
		delete [] _name;
		if(name !=  nullptr){
			_name = new char[strlen(name)+1];
			strcpy(_name,name);
		}
		else{
			_name=nullptr;
		}
	}

	void Item::taxed(bool taxed){
		_taxed = taxed;
	}

	void Item::quantity(int quantity){
		_quantity = quantity;
	}

	void Item::qtyNeeded(int qtyNeeded){
		_qtyNeeded = qtyNeeded;
	}

  // getters
	const char* Item::upc() const{
		return _upc;
	}

	double Item::price() const{
		return _price;
	}

	const char* Item::name() const{
		return _name;
	}

	bool Item::taxed() const{
		return _taxed;
	}

	int Item::quantity() const{
		return _quantity;
	}

	int Item::qtyNeeded() const{
		return _qtyNeeded;
	}

	double Item::cost() const{
		if(_taxed){
			return _price*(1+TAX);
		}
		else{
			return _price;
		}
	}

  // member operator overloads
	bool Item::operator==(const char* upc){
		if(!strcmp(_upc,upc)){
			return true;
		}
		else{
			return false;
		}
	}

	int Item::operator+=(int quantity){
		_quantity += quantity;
		return _quantity;
	}

  // non-member operator overload
	 double operator+=(double& d, const Item& I){
		double cost=I.cost();
		int quantity=I.quantity();
		d += cost * quantity;
		return d;
	 }

  // destructor
	Item::~Item(){
		if(_name != nullptr){
			delete [] _name;
		}
		_name = nullptr;
	}
}
