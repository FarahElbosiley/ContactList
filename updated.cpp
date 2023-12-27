
#include <string>
#include "ContactList.h"
#include <iostream>
#include <regex>
#include <fstream>
#include<vector>
using namespace std;

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
     if(!(isValidPhoneNumber(phoneNumber))){
         cout<<"wrong number format"<<endl<<"Enter contact Number:"<<endl;
         string n;
         getline(cin,n);
         setPhoneNum(n);}
    else
        this->phoneNum = phoneNumber;
}

void Contact::setEmail (string email)
{
    if(!(isValidEmail(email))){
        cout<<"InValid Input"<<endl<<"please enter Email:"<<endl;
        string i;
        getline(cin, i);
        setEmail(i);
    }
    else
        this->email = email;
}

void Contact::setAddress (string address)
{
    this->address = address;
}

bool Contact::isValidEmail(const string email) {
    regex pattern("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
    return regex_match(email, pattern);
}

bool Contact::isValidPhoneNumber(string phoneNumber) {
    // Check if the phone number starts with "+20"
    if (phoneNumber.substr(0, 3) == "+20") {
        // Check if it's a landline number (2 for area code + 8 for local number = 10 + 3 for country code = 13 total)
        if (phoneNumber.length() == 13) {
            return true;
        }
        // Check if it's a mobile number (10 for the number + 3 for country code = 13 total)
        else if (phoneNumber.length() == 14) {
            return true;
        }
        // If it's neither a landline nor a mobile number, it's invalid
        else {
            return false;
        }
    }
    // Check if the phone number starts with "01" and has a length of 11
    else if (phoneNumber.substr(0, 2) == "01" && phoneNumber.length() == 11) {
        // Add "+20" to the start of the phone number
        phoneNumber = "+20" + phoneNumber;
        return true;
    }
    // For non-Egyptian numbers, check if the number starts with "+" followed by 1 to 3 digits for the country code,
    // and then 8 to 15 digits for the phone number
    else if (phoneNumber[0] == '+' && phoneNumber.length() >= 9 && phoneNumber.length() <= 18) {
        return true;
    }
    else if (phoneNumber[0] == '+' && phoneNumber[4] == ' ' && phoneNumber.length() >= 13 && phoneNumber.length() <= 20) {
        return true;
    }
    // If none of the above checks pass, the phone number is invalid
    else {
        return false;
    }
}

///////////////////////////////////////////////
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

int ContactList::display(ostream& output)
{
    inOrder(root, output);
    return insertSize;
}
vector<ContactFileData> ContactList::BSTtoVector()
{
    return copyBSTtoVector(root);
}
vector<ContactFileData> ContactList::copyBSTtoVector(Node* root) {
    vector<ContactFileData> result;
    inOrderTraversal(root, result);
    return result;
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
    if(!isValidSize()){
        cout<<"The list is full"<<endl;
        return 0;
    }
    link newNode = new Node(newContact);
    if (newNode == NULL) { // Check if new node is created successfully
        return -1; // Return -1 to indicate error
    }

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
        if (newContact.getName() < current->data.getName()) {
            current = current->left;
        } else if (newContact.getName() > current->data.getName()) {
            current = current->right;
        } else {
            // If a contact with the same  name already exists, do not insert
            delete newNode;
            return 0; // Return 0 to indicate that no new contact was inserted
        }
    }

    // Insert the new node as a child of the parent node
    if (newContact.getName() < parent->data.getName()) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
      insertSize++;
    return 1; // Return 1 to indicate success
}



bool ContactList::Search(ostream& output, string pattern) {
    regex r(pattern);
    link foundNode = find_name_InTree(output, root, r);
    if (foundNode == NULL) {
        output << "Contact not found." << endl;
        return false;  // Contact not found
    } else {
        displayContact(foundNode);
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

vector<ContactFileData> getAllContacts(const string& fileName) {
    ifstream file(fileName);

    vector<ContactFileData> contactsVector;

    if (!file.is_open()) {
        cerr << "Empty Contact List." << endl;
        return contactsVector;
    }

    ContactFileData contact;
    while (file >> contact.name >> contact.phoneNumber >> contact.email) {
        contactsVector.push_back(contact);
    }

    file.close();
    return contactsVector;
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

void ContactList::deleteContact1(ostream& output, string name) {
    deleteContact(output, root, name);
}

link ContactList::deleteContact(ostream& output, link& root, string xname)
{
    if(root == NULL){
        output << "Contact not found!";
        return root;
    }
    else if(xname < root->data.getName()){
        deleteContact(output, root->left, xname);
    }
    else if(xname > root->data.getName()){
        deleteContact(output, root->right, xname);
    }
    else{
        if(root->left == NULL){
            link temp = root->right;
            delete root;
            root = temp;
        }
        else if(root->right == NULL){
            link temp = root->left;
            delete root;
            root = temp;
        }
        else
    {
      link temp = root->right;

      while (temp->left != NULL)
        temp = temp->left;

      root->data = temp->data;

      root->right = deleteContact(output,root->right,temp->data.getName());
    }
  }
  insertSize--;
  return root;
}

void ContactList::editContact1(ostream& output, string name) {

    editContact(output, root, name);
}

void ContactList:: editContact (ostream& output, link root, string name)
{
     regex x(name);
     link ptr=find_name_InTree( output, root, x);
     if (ptr==NULL)
     return;
     else{
     string data;
     int choice;
     output<<"Select Option to edit 1 for name 2 for email and 3 for address and 4 for number:";
     cin>>choice;
    output<<"enter data to modify: ";
    cin>>data;

    switch(choice){
    case 1:{
    ContactList myContacts;
    Contact h(data, ptr->data.getPhoneNum(),ptr->data.getEmail(),ptr->data.getAddress());
    myContacts.insert(h);
    deleteContact(output,ptr,ptr->data.getName());
    break;
    }
    case 2:{
    ptr->data.setEmail(data);
    break;}
    case 3:{
        ptr->data.setAddress(data);
    break;}
    case 4:{
        ptr->data.setPhoneNum(data);
    break;
        }
    default: {
        output<<"error";
        return;
        }
    }
    }
    }

    void clearFile(const std::string& fileName) {
    std::ofstream file(fileName, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        file.close();
    } else {
        std::cerr << "Error saving file." << std::endl;
    }
}

int main(){
     ContactList myContacts;

     vector<ContactFileData> allContacts = getAllContacts("contacts.txt");
    for (const auto& contact : allContacts) {
        Contact h(contact.name,contact.phoneNumber,contact.email,contact.address);
        myContacts.insert(h);
    }
    cout<<"Hello, Welcome to Contact list"<<endl;
    string name, number, email, address;
    int choice;

    while (true) {
        cout << "Please choose an operation:\n";
        cout << "1. Insert new contact\n";
        cout << "2. Search for contact by name\n";
        cout << "3. Display contactList\n";
        cout << "4. Display information of contact\n";
        cout << "5. Delete contact\n";
        cout << "6. Edit contact information\n";
        cout << "7. Exit\n";
        cin >> choice;
        cin.ignore();  // Ignore newline character in input buffer

        switch (choice) {
            case 1:{
                cout << "Enter contact name: ";
                getline(cin, name);
                cout << "Enter contact number: ";
                getline(cin, number);
                cout << "Enter contact email: ";
                getline(cin, email);
                cout << "Enter contact address: ";
                getline(cin, address);
                Contact h(name, number, email, address);
                myContacts.insert(h);
                break;
            }
            case 2:{
                cout << "Enter contact name to search: ";
                getline(cin, name);
                myContacts.Search(cout, name);
                break;}
            case 3:{
                myContacts.display(cout);
                break;}
            case 4:{
                cout << "Enter contact name to display information: ";
                getline(cin, name);
                myContacts.Search(cout, name);
                break;}
            case 5:{
                cout << "Enter contact name to delete: ";
                getline(cin, name);
                myContacts.deleteContact1(cout, name);
                 if (!myContacts.isValidSize()) {
                 cout << "Error:: invalid list size" << endl;
                }
                break;}
            case 6:{
                cout << "Enter contact name to edit: ";
                getline(cin, name);
                myContacts.editContact1(cout, name);
                break;}
            case 7:{

                    clearFile("contacts.txt");
                        ofstream file("contacts.txt");
                    for (const auto& contact : myContacts.BSTtoVector()) {
                        file << contact.name << " " << contact.phoneNumber << " " << contact.email <<contact.address <<endl;
                    }

                    file.close();
                    cout << "Contacts saved to file successfully." << endl;


                return 0;}
            default:{
                cout << "Invalid choice. Please try again.\n";
        }}
    }

    return 0;
}
