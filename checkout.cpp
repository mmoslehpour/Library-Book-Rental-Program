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

	if (personPtr != nullptr) {
		Book * b = searchBook(myBooks, askBookID(myBooks));
	}

	for (int i = 0; i < myBooks.size(); i++) {
		if (myBooks[i] -> getId() == id) {
			if (myBooks[i] -> getPersonPtr() != nullptr) {
				cout << "Book already checked out. " << endl;
				return;
			}
		}
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

    readBooks(books);
    readPersons(cardholders);
    
    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that 
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                break;

            case 4:
                // View all outstanding rentals
                break;

            case 5:
                // View outstanding rentals for a cardholder
                break;

            case 6:
                // Open new library card
                break;

            case 7:
                // Close library card
                break;
                
            case 8:
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
