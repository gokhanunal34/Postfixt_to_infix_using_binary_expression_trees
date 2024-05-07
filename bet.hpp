// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Start Date: 3/18/2024                                                         *
// * For the sake of consistency, each line of code or description is limited      *
// * to 85 charachters. Forgive me if there are slip ups in max chars per line.    *
// * ******************************************************************************* 


// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/18/2024                                                               *
// * Description: non-parameter constructor that initiates an empty tree.          *
// * *******************************************************************************
template<typename T>
BET<T>::BET()
{
	//empty tree
	//everything the new Binary node points to nullptr by default in the
	//struct
	rootnode = new BinaryNode;
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024-3/21/2024                                                     *
// * Description: calls the private helper makeEmpty                               *
// * *******************************************************************************
template<typename T>
BET<T>::~BET()
{
	if (!empty()) { makeEmpty(rootnode); }
	if (rootnode != nullptr) { delete rootnode; }
	deleteStack();
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024-3/21/2024-3/22/2024                                           *
// * Description: return true if a valid tree is built, false otherwise            *
// * References: Algorithim is fully from Postfixtoinfix.pptx slide #3,            *
// * my in2post.cpp evaluatepost function and Dr. Gaitros' postfixtoinfix          *
// * video.                                                                        *
// * *******************************************************************************
template<typename T>
bool BET<T>::buildFromPostfix(const string& postfix)
{
	//if there are nodes in the current tree; delete them first
	//as per instructions
	if (!empty()) 
	{ 
		makeEmpty(rootnode); 
		//delete the stack just incase 
		deleteStack();
	}
	//boolean control for return value
	bool control = true;
	string p = postfix;
	string curr {};
	istringstream stream(postfix);
	//step 1: while there are input symbols left
	while (stream >> curr)
	{
		try
		{
			//step 2: if the symbol is an operand, push it onto the stack
			if (operandcheck(curr))
			{
				BinaryNode* n = new BinaryNode;
				n->item = curr;
				exprstack.push(n);
			}
			else if (exprstack.size() < 2) 
			{
				throw error_code();
			}
			//step 5: pop two vals and push the root onto the stack
			else 
			{
				BinaryNode* rightc = exprstack.top(); 
				exprstack.pop();//pop #1
				BinaryNode* leftc = exprstack.top();
				exprstack.pop();//pop #2
				
				BinaryNode* root = new BinaryNode;
				root->item = curr;
				root->rightchild = rightc;
				root->leftchild = leftc;
				//step 7: push the root of the tree back to the stack
				exprstack.push(root);
			}
		}
		catch (const error_code& ec)
		{
			std::cerr << "--INSUFFICIENT VALUES IN THE EXPRESSION--" << endl;
			control = false;
			exit;
		}
	}//while loop
	
	//step 8 & 9: if there are more values on the stack
	if (!exprstack.empty() && control == true)
	{
		rootnode = exprstack.top();
		exprstack.pop();
		//if there is another value, it should return false
		if (!exprstack.empty()) { return false; }
	}
	//any other condition will also yield false
	else 
	{
		control = false;
	}
	//if it is flagged false, delete everything
	if (!control)
	{       
		makeEmpty(exprstack.top());
		deleteStack();//delete if redundant
	}
	//return true if tree is successful false if not.
	return control;
}//function end

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/21/2024                                                               *
// * Description: Private helper delete the binary expression stack                *
// * *******************************************************************************
template<typename T>
void BET<T>::deleteStack()
{
	while (!exprstack.empty())
	{
		exprstack.pop();
	}
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024                                                               *
// * Description: return true if empty, false if not empty                         *
// * *******************************************************************************
template<typename T>
bool BET<T>::empty()
{
	return (rootnode == nullptr);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024                                                               *
// * Description:one-parameter constructor, where parameter "postfix" is           *
// * string containing a postfix expression.The tree should be built based         *
// * on the postfix expression.Tokens in the postfix expression are                *
// * separated by spaces.                                                          *
// * *******************************************************************************
template<typename T>
BET<T>::BET(const string& postfix)
{
	rootnode = new BinaryNode;
	//rootnode->item = postfix;
	//printPostfixExpression(rootnode);
	//cout << endl;
	//buildFromPostfix(rootnode);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/18/2024                                                               *
// * Description:copy constructor - makes appropriate deep copy of the tree        *
// * *******************************************************************************
template<typename T>
BET<T>::BET(const BET& tree)
{
	rootnode = clone(tree.rootnode);//clone goes all the way
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/18/2024-3/19/2024-3/20/2024                                           *
// * Description:clone all nodes in the subtree pointed to by t.Can be             *
// * called by functions such as the assignment operator=.                         *
// * This is a recursive implementation                                            *
// * *******************************************************************************
template<typename T>
typename BET<T>::BinaryNode* BET<T>::clone(BinaryNode* t)
{
	//empty case
	if (t == nullptr){return nullptr;}
	//newnode points to the dynamically created BinaryNode
	BinaryNode* newnode = new BinaryNode;
	//copy the parent, then keep going on until there is no recursion
	newnode->item = t->item;
	newnode->leftchild = clone(t->leftchild);
	newnode->rightchild = clone(t->rightchild);
	//return newnode ptr
	return newnode;
	
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024                                                               *
// * Function name: size(BinaryNode* t) - private helper                           *
// * Description:Return the number of nodes in the tree                            *
// * Reference: Dr. Gaitros' 3/20 class verbatim                                   *
// * *******************************************************************************
template<typename T>
size_t BET<T>::size(BinaryNode* t)
{
	if (t == nullptr) { return 0; }
	else 
	{
		return (size(t->leftchild) + size(t->rightchild) + 1);
	}
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024                                                               *
// * Description:Return the number of nodes in the tree (using the private         *
// * recursive function)                                                           *
// * Reference: Dr. Gaitros' 3/20 class verbatim                                   *
// * *******************************************************************************
template<typename T>
size_t BET<T>::size()
{
	return size(rootnode);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024                                                               *
// * Function name: leaf_nodes(BinaryNode* t) - private helper                     *
// * Description:return the number of leaf nodes in the subtree pointed            * 
// * to by BinaryNode* t                                                           *
// * Reference: Dr. Gaitros' 3/20 class verbatim                                   *
// * ******************************************************************************* 
template<typename T>
size_t BET<T>::leaf_nodes(BinaryNode* t)
{
	if (t == nullptr) { return 0; }
	//size 1 case
	else if (t->leftchild == nullptr && t->rightchild == nullptr) {return 1;}
	else 
	{
		return (leaf_nodes(t->leftchild) + leaf_nodes(t->rightchild));
	}
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024                                                               *
// * Function name: leaf_nodes()                                                   *
// * Description:uses the recursive private helper above                           *
// * Reference: Dr. Gaitros' 3/20 class verbatim                                   *
// * *******************************************************************************
template<typename T>
size_t BET<T>::leaf_nodes()
{
	return leaf_nodes(rootnode);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024                                                               *
// * Function name: make empty                                                     *
// * Description:Private helper. Delete all nodes in the subtree pointed           *
// * to by t.                                                                      *
// * Reference: Dr. Gaitros' 3/20 class verbatim                                   *
// * *******************************************************************************
template <typename T>
void BET<T>::makeEmpty(BinaryNode* &t)
{
	if (t == nullptr) { return; }
	else
	{
		if (t->leftchild != nullptr) { makeEmpty(t->leftchild); }
		if (t->rightchild != nullptr) { makeEmpty(t->rightchild); }
		delete t;
	}
	//set t to nullptr
	t = nullptr;
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/20/2024                                                               *
// * Function name: printPostfixExpression(BinaryNode* n)                          *
// * Description:Private helper.print to the standard output the                   *
// * corresponding postfix expression.                                             *
// * Reference: Dr. Gaitros' 3/20 class verbatim                                   *
// * *******************************************************************************
template <typename T>
void BET<T>::printPostfixExpression(BinaryNode* n)
{	
	//empty case
	if (n == nullptr) { return; }
	//if n is not empty then go into the recursion
	printPostfixExpression(n->leftchild);
	printPostfixExpression(n->rightchild);
	//print the data at the current note and add a space after each string
	cout << n->item << " ";
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/21/2024                                                               *
// * Function name: printPostfixExpression()                                       *
// * Description: Calls the private helper function                                *
// * Reference: Dr. Gaitros' 3/20 class verbatim                                   *
// * *******************************************************************************
template<typename T>
void BET<T>::printPostfixExpression()
{
	printPostfixExpression(rootnode);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/22/2024                                                               *
// * Function name: printInfixfixExpression(BinaryNode* n)                         *
// * Description:Private helper.print to the standard output the                   *
// * corresponding infix expression.                                               *
// * Reference: Derived and expanded from my printPostfixExpression function       *
// * which is taken from Dr. Gaitros' 3/20/2024 class                              *
// * *******************************************************************************
template<typename T>
void BET<T>::printInfixExpression(BinaryNode* n)
{
	if (n != nullptr)
	{
		//if operator and not the root
		if (operatorcheck(n->item) && n != rootnode)
		{
			cout << "( ";
		}//inner if

		//recursion
		//print leftchild
		printInfixExpression(n->leftchild);
		//print the data
		cout << n->item << " "; //space after each itm
		//recursion for right cihld
		printInfixExpression(n->rightchild);
		
		//exit check
		if (operatorcheck(n->item) && n != rootnode)
		{
			cout << ") ";
		}
	}//major condition if
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/22/2024                                                               *
// * Function name: printInfixfixExpression()                                      *
// * Description: Calls the private helper                                         * 
// * *******************************************************************************
template<typename T>
void BET<T>::printInfixExpression()
{
	printInfixExpression(rootnode);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/21/2024                                                               *
// * Description: return true if operator, false otherwise                         *
// * *******************************************************************************
template <typename T>
bool BET<T>::operatorcheck(string str)
{
	//return true if str is an operator
	return (str == "*" || str == "/" || str == "+" || str == "-");
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/21/2024                                                               *
// * Description: return true if valid operand, false otherwise                    *
// * I am aware that it is easy to mix up operandcheck with operatorcheck          *
// * yet this is the cleanest name I can come up with my English.                  *
// * *******************************************************************************
template <typename T>
bool BET<T>::operandcheck(string str)
{
	//check if it is just one character or multi char string
	if (str.length() == 1)
	{
		//force c to the length 1 str
		char c = str[0];
		//if it is a valid single character operand and not an operator
		// return true. Don't forget underscore in any version of this code
		return(c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' ||
			c >= 'a' && c <= 'z' || c == '_');
	}
	//if str is longer than 1 char, then assume it is a valid operand and 
	//return true
	else { return true; }

}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Date: 3/22/2024                                                               *
// * Function name: operator=                                                      *
// * Description: Returns const BET<T>& and simply overloads operator =            *
// * using the private helper clone(BinaryNode* n)                                 *
// * *******************************************************************************
template<typename T>
const BET<T>& BET<T>::operator=(const BET<T>&)
{
	rootnode = clone(rootnode);
	return *this;//return current rootnode after cloning
}