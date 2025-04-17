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
#include <QDataStream>  // Required for binary data operations
#include"ContactList.h"
//#include<fstream>
#include<iostream>
#include <QString>

ContactList S;

class ContactBookWidget : public QWidget {
    Q_OBJECT

private:
    QListWidget* contactList;
    QLineEdit* nameLineEdit;
    QLineEdit* numberLineEdit;
    QLineEdit* emailLineEdit;
    QLineEdit* addressLineEdit;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* editButton;
    QPushButton* searchButton;
    QPushButton* displayButton;
    QLabel* editLabel;
    QString contactsFilePath;

public:

    ContactBookWidget(QWidget* parent = nullptr) : QWidget(parent){
        QVBoxLayout* layout = new QVBoxLayout(this);
        QLabel* nameLabel = new QLabel("Name:");
        QLabel* numberLabel = new QLabel("Phone Number:");
        QLabel* EmailLabel = new QLabel("Email:");
        QLabel* AddressLabel = new QLabel("Address:");

        nameLineEdit = new QLineEdit(this);
        numberLineEdit = new QLineEdit(this);
        emailLineEdit = new QLineEdit(this);
        addressLineEdit = new QLineEdit(this);

        setWindowTitle("Contact List Application");

        addButton = new QPushButton("Add Contact", this);
        deleteButton = new QPushButton("Delete Contact", this);
        editButton = new QPushButton("Edit Contact", this);
        editLabel = new QLabel("", this);


        searchButton = new QPushButton("Search Contact", this);
        displayButton = new QPushButton("Display Contact", this);
        contactList = new QListWidget(this);

        layout->addWidget(editButton);
        layout->addWidget(editLabel);

        layout->addWidget(nameLabel);
        layout->addWidget(nameLineEdit);

        layout->addWidget(numberLabel);
        layout->addWidget(numberLineEdit);

        layout->addWidget(EmailLabel);
        layout->addWidget(emailLineEdit);

        layout->addWidget(AddressLabel);
        layout->addWidget(addressLineEdit);

        layout->addWidget(addButton);
        layout->addWidget(deleteButton);

        layout->addWidget(editButton);
        layout->addWidget(searchButton);
        layout->addWidget(displayButton);

        layout->addWidget(editLabel);

        layout->addWidget(contactList);

        // Load contact names from file and display them in the contactList widget

        QFile file("D:\\contacts.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QString contactName = line.split('-')[0];
                contactList->addItem(contactName);
            }
            file.close();
        }
        // Buttons connections
        connect(editButton, SIGNAL(clicked()), this, SLOT(editContact()));
        connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
        connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteContact()));
        connect(searchButton, SIGNAL(clicked()), this, SLOT(searchContact()));
        connect(displayButton, SIGNAL(clicked()), this, SLOT(display()));

    }
public slots:

    void display() {
        QListWidgetItem* selectedItem = contactList->currentItem();
        bool found = false;
        if (selectedItem) {
            QString contactName = selectedItem->text();  // Get the name of the selected item
            QFile file("D:\\contacts.txt");
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString matchingContactInfo; // Store matching contact information
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    if (line.contains(contactName, Qt::CaseInsensitive)) {
                        // Contact found
                        matchingContactInfo = line;
                        found = true;
                        break; // No need to continue searching once found
                    }
                }
                file.close();
                if(found){
                    // Split the contact information using the "-" delimiter
                    QStringList contactDetails = matchingContactInfo.split('-');

                    // Display matching contact information
                    QString displayText = "Selected Contact Information:\n";
                    displayText += "Name: " + contactDetails.value(0) + "\n";
                    displayText += "PhoneNumber: " + contactDetails.value(1) + "\n";
                    displayText += "Email: " + contactDetails.value(2) + "\n";
                    displayText += "Address: " + contactDetails.value(3) + "\n";

                    QMessageBox::information(this, "Contact Information", displayText);
                }
                else{
                    QMessageBox::warning(this, "Wrong contact", "Contact not found");
                    return;
                }
            }
        }
    }

    //check if the email entered is valid

    bool isValidEmail(const string email) {
        regex pattern("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
        return regex_match(email, pattern);
    }

    //check if the phone number entered is valid
    bool isValidPhoneNumber(const QString& phoneNumber) {
        if (phoneNumber.startsWith("+20")) {
            if (phoneNumber.length() == 13) {
                return true;
            }
            else if (phoneNumber.length() == 14) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (phoneNumber.startsWith("01") && phoneNumber.length() == 11) {
            QString modifiedPhoneNumber = "+20" + phoneNumber;
            return true;
        }
        else if (phoneNumber.startsWith("+") && phoneNumber.length() >= 9 && phoneNumber.length() <= 18) {
            return true;
        }
        else if (phoneNumber.startsWith("+") && phoneNumber.mid(4, 1) == " " && phoneNumber.length() >= 13 && phoneNumber.length() <= 20) {
            return true;
        }
        else {
            return false;
        }
    }

    void addContact() {
        QString newName = nameLineEdit->text();
        QString newNumber = numberLineEdit->text();
        QString newEmail = emailLineEdit->text();
        QString newAddress = addressLineEdit->text();
        if (newName.isEmpty() || newNumber.isEmpty()) {
            QMessageBox::warning(this, "Empty Fields", "Please fill in the contact details.");
            return;
        }

        if (!(isValidPhoneNumber(newNumber))) {
            QMessageBox::warning(this, "Wrong number format", "Please enter correct number.");
            return;
        }
        if (!(isValidEmail(newEmail.toStdString()))) {
            QMessageBox::warning(this, "Wrong email format", "Please enter correct email format.");
            return;
        }
        // Check for duplicates
            bool duplicate = false;
            QFile file("D:\\contacts.txt");
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QStringList matchingContacts; // Store matching contact names
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    if (line.contains(newName, Qt::CaseInsensitive) || (line.contains(newNumber, Qt::CaseInsensitive))) {
                        // Contact found
                        duplicate = true;
                        matchingContacts.append(line.split('-')[0]); // store the names of matching contacts
                    }
                }
                file.close();

                if (duplicate) {
                    // Display matching contact names
                    QString names = matchingContacts.join("\n");
                    QMessageBox::warning(this, "Duplicate Contact", "Contacts with the same name or mobile number already exists.\n"+names);

                } else {
                    // No duplicate found, add the contact
                    QString contact = newName;
                    QListWidgetItem* newItem = new QListWidgetItem(contact);
                    contactList->addItem(newItem);
                    Contact  h(newName.toStdString(),newNumber.toStdString(),newEmail.toStdString(),newAddress.toStdString());
                    S.insert(h);
                   // S.clearFile();
                   // S.saveNewData(S.getRoot());
                    // Clear input fields
                    nameLineEdit->clear();
                    numberLineEdit->clear();
                    emailLineEdit->clear();
                    addressLineEdit->clear();
                }
            }
    }

    void deleteContact() {
        QListWidgetItem* selectedItem = contactList->currentItem();

        if (selectedItem) {
            QString contactName = selectedItem->text();  // Get the name of the selected contact

            // Ask for confirmation before deletion
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Delete Contact",
                                          "Are you sure you want to delete the contact: " + contactName + "?",
                                          QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                S.deleteContact1(cout,contactName.toStdString());
                S.clearFile();
                S.saveNewData(S.getRoot());
                delete selectedItem;
            }
        } else {
            QMessageBox::warning(this, "Contact Not Found", "Please select a contact to delete.");
        }
    }

    void editContact() {
        QListWidgetItem* selectedItem = contactList->currentItem();
        QString name;
        QString phone;
        QString email;
        QString address;

        if (selectedItem) {
            QString contactName = selectedItem->text();  // Get the name of the selected contact
            QFile file("D:\\contacts.txt");
            if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QTextStream in(&file);
                QStringList allContacts; // Store all contacts
                bool contactFound = false;

                // Read all contacts from the file
                while (!in.atEnd()) {
                    QString line = in.readLine();

                    if (line.contains(contactName, Qt::CaseInsensitive)) {
                        // Contact found
                       contactFound = true;

                        // Split the contact information using the "-" delimiter
                       QStringList contactDetailsedit = line.split("-");
                        // Create a QDialog for editing
                        QDialog dialog(this);
                        dialog.setWindowTitle("Edit Contact Information");

                        QVBoxLayout layout(&dialog);

                        // Create QLineEdit widgets for each piece of information
                        QLineEdit* nameLineEdit = new QLineEdit(contactDetailsedit.value(0), &dialog);
                        layout.addWidget(new QLabel("Name:", &dialog));
                        layout.addWidget(nameLineEdit);
                        name = contactDetailsedit.value(0);

                        QLineEdit* phoneNumberLineEdit = new QLineEdit(contactDetailsedit.value(1), &dialog);
                        layout.addWidget(new QLabel("PhoneNumber:", &dialog));
                        layout.addWidget(phoneNumberLineEdit);
                        phone = contactDetailsedit.value(1);


                        QLineEdit* emailLineEdit = new QLineEdit(contactDetailsedit.value(2), &dialog);
                        layout.addWidget(new QLabel("Email:", &dialog));
                        layout.addWidget(emailLineEdit);
                        email = contactDetailsedit.value(2);


                        QLineEdit* addressLineEdit = new QLineEdit(contactDetailsedit.value(3), &dialog);
                        layout.addWidget(new QLabel("Address:", &dialog));
                        layout.addWidget(addressLineEdit);
                        address = contactDetailsedit.value(3);


                        // Add OK and Cancel buttons
                        QPushButton* okButton = new QPushButton("OK", &dialog);
                        QPushButton* cancelButton = new QPushButton("Cancel", &dialog);
                        layout.addWidget(okButton);
                        layout.addWidget(cancelButton);

                        // Connect the signals for OK and Cancel buttons
                        connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
                        connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

                        // Execute the dialog
                        if (dialog.exec() == QDialog::Accepted) {

                            // User clicked OK, update the contact information
                            contactDetailsedit.replace(0, nameLineEdit->text());
                            contactDetailsedit.replace(1, phoneNumberLineEdit->text());
                            contactDetailsedit.replace(2, emailLineEdit->text());
                            contactDetailsedit.replace(3, addressLineEdit->text());

                            // Update the name displayed in the GUI
                            selectedItem->setText(contactDetailsedit.value(0));

                            // Remove the old contact from the list
                            allContacts.removeAll(contactName);

                            // Append the modified contact to the list
                            allContacts.append(contactDetailsedit.join('-') + "\n");

                        }
                        break;
                    }

                }
                file.close();
                if(contactFound){
                    Contact c(name.toStdString(), phone.toStdString(), email.toStdString(), address.toStdString());
                    S.editContact1(cout,contactName.toStdString(),c);
                }
                // Clear the file and write all contacts back
                QFile file("D:\\contacts.txt");
                if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    QTextStream out(&file);
                    out << allContacts.join(" \n");
                    file.close();
                }
                if (contactFound) {
                    QMessageBox::information(this, "Edit Successful", "Contact information updated successfully.");
                } else {
                    QMessageBox::information(this, "Contact Not Found", "Please select a contact to edit.");
                }
                } else {
                QMessageBox::warning(this, "Error", "Unable to open contacts file.");
            }
        }
    }


    void searchContact() {
        QString searchTerm = nameLineEdit->text();
        if (searchTerm.isEmpty()) {
            searchTerm = numberLineEdit->text();
        }
        if (searchTerm.isEmpty()) {
            searchTerm = emailLineEdit->text();
        }
        if (!searchTerm.isEmpty()) {
            bool found = false;
            QFile file("D:\\contacts.txt");
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QStringList matchingContacts; // Store matching contact names
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    if (line.contains(searchTerm, Qt::CaseInsensitive)) {
                        // Contact found
                        found = true;
                        matchingContacts.append(line.split('-')[0]); // Store the name of the contact to search for
                    }
                }
                file.close();

                if (found) {
                    // Display matching contact names
                    QString names = matchingContacts.join("\n");
                    QMessageBox::information(this, "Search Result","Matching Contacts: \n"+names);
                } else {
                    QMessageBox::information(this, "Contact Not Found", "No contact found matching the search term.");
                }
            }
        } else {
            QMessageBox::information(this, "Empty Search Term", "Please enter a name or phone number to search.");
        }
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QFile file("D:\\contacts.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);
        QStringList allContacts; // Store all contacts
        while (!in.atEnd()) {
            QString line = in.readLine();
            allContacts = line.split('-');
            Contact h(allContacts.value(0).toStdString(),allContacts.value(1).toStdString(),allContacts.value(2).toStdString(),allContacts.value(3).toStdString());
            S.insert(h);
            //S.clearFile();            //already done by insert function
            //S.saveNewData(S.getRoot());            //already done by insert function
            }
        }
        file.close();
        ContactBookWidget contactBookWidget;
        contactBookWidget.show();
    return app.exec();
}



#include "main.moc"
