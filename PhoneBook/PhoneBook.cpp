#include "PhoneBook.h"

/*
* checkphonenum -  a function that checks if the phone number is
* equal zero and all numbers only no letters for special characters.
* the function is called in add entry.
* @phone:  phone number to be checked
*
* Return: the function returns 1 on success and 0 on failing.
*/
bool checkphonenum(string phone)
{
    if (phone.length() != 11)
    {
        return false;
    }

    for (char digit : phone)
    {
        if (digit < '0' || digit > '9')
        {
            return false;
        }
    }

    return true;
}

// class methods
void PhoneBook::setSize(int size)
{
    phoneBookSize = size;
    names =  new string[phoneBookSize];
    phones =  new string[phoneBookSize];
}
void PhoneBook::copyPB(const PhoneBook &pb)
{
    names =  new string[phoneBookSize];
    phones =  new string[phoneBookSize];
    phoneBookSize = pb.phoneBookSize;

    for (int i = 0; i < phoneBookSize; i++)
    {
        names[i] = pb.names[i];
        phones[i] = pb.phones[i];
    }
}

bool PhoneBook::addEntry(string name, string phoneNumber)
{
    if (checkphonenum(phoneNumber))
    {
        for (int i = 0; i < phoneBookSize; i++)
        {
            if (names[i].empty() && phones[i].empty())
            {
                names[i] = name;
                phones[i] = phoneNumber;
                return true;
            }
        }
        cout << "Phone book is full. Cannot add more entries." << endl;
        return false;
    }
    cout << "Enter a valid phone number" << endl;
    return false;
}

void PhoneBook::displayAll()
{
    for (int i = 0; i < phoneBookSize; i++)
    {
        if (names[i] != "")
        {
            cout << "the name and the phone number of " << (i + 1) << " student is: " << endl;
            cout << "Name: " << names[i] << endl;
            cout << "Phone: " << phones[i] << endl;
        }
    }
}

bool PhoneBook::updateNameAt(string str, int index)
{
    if (index > phoneBookSize || str.empty())
        return false;
    names[index] = str;
    return true;
}

bool PhoneBook::updatePhoneAt(string num, int index)
{
    if (index > phoneBookSize || num.empty())
        return false;
    phones[index] = num;
    return true;
}

bool PhoneBook::displayEntryAtIndex(int index)
{
    if (index > phoneBookSize)
        return false;
    cout<<"name:"<<names[index]<<endl;
    cout<<"number:"<<phones[index]<<endl;
    return true;
}

int* PhoneBook::findByName(string name)
{
    int count = 0;
    int* check = new int[phoneBookSize];

    for (int i = 0; i < phoneBookSize; i++)
    {
        if (names[i] == name)
        {
            check[i] = 1;
            count++;
        }
        else
        {
            check[i] = 0;
        }
    }

    if (count == 0)
    {
        cout << "No matching entries found." << endl;
    }

    return check;
}

void PhoneBook::displayEntryAtIndices(int* check)
{
    for (int i = 0; i < phoneBookSize; i++)
    {
        if (check[i] == 1)
        {
            cout << "name: " << names[i] << endl;
            cout << "phone: " << phones[i] << endl;
        }
    }
}

string PhoneBook::findByPhone(string phone)
{
    for (int i = 0; i < phoneBookSize; i++)
    {
        if (phones[i] == phone)
        {
            displayEntryAtIndex(i);
            return names[i];
        }
    }
    cout << "No entry found for phone number: " << phone << endl;
    return "";
}

void PhoneBook::clear()
{
    delete[] names;
    delete[] phones;

    names = nullptr;
    phones = nullptr;
}
