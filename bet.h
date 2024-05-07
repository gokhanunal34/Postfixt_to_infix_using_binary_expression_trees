// **************************************************************************
// * Author: Gokhan Unal                                                    *
// * Start Date: 3/18/2024                                                  *
// * Reference & Updates: Rearranged and initialized lc and rc in the struct*
// * rather than writing a constructor for it - I saw this implementation   *
// * in Dr. Gaitros' class on 3/20/2024. As of now, I am choosing to        *
// * continue without keeping track of an integer thesize.                  *
// * ************************************************************************
#ifndef BET_H
#define BET_H
#include <iostream>
#include<sstream>
#include<stack>
#include<string>
#include <cstdlib>
using namespace std;

template<typename T>
class BET
{
private:
	//nested structure binary node
	struct BinaryNode
	{
		string item = " ";
		BinaryNode* leftchild = nullptr;
		BinaryNode* rightchild = nullptr;
	};//BINARY NODE
	//string& returnPostfixExpression(string& temp, BinaryNode* t);
	void printInfixExpression(BinaryNode* n);
	void makeEmpty(BinaryNode*& t);
	BinaryNode* clone(BinaryNode* t);
	void printPostfixExpression(BinaryNode* n);
	size_t size(BinaryNode* t);
	size_t leaf_nodes(BinaryNode* t);
	void deleteStack();
	stack<BinaryNode*> exprstack;//stack of BinaryNode pointers
	BinaryNode* rootnode;

public:
	BET();//empty tree
	BET(const string& postfix);
	BET(const BET&);//COPY CONSTRUCTOR
	~BET();//DESTRUCTOR--CLEAN UP ALL DYNAMIC SPACE IN THE TREE
	bool buildFromPostfix(const string& postfix);
	//DEEP COPY(BinaryNode* clone(BinaryNode*)) UTILIZING ASSIGNTMENT OPTR
	const BET& operator=(const BET&);
	void printInfixExpression();//use private recursive funct
	void printPostfixExpression();//use private recursive funct
	size_t size();//use private recursive funct
	size_t leaf_nodes();//use the private recursive funct 
	bool empty();//tree empty-> true; not empty->false
	bool operatorcheck(string str);
	bool operandcheck(string str);

};//BET
#include "bet.hpp"
#endif // !BET_H

