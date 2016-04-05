 #pragma once
 // CustomerOrder Milestone - CustomerOrder Interface
 // CustomerOrder.h
 // Chris Szalwinski
 // v1.0 9/11/2015
 #include <iostream>
 #include <string>

 class Item;
 class ItemOrder;

 class CustomerOrder {
     std::string name;
     std::string product;
     ItemOrder* order;
     unsigned int nOrders;
     static char delimiter;
     static size_t field_width;
 public:
     CustomerOrder(const std::string&);
     CustomerOrder(const CustomerOrder&);
     CustomerOrder& operator=(const CustomerOrder&) = delete; 
     CustomerOrder(CustomerOrder&&);
     CustomerOrder&& operator=(CustomerOrder&&);
     ~CustomerOrder();
     unsigned int noOrders() const;
     const std::string& operator[](unsigned int i) const;
     void fill(Item&);
     void remove(Item&);
     bool empty() const;
     void display(std::ostream&) const;
     static void setDelimiter(const char);
 };
