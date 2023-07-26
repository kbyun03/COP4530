// Young0Bin Byun
// FSUID: YB23E
// EMPLID: 201093220

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

class Rock {
public:
    Rock(){
        name = "";
        size = 0;
    };
    Rock(string n, double s){
        name = n;
        size = s;
    };

    string getName() const{
        return name;
    };
    double getSize() const{
        return size;
    };
    void setName(string n){
        name = n;
    };
    void setSize(double s){
        size = s;
    };

    friend ostream &operator<<( ostream &output, const Rock &R){
        output << R.getName() << ":" << R.getSize();
        return output;
    }

private:
    string name;
    double size;


};

class ComparatorRocks{
public:
    bool operator()(Rock r1, Rock r2){
        double r1Size = r1.getSize();
        double r2Size = r2.getSize();

        if(r1Size < r2Size){
            return true;
        }
        if(r1Size == r2Size){
            string r1Name = r1.getName();
            string r2Name = r2.getName();
            if(r1Name < r2Name){
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }
};

void insert(vector<Rock> &rocks, Rock newRock, ComparatorRocks cmp){
    vector<Rock>::iterator i = rocks.begin();
    bool condition = true;
    for(i; i < rocks.end(); ++i){
        if(cmp(*i,newRock)){
            //cout << "rock at index i is smaller than newRock" << i->getSize() << "--" << newRock.getSize() << endl;
            continue;
        }
        else{
            if(condition){
                //cout << "rock at index i is larger than newRock" << i->getSize() << "--" << newRock.getSize() << endl;
                //cout << "inserting newrock";
                rocks.insert(i, newRock);
            }
            condition = false;
        }
    }
    if(condition){
        rocks.push_back(newRock);
    }
}

void sort_rocks(vector<Rock> &rocks){
    //cout << "sort rocks " << endl;
    ComparatorRocks cmp;

    for (vector<Rock>::iterator i = rocks.begin() + 1; i < rocks.end(); ++i){
        Rock x = *i;
        vector<Rock>::iterator j = i - 1;
        while( j >= rocks.begin() and cmp(x,*j)){

            *(j+1) = *j;
            j--;
        }
        *(j+1) = x;
    }
}

void runSimulation(vector<Rock> &rocks, Rock &r0, ComparatorRocks cmp, bool &survive){
    Rock firstRock = *rocks.begin();
    if(cmp(firstRock,r0)){
        r0.setSize(r0.getSize()+firstRock.getSize());
        cout << firstRock << " was absorbed" << endl;
        // remove first rock from rocks vector
        rocks.erase(rocks.begin());
    }
    else{
        // first rock is bigger than r0. r0 did not survive
        cout << r0 << " was destroyed by colliding with " << firstRock <<endl;
        survive = false;
        rocks.clear();

    }
}

void printRocks(vector<Rock> &rocks, Rock &r0){
    cout <<"----- printing rocks ------- " << endl;
    for (vector<Rock>::iterator i = rocks.begin(); i < rocks.end(); ++i){
        cout << *i << endl;
    }
    cout << "r0 " << r0 << endl;
    cout <<"------------ " << endl;
}

int main(){
    // creating rock 0
    cout << "Enter the values for Rock 0 : " ;
    string rock0_name;
    double rock0_size;
    cin >> rock0_name >> rock0_size ;
    Rock r0(rock0_name, rock0_size);

    // creating rocks vector
    cout << "Enter the number of other rocks in the asteroid field : " ;
    int numberOfOtherRocks;
    cin >> numberOfOtherRocks;

    cout << "Enter the values for the other rocks" << endl;
    vector<Rock> rocks;
    for(int i = 0 ; i < numberOfOtherRocks ; i++){
        string rock_name;
        double rock_size;
        cout << "enter " << i << " ";
        cin >> rock_name >> rock_size;
        Rock rn(rock_name, rock_size);
        rocks.push_back(rn);
    }
    // sort rocks
    sort_rocks(rocks);

    // run simulations
    bool condition = true;
    bool survive = true;
    while (condition) {
        printRocks(rocks, r0);
        cout << "P - Progress the simulation \nA - Add another rock \nC - Complete the simulation \nEnter your choice: " << endl;
        char userChoice;
        cin >> userChoice;
        ComparatorRocks cmp;
        if(userChoice == 'P'){
            // progress the simulation
            runSimulation(rocks,r0,cmp, survive);
        }
        else if(userChoice == 'A'){
            // add another rock
            cout << "Enter the values for the new rock: ";
            string rock_name;
            double rock_size;
            cin >> rock_name >> rock_size;
            Rock rn(rock_name, rock_size);
            insert(rocks,rn, cmp);
            condition = true;
        }
        else if(userChoice == 'C'){
            // Complete the simulation
            condition = false;
            while(!rocks.empty()){
                runSimulation(rocks,r0,cmp, survive);
            }
        }
        else{
            // wrong input
            cout << "it was wrong input. Please enter new user input" << endl;
            condition = true;
        }

        // check termination conditions
        if(!survive){
            condition = false;
        }
        else if(rocks.empty()){
            condition = false;
        }
    }

    if (survive){
        cout << "Yes: " << r0 << " has survived"<< endl;
    }
    else{
        cout << "No: " << r0 << " did not survive" << endl;
    }
}


