#ifndef CS20A_LIST_H
#define CS20A_LIST_H

#include<iostream>
#include<assert.h>
// Linked List object that maintains both m_head and m_tail pointers
// and the m_size of the list.  Note that you have to keep the m_head,
// m_tail and m_size consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Item>
class List {
public:

	List();//

	List(const List<Item>& other);

	List<Item>& operator=(const List<Item>& other);

	~List();

	void	print() const; //
	bool	empty() const; //

	void	push_front(const Item &item); //
	void	push_rear(const Item &item);//
	void	insert(int index, const Item &item);//

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions.
	Item	front() const; //
	Item	rear() const; //
	Item	get(int index) const;//

	int		size() const; //
	int		find(const Item &item) const;//

	bool	pop_front();//
	bool	pop_rear();//
	bool	remove(int index);//

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node;

	// We'll have both m_head and m_tail points for 
	// Fast insertion/deletion from both ends.
	Node*	m_head;
	Node*	m_tail;

	// Keep track of number of nodes in the list
	int		m_size;
};


/* List Implementation
//
//  Since List is a template class (which is not an actual 
//  class yet, not until we actually instantiate the list) 
//  we need to keep the implementation together with 
//  the definition.  There are ways to simulate having 
//  separate "implementation/definition" with templates, 
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Item>
struct List<Item>::Node {
	Node() :next(nullptr), prev(nullptr) {}
	Node(Item it, Node* p, Node* n) : item(it), next(n), prev(p) {}

	Item  item;
	Node* next;
	Node* prev;
	
};



/* List default constructor
//		Set m_head and m_tail pointer to point to nothing, m_size is zero
//		Already implemented, nothing to do.
*/
template<typename Item>
List<Item>::List() :m_head(nullptr), m_tail(nullptr), m_size(0) {
}


/* Copy constructor  
*/
template<typename Item>
List<Item>::List(const List<Item>& other){
	/* TODO */
	if(other.m_head == nullptr)
	{
		m_head = nullptr; //Default list settings
		m_tail = nullptr;
	}
	else //If list is >= 1
	{
		m_head = new Node;
		m_head->item = other.m_head->item;	//copying first item into new node
		Node *tempOther = other.m_head->next;  //tempOther points to next node on rhs list
		Node *temp = m_head; 
		while(tempOther != nullptr)
		{
			temp->next = new Node(tempOther->item, temp, nullptr); //new node is linked and data is copied from other list, temp is previous new node
			temp = temp->next; //advance
			tempOther = tempOther->next;
		}
		m_tail = temp;
	}
}
/* Overloaded assignment operator 
*/
template<typename Item>
List<Item>& List<Item>::operator=(const List<Item>& other) {
	/* TODO */
	if(this == &other)
		return *this;
	else if(other.m_head == nullptr)
	{
		m_head = nullptr;
		m_tail = nullptr;
		return *this;
	}
	else
	{
		Node *temp = m_head;
		Node *deleteNode = m_head;
		while(temp != nullptr)
		{
			deleteNode = temp;
			temp = temp->next;
			delete deleteNode;
		}
		m_head = new Node;
		m_head->item = other.m_head->item;	//copying first item into new node
		Node *tempOther = other.m_head->next;  //tempOther points to next node on rhs list
		temp = m_head; 
		while(tempOther != nullptr)
		{
			temp->next = new Node(tempOther->item, temp, nullptr); //new node is linked and data is copied from other list, temp is previous new node
			temp = temp->next; //advance
			tempOther = tempOther->next;
		}
		m_tail = temp;
	}
	return *this;
}


/* List destructor
*/
template<typename Item>
List<Item>::~List() {
	/* TODO */
	Node *temp = m_head;
	Node *deleteNode = m_head;
	if(m_head->next == nullptr)
	{
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
	}
	else
	{
		while(temp != nullptr)
		{
			deleteNode = temp;
			temp = temp->next;
			delete deleteNode;
		}
	delete temp;
	}
	
}

/* List print
*/		
template<typename Item>
void List<Item>::print() const {
	/* TODO */
	
	Node *temp = m_head;

	//Checks if list is empty
	if(temp == nullptr)
	{
		std::cout << "List is empty" << std::endl;
		return;
	}
	//Checks if there is a single element in List
	else if(m_head->next == nullptr)
	{
		std::cout << temp->item << std::endl;
		return; 
	}
	//Otherwise prints entire list
	else 
	{
		while(temp != nullptr)
		{
		std::cout << temp->item << std::endl;
		temp = temp->next;
		}
	}
}

/* List empty
*/
template<typename Item>
bool List<Item>::empty() const {
	/* TODO */
	if(m_head == nullptr)
		return true;
	
	return false;
}


/* List push_front
*/
template<typename Item>
void List<Item>::push_front(const Item &item) {
	/* TODO */
	Node *newNode = new Node; //New node
	newNode->item = item;
	//Checking if list is empty. If true, assigns adress of new node to m_head
	if(m_head == nullptr)
	{
		m_head = newNode;
		m_tail = newNode;	
		m_size++;
		return;
	}
	//One element
	else if(m_head->next == nullptr){
		newNode->next = m_head;
		m_head->prev = newNode;
		m_head = newNode;
		m_size++;
		return;
	}
	m_head->prev = newNode;
	newNode->next = m_head;
	m_head = newNode;
	m_size+=1;
	
}

/* List push_rear
*/
template<typename Item>
void List<Item>::push_rear(const Item &item) {
	/* TODO */
	Node *newNode = new Node;
	newNode->item = item;
	
	if(m_head == nullptr){
		std::cout << "yellow" << std::endl;
		m_head = newNode;
		m_tail = newNode;
		m_size++;
		m_head->next = nullptr;
		return;
	}
	else if(m_head->next == nullptr){
		m_head->next = newNode;
		newNode->prev = m_head;
		m_tail = newNode;
		m_size++;
		return;
	}
	m_tail->next = newNode;
	newNode->prev = m_tail;
	m_tail = newNode;
	m_size++;
}

/* List insert
*/
template<typename Item>
void List<Item>::insert(int index, const Item &item) {
	/* TODO */
	if(index <= 0)
	{
		this->push_front(item);
		return;
	}
	else if(index == m_size)
	{
		this->push_rear(item);
		return;
	}
	Node *temp = m_head;
	int i = 0;
	while(i != index)
	{
		temp = temp->next;
		i++;
	}
	Node *newNode = new Node;
	newNode->item = item;
	temp->prev->next = newNode;
	newNode->next = temp;
	m_size++;
	return;
}

/*  List front
*/
template<typename Item>
Item List<Item>::front() const {
	// Force check that the m_head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_head != nullptr); 

	/* TODO */
	
	return m_head->item;	
}

/* List rear
*/
template<typename Item>
Item List<Item>::rear() const {

	// Force check that the m_tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_tail != nullptr);

	/* TODO */
	
	return m_tail->item;
	
}

/* List get
//		returns the item at index
*/
template<typename Item>
Item List<Item>::get(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < m_size);

	/* TODO */
	if(index < 0)
		return m_head->item;
	
	Node *temp = new Node;
	temp = m_head;
	int i = 0;
	if(m_head->next == nullptr)
		return m_head->item;
	while(i != index){
		temp = temp->next;
		i++;
	}
	
	return temp->item;
}

/* List size
*/
template<typename Item>
int List<Item>::size() const {
	/* TODO */
	return m_size;
}

/* List find
*/
template<typename Item>
int List<Item>::find(const Item &item) const {

	/* TODO */
	if(m_head == nullptr)
		std::cout << "List Is empty" << std::endl;
	else if(m_head->item == item)
		return 0;
	Node *temp = new Node;
	temp = m_head;
	int i = 0;
	while(temp != nullptr){
		if(temp->item == item)
			return i;
		temp= temp->next;
		i++;
	}
	std::cout << "Item not in list ";
	return 8675309;
}

/* List pop_front
*/		
template<typename Item>
bool List<Item>::pop_front() {
	/* TODO */
	if(m_head == nullptr)
		return false;
	else if(m_head->next == nullptr){
		m_size = 0;
		Node *temp;
		temp = m_head;
		delete temp;
		m_head = nullptr;
		m_tail = nullptr;
		return true;
	}
	Node *temp;
	temp = m_head;
	m_head = m_head->next;
	m_size--;
	delete temp;
	return true;
	
}

/* List pop_rear
*/	
template<typename Item>
bool List<Item>::pop_rear() {
	/* TODO */
	Node *temp;
	if(m_head == nullptr)
		return false;
	else if(m_head->next == nullptr){
		m_size = 0;
		temp = m_head;
		delete temp;
		m_head = nullptr;
		m_tail = nullptr;
		return true;
	}
	temp = m_tail;
	m_tail = m_tail->prev;
	m_tail->next = nullptr;
	m_size--; 
	delete temp;
	return true;
}

/* List remove
*/
template<typename Item>
bool List<Item>::remove(int index) {

	/* TODO */
	if(index < 0)
	{
		std::cout << "Index is out of bounds" << std::endl;
		return false;
	}
	else if(index == 0){
		this->pop_front();
		return true;
	}
		
	Node *temp = m_head;
	int i = 0;

	while(i != index) //traverses list till desired list index
	{
		if(temp->next == nullptr)
		{
			std::cout << "Index is out of bounds" << std::endl;
		}
		temp = temp->next;
		i++;
	}
	if(temp == m_tail) //checks if temp ptr has reached the end of list
	{
		m_tail = m_tail->prev;
		m_tail->next = nullptr;
		m_size--;
		delete temp;
		return true;
	}

	temp->prev->next = temp->next;
	delete temp;
	m_size--;
	return true;

}






#endif // _X_XMMXX