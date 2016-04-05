
#ifndef __244_ITEM__
#define __244_ITEM__
#include "general.h"

// header file includes
#include <iostream>
#include <fstream>
#include <cstring>
#include "Streamable.h"

namespace oop244{

  class Item : public Streamable {

  private:
		char _upc[MAX_UPC_LEN+1];
		char* _name;
		double _price;
		bool _taxed;
		int _quantity;
		int _qtyNeeded;

  public:
    // constructors
        Item();
		Item(const char*,const char*,double,int,bool Taxed = true);
		Item(const Item& src);

    // destructor
		~Item();

    // setters
		void upc(const char*);
		void price(double);
		void name(const char*);
		void taxed(bool);
		void quantity(int);
		void qtyNeeded(int);

    // getters
		const char* upc() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;
		double cost() const;

    // operators
		Item& operator=(const Item &src);
		bool operator==(const char*);
		int operator+=(int);

  };
  // Non-member operator overload prototype
  double operator+=(double& d, const Item& I);
}


#endif
