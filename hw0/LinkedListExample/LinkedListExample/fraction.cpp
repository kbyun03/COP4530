#include<iostream>

#include "fraction.h"

using namespace std;

Fraction& Fraction::operator=(const Fraction &f)
{
    num = f.num;
    den = f.den;
    return *this;
}



//default constructor
Fraction::Fraction(): VAL(10)
{
    num = 1;
    den = 1;
}

Fraction::Fraction(int n, int d): VAL(10)
{
    num = n;
    if(d!=0)
        den = d;
    else den = 1;
}

Fraction::Fraction(double x): VAL(10)
{
    int count=0;
    den = 1;
    num = static_cast<int>(x);
    while( count++<8 && x - static_cast<double>(num) !=0)
    {
        num = static_cast<int>(x*VAL);
        den *=VAL;
        x*=VAL;
    }
}



int Fraction::getNum() const
{
    return num;
}

int Fraction::getDen() const
{
    return den;
}

void Fraction::setNum(int n)
{
    num = n;
}

void Fraction::setDen(int d)
{
    if(d!=0)
        den = d;
    else den=1;
}

void Fraction::print() const
{
    cout<<"The fraction is "<< num <<"/"<< den<<endl;
}

void Fraction::input()
{
    cout<<"Enter the numerator: ";
    cin>>num;
    cout<<"Enter the denominator: ";
    cin>>den;
    while(den==0)
    {
        cout<<"Denominator cannot be 0. Please enter the denominator: ";
        cin>>den;
    }
}

double Fraction::decimal() const
{
    return static_cast<double>(num) /den;
}

Fraction Fraction::add(const Fraction x)
{
    int sumN, sumD;
    sumD = den * x.den;
    sumN = num*x.den + x.num*den;

    return Fraction(sumN, sumD);
}

Fraction Add(const Fraction &x, const Fraction &y)
{
    int sumN, sumD;
    sumD = y.den * x.den;
    sumN = y.num*x.den + x.num*y.den;
    return Fraction(sumN, sumD);
}

Fraction Fraction::operator+(const Fraction &x) const
{
    int n,d;
    d = den*x.den;
    n = num*x.den + den*x.num;
    return Fraction(n,d);
}

bool operator==(const Fraction &x, const Fraction &y)
{
    if(x.num == y.num && x.den == y.den)
        return true;
    return false;
}

ostream& operator<<(ostream &out, const Fraction &x)
{
    out<<"Fraction: "<<x.num<<"/"<<x.den<<endl;
    return out;
}

istream& operator>>(istream &in, Fraction &x)
{
    char slash;
    in>>x.num>>slash>>x.den;
    return in;
}

Fraction& Fraction::operator++()
{
    num = num + den;
    return *this;
}

Fraction& Fraction::operator++(int x)
{
    Fraction temp = *this;
    num = num + den;

    return temp;
}


















