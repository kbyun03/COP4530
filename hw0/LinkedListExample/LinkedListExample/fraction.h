#include<iostream>
#include<iomanip>

using namespace std;

class Fraction
{
    //friend function 
    friend Fraction Add(const Fraction &x, const Fraction &y);    
    friend bool operator==(const Fraction &x, const Fraction &y);

    friend ostream& operator<<(ostream &out, const Fraction &x);
    friend istream& operator>>(istream &in, Fraction &x);


    public:

    Fraction();
    Fraction(int n, int d=1);
    Fraction(double x);
    
    int getNum() const;
    int getDen() const;
    void setNum(int n);
    void setDen(int d);

    void print() const;
    void input();
    double decimal() const;

    Fraction add(const Fraction x);
    
    Fraction operator+(const Fraction&x) const;

    Fraction& operator++();
    Fraction& operator++(int x);
    Fraction& operator=(const Fraction &f);
    private:
    int num,den;
    const int VAL;
};
