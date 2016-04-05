#ifndef __244_NFI_H__
#define __244_NFI_H__

// includes go here
#include "Item.h"
#include "general.h"
#include "ErrorMessage.h"

namespace oop244{
  class NFI : public Item{
  private:
    ErrorMessage _err;
  public:
    // default constructor
	NFI();
    // pure virutal method implementation prototypes
	std::fstream& store(std::fstream&) const;
	std::fstream& load(std::fstream&);
    std::ostream& display(std::ostream&, bool) const;
    std::istream& conInput(std::istream&);
  };
}
#endif
