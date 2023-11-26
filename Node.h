#include <string>
#include <iostream>
#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    string name;
    string phoneNumber;
    string email;
    string address;
    Node* left;
    Node* right;

    Node(string name, string phoneNumber, std::string email, std::string address) :
        name(name), phoneNumber(phoneNumber), email(email), address(address), left(NULL), right(NULL) {}
};

#endif //NODE_H
