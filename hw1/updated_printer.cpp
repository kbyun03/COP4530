// Young0Bin Byun
// FSUID: YB23E
// EMPLID: 201093220

// to reference of iterator object &(*it)
// document's user can be implemented as User Class



#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iterator>

using namespace std;

class Document{
public:
    Document(){
        name = "";
        user = "";
        pages = 0;
        status = false; // true -- canceled, false -- not canceled
    }
    Document(string n, string u, int p, bool s){
        name = n;
        user = u;
        pages = p;
        status = s;
    }

    string getName() const{
        return name;
    }
    string getUser() const{
        return user;
    }
    int getPages() const{
        return pages;
    }
    bool getStatus() const{
        return status;
    }

    void setName(string n){
        name = n;
    }
    void setUser(string u){
        user = u;
    }
    void setPages(int p){
        pages = p;
    }
    void setStatus(bool s){
        status = s;
    }

    friend ostream &operator<<( ostream &output, const Document &D){
        output << D.getName() << ":" << D.getUser() << ":" << D.getPages() << ":" << D.getStatus() << "\n";
        return output;
    }

    friend istream &operator>>( istream &in, Document &D){
        in >> D.name >> D.user >> D.pages;
        return in;
    }

private:
    string name;
    string user;
    int pages;
    bool status;

};

class User{
public:
    User(){
        userName = "";
        totalPages = 0;
    }
    User(string un, int tp){
        userName = un;
        totalPages = tp;
    }

    string getUserName() const{
        return userName;
    }
    int getTotalPages() const{
        return totalPages;
    }

    void setUserName(string un){
        userName = un;
    }
    void setTotalPages(int tp){
        totalPages = tp;
    }

    friend ostream &operator<<( ostream &output, const User &U){
        output << U.getUserName() << ": " << U.getTotalPages() << "\n";
        return output;
    }

    friend istream &operator>>( istream &in, User &U){
        in >> U.userName >> U.totalPages;
        return in;
    }

private:
    string userName;
    int totalPages;

};

bool checkQueue(deque<Document*> jobs){
    if(jobs.empty()){
        // end while loop
        return false;
    }
    for (deque<Document*>::iterator i = jobs.begin(); i < jobs.end(); ++i){
        Document* thisDoc= *i;
        if( !(thisDoc->getStatus()) ){
            // if any of the documents are NOT canceled and if it is in the queue, then continue
            return true;
        }
    }
    // all the documents in jobs are canceled
    return false;
}

bool printFinal(vector<User> users){
    cout << "User Totals:" << endl;
    for (vector<User>::iterator i = users.begin(); i < users.end(); ++i){
        cout << *i << endl;
    }
}

void printQueue(deque<Document*> &jobs){
    cout <<"----- printing jobs ------- " << endl;
    for (deque<Document*>::iterator i = jobs.begin(); i < jobs.end(); ++i){
        cout << *i << endl;
        cout << "here1" << endl;
        Document ptr = **i;
//        cout << "here1" << ptr.getName() << endl;

    }
    cout <<"------------ " << endl;
}

void printUsers(vector<User> &users){
    cout <<"----- printing users ------- " << endl;
    for (vector<User>::iterator i = users.begin(); i < users.end(); ++i){
        cout << *i << endl;
    }
    cout <<"------------ " << endl;
}

// User& findUser(vector<User> &users, User &un){
//     for (vector<User>::iterator i = users.begin(); i < users.end(); ++i){
//         if(i->getUserName() == un.getUserName()){
//             return &(*i);
//         }
//     }
//     cout << "create user object in vector" << endl;
//     users.push_back(un);
//     return un;
// }

vector<User>::iterator findUser(vector<User> &users, string un){
    for (vector<User>::iterator i = users.begin(); i < users.end(); ++i){
        if(i->getUserName() == un){
            cout << "Found User" << endl;
            return i;
        }
    }
    cout << "create user object in vector" << endl;
    User newUser(un, 0);
    users.push_back(newUser);
    return users.end() -1;
}

void updateUserPage(vector<User> &users, string un, int pages){
    cout << "here" << endl;
    for (vector<User>::iterator i = users.begin(); i < users.end(); ++i){
        if(i->getUserName() == un){
            cout << "found user" << endl;
            i->setTotalPages(i->getTotalPages() + pages);
            return;
        }
    }
    cout << "create user" << endl;
    User newUser(un, pages);
    users.push_back(newUser);
    return ;

}

void progress(deque<Document*> &jobs, vector<User> &users){
    int currentPageCount = 0;

    while ((currentPageCount < 8) && (! jobs.empty())){
        Document* front = jobs.front();
        // User thisUser = *(findUser(users, front.getUser()));

        cout << "progress document is "<< front;

        if (currentPageCount + front->getPages() <= 8){
            currentPageCount += front->getPages();
            jobs.pop_front();
            cout << "here000 " << endl;
            string userName = front->getUser();
            cout << "here111 " << endl;
            updateUserPage(users, "userName", front->getPages());
        }
//        else{
//            int pageCount = 8 - currentPageCount;
//            int rest = front.getPages() - pageCount;
//            front.setPages(rest);
//            updateUserPage(users, front.getUser(), 8);
//            currentPageCount = 8;
//        }
        cout << "after processing " << endl;
        printQueue(jobs);
        printUsers(users);
    }

}

int main(){
    vector<User> users;
    deque<Document*> jobs;
    int numberOfJobs;
    cout << "Enter the number of Jobs in the Queue: " ;
    cin >> numberOfJobs;

    cout << "Enter the jobs " ;
    for(int i = 0; i < numberOfJobs ; i++){
        Document d;
        cin >> d;
        cout << "job entered : " << d << "," << &d <<endl;
        jobs.push_back(&d);
    }
    int totalTime = 0;
    bool condition = true;
    while (condition){
        printQueue(jobs);
        printUsers(users);
        cout << "A - Add a new job \nC - Cancel a Job \nN - print next \nEnter your choice: ";
        char userChoice;
        cin >> userChoice;

        if(userChoice == 'A'){
            //adding jobs
            Document newDocument;
            cout << "Enter the job: " ;
            cin >> newDocument;
            jobs.push_back(&newDocument);
        }
        else if(userChoice == 'C'){
            // cancel job
        }
        else if(userChoice == 'N'){
            // continue
            cout << "progressing" << endl;
            progress(jobs, users);
        }
        else if(userChoice == 'T'){
            condition = false;
        }
        condition = checkQueue(jobs);
    }
    cout << "Queue cleared" << endl;
    printFinal(users);

}