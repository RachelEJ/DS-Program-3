/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler: Visual Studio
Program Description: Program that manages 2 BSTs and organizes them by user ID and ticket number.
*/
#pragma once
#include <string>
#include <iostream>
#include <ostream>
using std::cout;
using std::endl;
using std::string;
using std::ostream;

// Sets up the Node class
class Node
{
public:
	string userID;
	int tickNum;
	Node* left;
	Node* right;

	Node() : userID(""), tickNum(0), left(nullptr), right(nullptr) {}
	Node(string userID, int tickNum) : userID(userID), tickNum(tickNum), left(nullptr), right(nullptr) {}

	// finds the degree of a particular node
	int degree() const
	{
		if (left == nullptr && right == nullptr)
		{
			return 0;
		}
		else if (left != nullptr && right == nullptr)
		{
			return 1;
		}
		else if (left == nullptr && right != nullptr)
		{
			return 1;
		}
		else 
		{
			return 2;
		}
	}
};

// Sets up the BST class
template <typename T>
class BST
{
private:
	Node* root;
	bool insertID(Node*& node, string userID, int tickNum);
	bool insertNum(Node*& node, string userID, int tickNum);
	bool removeID(Node*& node, string userID, int tickNum);
	bool removeNum(Node*& node, string userID, int tickNum);
	bool findID(Node* node, string userID, int tickNum);
	bool findNum(Node* node, string userID, int tickNum);
	void inOrder(Node* node, ostream& os);
	void preOrder(Node* node, ostream& os);
	int postOrder(Node* node, ostream& os);
	void destroy(Node*& node);

public:
	BST() : root(nullptr) {}
	~BST();
	bool insertID(string userID, int tickNum);
	bool insertNum(string userID, int tickNum);
	bool removeID(string userID, int tickNum);
	bool removeNum(string userID, int tickNum);
	bool findID(string userID, int tickNum);
	bool findNum(string userID, int tickNum);
	void inOrder(ostream& os);
	void preOrder(ostream& os);
	int postOrder(ostream& os);
};

// destructor
template <typename T>
BST<T>::~BST()
{
	destroy(root);
}

// destroy function
template <typename T>
void BST<T>::destroy(Node*& node)
{
	// deletes each node in a post order traversal
	if (node == nullptr)
	{
		return;
	}
	destroy(node->left);
	destroy(node->right);
	delete node;
	node = nullptr;
}

// insert into user BST function
template <typename T>
bool BST<T>::insertID(Node*& node, string userID, int tickNum)
{
	// if node doesn't exist
	if (node == nullptr)
	{
		node = new Node(userID, tickNum);
		return true;
	}

	// if ID is less than node's ID, call on node's left child
	if (userID < node->userID)
	{
		return insertID(node->left, userID, tickNum);
	}

	// if ID is greater than node's ID, call on node's right child
	if (userID > node->userID)
	{
		return insertID(node->right, userID, tickNum);
	}

	// if ID is equal to node's ID, keeps comparing and recursively calling until it finds the correct place
	if (userID == node->userID)
	{
		if (node == nullptr)
		{
			node = new Node(userID, tickNum);
			return true;
		}
		if (tickNum < node->tickNum)
		{
			return insertID(node->left, userID, tickNum);
		}
		if (tickNum > node->tickNum)
		{
			return insertID(node->right, userID, tickNum);
		}
		return false;
	}
	return false;
}

// public insert ID
template <typename T>
bool BST<T>::insertID(string userID, int tickNum)
{
	return insertID(root, userID, tickNum);
}

// insert into ticket BST function
// exactly the same as insertID except with the userID and ticketNum comparisons flipped
template <typename T>
bool BST<T>::insertNum(Node*& node, string userID, int tickNum)
{
	if (node == nullptr)
	{
		node = new Node(userID, tickNum);
		return true;
	}
	if (tickNum < node->tickNum)
	{
		return insertNum(node->left, userID, tickNum);
	}
	if (tickNum > node->tickNum)
	{
		return insertNum(node->right, userID, tickNum);
	}
	if (tickNum == node->tickNum)
	{
		if (node == nullptr)
		{
			node = new Node(userID, tickNum);
			return true;
		}
		if (userID < node->userID)
		{
			return insertNum(node->left, userID, tickNum);
		}
		if (userID > node->userID)
		{
			return insertNum(node->right, userID, tickNum);
		}
		return false;
	}
	return false;
}

// public insert ticket
template <typename T>
bool BST<T>::insertNum(string userID, int tickNum)
{
	return insertNum(root, userID, tickNum);
}

// remove from ID BST function
template <typename T>
bool BST<T>::removeID(Node*& node, string userID, int tickNum)
{
	// runs the same comparisons as insertID
	if (node == nullptr)
	{
		return false;
	}
	if (userID < node->userID)
	{
		return removeID(node->left, userID, tickNum);
	}
	if (userID > node->userID)
	{
		return removeID(node->right, userID, tickNum);
	}
	if (userID == node->userID)
	{
		if (node == nullptr)
		{
			return false;
		}
		if (tickNum < node->tickNum)
		{
			return removeNum(node->left, userID, tickNum);
		}
		if (tickNum > node->tickNum)
		{
			return removeNum(node->right, userID, tickNum);
		}
		if (tickNum == node->tickNum)
		{
			// when the correct node is found, delete based on degree
			int deg = node->degree();

			// delete the leaf
			if (deg == 0)
			{
				delete node;
				node = nullptr;
			}

			// delete the node and replace with child
			else if (deg == 1)
			{
				Node* tmp = node;
				if (node->left != nullptr)
				{
					node = node->left;
				}
				else
				{
					node = node->right;
				}
				delete tmp;
			}

			// find a suitable replacement, replace the node with it, reorganize tree logically
			else
			{
				Node* tmp = node->left;
				while (tmp->right != nullptr)
				{
					tmp = tmp->right;
				}
				node->userID = tmp->userID;
				node->tickNum = tmp->tickNum;
				removeNum(node->left, tmp->userID, tmp->tickNum);
			}
			return true;
		}
	}
	return false;
}

// remove from ticket BST function
// exactly the same as ID BST except with userID and tickNum flipped
template <typename T>
bool BST<T>::removeNum(Node*& node, string userID, int tickNum)
{
	if (node == nullptr)
	{
		return false;
	}
	if (tickNum < node->tickNum)
	{
		return removeNum(node->left, userID, tickNum);
	}
	if (tickNum > node->tickNum)
	{
		return removeNum(node->right, userID, tickNum);
	}
	if (tickNum == node->tickNum)
	{
		if (node == nullptr)
		{
			return false;
		}
		if (userID < node->userID)
		{
			return removeNum(node->left, userID, tickNum);
		}
		if (userID > node->userID)
		{
			return removeNum(node->right, userID, tickNum);
		}
		if (userID == node->userID)
		{
			// deletes nodes based on degree
			int deg = node->degree();
			if (deg == 0)
			{
				delete node;
				node = nullptr;
			}
			else if (deg == 1)
			{
				Node* tmp = node;
				if (node->left != nullptr)
				{
					node = node->left;
				}
				else
				{
					node = node->right;
				}
				delete tmp;
			}
			else
			{
				Node* tmp = node->left;
				while (tmp->right != nullptr)
				{
					tmp = tmp->right;
				}
				node->userID = tmp->userID;
				node->tickNum = tmp->tickNum;
				removeNum(node->left, tmp->userID, tmp->tickNum);
			}
			return true;
		}
	}
	return false;
}

// public version of the remove ID function
template <typename T>
bool BST<T>::removeID(string userID, int tickNum)
{
	return removeID(root, userID, tickNum);
}

// public version of the remove ticket function
template <typename T>
bool BST<T>::removeNum(string userID, int tickNum)
{
	return removeNum(root, userID, tickNum);
}

// find node in ID BST function
template <typename T>
bool BST<T>::findID(Node* node, string userID, int tickNum)
{
	// if the node doesn't exist
	if (node == nullptr)
	{
		return false;
	}

	// if the ID is less than node's ID, call on left child
	if (userID < node->userID)
	{
		return findNum(node->left, userID, tickNum);
	}

	// if the ID is greater than node's ID, call on right child
	if (userID > node->userID)
	{
		return findNum(node->right, userID, tickNum);
	}

	// if the ID is equal to the node's ID, return truee
	if (node->tickNum == tickNum)
	{
		if (node->userID == userID)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

// find node in ticket BST
// exactly the same as the ID version but with stuff flipped
template <typename T>
bool BST<T>::findNum(Node* node, string userID, int tickNum)
{
	if (node == nullptr)
	{
		return false;
	}
	if (tickNum < node->tickNum)
	{
		return findNum(node->left, userID, tickNum);
	}
	if (tickNum > node->tickNum)
	{
		return findNum(node->right, userID, tickNum);
	}
	if (node->userID == userID)
	{
		if (node->tickNum == tickNum)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

// public version of find ID function
template <typename T>
bool BST<T>::findID(string userID, int tickNum)
{
	return findID(root, userID, tickNum);
}

// public version of find ticket function
template <typename T>
bool BST<T>::findNum(string userID, int tickNum)
{
	return findNum(root, userID, tickNum);
}

// In Order Traversal function
template <typename T>
void BST<T>::inOrder(Node* node, ostream& os)
{
	// in case it's empty
	if (root == nullptr)
	{
		cout << "This BST is empty" << endl;
		return;
	}
	if (node == nullptr)
	{
		return;
	}

	// LNR
	inOrder(node->left, os);
	os << node->userID << " @ " << node->tickNum << endl;
	inOrder(node->right, os);
}

// public version of the inOrder traversal function
template <typename T>
void BST<T>::inOrder(ostream& os)
{
	return inOrder(root, os);
}

// Pre Order Traversal Function
template <typename T>
void BST<T>::preOrder(Node* node, ostream& os)
{
	if (root == nullptr)
	{
		cout << "This BST is empty" << endl;
		return;
	}
	if (node == nullptr)
	{
		return;
	}

	// NLR
	os << node->userID << " @ " << node->tickNum << endl;
	preOrder(node->left, os);
	preOrder(node->right, os);
}

// public version of preOrder traversal function
template <typename T>
void BST<T>::preOrder(ostream& os)
{
	return preOrder(root, os);
}

// Post Order Traversal Function
template <typename T>
int BST<T>::postOrder(Node* node, ostream& os)
{
	if (root == nullptr)
	{
		return 1;
	}
	if (node == nullptr)
	{
		return 0;
	}
	// LRN
	postOrder(node->left, os);
	postOrder(node->right, os);
	os << node->userID << " @ " << node->tickNum << endl;
}

// public version of postOrder traversal function
template <typename T>
int BST<T>::postOrder(ostream& os)
{
	return postOrder(root, os);
}