// Mina Moslehpour
// Section #3

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void readBooks(vector<Book *> & myBooks);
int readPersons(vector<Person *> & myCardholders);


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


// repeated part: asking user card ID
int askCardID(vector<Person *> myCardholders) {

	int cardNo = 0;

	cout << "Please enter the card ID: " << endl;
	cin >> cardNo;

	for (int i = 0; i < myCardholders.size(); i++) {

		if (myCardholders[i]->getId() == cardNo) {
			return cardNo;
		}

		else if (cardNo == NULL) {
			cout << "Card ID not found. " << endl;
			return nullptr;
		}
	}

}

// repeated part: asking user book ID
int askBookID(vector<Book *> myBooks) {

	int id;

	cout << "Please enter the book ID: " << endl;
	cin >> id;

	for (int i = 0; i < myBooks.size(); i++) {
		if(myBooks[i] -> getId() == id) {
			return id;
		}
		else if (id == NULL) {
			cout << "Book ID not found. " << endl;
			return nullptr;
		}
	}
}



void readBooks(vector<Book *> & myBooks) {

    int id;
    string bookName, auth, cat;

    // read book.txt
    ifstream file;
    file.open("books.txt");

    // if fail to open file
    if (!file) {
        cout << "Unable to open file. " << endl;
        exit(1);
    }

    // read data in file
    while (file >> id >> bookName >> auth >> cat) {
        Book * b;
        b = new Book(id, bookName, auth, cat);
        myBooks.push_back(b); // save all data to end of vector

    }
    file.close();

    return;
}



int readPersons(vector<Person *> & myCardholders) {

    string fName, lName;
    int cardNo;
    bool act;

    Person * personPtr = nullptr;

    ifstream file;
    file.open("persons.txt");

    if (!file) {
        cout << "Unable to open file. " << endl;
        exit(1);
    }

    int temp = 0;

    while (file >> fName >> lName >> cardNo >> act) {
        Person * personPtr;
        personPtr = new Person (fName, lName, cardNo, act);
        myCardholders.push_back(personPtr);

    }
    file.close();


    return 0;
}



void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {

    int id, cardNo;
    Person * personPtr = nullptr;


    ifstream file;
    file.open("rentals.txt");

    if(!file) {
        cout << "Unable to open file. " << endl;
        exit(1);
    }

    while (file >> id >> cardNo) {
    	for (int i = 0; i < myCardholders.size(); i++) {

    		if (myCardholders[i]->getId() == cardNo) {
    			personPtr = myCardholders[i];
    		}
    	}

    }

    for (int i = 0; i < myBooks.size(); i++) {
    	if (myBooks[i]->getId() == id) {
    		myBooks[i]->setPersonPtr(personPtr);
    	}
    }

    file.close();
    return;
}

// 1. book chechout
void bookCheckout(vector<Book *> myBooks, vector<Person *> myCardholders) {
	
	Person * personPtr = askCardID(myCardholders);

	if (personPtr != NULL) {
		Book * b = searchBook(myBooks, askBookID(myBooks));
	}

	for (int i = 0; i < myBooks.size(); i++) {
		if (myBooks[i] -> getId() == id) {
			if (myBooks[i] -> getPersonPtr() != NULL) {
				cout << "Book already checked out. " << endl;
				return;
			}
		}
	}

	for (int i = 0; i < myBooks.size(); i++) {
		if (id == myBooks[i]->getId()) {
			cout << "Title: "<< myBooks[i]->getTitle() << endl;
			myBooks[i]->setPersonPtr(personPtr);
			cout << "Rental Completed. " << endl;
		}
	}

}

// 2. book return
void bookReturn(vector<Book *> myBooks) {

	Person * personPtr = askBookID(myBooks);

	for (int i = 0; i < myBooks.size(); i++) {
		if (id == myBooks[i]->getId()) {
			cout << "Titile: " << myBooks[i] -> getTitle() << endl;
			myBooks[i] -> setPersonPtr(personPtr);
			cout << "Return Completed. " << endl;
		}		
		else {
			cout << "Book was not checked out. " << endl;
		}
	}

}

// 3. view all availble book
void availbleBook(vector<Book *> myBooks) {

	for (int i = 0; i < myBooks.size(); i++) {
		if (myBooks[i] -> getPersonPtr() == nullptr) {
			cout << "Book ID: " << myBooks[i]->getId() << endl;
			cout << "Title: " << myBooks[i] -> getTitle() << endl;
			cout << "Author: " << myBooks[i] -> getAuthor() << endl;
			cout << "Category: " << myBooks[i] -> getCategory() << endl;
		}
	}
	if (myBooks[i] == 0) {
		cout << "No availble books. " << endl;
	}
}

// 4. view all outstanding rentals
void outstandingRental (vector<Book *> myBooks) {

	int count = 0;

	for (int i = 0; i < myBooks.size(); i++) {
		if (myBooks[i] -> getPersonPtr() != nullptr) {
			cout << "Book ID: " << myBooks[i] -> getId() << endl;
			cout << "Titile: " << myBooks[i] -> getTitle() << endl;
			cout << "Author: " << myBooks[i] -> getAuthor() << endl;
			cout << "Cardholder: " << myBooks[i] -> getPersonPtr() -> fullName() << endl;
			cout << "Card ID: " << myBooks[i] -> getId() << endl;

			count++;
		}
	}
	if (count == 0) {
		cout << "No outstanding rentals. " << endl;
	}
}

// 5. view outstanding rental for a cardholder
void cardholderOutstanding (vector<Book *> &myBooks, vector<Person *> &myCardholders) {
	int count = 0

	Person * personPtr = askCardID(myCardholders);

	for (int i = 0; i < myBooks.size(); i++) {
		if (myBooks[i] -> getPersonPtr() != nullptr) {
			cout << "Book ID: " << myBooks[i]->getId() << endl;
			cout << "Title: " << myBooks[i] -> getTitle() << endl;
			cout << "Author: " << myBooks[i] -> getAuthor() << endl;

			cout ++;
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

	Person * newCard = new Person(nextID, true, fName, lName);
	myCardholders.push_back(newCard);

	cout << "Card ID " << nextID << " active" << endl;
	cout << "Cardholder: " << fName << " " << lName << endl;


    return;
}

// 7. close library card
void closeCard(vector<Person *> &myCardholders, int id) {

	char choice;

	Person * personPtr = askCardID(myCardholders);

	cout << "Please enter the card ID: " << endl;
	cin >> id;

	for (int i = 0; i < myCardholders.size(); i++) {

		if (personPtr -> isActive()) {
			cout << "Cardholder: " << myCardholders[i] -> fullName() << endl;
		}

		else {
			cout << "Are you sure you want to deavtiveate card? (y/n)? ";
			cin >> choice;

			if (choice == 'y' || choice == 'Y') {
				personPtr -> setActive(0);
				cout << "Card ID deactivated. " << endl;
			}
		}
	}

}

// 8. update
void update(vector<Book *> myCardholders, vetor<Book *> myBooks) {

	ofstream file;
	file.open("persons.txt");

	for (int i = 0; i < myCardholders.size(); i++) {
		file << myCardholders[i] -> getId();
		file << myCardholders[i] -> isActive();
		file << myCardholders[i] -> fullName();
		cout << endl;
	}
	file.close();

	ofstream file2;
	file2.open("rentals.txt");

	for (int i = 0; i < myBooks.size(); i++) {
		if (myBooks[i] -> getPersonPtr() != nullptr) {
			file2 << myBooks[i] -> getId();
			file2 << myBooks[i] -> getPersonPtr() -> getId();
			cout << endl;
		}
	}
	file2.close();
}




// search book
Book * searchBook(vector<Book *> myBooks, int id) {

	for (int i = 0; i < myBooks.size(); i++) {

		if(myBooks[i]->getId() == id) {
			return myBooks[i];
		}
	}
	cout << "Book ID not found. " << endl;
    return nullptr;
}



int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;

    int choice;
    int nextID;

    readBooks(books);
    readPersons(cardholders);
    nextID = readPersons(cardholders);
    

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
                break;

            case 7:
                close(cardholders);
                break;
                
            case 8:
                update(books, cardholders);

                cout << "Closing Program. " << endl;
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
