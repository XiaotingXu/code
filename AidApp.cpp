#include <cstring>
#include <new>
#include <iomanip>
#include "AidApp.h"
#include <cstdlib>

using namespace std;

namespace oop244{

	// copy constructor and assignment operator

	AidApp::AidApp(const AidApp& a){}

	AidApp& AidApp::operator=(const AidApp& a){
		return *this;
	}

	// constructor
	// copies filename to _filename
	// sets all the _items to null
	// sets _noOfItems to null
	// loads the Records
	AidApp::AidApp(const char* filename){
		strcpy(_filename, filename);
		for(int i = 0; i < MAX_NO_RECS; i++){
			_items[i] = nullptr;
		}
		_noOfItems = 0;
		loadRecs();
	}

	// Menu() displays the menu as follows and waits for the user to
	// select an option.
	// if the selection is valid, it will return the selection
	// if not it will return -1
	// this funtion makes sure there is no characters left in keyboard
	// and wipes it before exit.

	int AidApp::menu(){
		int selection;
		cout << "Disaster Aid Supply Management Program" << '\n';
		cout << "1 - List Items" << '\n';
		cout << "2 - Add Non-food item Item" << '\n';
		cout << "3 - Add Perishable item" << '\n';
		cout << "4 - Update item quantity" << '\n';
		cout << "0 - Exit program\n>";
		cin >> selection;
		cin.ignore(2000,'\n');
		if (selection < 0 || selection > 4){
			return -1;
		}
		else
			return selection;
	}

  // lists all the items in linear format on the screen

	void AidApp::listItems()const{
		double total;
		cout << " Row | UPC    | Item Name          | Cost  | QTY|Need| Unit     | Expiry" << '\n' << "-----|--------|--------------------|-------|----|----|----------|----------" << endl;
		for(int i = 0; i < _noOfItems; i++){
			cout <<  setw(4) <<  right << i+1 << " | " << *_items[i] << endl;
			total += *_items[i];
		}
		cout << "---------------------------------------------------------------------------" << '\n' << "Total cost of support: $" << fixed << setprecision(2) << total << endl;
	}

	// opens the file for writing
	// stores the items in the file
	// closes the file

	void AidApp::saveRecs(){
		datafile.open(_filename, ios::in| ios::out| ios::trunc);
		if(datafile.is_open()){
			for(int i = 0; i < _noOfItems; i++){
				_items[i]->store(datafile);
			}
		}
		else
			cout << "File is not open." <<  endl;
		datafile.close();
	}

	// Opens the file for reading, if it does not exist, it will create an
	// empty file and exits otherwise :
	// Loads Records from the file overwriting the old ones pointed by item.
	// This function makes sure when loading records into _item pointers, they
	// are deallocated before if they are already pointing to an item
	// closes the file

	void AidApp::loadRecs(){

		int readIndex = 0;
		char id;
		char buf;
		_items[0] = nullptr;
		datafile.open(_filename);
		if( datafile.fail()){
			datafile.clear();
			datafile.close();
			datafile.open(_filename,ios::out);
			datafile.close();
		}
		else{
			while(!datafile.eof()){
				if(_items[readIndex] != nullptr){
					delete _items[readIndex];
					_items[readIndex] = nullptr;
				}
				datafile >> id;
				datafile >> buf;
				if( id == 'P'){	
					Perishable* temp;
					temp = new Perishable;					
					temp->load(datafile);				
					_items[readIndex] = temp;					
					readIndex++;
				}
				else if( id == 'N'){		
					NFI* temp;
					temp = new NFI;
					temp -> load(datafile);
					_items[readIndex] = temp;
					readIndex++;
				}
			}		
			readIndex--; 
			datafile.close();
			_noOfItems = readIndex;		
		}
	}


	// Searchers for the item in the _items array with the same UPC.
	// if found, it will display the item in non-linear format and then
	// asks for the value of the items purchased, and if the value does not exceed
	// the number needed to fulfill the requirement, it will update the quantity onhand
	// value of the found record and then saves all the records to the file, overwriting
	// the old values

	void AidApp::updateQty(const char* UPC){
		int no;
		int index = SearchItems(UPC);
		if(index == -1)
			cout << "Not found!" <<  endl;
		else{
			_items[index]->display( cout,false); 
			cout << "\nPlease enter the number of purchased items: ";
			cin >> no;
			while( cin.fail()){
				cout << "Invalid Quantity value!" <<  endl;
				cin >> no;
			}		
			int qtyShort = _items[index]->qtyNeeded() - _items[index]->quantity();
			if(no <= qtyShort)
				*_items[index] += no; 
			else{
				int qtyNeeded = _items[index]->qtyNeeded();
				int quantityOH = _items[index]->quantity();
				_items[index]->quantity(qtyNeeded);
				cout << "Too much items, only " << qtyShort << " is needed, please return the extra " << no - qtyShort << " items" <<  endl;
			}
			saveRecs();
			cout << "Updated!" <<  endl;
		}
	}

	// searches for an item in the _items array for the same upc
	// if found it will return the index of the found item in _items
	// otherwise returns -1

	int AidApp::SearchItems(const char* upc) const{
		for (int i = 0; i < _noOfItems; i++){
			if(*_items[i] == upc){
				return i;
			}
		}
		return -1;
	}

	// creates a new item (NFI or Perishable) based on the argument
	// recieved dynamically, asks the user to fill in the values
	// if the user fills the values with no mistake, it will open the file
	// for writing, and then stores the item in the file.
	// and print a proper message.
	// if the user makes a mistake (cin fails) it will only display the item
	// to show the error.
	// in any way it will delete the item before exiting the function

	void AidApp::addItem(bool isPerishable){
		if(isPerishable){
			Perishable* temp;
			temp = new Perishable;
			temp -> conInput(std::cin);
			if(cin.fail()){
				temp -> display(std::cout, false);
				cin.ignore(2000,'\n');
				cin.clear();
			}
			else{
				_items[_noOfItems] = temp;
				datafile.open(_filename, ios::in| ios::out| ios::app);
				_items[_noOfItems]->store(datafile);
				_noOfItems++;
				datafile.close();
				saveRecs();
			}
		}
		else{
			NFI* temp;
			temp = new NFI();
			temp -> conInput(std::cin);
			if(cin.fail()){
				temp -> display(std::cout, false);
				cin.ignore(2000,'\n');
				cin.clear();
			}
			else{
				_items[_noOfItems] = temp;
				datafile.open(_filename, ios::in| ios::out| ios::app);
				_items[_noOfItems]->store(datafile);
				_noOfItems++;
				datafile.close();
				saveRecs();
			}
		}
	}
	
	// diplays the menu and receives the user selection
	// if valid, it will preform the action requsted:
	// 1, lists the items in the file on the screen
	// 2 and 3, adds the item and then re-loads the records
	//     from the file into the AidApp
	// 4, gets a UPC and then updates the quantity of it
	// 0, exits the program.

	int AidApp::run(){
		int selection;
		char UPC[MAX_UPC_LEN + 1];
		selection = menu();
		do{
			while(selection == -1){
				cout << "===Invalid Selection, try again.===" << endl;
				selection = menu();
			}
			switch (selection){
				case 1 : 
					listItems();break; 
				case 2 : 
					addItem(false);cin.ignore(2000,'\n');break;
				case 3 : 
					addItem(true);cin.ignore(2000,'\n');break;
				default :
					cout << "Please enter the UPC: ";
					cin >> UPC;
					cin.ignore(2000,'\n');
					updateQty(UPC);
					break;
			}
			
			selection = menu();
		} while(selection);
			cout << "Good Bye!" << endl;
		return 0;
	}
}
	
