#ifndef __CONTACTLIST_H__ 
#define __CONTACTLIST_H__

#include <string>
#include <iostream>

class Name
{
public:
    Name();
    string first();
    string last();
    void setFirstName  (string firstname);
    void setLastName   (string lastname);
private:
    string firstname;
    string lastname;
};

class Contact
{
public:
    Contact ();
    Contact (Name person, string phoneNum, string email);
    void set (string firstname, string lastname, string phoneNum, string email);
    void getName  (Name& fullname);
    void getPhoneNum   (string& phoneNum);
    void getEmail (string& email);
    void setName  (string fullname);
    void setPhoneNum   (string phoneNum);
    void setEmail (string email);

private:
    Name fullname;
    string phoneNum;
    string email;
};

typedef class tree_node* link;  // link aka (tree_node *)
class tree_node
{
private:
    tree_node ()   {};
    // Non-default constructor:
    Contact record;             // item_type item
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