//
//  main.cpp
//  Library Book Rental
//
//  Created by Mina Moslehpour on 8/4/19.
//  Copyright © 2019 Mina Moslehpour. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.h"
#include "book.h"

using namespace std;

Book *searchBook(vector<Book* > myBooks, int bid) {
    for (int i = 0; i < myBooks.size(); i++) {
        if(myBooks.at(i)->getBid() == bid) {
            cout << "Book Title: " << myBooks.at(i)->getTitle() << endl;
            return myBooks.at(i);
        }
    }
    return nullptr;
}

Person *searchPerson(vector<Person *> myCardholers, int pid) {
    for (int i = 0; i < myCardholers.size(); i++) {
        if(myCardholers.at(i)->getId() == pid) {
            cout << "Cardholder Name : " << myCardholers.at(i)->fullName() << endl;
            return myCardholers.at(i);
        }
    }
    return nullptr;
}

int askBookID(vector<Book*> myBooks) {
    int bid;
    cout << "Please Enter The Book ID: ";
    cin >> bid;
    
    Book *bookptr = searchBook(myBooks, bid);
    if (bookptr == nullptr) {
        cout << "Book ID not found. " << endl;
        return NULL;
    }
    return bid;
}

int askPersonID(vector<Person *> myCardholders) {
    int pid;
    cout << "Please Enter Your Card ID: ";
    cin >> pid;
    
    Person *personptr = searchPerson(myCardholders, pid);
    if (personptr == nullptr) {
        cout << "Cardholder ID not found. " << endl;
        return NULL;
    }
    return pid;
}

void readBooks(vector<Book* > &myBooks) {
    
    Book *bookptr;
    string title, author, catergory, sBookID;
    int bookID;
    
    ifstream file("books.txt");
    
    if (file.fail()) {
        cout << "cant open file. ";
    }
    
    while(!file.eof()) {
        getline(file, sBookID);
        getline(file, title);
        getline(file, author);
        getline(file, catergory);
        file >> ws;
        
        bookID = stoi(sBookID);
        bookptr = new Book(bookID, title, author, catergory);
        myBooks.push_back(bookptr);
    }
    //for (int i = 0; i < myBooks.size(); i++) {
   //     cout << "Titile: " << myBooks.at(i)->getTitle() << endl;
   // }
    file.close();
}

void readPerson(vector<Person* > &myCardholders, int &newID) {
    
    Person *personptr;
    int cardID;
    bool active;
    string firstName, lastName;
    
    ifstream file("persons.txt");
    
    while(!file.eof()) {
        file >> cardID >> active >> firstName >> lastName;
        personptr = new Person(cardID, active, firstName, lastName);
        myCardholders.push_back(personptr);
        newID++;
    }
  //  for (int i = 0; i < myCardholders.size(); i++) {
   //     cout << "Name: " << myCardholders.at(i)->fullName() << endl;
    //}
    cout << "new ID: " << newID << endl;
    file.close();
}

void readRentals(vector<Book*> &myBooks, vector<Person*> &myCardholders) {
    ifstream myFile("rentals.txt");
    
    int bookID, cardID;
    
    while(myFile >> bookID >> cardID) {
        searchBook(myBooks, bookID)->setPersonPtr(searchPerson(myCardholders, cardID));
    }
    myFile.close();
}



void bookCheckOut(vector<Book*> &myBooks, vector<Person*> &myCardholders) {
    int pid, bid;
    bid = askBookID(myBooks);
    pid = askPersonID(myCardholders);
    Person *personptr =  searchPerson(myCardholders, pid); // 找到personID在mycardholder的位置

    
    for (int i = 0; i < myBooks.size(); i++) {
        if(myBooks.at(i)->getBid() == bid) {
            if(myBooks.at(i)->getPersonPtr() == nullptr) {
                myBooks.at(i)->setPersonPtr(personptr); // ???
                cout << "Rental Completed. " << endl;
            }
            else {
                cout << "Sorry, Book Already checked Out. " << endl;
            }
        }
    }
    
    
}

void bookReturn(vector<Book*> &myBooks, vector<Person*> &myCardholders) {
    
 //   askPersonID(myCardholders, pid);
  //  askBookID(myBooks);
   // Person *personptr = nullptr;
    int pid, bid;
    bid = askBookID(myBooks);

  //  Person *personptr =  searchPerson(myCardholders, pid); // 找到personID在mycardholder的位置
    
    for (int i = 0; i < myBooks.size(); i++) {
        if(myBooks.at(i)->getBid() == bid) {
            if(myBooks.at(i)->getPersonPtr() == nullptr) {
                
                cout << "error, Book is not checked out." << endl;
            }
            
            else if(myBooks.at(i)->getPersonPtr() != nullptr) {
                pid = askPersonID(myCardholders);
                if(myBooks.at(i)->getPersonPtr()->getId() == pid) {
                    myBooks.at(i)->setPersonPtr(nullptr);
                    cout << "Return Completed. " << endl;
                }
                else{
                    cout << "error, cardholder ID not matching with book ID. " << endl;
                }
            }
        }
    }
}


void availableBook(vector<Book*> &myBooks) {
    for (int i = 0; i < myBooks.size(); i++) {
        if(myBooks.at(i)->getPersonPtr() == nullptr) {
            cout << "Book ID: " << myBooks.at(i)->getBid() << endl;
            cout << "Title: " << myBooks.at(i)->getTitle() << endl;
            cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
            cout << "Category: " << myBooks.at(i)->getCategory() << endl;
            cout << endl;
        }
        else if (myBooks.size() == 0) {
            cout << "No availble Books. " << endl;
        }
    }
}

void outStandingRentals(vector<Book*> &myBooks) {
    for (int i = 0; i < myBooks.size(); i++) {
        if(myBooks.at(i)->getPersonPtr() != nullptr) {
            cout << "Cardholder Name: " << myBooks.at(i)->getPersonPtr()->fullName() << endl;
            cout << "Cardholder ID: " << myBooks.at(i)->getPersonPtr()->getId() << endl;
            cout << endl;
            
            cout << "Book ID: " << myBooks.at(i)->getBid() << endl;
            cout << "Title: " << myBooks.at(i)->getTitle() << endl;
            cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
            cout << "Category: " << myBooks.at(i)->getCategory() << endl;
            cout << endl;
        }
    }
}

void cardHolderRentals(vector<Book*> &myBooks, vector<Person*> &myCardholders) {
    int pid, bid;
 //   bid = askBookID(myBooks);
    pid = askPersonID(myCardholders);
    Person *personptr =  searchPerson(myCardholders, pid); // 找到personID在mycardholder的位置
    
    for (int i = 0; i < myBooks.size(); i++) {
        if(myCardholders.at(i)->getId() == pid) {
            
        }
    }

}

void openNewCard(vector<Person*> &myCardholders, int newID) {
    
    string fname, lname;
    bool act = true;
    
    cout << "Enter your first Name: ";
    cin >> fname;
    cout << "Enter your last name: ";
    cin >> lname;
    
    Person *personptr = new Person(newID, act, fname, lname);
    myCardholders.push_back(personptr);
    
    cout << "Cardholder ID: " << newID  << " " << fname << " " << lname << " is now activated. " << endl;
    
}

void closeCard(vector<Person*> &myCardholders) {
    
    char answer;
    int pid;
    pid = askPersonID(myCardholders);
    
    
    if(searchPerson(myCardholders, pid)->isActive()) {
        cout << "Are you sure you want to deactivate card (y/n)? ";
        cin >> answer;
        
        if(answer == 'y' || 'Y') {
            searchPerson(myCardholders, pid)->setActive(false);
            cout << "Card ID deactivated" << endl;
        }
        else if (answer == 'n' || 'N') {
            cout << "cancel current deactivation. " << endl;
        }
        else if (answer != 'y' || 'Y' || 'n' || 'N') {
            cout << "You must input either y or n" << endl;
        }
        

    } else {
        cout << "Card ID is already inactive" << endl;
        return;
    }
}

void update(vector<Book*> &myBooks, vector<Person*> &myCardholders) {
    
    ofstream file("persons.txt");
    for(int i = 0; i < myCardholders.size(); i++) {
        file << myCardholders.at(i)->getId() << " " << myCardholders.at(i)->isActive() << " " << myCardholders.at(i)->fullName() << endl;
    }
    file.close();
    
    ofstream file2("rentals.txt");
    for(int i = 0; i < myBooks.size(); i++) {
        if(myBooks.at(i)->getPersonPtr() != nullptr) {
            cout << myCardholders.at(i)->getId() << " " << myBooks.at(i)->getBid() << endl;
        }
    }
    cout << "data updated . . ." << endl;
    file2.close();
    
}


void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

int main() {
    
    int choice;
    int newID = 1000;
    vector<Book *> books;
    vector<Person *> cardholders;
    
    readBooks(books);
    readPerson(cardholders, newID);
    readRentals(books, cardholders);
    
    do {
        printMenu();
        cin >> choice;
        cin.ignore();
        cout << endl;
        switch(choice) {
            case 1:
                bookCheckOut(books, cardholders);
                break;
               
            case 2:
                bookReturn(books, cardholders);
                break;
                
            case 3:
                availableBook(books);
                break;
                
            case 4:
                outStandingRentals(books);
                break;
                
            case 5:
                cardHolderRentals(books, cardholders);
                break;
                
            case 6:
                openNewCard(cardholders, newID);
                break;
                
            case 7:
                closeCard(cardholders);
                break;
                
            case 8:
                update(books, cardholders);
                return 0;
                
            default:
                cout << "Invalid Entry, Please Try Again. " << endl;
                break;
        }
        cout << endl;
    } while (choice != 8);
    return 0;
}
