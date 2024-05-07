// *********************************************************************************
// * Author of this project: Gokhan Unal. There are NO generative AI used in this  *
// * program; including but not limited to: Chatgpt, Google's AI, Github Co-pilot  *
// * or any other cheating machine out there.(not that they are very capable)      *
// * I hate Sam Altman (a person who promotes his religion in any platform         *
// * he is active on), and any person who promotes a religion all the time:)       *
// * I firmly refuse any association with                                          *
// * Sam Altman's or Zuckerberg's AI firms, or the likes of them. I will do this   *
// * for a living, so I am ready 24/7 on my computer to answer any random questions*
// * on my homework or my coding knowledge.                                        *
// * Project name: BET(Binary Expression Tree) project                             *
// * Class: COP4530 - Dr. Gaitros - Due: March 22th 2024                           *
// * Assumptions: The only thing missing is the redundant paranthesis removal,     *
// * otherwise the program prints out valid expressions.                           *
// * *******************************************************************************
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "bet.h"
using namespace std;

int main(void)
{
	BET<string> myinfix1;
	BET<string> myinfix2("4 5 + 5 6 + /");
	BET<string> myinfix3;
	myinfix2.printInfixExpression();
	cout << "Number of Leaf Nodes  in myinfix2: " << myinfix2.leaf_nodes() << endl;
	cout << "Size of myinfix2: " << myinfix2.size() << endl;
	string instr;
	cout << "Enter in a postfix notation: ";
	getline(cin, instr);
	myinfix1.buildFromPostfix(instr);
	myinfix1.printInfixExpression();
	cout << "Number of Leaf Nodes in myinfx1: " << myinfix1.leaf_nodes() << endl;
	cout << "Size of myinfix1: " << myinfix1.size() << endl;
	cout << " Testing the assignment operator= overload" << endl;
	myinfix3 = myinfix2;
	cout << "Size of myinfix3 (copied from myinfx2) is: " << myinfix3.size() << endl;
	myinfix3.printInfixExpression();
	cout << " Testing the copy constructor, creating myinfix4. " << endl;
	BET<string> myinfix4(myinfix1);
	cout << "Size of myinfix4(copied from myinfix1) is: " << myinfix4.size() << endl;
	myinfix4.printInfixExpression();
	cout << endl;
	return 0;
}

