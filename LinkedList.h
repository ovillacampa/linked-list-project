#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

template <class T>
class LinkedList {
public:
	class Node {
	public:
		Node(T elem) {
			prev = 0;
			next = 0;
			data = elem;
		}
		T data; // the node data
		Node *prev; // previous link
		Node *next; // next link
	};

private:
	Node *head; // first node in the list
	Node *tail; // last node in the list
	unsigned int size;
public:
	LinkedList();
	LinkedList(const LinkedList<T> &list);
	~LinkedList();
	void AddHead(const T &data);
	void AddTail(const T &data);
	void AddNodesHead(const T *data, unsigned int count);
	void AddNodesTail(const T *data, unsigned int count);
	void InsertAt(const T&, unsigned int);
	void InsertBefore(Node* node, const T &data);
	void InsertAfter(Node* node, const T &data);
	Node *GetNode(unsigned int index);
	const Node *GetNode(unsigned int index) const;
	Node *Find(const T &data);
	const Node *Find(const T &data) const;
	void FindAll(vector<Node *> &outData, const T&value) const;
	const Node *Head() const;
	Node *Head();//return head node in the list
	Node *Tail();//return tail node in the list
	const Node *Tail() const;
	unsigned int Remove(const T & data);
	bool RemoveHead();//removes first node from list
	bool RemoveTail();
	bool RemoveAt(unsigned int index);//delete node from the list
	void PrintForward();//print out all nodes on the screen
	void PrintReverse();
	unsigned int NodeCount();//return the number of nodes in the list
	void Clear();
	const T &operator[](unsigned int index) const;
	T & operator[](unsigned int index);
	bool operator==(const LinkedList<T> &rhs) const;
	LinkedList<T> &operator=(const LinkedList<T> &rhs);
};

template <class T>
LinkedList<T>::LinkedList()
{
	head = 0;
	tail = 0;
	size = 0;
}

//copy constructor
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
	typename LinkedList<T>::Node *p = list.head;
	head = NULL;
	tail = NULL;
	size = 0;

//	typename LinkedList<T>::Node *q = head;
//	q->data = p->data;
//	q->next = NULL;
//	size++;
//	p = p->next;
	for (unsigned int i = 0; i < list.size; i++) {
		T newItem = p->data;
		p = p->next;
	//	InsertAt(newItem, i);
		AddTail(newItem);
	//	cout << newItem << endl;
	}
}


//destructor
template <class T>
LinkedList<T>::~LinkedList(void)
{
	typename LinkedList<T>::Node *item;
	typename LinkedList<T>::Node *next;

	for (item = head; item != 0; item = next) {
		next = item->next;
		delete item;
	}
}

//insert item
template <class T>
void LinkedList<T>::AddHead(const T &data)
{
	typename LinkedList<T>::Node *item = new typename LinkedList<T>::Node(data);//new data to be inserted
																				//empty list
	if (head == 0 && tail == 0) {
		head = item;
		tail = item;
	}
	//insert new item at the beginning of the list
	else
	{
		Node *f;
		f = head;
		head = item;
		head->next = f;
		f->prev = head;
	}
	size++;
}

template <class T>
void LinkedList<T>::AddTail(const T &data)
{
	typename LinkedList<T>::Node *item = new typename LinkedList<T>::Node(data);//new node to be inserted
																				//empty list
	if (head == 0 && tail == 0) {
		head = item;
		tail = item;
	}
	//insert new item at the end of the list
	else {
		Node *t;
		Node *x;
		t = tail;
		x = t;
		t = item;
		x->next = t;
		t->prev = x;
		tail = t;
	}
	size++;
}

template <class T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count)
{
	unsigned int temp = count - 1;
	for (unsigned int i = 0; i < count; i++) {
		AddHead(data[temp-i]);
	}
	size = size + count;
}

template <class T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++) {
		AddTail(data[i]);
	}
	size = size + count;
}

template <class T>
void LinkedList<T>::InsertBefore(Node* node, const T &data)
{
	unsigned int counter;
	counter = NodeCount();
	typename LinkedList<T>::Node *i = NULL;
	// temp = this->Find(data);
	for (i = tail; i != 0; i = i->prev) {
		if (i == Find(node->data)) {
			this->InsertAt(data, counter - 1);
		}
		counter--;
	}
	size++;
}

template <class T>
void LinkedList<T>::InsertAfter(Node* node, const T &data)
{
	unsigned int counter;
	counter = 0;
	typename LinkedList<T>::Node *i = NULL;
	// temp = this->Find(data);
	for (i = head; i != 0; i = i->next) {
		if (i == Find(node->data)) {
			this->InsertAt(data, counter + 1);
		}
		counter++;
	}
	size++;
}

template <class T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index)
{
	typename LinkedList<T>::Node *item = new typename LinkedList<T>::Node(data);//new node to be inserted
	index = index + 1;																			//empty list
	if (head == 0 && tail == 0) {
		head = item;
		tail = item;
	}
	//insert new item at the beginning of the list
	else if (index == 1)
	{
		typename LinkedList<T>::Node *f;
		f = head;
		head = item;
		head->next = f;
		f->prev = head;
	}
	//insert new item between items
	else if (index>1 && index <= NodeCount()) {
		typename LinkedList<T>::Node *ta;
		ta = head;
		for (unsigned int t = 1; t<index; t = t + 1) { ta = ta->next; }
		item->next = ta;
		item->prev = ta->prev;
		ta->prev->next = item;
		ta->prev = item;
	}
	//insert new item at the end of the list
	else if (index == NodeCount() + 1) {
		typename LinkedList<T>::Node *t;
		typename LinkedList<T>::Node *x;
		t = tail;
		x = t;
		t = item;
		x->next = t;
		t->prev = x;
		tail = t;
	}
	//show message if index is not valid
	else
		cout << "Invalid index! index must be between 1 and " << NodeCount() + 2 << "\n";

	size++;
}

//Print out all items on the screen
template <class T>
void LinkedList<T>::PrintForward()
{
	if (NodeCount()>0) {
		typename LinkedList<T>::Node *i;
		for (i = head; i != 0; i = i->next) {
			// cout << "\n" << "Address " << i <<" Prev " << i->prev << " " << i->data << " Next " << i->next;   // Print with memory locations to troubleshoot
			cout << i->data << endl;

		}
	}
	else
		cout << "\nNo item found";
}

template <class T>
void LinkedList<T>::PrintReverse() {

	if (NodeCount()>0) {
		typename LinkedList<T>::Node *i;
		for (i = tail; i != 0; i = i->prev) {
			cout << i->data << endl;
		}
	}
	else
		cout << "\nNo item found";
}

template <class T>
unsigned int LinkedList<T>::NodeCount()
{
	/*
	typename LinkedList<T>::Node *i;
	int t = 0;
	for (i = head; i != 0; i = i->next) {
	t = t + 1;
	}
	return t;
	*/
	return size;
}

template <class T>
typename LinkedList<T>::Node *LinkedList<T>::Head()
{
	return head;
}

template <class T>
const typename LinkedList<T>::Node *LinkedList<T>::Head() const
{
	return head;
}

template <class T>
typename LinkedList<T>::Node *LinkedList<T>::Tail()
{
	return tail;
}


template <class T>
const typename LinkedList<T>::Node *LinkedList<T>::Tail() const
{
	return tail;
}


template <class T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index)
{
	//  index = index+1;
	typename LinkedList<T>::Node *temp = head;
	for (unsigned int i = 0; i < NodeCount(); i++) {
		if (i != 0)
			temp = temp->next;
		if (i == index) {
			break;
		}
	}
	return temp;
}

template <class T>
const typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) const
{
	//  index = index+1;
	typename LinkedList<T>::Node *temp = head;
	for (unsigned int i = 0; i < NodeCount(); i++) {
		if (i != 0)
			temp = temp->next;
		if (i == index) {
			break;
		}
	}
	return temp;
}

template <class T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data)
{
	typename LinkedList<T>::Node *temp = NULL;
	typename LinkedList<T>::Node *i;
	for (i = head; i != 0; i = i->next) {
		if (i->data == data)
			temp = i;
	}
	return temp;
}

template <class T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) const
{
	typename LinkedList<T>::Node *temp = NULL;
	typename LinkedList<T>::Node *i;
	for (i = head; i != 0; i = i->next) {
		if (i->data == data)
			temp = i;
	}
	return temp;
}
//Remove
template<class T>
inline unsigned int LinkedList<T>::Remove(const T & data)
{
	unsigned int delCount = 0;
	int cntr = 0;
	typename LinkedList<T>::Node *i;
	vector<int> delItems;
	for (i = head; i != 0; i = i->next) {
		if (i->data == data) {
			delItems.push_back(cntr);
			delCount++;
		}
		cntr++;
	}
	for (unsigned int j = delCount; j >= 1 && j <= delCount; --j)
		RemoveAt(delItems[j - 1]);

	size = size - delCount;
	return delCount;

}

//FindAll
template <class T>
void LinkedList<T>::FindAll(vector<Node*> &outData, const T&value) const
{
	typename LinkedList<T>::Node *i;
	unsigned int j = 0;
	for (i = head; i != 0; i = i->next) {
		if (i->data == value) {
			outData.push_back(i);
			j++;
		}
	}
}

template <class T>
bool LinkedList<T>::RemoveHead()
{
	bool NodeWasDeleted = false;

	if (size > 1) {

		typename LinkedList<T>::Node *temp;
		temp = head;
		head = head->next;
		head->prev = 0;
		delete temp;
		size--;
		NodeWasDeleted = true;
	}
	else if (size == 1)
	{
		       Clear();
		NodeWasDeleted = true;
	}

	return NodeWasDeleted;
}
template <class T>

bool LinkedList<T>::RemoveTail()
{
	bool NodeWasDeleted = false;

	if (NodeCount() > 1) {
		typename LinkedList<T>::Node *temp;
		temp = tail;
		tail = tail->prev;
		tail->next = 0;
		delete temp;
		size--;
		NodeWasDeleted = true;
	}
	else if (NodeCount() == 1){
		Clear();
		NodeWasDeleted = true;
	}

	return NodeWasDeleted;
}

template <class T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
	  index = index+1;
	bool NodeWasDeleted = false;
	if (NodeCount() > 0) {
		typename LinkedList<T>::Node *temp;
		if (index == 1) {
			temp = head;
			head = head->next;
			head->prev = 0;
			delete temp;
			NodeWasDeleted = true;
		}

		else if (index>1 && index<NodeCount()) {
			temp = head;
			for (unsigned int i = 1; i<index; i++) {
				temp = temp->next;
			}
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			NodeWasDeleted = true;
		}
		else if (index == NodeCount()) {
			temp = tail;
			tail = tail->prev;
			tail->next = 0;
			delete temp;
			NodeWasDeleted = true;
		}
	}
	else
		cout << "\n No item found";



	size--;
	return NodeWasDeleted;
}

template <class T>
void LinkedList<T>::Clear()
{
	typename LinkedList<T>::Node *temp = head;
	while (temp != nullptr)
	{
		typename LinkedList<T>::Node *del = temp;
		temp = temp->next;
		delete del;
	}
	head = nullptr;
	tail = nullptr;

	size = 0;
}

template <class T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	unsigned int j = 0;
	typename LinkedList<T>::Node *temp;
	typename LinkedList<T>::Node *i;
	for (i = head; i != 0; i = i->next) {
		if (j == index)
			temp = i;
		j++;
	}
	return temp->data;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
	typename LinkedList<T>::Node *p = rhs.head;
	head = NULL;
	tail = NULL;
	size = 0;

	for (unsigned int i = 0; i < rhs.size; i++) {
		T newItem = p->data;
		p = p->next;
		AddTail(newItem);
	}
	return *this;
}
template <class T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const
{
	bool ListSame = true;

	if (size != rhs.size) {
		ListSame = false;
		return ListSame;
	}
	if(head == nullptr && rhs.head == nullptr){
		return ListSame;
	}
	typename LinkedList<T>::Node *p;
	typename LinkedList<T>::Node *q;
	p = head;
	q = rhs.head;
	while (p != nullptr)
	{
		if (p->data != q->data) {
			ListSame = false;
		}
		p = p->next;
		q = q->next;

	}
	return ListSame;
}
template <class T>
T& LinkedList<T>::operator[](unsigned int index)
{
	unsigned int j = 0;
	typename LinkedList<T>::Node *temp;
	typename LinkedList<T>::Node *i;
	for (i = head; i != 0; i = i->next) {
		if (j == index)
			temp = i;
		j++;
	}
	return temp->data;
}




