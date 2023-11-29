#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/* 
*PhoneBook -  a class that contains 2 private Parrallel
* dynamic arrays and methods on them.
* @names: user names.
* @phones: phone numbers of users.
* @phoneBookSize: size of both dynamic arrays.
*/
class PhoneBook
{
private:

    string* names;
    string* phones;
    int phoneBookSize;
public:

    void setSize(int);
    void copyPB(const PhoneBook&);
    bool addEntry(string ,string);
    void displayAll();
    bool displayEntryAtIndex(int);
    void displayEntryAtIndices(int*);
    int* findByName(string);
    string findByPhone(string);
    bool updateNameAt(string, int);
    bool updatePhoneAt(string, int);
    void clear();
};
