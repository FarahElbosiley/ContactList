#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <string>
#include "ContactList.h"
#include <iostream>
#include <regex>
#include <fstream>
#include<vector>

using namespace std;

/*////////////////////////////////////////////

     Class Contact

//////////////////////////////////////////////*/

Contact::Contact (){ }

Contact::Contact (string name, string phoneNum, string email, string address)
{
    setName(name);
    setEmail(email);
    setPhoneNum(phoneNum);
    setAddress(address);
}
Contact::Contact(const Contact& other)
    : name(other.name), phoneNum(other.phoneNum), email(other.email), address(other.address) {}

string Contact::getName()
{
    return name;
}

string Contact::getPhoneNum()
{
    return phoneNum;
}
string Contact::getEmail()
{
    return email;
}
string Contact::getAddress()
{
    return address;
}

void Contact::setName  (string name)
{
    this->name = name;
}
void Contact::setPhoneNum (string phoneNumber)
{
       this->phoneNum = phoneNumber;
}

void Contact::setEmail (string email)
{
        this->email = email;
}

void Contact::setAddress (string address)
{
    this->address = address;
}

/*////////////////////////////////////////////

     Class ContactList

//////////////////////////////////////////////*/

ContactList::ContactList() {
    root = nullptr;
    insertSize = 0;
    count = 0;
    MaxSize = 1024;
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

link ContactList::getRoot(){
    return root;
}

int ContactList::display(ostream& output)
{
    inOrder(root, output);
    return insertSize;
}

void ContactList::inOrderTraversal(Node* root,vector<ContactFileData>& result) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->left, result);
    ContactFileData contactData;
    contactData.name = root->data.getName();
    contactData.phoneNumber = root->data.getPhoneNum();
    contactData.email = root->data.getEmail();
    contactData.address = root->data.getAddress();

    result.push_back(contactData);

    inOrderTraversal(root->right, result);
}

void ContactList::inOrder(link current, ostream& output)
{
    if(current != NULL)
    {
        inOrder(current->left, output);
        displayContact(current);
        inOrder(current->right, output);
    }
}


int ContactList::insert(Contact newContact) {
    if (!isValidSize()) {
        cout << "The list is full" << endl;
        return 0;
    }

    link newNode = new Node(newContact);
    if (newNode == NULL) {
        return -1; // Return -1 to indicate error
    }

    // If the tree is empty, set the new node as the root
    if (root == NULL) {
        root = newNode;
        clearFile();
        saveNewData(root); // Save contact to file
        insertSize++;
        return 1; // Return 1 to indicate success
    }

    // Otherwise, find the correct position for the new node
    link current = root;
    link parent = NULL;
    while (current != NULL) {
        parent = current;
        if (newContact.getName() < current->data.getName()) {
            current = current->left;
        } else if (newContact.getName() > current->data.getName()) {
            current = current->right;
        } else {
            // If a contact with the same name already exists, do not insert
            delete newNode;
            return 0; // Return 0 to indicate that no new contact was inserteds
        }
    }

    // Insert the new node as a child of the parent node
    if (newContact.getName() < parent->data.getName()) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    clearFile(); // clear text file
    saveNewData(root); // Save contact to file
    insertSize++;
    return 1;
}



bool ContactList::Search(ostream& output, string pattern) {
    regex r(pattern);
    link foundNode = find_name_InTree(output, root, r);
    if (foundNode == NULL) {
        return false;  // Contact not found
    } else {
        return true;  // Contact found
    }
}

link ContactList::find_name_InTree(ostream& output, link current, regex& r) {
    if (current == NULL) {
        return NULL;
    }
    else if (regex_match(current->data.getName(), r)) {
        return current;
    }
    else {
        link foundNode = find_name_InTree(output, current->left, r);
        if (foundNode != NULL) {
            return foundNode;
        }
        return find_name_InTree(output, current->right, r);
    }
}

void ContactList::displayContact(link current){
    cout << "The contact is found: " << endl;
    cout << "Name: " << current->data.getName()<< endl;
    cout<< "Telephone number: " << current->data.getPhoneNum() <<"    "<< "Email: " << current->data.getEmail()<< endl;
}

bool ContactList::isValidSize() {
    return insertSize < MaxSize;
}
int ContactList::countNodes(link node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

link ContactList::deleteContact(ostream& output, link& root, const string&  xname) {
    if (root == NULL) {
        output << "Contact not found!";
        return root;
    } else if (xname < root->data.getName()) {
        root->left = deleteContact(output, root->left, xname);
    } else if (xname > root->data.getName()) {
        root->right = deleteContact(output, root->right, xname);
    } else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        } else if (root->left == NULL) {
            link temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == NULL) {
            link temp = root;
            root = root->left;
            delete temp;
        } else {
            link successor = root->right;
            while (successor->left != NULL)
                successor = successor->left;

            root->data = successor->data;
            root->right = deleteContact(output, root->right, successor->data.getName());
        }
    }
    return root;
}

void ContactList::deleteContact1(ostream& output, const string& name) {
    root= deleteContact(output, root, name);
        // Update the text file after deleting the contact
            clearFile();
            saveNewData(root);
}

void ContactList::editContact1(ostream& output, string name, Contact newContact) {

    editContact(output, root, name, newContact);
}

void ContactList:: editContact (ostream& output, link root, string name, Contact newContact){
    regex x(name);
    link ptr=find_name_InTree( output, root, x); // return pointer to the contact
    if (ptr==NULL){
        return;
    }
    else{ // the contact is found
            deleteContact(cout, root,name);
            insert(newContact);
            //deleteContact(output,ptr,ptr->data.getName());

            return;
        }
}


void ContactList::clearFile() {
    ofstream file("D:\\contacts.txt", std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        cerr << "Error clearing file." << std::endl;
    }
    file.close();
}



void ContactList::saveNewData(link root, ofstream& file) {
    if (root != NULL) {
        saveNewData(root->left, file);
        file << root->data.getName() << "-" << root->data.getPhoneNum() << "-" << root->data.getEmail() << "-" << root->data.getAddress() << endl;
        saveNewData(root->right, file);
    }
}

void ContactList::saveNewData(link root) {
    ofstream file("D:\\contacts.txt", std::ios::app);
    if (file.is_open()) {
        saveNewData(root, file);
        file.close();
    } else {
        // Handle the case where the file couldn't be opened
        cerr << "Unable to open the file." << std::endl;
    }
}

