#include<iostream>
#include<string>
using namespace std;
int main(){
    cout<<"Hello, Welcome to Contact list"<<endl;
    ContactList myContacts;
    string name, number;
    int choice;

    while (true) {
        cout << "Please choose an operation:\n";
        cout << "1. Insert new contact\n";
        cout << "2. Search for contact by name\n";
        cout << "3. Display contactList\n";
        cout<<  "4. Display information of contact"
        cout << "5. Delete contact\n";
        cout << "6. Delete all contacts\n";
        cout << "7. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter contact name: ";
                cin >> name;
                cout << "Enter contact number: ";
                cin >> number;
                cout << "Enter contact email ";
                cin >> email;
                cout << "Enter contact address: ";
                cin >> address;
                myContacts.insert(name, number,email,address);
                break;
            case 2:
                cout << "Enter contact name to search: ";
                cin >> name;
                Contact* foundcontact = myContacts.search(name);
                if (foundContact != nullptr) {
                    cout << "Contact found: " << foundContact->getName() << ", " << foundContact->getNumber() << endl;
                } else {
                    cout << "Contact not found." << endl;
                }
                break;
            case 3:
                myContacts.display();
                break;
            case 4:
                cout << "Enter contact name to display information: ";
                cin >> name;
                Contact* foundcontact = myContacts.search(name);
                if (foundContact != nullptr) {
                    cout << "Contact found: " << foundContact->getName() << ", number:  " << foundContact->getNumber() <<<< ", email: " << foundContact->getEmail() <<<< ", address: " << foundContact->getAddress() << endl;
                } else {
                    cout << "Contact not found." << endl;
                }
                break;
            case 5:
                cout << "Enter contact name to delete: ";
                cin >> name;
                myContacts.deleteContact(name);
                break;
            case 6:
                myContacts.deleteContactList();
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
};