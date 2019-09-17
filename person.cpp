#include "person.h"

Person::Person(int pid, bool act, string fName, string lName ) {
    firstName = fName;
    lastName = lName;
    //setActive(act);
    active = act;
    cardID = pid;
  //  fullName() = _fullname;
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
    active = act;
} // complete

bool Person::isActive() {
    if(active == 0) {
        return true;
    }
    else {
        return false;
    } // complete
}

string Person::fullName() {
    return firstName + " " + lastName; // complete
}
