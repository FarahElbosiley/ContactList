#ifndef __CONTACTLIST_H__
#define __CONTACTLIST_H__
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
using namespace std;

class Contact
{
public:
    Contact ();
    Contact (string name, string phoneNum, string email, string address);
    string getName();
    string getPhoneNum();
    string getEmail();
    string getAddress();
    void setName  (string name);
    void setPhoneNum   (string phoneNumber);
    void setEmail (string email);
    void setAddress (string address);

private:
    string name;
    string phoneNum;
    string email;
    string address;
};

class Node {
public:

    Contact data;
    Node* left;
    Node* right;

    Node (Contact item) : data(item), left(NULL), right(NULL){}
};

typedef  Node* link;

class ContactList
{
public:
    ContactList();
    ~ContactList();
    void deleteTree(link node);
    int display(ostream& output);
    void inOrder(link current, ostream& output);
    int insert(Contact newContact);
    void deleteContact(ostream& output,link root, string xname);
    bool Search(ostream& output, string name);
    link find_name_InTree(ostream& output, link current, string name);
    void editContact(ostream& output,link root, string name, Contact newContact);
    void displayContact(link current);
    void deleteContact1(ostream& output, string name);
private:
    link root;      // pointer to root of tree
    int insertSize; // list size
    int count;      // general count used for find and delete
};

#endif //NODE_H
#endif  //__CONTACTLIST_H__
