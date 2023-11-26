#include "contactlist.h"
#include <string>
#include <iostream>
using namespace std;

int ContactList::insert(Contact newContact) {
    // Create a new tree_node
    link newNode = new tree_node;
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
