

// Choose which run to compile
#define RUN1 //RUN1 RUN2 RUN3


#ifdef RUN0 

#include"list.h"
#include"studentinfo.h"
#include<iostream>
#include<string>
int main() {

	std::cout << StudentInfo::name() << std::endl;
	std::cout << StudentInfo::id() << std::endl;

	List<int> l; //List of integers

	l.push_rear(0);
	// l.push_front(5);
	
	
	
	
	l.push_front(7);
	l.push_front(42);
	l.push_front(6);
	l.push_front(0);
	l.push_front(1);
	l.print();
	l.insert(0, 4);
	std::cout << std::endl;
	//l.remove(5);
	l.print();
	
	std::cout <<  "Size of l: " <<l.size() << std::endl;

	List<int> k;
	k.push_front(20);
	k.push_front(20);
	//k.print();
	List<int> j = k;
	std::cout << &j << " " << &k << std::endl;
	j.print();
	k.push_front(2);
	j.push_front(0);
	k = l; 
	std::cout << std::endl;
	k.print();
	// k.remove(0);
	// k.print();
	// std::cout <<  "Size of l: " <<l.size() << std::endl;
	// l.pop_front();
	// l.pop_front();
	

	// std::cout <<  "Size of l: " <<l.size() << std::endl;
	


	//l.pop_rear();
	//l.pop_rear();
	
	
	//std::cout << l.rear() << std::endl;
	
	// std::cout << "---------------" << std::endl;
	// std::cout << l.front() << std::endl;
	// std::cout << l.size() << std::endl;
	// List<std::string> strList;
	// strList.push_front("Kalvin");
	// //std::cout << strList.front()  << " " << strList.size() << " Get " << l.get(1) <<  std::endl;
	// //l.push_rear(2);
	// // l.pop_front();
	// // l.pop_front();
	// l.pop_rear();
	// //l.pop_rear();
	// //l.pop_rear();
	// //l.pop_rear();
	// std::cout << std::endl;
	// l.print();
	// std::cout << std::endl;
	// std::cout << "Find: " << l.find(5) << std::endl;
	// std::cout << "Rear " << l.rear() << std::endl;
	// //l.print(); // 2 Bob World Hello

	return 0;
}

#elif defined RUN1

#include"list.h"
#include"studentinfo.h"
#include<iostream>
#include<string>

int main() {

	std::cout << StudentInfo::name() << std::endl;
	std::cout << StudentInfo::id() << std::endl;

	List<std::string> l; //List of integers

	l.push_rear("Hello");
	l.push_front("World");
	l.push_front("Bob");
	l.push_front("2");

	l.print(); // 2 Bob World Hello

	l.pop_rear();
	l.print(); // 2 Bob World 

	std::cout << l.front() << std::endl; // 2
	return 0;
}

#elif defined RUN2

#define MAKE_MEMBERS_PUBLIC
#include"list.h"
#include<assert.h>

//Unit test example for push_font on initially empty list

int main() {

	// Step 1: Initial state
	// Assume that constructor implemented properly
	// If you're not sure if the constructor is 
	// implemented properly, STOP, go back and make
	// sure. Luckily the default constructor is 
	// done for you.  But the point remains, never,
	// ever, use a function in a test that isn't itself
	// verified to function according to spec.
	List<int> l;


	// Step 2: Execute the function to test
	l.push_front(99);

	// Step 3: Verify what you expect to observe.
	// You must know what is supposed to happen in
	// order to analyze for correctness. Generally, 
	// you must permute all possible combinations
	// of all member variables.
	assert(l.m_head != nullptr);
	assert(l.m_tail != nullptr);
	assert(l.m_size == 1);
	assert(l.m_head->prev == nullptr);
	assert(l.m_head->next == nullptr);
	assert(l.m_head->item == 99);


}


#else

#define MAKE_MEMBERS_PUBLIC
#include"list.h"
#include<assert.h>
#include<string>

//Unit test example for push_font on initially non empty list

int main() {

	// Step 1: Initial state
	// Same as above, except we must first populate the list
	// However, since we are testing push_front, we cannot
	// use it to generate the initial state of our list
	// to test.  So we have to manually set the initial state
	// in this case we are creating a list with three nodes.
	List<std::string>::Node* first = new List<std::string>::Node;
	List<std::string>::Node* second = new List<std::string>::Node;
	List<std::string>::Node* third = new List<std::string>::Node;

	// We have to manually linked everything together:
	first->item = "first";
	first->prev = nullptr;
	first->next = second;

	second->item = "second";
	second->prev = first;
	second->next = third;

	third->item = "third";
	third->prev = second;
	third->next = nullptr;

	// Now we create  List object and inject the initial control state:
	List<std::string> l;
	l.m_head = first;
	l.m_tail = third;
	l.m_size = 3;

	// Step 2: Now with the list given a complete and correct starting state
	// We can test various member functions for correctness.
	// For example we can use this as one test for push_front;
	l.push_front("Zero");

	// Step 3: Verify:  Technically, we should examine all 
	// member variables, and all nodes' item, next, prev pointers
	// to ensure that the push_front didn't mangle any of the
	// internal nodes.  But, this is mostly just to illustrate
	// how you might develop your own tests.  
	assert(l.m_size == 4);
	assert(l.m_head->prev == nullptr);
	assert(l.m_head == first->prev);
	assert(l.m_head->next == first);
	assert(l.m_head->item == "Zero");
	assert(l.m_tail == third);
}



#endif