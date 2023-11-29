#include<iostream>
using namespace std;


int main ()
{
    Contact *root = new Contact(4, "01019341923", "ahmedmohsab@gmail.com", "10th of ramadan");
    root->left = new Contact(2, "01019341923", "ahmedmohsab@gmail.com", "10th of ramadan");
    root->right = new Contact(7, "01019341923", "ahmedmohsab@gmail.com", "10th of ramadan");
    root->left->left = new Contact(1, "01019341923", "ahmedmohsab@gmail.com", "10th of ramadan");
    root->left->right = new Contact(3, "01019341923", "ahmedmohsab@gmail.com", "10th of ramadan");
    root->right->left = new Contact(5, "01019341923", "ahmedmohsab@gmail.com", "10th of ramadan");
    root->right->right = new Contact(9, "01019341923", "ahmedmohsab@gmail.com", "10th of ramadan");

  cout << "Inorder Traversal of the Binary Search Tree:";
  inorder_traversal (root);
  cout << endl;
  cout << "Value to be deleted 7"<<endl;
  deleteContact(root, 7);
  cout << "Inorder Traversal :";
  inorder_traversal (root);
  cout << endl;
}
