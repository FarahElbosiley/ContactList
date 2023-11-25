#include "ContactList.h"
#include <string>
#include <iostream>
using namespace std;

Contact::Contact (){ }

Contact::Contact (string firstname,string lastname, string phoneNum, string email, string address)
{
    firstname = firstname;
    lastname = lastname
    phoneNum = phoneNum;
    email = email;
    address = address;
}

string Contact::getFirstName (string fname)
{
    return firstname;
}
string Contact::getLasttName (string lname)
{
    return lastname;
}
string Contact::getPhoneNum  (string PhoneNumber)
{
    return phoneNum;
}
string Contact::getEmail (string email)
{
    return email;
}
string Contact::getAddress (string address)
{
    return address;
}

void Contact::setFirstName  (string fname)
{
    firstname = fname;
}
void Contact::setLastName  (string lname)
{
    lastname = lname;
}
void Contact::setPhoneNum (string phoneNumber) 
{
    phoneNum = phoneNumber;
}
void Contact::setEmail (string email) 
{
    email = email;
}
void Contact::getAddress (string address)
{
    address = address;
}