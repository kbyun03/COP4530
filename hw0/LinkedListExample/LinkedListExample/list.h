/* Class Declaration for a Templated Linked List Class
 * A Linked List is linear List Data Structure where each 
 * element of the list contains a data item as well as 
 * a pointer to the next element of the list.
 * The List is Ordered (elements are positional, like an array) 
 * but they are not contiguous in memory (unlike an array). 
 *
 * A Templated class is a class that describes a generic typedef
 * The data type for each instaitation of the class is decided
 * when the object is created. 
 */

#include<iostream>
using namespace std;

#ifndef LIST_H
#define LIST_H

/* Declares the Node class which holds one element of the list
 * Each node consists of an item of the templated generic type,
 * and a self-referential pointer to the next Node in the List
 */
 
template <class T>
class Node
{
    public:
    Node(T v);				// parameterized constructor
    T getVal() const;		// getter for Value
    Node<T>* getNext() const;	// getter for the next pointer
    void setVal(T v);		// setter for value
    void setNext(Node<T> *n);	// setter for the next pointer

    private:
    T val;					// The item in the List
    Node<T> *next;			// self-referential pointer to the next item
};


/* Declaration of the List class name. 
 * Required if we want any templated classes to also have overloads
 * for the inserstion and extraction operators (or any other classes)
 */

template <class T> class List;
template <class T> istream& operator>>(istream &in, List<T> &l);

/* Declaration of the List Class. 
 * Each instantiation of the List class will be one Linked List 
 * of several Nodes
 * The only way to access a Linked List is through the Head of the 
 * list, which is a pointer to the first element of the list. 
 */
template <class T>
class List
{
    friend istream& operator>> <T>(istream &in, List<T> &l);
	
    public:
    List();							// default constructor
    ~List();						// destructor
    List(const List<T> &);			// copy constructor
    List(const T *arr, int size);	// conversion constructor from an array
    List<T>& operator=(const List<T>&);		// assignment operator overload

    void print() const;				// print function
    bool isEmpty() const;			// checks if the List is empty
    int size() const;				// Returns the size of the list
    void clear();					// empties out the list
    void addElement(T );			// Adds an element at the end of the list
    bool insert(T, int);    		// inserts an element at a given position
    bool remove(T);					// removes an element from the list
    bool search(T) const;			// looks for the given item in the list

    private:
    Node<T> *head;					// pointer to the first Node in the list
};


#endif













