#include<iostream>
using namespace std;

    class Contact
        {
        public:
        int name;
        string phone;
        string email;
        string address;
        Contact *left = NULL, *right = NULL;
        Contact (int ename,string ephone, string eemail,string eaddress){
            name = ename;
            phone = ephone;
            email = eemail;
            address = eaddress;
            left = NULL;
            right = NULL;
        }};


Contact *deleteContact(Contact *root, int xname)
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


void inorder_traversal (Contact * root)
{
  if (root == NULL)
    return;
  inorder_traversal (root->left);

  cout << root->name << " ";

  inorder_traversal (root->right);

}

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
