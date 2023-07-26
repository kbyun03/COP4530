/* Implementation file for the List class
 * contains the function defintions for each of the
 * member functions of the Node ad List classes
 * Detailed descritions are included where necessary
 */

#include<iostream>
#ifndef LIST_H
#include "list.h"
#endif
using namespace std;

/* Parameterized constructor for the Node class
 * Creates a Node object of the required type, sets the 
 * value to the given value, and sets the next pointer to NULL
 */
template <class T>
Node<T>::Node(T v)
{
    val = v;
    next = NULL;
}

// getter for the vlaue
template <class T>
T Node<T>::getVal() const
{
    return val;
}

// getter for the next pointer
template<class T>
Node<T>* Node<T>::getNext() const
{
    return next;
}

// setter for the value
template <class T>
void Node<T>::setVal(T v)
{
    val = v;
}

// setter for the next pointer
template<class T>
void Node<T>::setNext(Node<T> *n)
{
    next = n;
}

/* default constructor for a List object
 * sets the Head pointer to NULL indicating an empty list
 */
template<class T>
List<T>::List()
{
    head = NULL;
}

/* Function to check if the list is empty
 * The list is empty if the head pointer is NULL
 */
template<class T>
bool List<T>::isEmpty() const
{
    if(head == NULL)
        return true;
    return false;
}

/* Function to return the size of the list. 
 * The function counts every Node in the list before moving
 * to the next node. We have reached the end of the list when
 * the next node is NULL
 */
template <class T>
int List<T>::size() const
{
    int count=0;
    Node<T>* cur = head;
    while(cur!=NULL)
    {
        count++;
        cur = cur->getNext();
    }
    return count;
}

/* Function to add an element to the end of the list. 
 * We create a new Node object for the given item.
 * Then, we traverse the list to the end using the same
 * logic as the size() function, and then attach the new
 * Node at the end
 */
template <class T>
void List<T>::addElement(T v)
{
    Node<T> *cur,*incoming;
	// create a new Node
    incoming = new Node<T>(v);
    
    cur = head;
	// List was empty
    if(cur == NULL)
    {
        head = incoming;
    }
    else
    {
		// move to the end of the list
        while (cur->getNext() != NULL)
        {
            cur = cur->getNext();
        }
		// attach the new node at the end
        cur->setNext(incoming);
    }
}

/* Function to cleare out the List. 
 * Start at the head. Capture the next node so that we do not
 * lose the rest of the list. Then delete the current node. 
 * Repeat until the next Node is NULL (end of the list)
 */
template<class T>
void List<T>::clear()
{
    Node<T> *cur,*element;
    cur = head;
    while(cur!=NULL)
    {
        element = cur;		// pointer to the current node
        cur = cur->getNext();	// move to the next node
        delete element;		// delete the "current" node
    }
    head = NULL;
}

/* Destructor. 
 * Use the clear function to empty out the list
 */
template<class T>
List<T>::~List()
{
    if(head !=NULL)
        clear();
}

/* Function to print the contents of the list. 
 * Traverse the list, printing the item at the current node
 * as we go. 
 * This assumes the << opertaor has been overloaded for 
 * all types that instantiate the list
 */
template <class T>
void List<T>::print() const
{
    Node<T> *cur = head;
    while(cur!=NULL)
    {
        cout<<cur->getVal()<<"\t";
        cur = cur->getNext();
    }
    cout<<endl;
}

/* Function to insert an element at the given position
 * If the given position is invalid (negative, or greater than the 
 * size of the list, the function fails and returns false
 * Otherwise, move through the list until we reach the given
 * position and then 
 * (a) Set the new node's next pointer to the current node's next
 * (b) set the current node's next pointer to the new node
 */
template<class T>
bool List<T>::insert(T val, int pos)
{
    if(pos <0 || pos>size())	// fails
        return false;
    
	// create a new node
    Node<T> *newNode = new Node<T>(val);
    if(pos == 0)		// insertion at the head
    {
        newNode->setNext(head);
        head = newNode;
    }
    else
    {
        int count=1;
        Node<T> * cur = head;
		// move to the previous position (i-1)
        while(cur!=NULL && count<pos)
        {
            cur = cur ->getNext();
            count++;
        } 
		// make the connections
        newNode->setNext(cur->getNext());
        cur->setNext(newNode);
    }

    return true;
}

/* Function to remove en element from the list. 
 * Function fails if the element were not found
 * Traverse the list until the element is located.
 * Set the previous node's next pointer to the target
 * node's next pointer
 * Then, delete the target node
 */
template <class T>
bool List<T>::remove(T val)
{
    Node<T> *cur = head,*pre = head;
    bool done=false;
	// Special case: remove the node at the head of the list
    if(head->getVal() == val)
    {
        head = head->getNext();
        delete cur;
        cur = NULL;
        done = true;
    }
	// locate the item
    while(cur!=NULL && !done)
    {
        if(cur->getVal() == val)
        {
            pre->setNext(cur->getNext());
            delete cur;
            done = true;
        }
		// set the pointers as described
        pre = cur;
        cur = cur->getNext();
    }
    return done;
}

/* Lnear search for an item
 * Returns truw if the item were found and false otherwise
 */
template <class T>
bool List<T>::search(T val) const
{
    Node<T> *cur = head;
    bool found = false;
    while(cur!=NULL && !found)
    {
        if(cur->getVal() == val)
            found = true;
        cur = cur->getNext();
    }
    return found;
}

/* Copy constructor */
template <class T>
List<T>::List(const List<T> &oldList)
{
    head = NULL;
    Node<T> *el = oldList.head;
    while(el!=NULL)
    {
        addElement(el->getVal());
        el = el->getNext();
    }
}

/* Assignment operator overload */
template<class T>
List<T>& List<T>::operator=(const List<T> &oldList)
{
    if(head!=NULL)
        clear();
    Node<T> *el = oldList.head;
    while(el!=NULL)
    {
        addElement(el->getVal());
        el = el->getNext();
    }
    return *this;
}

/* Conversion constructor */
template <class T>
List<T>::List(const T *arr, int size)
{
    head = NULL;
    for(int i=0; i<size; i++)
    {
        addElement(arr[i]);
    }
}

/* Extraction operator overload. 
 * Assumes the extraction operator has been overloeaded for the 
 * type used for instantiation */
template <class T>
istream& operator>>(istream &in, List<T> &l)
{
    l.clear();
    T val;
    in>>val;
    l.addElement(val);
    return in;
}























