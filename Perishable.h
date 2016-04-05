#ifndef __244_Perishable_H__
#define __244_Perishable_H__
// includes go here
#include "general.h"
#include "Item.h"
#include "ErrorMessage.h"
#include "Date.h"
#include <cstring>
#include <iostream>
#include <fstream>

namespace oop244{
  class Perishable : public Item{
  private:
    ErrorMessage _err;
    // expiry and unit go here
	char _unit[11];
	Date _expiry;
  public:
    // default constructor
	Perishable();
    // pure virutal method implementation prototypes
    std::fstream& store(std::fstream&) const;
    std::fstream& load(std::fstream&);
    std::ostream& display(std::ostream&, bool) const;
    std::istream& conInput(std::istream&);
    // Setters and Getters
	const Date& expiry() const;
	void expiry(const Date& value);
	const char* unit() const;
	void unit(const char* value);
  };
}


#endif

