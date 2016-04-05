#include "Streamable.h"
#include <iostream>
namespace oop244{

  // Non-memenber operator overoad implementation for cin and cout:
	std::ostream& operator<<(std::ostream& os ,const Streamable& S){
		S.display(os,true);
		return os;
	}

	std::istream& operator>>(std::istream& is, Streamable& S){
		S.conInput(is);
		return is;
	}
}
