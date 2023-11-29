#include "PhoneBook.h"

/*
* Main - Entry Point
*
* Return: O on (success)
*/
int main()
{
    int size, input;
    int *arr;
    PhoneBook Myphonebook, Myphonebook_copy;
    bool flag = true, check, check2;
    string flagstr, name, phonenumber;
    string update;
    bool check3 = true;
    string check4;
    string name_ser;
    string phone_ser;
    int r;

    cout <<"********************************************" << endl;
    cout <<"*                                          *" << endl;
    cout <<"*             WELCOME TO MY PROGRAM        *" << endl;
    cout <<"*                                          *" << endl;
    cout <<"********************************************" << endl;

    // gets phonebook size
    cout<<"Enter the size of phone book: "<<endl;
    cin>> size;
    Myphonebook.setSize(size);

    // fills the phonebook
    for (int i = 0; i < size; i++)
    {
        cout<< "Enter data for Person no." << (i + 1) <<endl;
        cout << "Name:" << endl;
        cin.ignore();
        getline(cin, name);
        cout << "Phone Number:" << endl;
        cin>> phonenumber;
        check = checkphonenum(phonenumber);
        check2 = Myphonebook.addEntry(name, phonenumber);
        if(!check2 && check)
        {
            cout<<"Failed to add entry!, array is full"<<endl;
            break;
        }
        while (!check)
        {
            cout << "Reenter a newphone number" <<endl;
            cin >>phonenumber;
            check = checkphonenum(phonenumber);
            Myphonebook.addEntry(name, phonenumber);
        }
    }

    // this keeps the program running UNTIL USER TYPES 8 "EXIT"
    while (flag)
    {
        cout << "1- Display all phone book\n"
         << "2- Search for entry/entries by name\n"
         << "3- Search for entry/entries by phone\n"
         << "4- Find an entry by index\n"
         << "5- Update name by index\n"
         << "6- Update phone by index\n"
         << "7- Copy phone book to another and display entries of the new phone book\n"
         << "8- Exit" << endl;
        cin>> input;
        switch (input)
        {
        case 1:
            Myphonebook.displayAll();
            break;
        
        case 2:
            while (check3)
            {
                cout<<"Enter Name you want to search: "<<endl;
                cin>>name_ser;
                arr = Myphonebook.findByName(name_ser);
                Myphonebook.displayEntryAtIndices(arr);
                cout << "do you wanna search for another name?"<<endl;
                cin>>check4;
                 if (check4 == "yes" || check4 == "YES" || check4 == "Yes")
                    check3 = true;
                else
                    check3 = false;
            }
            break;

        case 3:
            while (check3)
            {
                cout<<"Enter phone you want to search: "<<endl;
                cin>>phone_ser;
                Myphonebook.findByPhone(phone_ser);
                cout << "do you wanna search for another number?"<<endl;
                cin>>check4;
                 if (check4 == "yes" || check4 == "YES" || check4 == "Yes")
                    check3 = true;
                else
                    check3 = false;
            }
            break;

        case 4:
            cout<<"Enter the index to search"<<endl;
            cin>>r;
            Myphonebook.displayEntryAtIndex(r);
            break;

        case 5:
            cout<<"Enter the index to update the name"<<endl;
            cin>>r;
            cout<<"Enter the name you want to update"<<endl;
            cin.ignore();
            getline(cin, update);
            Myphonebook.updateNameAt(update, r);
            break;

        case 6:
            cout<<"Enter the index to update the phone number"<<endl;
            cin>>r;
            cout<<"Enter the phone number you want to update"<<endl;
            cin.ignore();
            getline(cin, update);
            Myphonebook.updatePhoneAt(update, r);
            break;
            
        case 7:
            Myphonebook_copy.copyPB(Myphonebook);
            Myphonebook_copy.displayAll();
            break;

        case 8:
            Myphonebook.clear();
            break;

        default:
            break;
        }

        if (input == 8)
        {
            cout <<"********************************************" << endl;
            cout <<"*                                          *" << endl;
            cout <<"*     THANK YOU FOR USING MY PROGRAM       *" << endl;
            cout <<"*                                          *" << endl;
            cout <<"********************************************" << endl;
            break;
        }
        else
        {
            cout<< "if you want to continue type yes"<<endl;
            cin>> flagstr;
            if (flagstr == "yes" || flagstr == "YES" || flagstr == "Yes")
                flag = true;
            else
                flag = false;
        }
    }

Myphonebook.clear();
return 0;
}
