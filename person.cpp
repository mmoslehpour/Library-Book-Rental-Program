#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName) {
    firstName = fName;
    lastName = lName;
    setActive(act);
    cardID = cardNo;
    // complete constructor
}

string Person::getFirstName() {
    return firstName; // complete
}

string Person::getLastName() {
    return lastName; // complete
}

int Person::getId() {
    return cardID; // complete
}

void Person::setActive(bool act) {
} // complete

bool Person::isActive() {
    return true; // complete
}

string Person::fullName() {
    return firstName + " " + lastName; // complete
}
