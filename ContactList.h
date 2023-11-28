#ifndef __CONTACTLIST_H__ 
#define __CONTACTLIST_H__
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>


class Contact
{
public:
    Contact ();
    Contact (string firstname,string lastname, string phoneNum, string email, string address);
    string getFirstName  (string fname);
    string getLastName  (string lname);
    string getPhoneNum   (string phoneNumber);
    string getEmail (string email);
    string getAddress (string address);
    void setFirstName  (string fname);
    void setLastName  (string lname);
    void setPhoneNum   (string phoneNumber);
    void setEmail (string email);
    void setAddress (string address);

private:
    string firstname;
    string lastname;
    string phoneNum;
    string email;
    string address;
};

typedef class Node* link;
class Node {
public:
    string name;
    string phoneNumber;
    string email;
    string address;
    Node* left;
    Node* right;

    Node(string name, string phoneNumber, string email,string address) :
        name(name), phoneNumber(phoneNumber), email(email), address(address), left(NULL), right(NULL) {}
};


class ContactList
{
public:
    ContactList();
    ~ContactList();
    void deleteTree(link node);
    int display(ostream& output);
    void inOrder(link current, ostream& output);
    void display_tree(Contact record, ostream& output);
    int insert(Contact newContact);
    int delete(Contact cont);
    int Search(ostream& output, string lastname, string firstname);
    void find_Lastname_Firstname_InTree(ostream& output, link current, string lastname, string firstname);
    int edit(Contact existingContact);

private:
    link root;      // pointer to root of tree
    int insertSize; // list size
    int count;      // general count used for find and delete
};

#endif //NODE_H
#endif  //__CONTACTLIST_H__
