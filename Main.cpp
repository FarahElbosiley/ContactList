#include<iostream>
#include<string>
using namespace std;
int main(){
    cout<<"Hello, Welcome to Contact list"<<endl;
    ContactList myContacts;
    string name, number, email, address;
    int choice;

    // Load contacts from binary file
    ifstream inFile("contacts.bin", ios::binary);
    if (inFile) {
        myContacts.loadFromBinaryFile(inFile);
        inFile.close();
    }

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
            case 1:
                cout << "Enter contact name: ";
                getline(cin, name);
                cout << "Enter contact number: ";
                getline(cin, number);
                if(!myContacts.isValidPhoneNumber(number)){
                    cout<<"wrong number format"<<endl;
                    break;
                }
               
                cout << "Enter contact email: ";
                getline(cin, email);
                cout << "Enter contact address: ";
                getline(cin, address);
                Contact h(name, number, email, address);
                myContacts.insert(h);
                break;
        
            case 2:
                cout << "Enter contact name to search: ";
                getline(cin, name);
                myContacts.Search(cout, name);
                break;
            case 3:
                myContacts.display(cout);
                break;
            case 4:
                cout << "Enter contact name to display information: ";
                getline(cin, name);
                myContacts.Search(cout, name);
                break;
            case 5:
                cout << "Enter contact name to delete: ";
                getline(cin, name);
                myContacts.deleteContact1(cout, name);
                 if (!myContacts.isValidSize()) {
                 cout << "Error:: invalid list size" << endl;
                }
                break;
            case 6:
                cout << "Enter contact name to edit: ";
                getline(cin, name);
                myContacts.editContact1(cout, name);
                break;
            case 7:
                // Save contacts to binary file before exiting
                ofstream outFile("contacts.bin", ios::binary);
                myContacts.saveToBinaryFile(outFile);
                outFile.close();
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
