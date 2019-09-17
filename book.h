//begin book.h
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "person.h"

class Book
{
private:
    string   title;
    string   author;
    string   category;
    int      bookID;
    Person * personPtr = nullptr;

public:
    Book(int bid, string bookName, string auth, string cat);
    string   getTitle();
    string   getAuthor();
    string   getCategory();
    int      getBid();
    void     setPersonPtr(Person * ptr);
    Person * getPersonPtr();
};
#endif // end book.h

