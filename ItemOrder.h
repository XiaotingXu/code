 #pragma once
 // CustomerOrder Milestone - ItemOrder Interface
 // ItemOrder.h
 // Chris Szalwinski
 // v1.0 - 9/11/2015
 #include <iostream>
 #include <string>

 class Item;

 class ItemOrder {
     std::string name;
     bool filled;
     unsigned int code;
 public:
     ItemOrder(const std::string& = std::string()); 
     bool asksFor(const Item&) const;
     bool isFilled() const;
     void fill(const unsigned int);
     void clear();
     const std::string& getName() const;
     void display(std::ostream&) const;
 };
