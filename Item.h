 #pragma once
 // CustomerOrder Milestone - Item Interface
 // Item.h
 // Chris Szalwinski
 // v1.0 - 9/11/2015
 #include <iostream>
 #include <string>

 class Item {
     std::string name;
     std::string source;
     std::string destination;
     std::string details;
     unsigned int code;
     static char delimiter;
     static size_t field_width;
 public:
     Item(const std::string& = std::string());
     bool empty() const;
     void operator++(int);
     unsigned int getCode() const;
     const std::string& getName() const;
     const std::string& getSource() const;
     const std::string& getDestination() const;
     void display(std::ostream&, bool = false) const; 
     static void setDelimiter(const char);
     static size_t getFieldWidth();
 };