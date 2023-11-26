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


ContactList::ContactList() {
    root = nullptr; 
    insertSize = 0; 
    count = 0; 
}
ContactList::~ContactList() {
    deleteTree(root);
}
void ContactList::deleteTree(link node) {
    if (node != nullptr) {
        deleteTree(node->left);  
        deleteTree(node->right); 
        delete node; 
    }
}

int ContactList::display(ostream& output)
{
    inOrder(root, output);
    return insertSize;
}

void ContactList::inOrder(link current, ostream& output)
{
    if(current != NULL)
    {
        inOrder(current->left, output);
        display_tree(current->record, output);
        inOrder(current->right, output);
    }
}

void ContactList::display_tree(Contact record, ostream& output)
{
    string lastnameInRecord, firstnameInRecord, telephone, email;
    record.getFirstName(firstInRecord);
    record.getLastName(lastInRecord);
    record.getPhoneNum(telephone);
    record.getEmail(email);
    record.getAddress(address);
    output << firstnameInRecord << "\t"<< lastnameInRecord << "\t" << telephone << "\t" << email << "\t" << address << endl;
}

int ContactList::insert(Contact newContact) {
    // Create a new tree_node
    link newNode = new Node;
    if (newNode == NULL) { // Check if new node is created successfully
        return -1; // Return -1 to indicate error
    }

    // Set the data of the new node
    newNode->data = newContact;
    newNode->left = NULL;
    newNode->right = NULL;

    // If the tree is empty, set the new node as the root
    if (root == NULL) {
        root = newNode;
        return 1; // Return 1 to indicate success
    }

    // Otherwise, find the correct position for the new node
    link current = root;
    link parent = NULL;
    while (current != NULL) {
        parent = current;
        if (newContact.getLastName() < current->data.getLastName()) {
            current = current->left;
        } else if (newContact.getLastName() > current->data.getLastName()) {
            current = current->right;
        } else {
            // If a contact with the same last name already exists, do not insert
            delete newNode;
            return 0; // Return 0 to indicate that no new contact was inserted
        }
    }

    // Insert the new node as a child of the parent node
    if (newContact.getLastName() < parent->data.getLastName()) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return 1; // Return 1 to indicate success
}


