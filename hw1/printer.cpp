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
        cout << *i;
    }
}

void printQueue(deque<Document*> &jobs){
    cout <<"----- printing jobs ------- " << endl;
    for (deque<Document*>::iterator i = jobs.begin(); i < jobs.end(); ++i){
        cout << **i << endl;
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

Document* findJob(deque<Document*> &jobs, string dn){
    for (deque<Document*>::iterator i = jobs.begin(); i < jobs.end(); ++i){
        if((*i)->getName() == dn){
//            cout << "Found Document" << endl;
            return *i;
        }
    }
    // if document is not found then return nullptr
    return NULL;
}

deque<Document*>::iterator findJobIterator(deque<Document*> &jobs){
    // find first job that is not canceled
    for (deque<Document*>::iterator i = jobs.begin(); i < jobs.end(); ++i){
        if( !((*i)->getStatus()) ){
            // if any of the documents are NOT canceled and if it is in the queue, then return the document
            return i;
        }
    }
    // if document is not found then return nullptr
    return jobs.end();
}

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
    for (vector<User>::iterator i = users.begin(); i < users.end(); ++i){
        if(i->getUserName() == un){
//            cout << "found user" << endl;
            i->setTotalPages(i->getTotalPages() + pages);
            return;
        }
    }
//    cout << "create user" << endl;
    User newUser(un, pages);
    users.push_back(newUser);
    return ;

}

void cancelJob(deque<Document*> &jobs, string jobName, deque<Document*> &finishedJobs){
    Document* doc= findJob(jobs, jobName);
    if (doc){
        // found document in the current queue
        if (doc->getStatus() == false){
            doc->setStatus(true);
            cout << "Job Canceled" << endl;
        }
        else{
            cout << "Error: Document already canceled" << endl;
        }
    }
    else{
        // check if document is already printed
        doc = findJob(finishedJobs, jobName);
        if (doc){
            cout << "Error: Document already printed" << endl;
        }
        else{
            cout << "Error: Document was not found" << endl;
        }
    }

}

void progress(deque<Document*> &jobs, vector<User> &users, deque<Document*> &finishedJobs){
    int currentPageCount = 0;

    while ( (currentPageCount < 8) && (checkQueue(jobs)) ){
        // deque<Document*>::iterator frontIterator = findJobIterator(jobs);
        // Document* front = *(frontIterator);
        Document* front = jobs.front();
        if (front->getStatus() == false){
            // the document is not canceled
            // cout << "progress document is "<< *front;
            if (currentPageCount + front->getPages() <= 8){
                currentPageCount += front->getPages();
                jobs.pop_front();
                // jobs.erase(frontIterator);
                updateUserPage(users, front->getUser(), front->getPages());

                // if finished, save it into the finishedJobs queue for later
                finishedJobs.push_back(front);
            }
            else{
                // if current page count and job's pages exceed limit
                int pageCount = 8 - currentPageCount; // how many pages we are going to process during this turn
                int rest = front->getPages() - pageCount; // rest of the pages left in current job
                front->setPages(rest); // set rest of pages to current job
                updateUserPage(users, front->getUser(), pageCount); // user's total count is going to get up by pageCount
                currentPageCount = 8;
            }
        }
        else{
            jobs.pop_front();
        }

        
    //    cout << "after processing " << endl;
    //    printQueue(jobs);
//        printUsers(users);
    }

}

int main(){
    vector<User> users;
    deque<Document*> jobs;
    deque<Document*> finishedJobs;

    int numberOfJobs;
    cout << "Enter the number of Jobs in the Queue: " ;
    cin >> numberOfJobs;

    cout << "Enter the jobs " ;
    for(int i = 0; i < numberOfJobs ; i++){
        Document *d = new Document() ;
        cin >> *d;
//        cout << "job entered : " << *d <<endl;
        jobs.push_back(d);
    }

    int totalTime = 1;
    bool condition = true;

    progress(jobs, users, finishedJobs);
    while (condition){
        totalTime += 1;
//        printQueue(jobs);
//        printUsers(users);
        cout << "\nA - Add a new job \nC - Cancel a Job \nN - print next \nEnter your choice: " << endl;
        char userChoice;
        cin >> userChoice;

        if(userChoice == 'A'){
            //adding jobs
            Document *newDocument = new Document();
            cout << "Enter the job: " ;
            cin >> *newDocument;
            jobs.push_back(newDocument);
            progress(jobs, users, finishedJobs);
        }
        else if(userChoice == 'C'){
            // cancel job
            string jobName;
            cout << "Enter the document name: ";
            cin >> jobName;
            cancelJob(jobs, jobName, finishedJobs);
            progress(jobs, users, finishedJobs);
        }
        else if(userChoice == 'N'){
            progress(jobs, users, finishedJobs);
            // cout << "progressing" << endl;
        }
        else{
            continue;
        }

        condition = checkQueue(jobs);
    }
    cout << "\nQueue cleared" << endl;
    cout << "Total time: " << totalTime <<endl;
    printFinal(users);

}
