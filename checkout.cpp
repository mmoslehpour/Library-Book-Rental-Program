// Mina Moslehpour
// Section #3

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;


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


// repeated part: searching for card number
Person *searchPerson (vector<Person *> &myCardholders, int cardNo) {


  //cout << "size of myCardholders(searchPerson): "<< myCardholders.size();

  for (int i = 0; i < myCardholders.size(); i++) {

   // cout << myCardholders[i]->getId() ;

    if (myCardholders.at(i)->getId() == cardNo) {
      cout << "Cardholder: " << myCardholders.at(i)->fullName() << endl;

      return myCardholders.at(i);
    }
  }
  return nullptr;
}

// repeated part: searching for book ID
Book *searchBook (vector<Book *> &myBooks, int id) {

  for (int i = 0; i < myBooks.size(); i++) {

   // cout << myCardholders[i]->getId() ;

    if (myBooks.at(i)->getId() == id) {
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      return myBooks.at(i);
    }

  }
  return nullptr;

}

// reading info inside Book
void readBooks(vector<Book *> & myBooks) {

    int id;
    string bookName, auth, cat, empty;

    // read book.txt
    ifstream file;
    file.open("books.txt");

    // if fail to open file
    if (!file) {
        cout << "Unable to open file. " << endl;
        exit(1);
    }

    // read data in file
    while (file >> id) {

      getline(file, empty);
      getline(file, bookName);
      getline(file, auth);
      getline(file, cat);
      getline(file, empty);
      Book * bookPtr;
      bookPtr = new Book(id, bookName, auth, cat);
      myBooks.push_back(bookPtr); // save all data to end of vector

    }

  //  cout << "size of myBooks: "<< myBooks.size();


    file.close();

    return;
}


// reading info inside person
int readPersons(vector<Person *> & myCardholders) {

    string fName, lName;
    int cardNo, nextID;
    bool act;

    Person * personPtr = nullptr;

    ifstream file;
    file.open("persons.txt");

    if (!file) {
        cout << "Unable to open file. " << endl;
        exit(1);
    }


    while (file >> cardNo >> act>> fName >> lName ) {
        personPtr = new Person (cardNo,act, fName, lName);
        myCardholders.push_back(personPtr);
        nextID = cardNo +1;

    }

 //  cout << "size of myCardholders(readPerson): "<< myCardholders.size();

    personPtr = NULL;
    file.close();

    return nextID;
}



void readRentals(vector<Book *> & myBooks, vector<Person *>& myCardholders) {

    int id, cardNo;
    Person * personPtr = nullptr;


    ifstream file;
    file.open("rentals.txt");

    if(!file) {
        cout << "Unable to open file. " << endl;
        exit(1);
    }

    while (file >> id >> cardNo) {
      searchBook(myBooks, id)->setPersonPtr(searchPerson(myCardholders, cardNo));
    }


    file.close();
    return;
}

// 1. book chechout
void bookCheckout(vector<Book *> &myBooks, vector<Person *> &myCardholders) {
  
 // int askcard= 0;
  int id, cardNo;

//  cout << "size of myCardholders(bookCheckout): "<< myCardholders.size();
  cout << "Please enter the card ID: ";
  cin >> cardNo;

  Person *personPtr = searchPerson(myCardholders, cardNo);


  if (personPtr==nullptr) {
      cout << "Card ID not found. ";
      return;
  } 


  cout << "Please enter the book ID: ";
  cin >> id;

  Book *bookPtr = searchBook(myBooks, id);


  if (bookPtr==nullptr) {
      cout << "Book ID not found. ";
      return;
  } 


  // use -> to dereference the pointer
 //  cout Invalid book , and return
  // cout << personPtr -> getId();

  // bookPointer

  for (int i = 0; i < myBooks.size(); i++) {
    if (myBooks.at(i)->getId() == id) {  // search to see if match
      if (myBooks.at(i)->getPersonPtr() == nullptr) {  // bookPter // PersonPtr
        cout << "Rental Completed. " << endl;
      }
        cout << "Book already checked out. ";
    }
  }
}

// 2. book return
void bookReturn(vector<Book *>& myBooks) {

  int id;

  cout << "Please enter the book ID to return: ";
  cin >> id;

  Book *bookPtr = searchBook(myBooks, id);

  for (int i = 0; i < myBooks.size(); i++) {
    if (myBooks[i]->getId() ==  id) {
     // cout << "Titile: " << myBooks[i] -> getTitle() << endl;
      myBooks.at(i)->setPersonPtr(nullptr);
      cout << "Return Completed. " << endl;
      return;
    }   
  }
}

// 3. view all availble book
void availbleBook(vector<Book *>& myBooks) {

  for (int i = 0; i < myBooks.size(); i++) {
    if (myBooks.at(i)->getPersonPtr() == nullptr) {  // BookPtr deReference personPtr set it to null cause we dont want it point it to person
      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
      cout << "Category: " << myBooks.at(i)->getCategory() << endl;
    }

    else if (myBooks.at(i) == 0) {
    cout << "No availble books. " << endl;
    }
  }

}

// 4. view all outstanding rentals
void outstandingRental (vector<Book *> &myBooks) {

  int count = 0;

  for (int i = 0; i < myBooks.size(); i++) {
    if (myBooks.at(i)->getPersonPtr() != nullptr) {
      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Titile: " << myBooks.at(i)->getTitle() << endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
      cout << "Cardholder: " << myBooks.at(i)->getPersonPtr()->fullName() << endl;
      cout << "Card ID: " << myBooks.at(i)->getId() << endl;

      count++;
    }
  }
  if (count == 0) {
    cout << "No outstanding rentals. " << endl;
  }
}

// 5. view outstanding rental for a cardholder
void cardholderOutstanding (vector<Book *> &myBooks, vector<Person *> &myCardholders) {
  int count = 0;
  int cardNo;

  cout << "Please enter the card ID: ";
  cin >> cardNo;

  Person *personPtr = searchPerson(myCardholders, cardNo);

  for (int i = 0; i < myBooks.size(); i++) {
    if (myBooks.at(i)->getPersonPtr() != nullptr) {
      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;

      count++;
    }
  }

  if (count == 0 ) {
    cout << "No books currently checked out. " << endl;
  }
}


// 6. open new library card
void openCard(vector<Person *> & myCardholders, int nextID) {

  string fName, lName;
  Person * personPtr = nullptr;
  bool act = 1;

  cout << "Please enter the first name: " << endl;
  cin >> fName;
  cout << "Please enter the last name: " << endl;
  cin >> lName;

  personPtr = new Person(nextID, true, fName, lName);
  myCardholders.push_back(personPtr);

  cout << "Card ID " << nextID << " active" << endl;
  cout << "Cardholder: " << fName << " " << lName << endl;
}

// 7. close library card
void closeCard(vector<Person *> &myCardholders) {

  char choice;
  int cardNo;


  cout << "Please enter the card ID: " << endl;
  cin >> cardNo;

  Person *personPtr = searchPerson(myCardholders, cardNo);


  for (int i = 0; i < myCardholders.size(); i++) {

    if (myCardholders.at(i)->isActive()) {
      cout << "Cardholder: " << myCardholders.at(i)->fullName() << endl;
    }

    else {
      cout << "Are you sure you want to deavtiveate card? (y/n)? ";
      cin >> choice;

      if (choice == 'y' || choice == 'Y') {
        myCardholders.at(i)->setActive(0);
        cout << "Card ID deactivated. " << endl;
      }
    }
  }

}

// 8. update
void update(vector<Book *> &myBooks, vector<Person *> &myCardholders) {

  ofstream file;
  file.open("persons.txt");

  for (int i = 0; i < myCardholders.size(); i++) {
    file << myCardholders.at(i)->getId();
    file << myCardholders.at(i)->isActive();
    file << myCardholders.at(i)->fullName();
  }
  file.close();

  ofstream file2;
  file2.open("rentals.txt");

  for (int i = 0; i < myBooks.size(); i++) {
    if (myBooks.at(i)->getPersonPtr() != nullptr) {
      file2 << myBooks.at(i)->getId();
      file2 << myBooks.at(i)->getPersonPtr()->getId();
    }
  }
  file2.close();
}



int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;

    int choice;
    int nextID;

    readBooks(books);
    // readPersons(cardholders);
    nextID = readPersons(cardholders);
    readRentals(books, cardholders);
    
    // use a loop to clean up dynamic memory all the -> (NEW)

    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that 
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                bookCheckout(books, cardholders);
                break;

            case 2:
                bookReturn(books);
                break;

            case 3:
                availbleBook(books);
                break;

            case 4:
                outstandingRental(books);
                break;

            case 5:
                cardholderOutstanding(books, cardholders);
                break;

            case 6:
                openCard(cardholders, nextID);
                nextID++;
                break;

            case 7:
                closeCard(cardholders);
                break;
                
            case 8:
                update(books, cardholders);

                cout << "File Updated, Exiting Program . . . " << endl;
                break;

            default:
                cout << "Invalid Entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}