#ifndef __244__Streamable__
#define __244__Streamable__
// hearfile includes:
#include <iostream>
#include <fstream>

namespace oop244{
  class Streamable{
  public:
    // pure virutal methods:
	virtual std::fstream& store(std::fstream&) const = 0;
	virtual std::fstream& load(std::fstream&) = 0;
	virtual std::ostream& display(std::ostream&, bool linear)const = 0;
	virtual std::istream& conInput(std::istream&) = 0;

    // virutal destructor:
    virtual ~Streamable(){}
  };
  // Non-memenber operator overoad prototypes for cin and cout:
	std::ostream& operator<<(std::ostream&,const Streamable&);
	std::istream& operator>>(std::istream&, Streamable&);

}
#endif


