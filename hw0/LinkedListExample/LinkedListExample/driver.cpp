/* Friver file for the Linked List Example. 
 * The Fraction class has been included as it was used to 
 * instantiate a List Class object */

#include<iostream>
#include<string>
#ifndef LIST_H
#include "list.h"
#endif

#include "fraction.h"
#include "list.hpp"			// need this for templated classes.
							// header file is not enough

using namespace std;

int main()
{
    cout <<"Integer list\n";

    List<int> intList;
    intList.addElement(10);
    intList.addElement(-15);
    intList.addElement(90);
    intList.insert(12,2);
    if(intList.insert(-90,7))
        cout<<"Element inserted\n";
    else cout<<"Invalid position\n";
    intList.insert(1023,0);
    if(intList.remove(10))
        cout<<"Element deleted";
    else cout<<"Element does not exist"<<endl;
    if(intList.remove(-90))
        cout<<"Element deleted"<<endl;
    else cout<<"Element does not exist\n";
        
    cout<<"The list is ";
    intList.print();
    cout<<"Number of elements: "<<intList.size();
    cout<<endl;

    cout<<"String list\n";
    List<string> stList;
    stList.addElement("Spongebob");
    stList.addElement("Patrick");
    stList.insert("Squidward",1);
    cout<<"The list is ";
    stList.print();
    if(stList.search("Gary"))
        cout<<"\"Gary\" was in the list"<<endl;
    else cout<<"\"Gary\" was not in the list"<<endl;
    
    List<int> newList = intList;
    newList.print();

    
    float arr[5] = {3.14, 2.5, 16.98, -7.32, 5.04};
    List<float> flList(arr, 5);
    flList.print();

    cout<<"Enter 1 value for a new list of doubles: ";
    List<double> dList;
    cin>>dList;

    dList.addElement(5.7);
    dList.print();

    List<Fraction> fList;
    fList.addElement(Fraction(3,4));
    fList.insert(Fraction(-2,7),0);
    fList.addElement(Fraction(4.5));
    fList.print();
    return 0;
}













