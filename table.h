#include <iostream>
#include <string>
#include <utility>
using namespace std;

template <class TYPE>
class Table{
public:
	Table(){}
	virtual bool update(const string& key, const TYPE& value)=0;
	virtual bool remove(const string& key)=0;
	virtual bool find(const string& key, TYPE& value)=0;
	virtual int numRecords() const=0;
	virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

	struct Record{
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data){
			key_ = key;
			data_ = data;
		}

	};

	Record** records_;   //the table
	int max_;           //capacity of the array
	int size_;          //current number of records held
	int search(const string& key);
	void sort();
	void grow();
public:
	SimpleTable(int maxExpected);
	SimpleTable(SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual int numRecords() const;
	virtual const SimpleTable& operator=(SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
};


//return the index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key){
	int rc = -1;
	int low = 0;
	int high = size_-1;
	int mid;
	while(rc == -1 && low <= high){
		mid = (low+high)/2;
		if(key < records_[mid]->key_)
			high = mid-1;
		else if(key > records_[mid]->key_)
			low = mid+1;
		else
			rc = mid;
	}
	return rc;
}

//sort the according to key in table
template <class TYPE>
void SimpleTable<TYPE>::sort(){ 
	if(size_ != 1){
		if(records_[size_-1]->key_ < records_[size_-2]->key_){// The latest record need to be sorted.
			Record* tmp = records_[size_-1]; // Store the last updated record.
			string key = records_[size_-1]->key_;
			if(key < records_[0]->key_){
				for(int i = size_-2; i >= 0; i--){ // Shift records.
					records_[i+1] = records_[i];
				}
				records_[0] = tmp;
			}
			else{
				int low = 0;
				int high = size_-2; // Don't need to compare the latest one.
				int mid;
				while(high-low != 1){ // To find the right position for the latest record.
					mid = (low+high)/2;
					if(key < records_[mid]->key_)
						high = mid;
					else
						low = mid;
				}
				for(int i = size_-2; i > low; i--){ // Shift records.
					records_[i+1] = records_[i];
				}
				records_[high] = tmp;
			}
   		}
	}
}

//the growth of the array is doubled 
template <class TYPE>
void SimpleTable<TYPE>::grow(){ 
	Record** newArray = new Record*[2*max_];
	max_ = 2*max_;
	for(int i = 0; i < size_; i++){
		newArray[i] = records_[i];
	}
	delete [] records_;
	records_ = newArray;
}

//one-parameter constructor
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected): Table<TYPE>(){
	records_ = new Record*[maxExpected];
	max_ = maxExpected;
	size_ = 0;
}

//copy constructor
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>& other){
	records_ = new Record*[other.max_];
	max_ = other.max_;
	size_ = other.size_;
	for(int i = 0; i < size_; i++){
		records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
	}
}

//move constructor
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other){
	size_ = other.size_;
	max_ = other.max_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.size_ = 0;
	other.max_ = 0;
}

//update the value of record if the key exists, otherwise add a new record.
template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value){
	int idx = search(key); //To be improved. It can be searched inside this function.
	if(idx == -1){
		if(size_ == max_){
			grow();
		}
		records_[size_++] = new Record(key,value);
		sort();
	}
	else{
		records_[idx]->data_ = value;
	}
	return true;
}

//if the record with given key exists, remove it and return true, otherwise return false only.
template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key){
	int idx = search(key);
	if(idx != -1){
		delete records_[idx];
		for(int i = idx; i < size_-1; i++){
			records_[i] = records_[i+1];
		}
		size_--;
		return true;
	}
	else{
		return false;
	}
}

//if the given key exists, return true and its corresponding value, otherwise return false only.
template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value){
	int idx = search(key);//To be improved. Calling a function is time-consuming.
	if(idx == -1)
		return false;
	else{
		value = records_[idx]->data_;
		return true;
	}
}

//return the number of records in the table
template <class TYPE>
int SimpleTable<TYPE>::numRecords() const{
	return size_;
}

//copy assignment operator
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>& other){
	if(this != &other){
		if(records_){
			for(int i = 0; i < size_; i++){
				delete records_[i];
			}
			delete [] records_;
		}
		records_ = new Record*[other.max_];
		max_ = other.max_;
		size_ = other.size_;
		for(int i = 0; i < size_; i++){
			records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
		}

	}
	return *this;
}

//move assignment operator
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other){
	if(this != &other){
		if(records_){
			for(int i = 0; i < size_; i++){
				delete records_[i];
			}
			delete [] records_;
		}
		size_ = other.size_;
		max_ = other.max_;
		records_ = other.records_;
		other.records_ = nullptr;
		other.size_ = 0;
		other.max_ = 0;	
	}
	return *this;
}

//destructor
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	if(records_){
		for(int i = 0; i < size_; i++){
			delete records_[i];
		}
		delete [] records_;
	}
}

template <class TYPE>
class RecentList{
	 struct Record{
                TYPE data_;
                string key_;
                Record(const string& key = "", const TYPE& data = TYPE{}){
                        key_ = key;
                        data_ = data;
                }

        };
        struct Node{
		Record data_;
		Node* next_;
        	Node* prev_;
		Node(const Record& data = Record{}, Node* next = nullptr, Node* prev = nullptr){
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
 	Node* first_; //pointer to the first node in the doubly linked list
 	Node* last_;  //pointer to the last node in the doubly linked list
public:
	class const_iterator{
		friend class RecentList;
	protected:
                Node* curr_;
		const RecentList* myList_;
	public:
		//constructor
		const_iterator(Node* curr = nullptr, const RecentList* list = nullptr){
			curr_ = curr;
			myList_ = list;
		}
		
		//return true if two const iterators equal
		bool operator==(const_iterator right){
			return (curr_ == right.curr_ && myList_ == right.myList_);
		}
		
		//return true if two const iterators do not equal
		bool operator!=(const_iterator right){
			return (curr_ != right.curr_ || myList_ != right.myList_);	
		}
		
		//move forward one const iterator, postfix
		const_iterator operator++(){
			if(curr_){
				curr_ = curr_->next_;
			}
			return *this;
		}
		
		//move backward one const iterator, postfix
		const_iterator operator--(){
			if(curr_){
             			curr_ = curr_->prev_;
			}
			return *this;
		}
		
		//move forward one const iterator, prefix
		const_iterator operator++(int){
			const_iterator tmp(curr_,myList_);
			if(curr_){ //if the current iterator is valid
				++(*this);
			}
			return tmp;
		}
		
		//move backward one const iterator, prefix
		const_iterator operator--(int){
			const_iterator tmp(curr_,myList_);
			if(curr_){ //if the current iterator is valid
				--(*this);
			}
			return tmp;
		}
		
		//return record of the current node
		const Record& operator*() const{
			Record rc = Record{};
                        if(curr_){
				return curr_->data_;
			}
    			return rc;
		}	
	};
	class iterator:public const_iterator{
		friend class RecentList;
                Node* curr_;
		const RecentList* myList_;
	public:
		//constructor
        	iterator(Node* curr = nullptr, const RecentList* list = nullptr){
			curr_ = curr;
			myList_ = list;
		}
		
		//return true if two iterators equal
		bool operator==(iterator right){
			return (curr_ == right.curr_ && myList_ == right.myList_);
		}
		
		//return true if two iterators do not equal
		bool operator!=(iterator right){
			return (curr_ != right.curr_ || myList_ != right.myList_);	
		}
		
		//move forward one iterator, postfix
		iterator operator++(){
			if(curr_){
				curr_ = curr_->next_;
			}
			return *this;
		}
		
		//move backward one iterator, postfix
		iterator operator--(){
			if(curr_){
				curr_ = curr_->prev_;
			}
			return *this;
		}
		
		//move forward one iterator, prefix
		iterator operator++(int){
			iterator tmp(curr_, myList_);
			if(curr_){ //if the current iterator is valid
				++(*this);
			}
			return tmp;
		}
		
		//move backward one iterator, prefix
		iterator operator--(int){
			iterator tmp(curr_,myList_);
			if(curr_){ //if the current iterator is valid  
				--(*this);
			}
			return tmp;
		}
		
		//get the key from the current node
		const string getKey(){
			string tmp = "";
			if(curr_)
				tmp = (curr_->data_).key_;
			return tmp; 
		}
		
		//get the data from current node
		const TYPE getData(){
			TYPE tmp = TYPE{};
			if(curr_)
				tmp = (curr_->data_).data_;
			return tmp;
		}
		
		//set the data to the current node
		void setData(const TYPE& value){
			if(curr_)
				(curr_->data_).data_ = value; 
		}
		
		//return the non-changable record of the current node
		const Record& operator*() const{
			Record rc = Record{};
			if(curr_){
				return curr_->data_;
			}
			return rc;
		}
		
		//return the record of the current node
		Record& operator*(){
			Record rc = Record{};
			if(curr_){
				return curr_->data_;
			}
			return rc;
		}
	};
	
	//default constructor
	RecentList(){
		first_ = nullptr;
		last_ = nullptr;
	}
	
	//return the iterator pointing to the beginning of the linked list
	iterator begin(){
		return iterator(first_, this);
	}
	
	//return the const iterator pointing to the beginning of the linked list
	const_iterator begin() const{
		return const_iterator(first_, this);
	}
	
	//return the iterator pointing to the end of the linked list
	iterator end(){
		return iterator(nullptr, this);
	}
	
	//return the const iterator pointing to the end of the linked list
	const_iterator end() const{
		return const_iterator(nullptr, this);
	}
	
	//insert an new record into the linked list
	void insert(const string& key, const TYPE& value){
		Record data(key, value);
		Node* newNode = new Node(data, first_); //make the new node point to the previous first node
		if(last_ == nullptr){ //if the doubly linked list is empty
			last_ = newNode;
		}
		else{
			first_->prev_ = newNode; //make the previous first node point to the new node
		}
		first_ = newNode;
	}
	
	//remove the record holds the given key if it exists in the linked list
	bool remove(const string& key){
		iterator remove = search(key);
		if(remove != end()){
			if(first_ == last_){
				delete first_;
				first_ = last_ = nullptr;
			}
			else{
				Node* removeNode = first_;
				first_ = first_->next_;
				delete removeNode;
				removeNode = nullptr;
				first_->prev_ = nullptr;
			}
			return true;
		}
		return false;
	}
	
	//search if the Record exists in the linked list, if exists, return the const interator 
	const_iterator search(const Record& key) const{
		const_iterator tmp = begin();
		while(tmp != end()){
			if(tmp.getKey() != key){
				++tmp;
			}
			else{
				return tmp;
			}
		}
		return tmp;
	}
	
	//search if the key exists in the doubly linked list, if exists, pull that record to the beginning of the linked list and return the iterator
	iterator search(const string& key){
		iterator tmp = begin();
		while(tmp != end()){
			if(tmp.getKey() != key){
				++tmp;
			}
			else{
				Node* curr = tmp.curr_;
				if(curr != first_){
					if(curr != last_){
						curr->prev_->next_ = curr->next_;
						curr->next_->prev_ = curr->prev_;
						curr->prev_ = nullptr;
						curr->next_ = first_;
						first_->prev_ = curr;
						first_ = curr;
					}
					else{
						Node* beforeCurr = curr->prev_;
						beforeCurr->next_ = nullptr;
						last_ = beforeCurr;
						curr->prev_ = nullptr;
						curr->next_ = first_;
						first_->prev_ = curr;
						first_ = curr;
					}
				}
				tmp = begin();
				return tmp;
			}
		}
		return tmp;
	}
	
	//destructor
	~RecentList(){ 
		while(first_ != nullptr){
			Node* tmp = first_->next_;
			delete first_;
			first_ = tmp;
		}
		last_ = nullptr; 
	}
	
	//copy constructor
	RecentList(const RecentList& rhs){ 
		first_ = last_ = nullptr;
		Node* tmp = rhs.last_;
		while(tmp){
			Record data = tmp->data_;
			insert(data.key_, data.data_);
			tmp = tmp->prev_;
		}	
	}
	
	//move constructor
	RecentList(RecentList&& rhs){ 
		first_ = rhs.first_;
		last_ = rhs.last_;
		rhs.first_ = rhs.last_ = nullptr;
		
	}
	
	//copy assignment operator
	RecentList& operator=(const RecentList& rhs){ 
		if(this != &rhs){
			if(first_ != nullptr){ //the linked list is not empty
				Node* curr = first_; 
				while(curr != nullptr){
					Node* tmp;
					tmp = curr->next_;
					delete curr;
					curr = tmp;
				}
				first_ = nullptr;
				last_ = nullptr;
			}
			string key;
			TYPE value;
			Node* tmp = rhs.last_;
			while(tmp){
				key = tmp->data_.key_;
				value = tmp->data_.data_;
				insert(key, value);
				tmp = tmp->prev_;
			}	
		}
		return *this;
	}
	
	//move assignment operator
	RecentList& operator=(RecentList&& rhs){ 
		if(this != &rhs){
			first_ = rhs.first_;
			last_ = rhs.last_;
			rhs.first_ = rhs.last_ = nullptr;
		}
	}
};

template <class TYPE>
class HashTable:public Table<TYPE>{
	RecentList<TYPE>* recordLists;
	int max_;           //capacity of the hash table
	int size_;          //current number of records held
public:
	HashTable(int maxExpected);
	HashTable(HashTable& other);
	HashTable(HashTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual int numRecords() const;
	virtual const HashTable& operator=(HashTable& other);
	virtual const HashTable& operator=(HashTable&& other);
	virtual ~HashTable();
};

//one-parameter constructor
template <class TYPE>
HashTable<TYPE>::HashTable(int maxExpected): Table<TYPE>(){
	recordLists = new RecentList<TYPE>[maxExpected];
	max_ = maxExpected;
	size_ = 0;
}

//copy constructor
template <class TYPE>
HashTable<TYPE>::HashTable(HashTable<TYPE>& other){
	recordLists = new RecentList<TYPE>[other.max_];
	max_ = other.max_;
	size_ = other.size_;
	for(int i = 0; i < max_; i++){
		recordLists[i] = other.recordLists[i];
	}
}

//move constrctor
template <class TYPE>
HashTable<TYPE>::HashTable(HashTable<TYPE>&& other){
	recordLists = other.recordLists;
	max_ = other.max_;
	size_ = other.size_;
	other.recordLists = nullptr;
	other.max_ = 0;
	other.size_ = 0;
}

//update the value of record and return true if the key exists, add a new record and return true if there is space, otherwise return false.
template <class TYPE>
bool HashTable<TYPE>::update(const string& key, const TYPE& value){
	hash<string> hasher;
	size_t hash = hasher(key)%max_;
	if(recordLists[hash].begin() != recordLists[hash].end()){ //when recordLists[hash] is not empty
		for(auto it = recordLists[hash].begin(); it != recordLists[hash].end(); ++it){
			if(it.getKey() == key){
				if(it.getData() != value)
					it.setData(value);
				return true;
			}	
		}
	}
	if(size_ < max_){
		recordLists[hash].insert(key,value);
		size_++;
		return true;
	}
	else
		return false;
}

//if the record with given key exists, remove it and return true, otherwise return false only.
template <class TYPE>
bool HashTable<TYPE>::remove(const string& key){
	hash<string> hasher;
	size_t hash = hasher(key) % max_;
	if(recordLists[hash].remove(key))
		size_--;
	return true;
}

//if the given key exists, return true and its corresponding value, otherwise return false only.
template <class TYPE>
bool HashTable<TYPE>::find(const string& key, TYPE& value){
	hash<string> hasher;
	size_t hash = hasher(key)%max_;
	auto it = recordLists[hash].search(key);
	if(it != recordLists[hash].end()){
		value = it.getData();
		return true;
	}
	return false;
}

//return the number of records in the table
template <class TYPE>
int HashTable<TYPE>::numRecords() const{
	return size_;
}

//copy assignment operator
template <class TYPE>
const HashTable<TYPE>& HashTable<TYPE>::operator=(HashTable<TYPE>& other){
	if(this != &other){
		if(recordLists){
			delete [] recordLists;
		}
		recordLists = new RecentList<TYPE>[other.max_];
		max_ = other.max_;
		size_ = other.size_;
		for(int i = 0; i < other.max_; i++){
			recordLists[i] = other.recordLists[i];
		}	
	}
	return *this;
}

//move assignment operator
template <class TYPE>
const HashTable<TYPE>& HashTable<TYPE>::operator=(HashTable<TYPE>&& other){
	if(this != &other){
		if(recordLists){
			delete [] recordLists;
		}
		recordLists = other.recordLists;
		max_ = other.max_;
		size_ = other.size_;
		other.recordLists = nullptr;
		other.max_ = 0;
		other.size_ = 0;
	}
	return *this;

}

//destrcuctor
template <class TYPE>
HashTable<TYPE>::~HashTable(){
	delete [] recordLists;
}