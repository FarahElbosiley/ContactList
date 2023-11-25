#ifndef __CONTACTLIST_H__ 
#define __CONTACTLIST_H__

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

typedef class tree_node* link; 
class tree_node
{
private:
    tree_node();
    ~tree_node();
    Contact data;             // item_type item
    link left;                  // tree_node *left; 
    link right;                 // tree_node *right; 
    friend class ContactList;   // provides functionality for private members
};

typedef void (*display_tree)(link, ostream&);

class ContactList
{
public:
    ContactList();
    ~ContactList();
    int display(ostream& output);
    int insert(Contact newContact);
    int delete(Contact cont);
    int search(ostream& output, string fname);
    int search(ostream& output, string lname, string fname);
    int edit(Contact existingContact);

private:
    link root;      // pointer to root of tree
    int insertSize; // list size
    int count;      // general count used for find and delete
};


#endif  //__CONTACTLIST_H__