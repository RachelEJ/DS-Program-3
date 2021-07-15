/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler: Visual Studio
Program Description: Program that manages 2 BSTs and organizes them by user ID and ticket number.
*/

#include <iostream>
#include <ostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include "bst.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::istream;
using std::ifstream;
using std::ofstream;
using std::stringstream;

// Function that saves the user BST into a file
void saveID(BST<Node>& user, ofstream& of, string fileName)
{
	of.open(fileName);
	if (of.is_open())
	{
		if (user.postOrder(of) == 1)
		{
			cout << "This BST is empty and " << fileName << " has not been saved" << endl << endl;
		}
		else
		{
			cout << "BST successfully saved into " << fileName << endl << endl;
		}
	}
	else
	{
		cout << "Failed to open the file" << endl;
	}
	of.close();
}

// Function that saves the ticket BST into a file
void saveNum(BST<Node>&ticketNum, ofstream& of, string fileName)
{
	of.open(fileName);
	if (of.is_open())
	{
		if (ticketNum.postOrder(of) == 1)
		{
			cout << "This BST is empty and " << fileName << " has not been saved" << endl << endl;
		}
		else
		{
			cout << "BST successfully saved into " << fileName << endl << endl;
		}
	}
	else
	{
		cout << "Failed to open the file" << endl;
	}
	of.close();
}

// Parsing Function that reads all commands and calls functions accordingly
void readLines(istream& is, bool isFile, BST<Node>&user, BST<Node>&ticketNum)
{
	while (true)
	{
		string line;
		string cmd;
		string arg1;
		string arg2;
		string arg3;
		if (isFile && is.eof()) return;
		getline(is, line);
		stringstream ss(line);
		getline(ss, cmd, ' ');
		cout << endl;

		// Exits the program
		if (cmd == "exit") return;

		// Loads up a file and processes it
		if (cmd == "load")
		{
			// This whole function is broken for now
			// Problem: How to differentiate between data and command files?

			ifstream inFile;
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must specify a file to open. Please try again" << endl << endl;
			}
			else
			{
				inFile.open(arg1);
				cout << "Attempting to open file..." << endl << endl;
				if (inFile.is_open())
				{
					readLines(inFile, true, user, ticketNum);
					cout << "File opened successfully" << endl << endl;
				}
				else
				{
					cout << "Failed to open the file" << endl << endl;
				}
				inFile.close();
			}
		}

		// Display Function
		if (cmd == "display")
		{
			// In case they don't have enough inputs
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must specify a BST and which traversal" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must specify which traversal" << endl << endl;
				}
				else
				{
					// displays the user BST
					if (arg1 == "user")
					{
						// displays In Order Traversal
						if (arg2 == "in")
						{
							cout << "User ID's In Order Traversal: " << endl << endl;
							user.inOrder(cout);
							cout << endl;
						}
						// displays Pre Order Traversal
						if (arg2 == "pre")
						{
							cout << "User ID's Pre Order Traversal: " << endl << endl;
							user.preOrder(cout);
							cout << endl;
						}
						// displays Post Order Traversal
						if (arg2 == "post")
						{
							cout << "User ID's Post Order Traversal: " << endl << endl;
							if (user.postOrder(cout) == 1)
							{
								cout << "This BST is empty" << endl;
							}
							cout << endl;
						}
					}
					// displays ticket BST
					if (arg1 == "ticket")
					{
						// displays In Order Traversal
						if (arg2 == "in")
						{
							cout << "Ticket Number's In Order Traversal: " << endl << endl;
							ticketNum.inOrder(cout);
							cout << endl;
						}
						// displays Pre Order Traversal
						if (arg2 == "pre")
						{
							cout << "Ticket Number's Pre Order Traversal: " << endl << endl;
							ticketNum.preOrder(cout);
							cout << endl;
						}
						// display Post Order Traversal
						if (arg2 == "post")
						{
							cout << "Ticket Number's Post Order Traversal: " << endl << endl;
							if (ticketNum.postOrder(cout) == 1)
							{
								cout << "This BST is empty" << endl;
							}
							cout << endl;
						}
					}
				}
			}
		}

		// New Function
		if (cmd == "new")
		{
			// basically deletes both BSTs
			user.~BST();
			ticketNum.~BST();
			cout << "BSTs cleared" << endl << endl;
		}

		// Remove Function
		if (cmd == "remove")
		{
			// in case the user doesn't have enough inputs
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must specify a user ID to remove" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must specify a ticket number to remove" << endl << endl;
				}
				else
				{
					try
					{
						// sets arg2 into an integer
						int arg2Int = stoi(arg2);

						// removes the data set from the BSTs and stores values if they worked
						int checkRemID = user.removeID(arg1, arg2Int);
						int checkRemNum = ticketNum.removeNum(arg1, arg2Int);

						// tell user if the removes worked or not
						if ((checkRemID + checkRemNum) == 2)
						{
							cout << arg1 << " @ " << arg2 << " has been removed successfully" << endl << endl;
						}

						// really not sure when this one can display but just in case
						else if ((checkRemID + checkRemNum) == 1)
						{
							cout << "An error has occurred. Please try again" << endl << endl;
						}

						// in case both removes fail
						else if ((checkRemID + checkRemNum) == 0)
						{
							cout << "Unable to remove " << arg1 << " @ " << arg2 << endl << endl;
						}

						// not sure how this one can display either
						else
						{
							cout << "An error has occurred. Please try again" << endl << endl;
						}
					}

					// for when stoi doesn't work because arg2 isn't a number
					catch (...)
					{
						cout << "You must specify a ticket number to remove" << endl << endl;
					}
				}
			}
		}

		// Find Function
		if (cmd == "find")
		{
			// in case the user doesn't have enough inputs
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must specify a user ID to find" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must specify a ticket number to find" << endl << endl;
				}
				else
				{
					try
					{
						// once again using the stoi function
						int arg2Int = stoi(arg2);

						// finds the data set and returns integer values
						int checkFindID = user.findID(arg1, arg2Int);
						int checkFindNum = ticketNum.findNum(arg1, arg2Int);

						// gives user feedback as to whether or not it worked
						if ((checkFindID + checkFindNum) == 2)
						{
							cout << arg1 << " @ " << arg2 << " was found" << endl << endl;
						}
						else if ((checkFindID + checkFindNum) == 1)
						{
							cout << "An error has occurred. Please try again" << endl << endl;
						}
						else if ((checkFindID + checkFindNum) == 0)
						{
							cout << "Unable to find " << arg1 << " @ " << arg2 << endl << endl;
						}
						else
						{
							cout << "An error has occurred. Please try again" << endl << endl;
						}
					}

					// in case stoi fails
					catch (...)
					{
						cout << "You must specify a ticket number to find" << endl << endl;
					}
				}
			}
		}

		// Add Function
		if (cmd == "add")
		{
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must specify a user ID to add" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2))
				{
					cout << "You must specify a ticket number to add" << endl << endl;
				}
				else
				{
					try
					{
						int arg2Int = stoi(arg2);
						int checkAddID = user.insertID(arg1, arg2Int);
						int checkAddNum = ticketNum.insertNum(arg1, arg2Int);
						if ((checkAddID + checkAddNum) == 2)
						{
							cout << arg1 << " @ " << arg2 << " has been inserted successfully" << endl << endl;
						}
						else if ((checkAddID + checkAddNum) == 1)
						{
							cout << "An error has occurred. Please try again" << endl << endl;
						}
						else if ((checkAddID + checkAddNum) == 0)
						{
							cout << "Unable to insert " << arg1 << " @ " << arg2 << endl << endl;
						}
						else
						{
							cout << "An error has occurred. Please try again" << endl << endl;
						}
					}
					catch (...)
					{
						cout << "You must specify a ticket number to find" << endl << endl;
					}
				}
			}
		}

		// Save Function
		if (cmd == "save")
		{
			if (!getline(ss, arg1, ' '))
			{
				cout << "You need to specify a BST to save. Please try again" << endl << endl;
			}
			else
			{
				if (!getline(ss, arg2, ' '))
				{
					cout << "You need to specify a file to save the BST into. Please try again" << endl << endl;
				}
				else
				{
					// gotta have "into"
					if (arg2 == "into")
					{
						if (!getline(ss, arg3))
						{
							cout << "You need to specify a file to save the BST into. Please try again" << endl << endl;
						}
						else
						{
							// saves user BST into file
							if (arg1 == "user")
							{
								ofstream of;
								saveID(user, of, arg3);
							}

							// saves ticket BST into file
							if (arg1 == "ticket")
							{
								ofstream of;
								saveNum(ticketNum, of, arg3);
							}
						}
					}
				}
			}
		}
	}
}

// my very short main function
int main()
{
	BST<Node> user;
	BST<Node> ticketNum;

	readLines(cin, false, user, ticketNum);

	return 0;
}