#include "ContactList.h"
#include <string>
#include <iostream>
using namespace std;

Contact::Contact (){ }

Contact::Contact (string name, string phoneNum, string email, string address)
{
    name = name;
    phoneNum = phoneNum;
    email = email;
    address = address;
}

string Contact::getName (string name)
{
    return name;
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

void Contact::setName  (string name)
{
    name = name;
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
    string nameInRecord, telephone, email;
    record.getName(nameInRecord);
    record.getPhoneNum(telephone);
    record.getEmail(email);
    record.getAddress(address);
    output << nameInRecord << "\t"<< telephone << "\t" << email << "\t" << address << endl;
}

int ContactList::insert(Contact newContact) {
    // Create a new tree_node
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

    return 1; // Return 1 to indicate success
}



int ContactList::Search(ostream& output, string name)
{
    count = 0;
    find_name_InTree(output, root, name);
    return count;
}

void ContactList::find_name_InTree(ostream& output, link current, string name)
{
    if (NULL == current) {
        return;         // contact is not found
    }


    // begin search
    else {


        // get current contact from the record
        string name_Record;
        current->record.getName(name_Record);


        // compare the name with the name from record
        if (name < name_Record) {
            // name to find is less so, search on the left
            find_name_InTree(output, current->left, name);
        }
        // compare the name in record with the name to find
        else if (name > name_Record) {
            // name to find is greater so, search on the right
            find_name_InTree(output, current->right, name);
        }


        // found the name
        else {
            // compare the name in record with the name 
            if (name < name_Record) {
                //  name to find is less so, search on the left
                find_name_InTree(output, current->left, name);
            }
            // compare the name in record with the name
            else if (name > name_Record) {
                // name to find is greater so, search on the right
                find_name_InTree(output, current->right, name);
            }


            // found the name
            else {
                string telephone;
                current->record.getPhoneNum(telephone);
                string email;
                current->record.getEmail(email);
                output << "The contact is found: " << endl;
                cout << "Name: " << name_Record << endl;
                cout<< "Telephone number: \t" << telephone << "Email: \t" << email << endl;
                count++;
            }
        }
    }
}
  
void ContactList:: deleteContact(Contact *root, string xname)
{
  if (root == NULL)
  {
    cout << "Node not found "<<endl;
    return NULL;
  }

  if (root->name > xname)
  {
    root->left = deleteContact(root->left, xname);
  }
  else if (root->name < xname)
  {
    root->right = deleteContact(root->right, xname);
  }
  else
  {
    if (root->left == NULL)
    {
      Contact *temp = root->right;
      delete (root);
      return temp;
    }
    else if (root->right == NULL)
    {
      Contact *temp = root->left;
      delete (root);
      return temp;
    }
    else
    {
      Contact *temp = root->right;

      while (temp->left != NULL)
        temp = temp->left;

      root->name = temp->name;

      root->right = deleteContact(root->right, temp->name);
    }
  }
  return root;
}


void ContactList:: inorder_traversal (Contact * root)
{
  if (root == NULL)
    return;
  inorder_traversal (root->left);

  cout << root->name << " ";

  inorder_traversal (root->right);

}

Contact ContactList:: editContact ( Contact *root, string name, Contact newContact)
{
    deleteContact (Contact *root, string name);
    insert (Contact newContact);
}