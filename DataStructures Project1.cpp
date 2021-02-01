
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <deque>
using namespace std;

typedef struct AST *pNODE;
struct AST { string info; pNODE children[2]; };
struct tokRslt {
	bool success;
	vector<string> syms;
};
struct parseRslt {
	bool success;
	AST ast;
};
struct TPERslt {
	bool val;
	string msg;
};
pNODE cons(string s, pNODE c1, pNODE c2);
void ifonlyfunct(vector<string> V, int j);
void impliesFunct(vector<string> V, int j);
void OrFunct(vector<string> V, int j);
void ReadVector(vector<string> Vin);
void AndFunct(vector<string> V, int j);
void TildeFunc(vector<string> V, int j);
void ParenthesisFunc(vector<string> V);
void prinTree(AST T);
bool eval(AST T);
TPERslt TPE(string s);
string ASTtoString(AST T);
tokRslt tokenize(string);
parseRslt parse(vector<string> V);
string TPEOut(string s);
//global variables
//~~~~~~~~~~~~~~~~
//this guy, this freaking vector gave me so much trouble
//deque replaced the vector because "vector" updates the memory addresses for the entire vector
//when using push_back, making my references unusable. Luckily, deque does not have that issue
//and uses the exact same function calls.
deque<AST> Tree;
int CurrentTreeNode = -1;
int CurrentVectorPos = -1;
AST bad = *cons("Failed to Compile Tree", NULL, NULL);
//~~~~~~~~~~~~~
int main() {
	string BooleanExpression;
	cout << "Please input your boolean expression using only 'T','F','^','v','~','=>','<=>','(',')'." << endl;
	getline(cin, BooleanExpression);
	cout << tokenize(BooleanExpression).success << "\n";
	ReadVector(tokenize(BooleanExpression).syms);
	cout << "\n";
	cout << parse(tokenize(BooleanExpression).syms).success << "\n";
	prinTree(parse(tokenize(BooleanExpression).syms).ast);
	cout << eval(parse(tokenize(BooleanExpression).syms).ast);
	cout << "\n" << TPEOut(BooleanExpression);
	return 0;
}


tokRslt tokenize(string s)
{
	tokRslt valuestoreturn;
	int x = s.length();
	//to avoid errors with checking i+1 and i+2 at the end of a string.
	s = s + ' ' + ' ';
	//checks each character individually to see if its one of the appropriate inputs.
	for (int i = 0; i<x;)
	{
		if (s.at(i) == 'T' || s.at(i) == 'F' || s.at(i) == '^' || s.at(i) == ' '
			|| s.at(i) == 'v' || s.at(i) == '~' || s.at(i) == '(' || s.at(i) == ')')
		{
			valuestoreturn.success = 1;
			i++;
		}
		else if ((s.at(i) + s.at(i + 1)) == '=' + '>')
		{
			valuestoreturn.success = 1;
			i++;
			i++;
		}
		else if ((s.at(i) + s.at(i + 1) + s.at(i + 2)) == '<' + '=' + '>')
		{
			i++; i++; i++; valuestoreturn.success = 1;
		}
		else
		{
			valuestoreturn.success = 0;
			break;
		}
	}
	if (valuestoreturn.success)
	{
		for (int i = 0; i<x;)
		{
			if (s.at(i) == 'T' || s.at(i) == 'F' || s.at(i) == '^'
				|| s.at(i) == 'v' || s.at(i) == '~' || s.at(i) == '(' || s.at(i) == ')')
			{
				valuestoreturn.syms.push_back(string() + s.substr(i, 1));
				i++;
			}
			else if (s.at(i) == ' ')
				i++;
			else if ((s.at(i) + s.at(i + 1)) == '=' + '>')
			{
				valuestoreturn.syms.push_back(string() + s.substr(i, 2));
				i++;
				i++;
			}
			else if ((s.at(i) + s.at(i + 1) + s.at(i + 2)) == '<' + '=' + '>')
			{
				valuestoreturn.syms.push_back(string() + s.substr(i, 3));
				i++; i++; i++;
			}
			else
				cout << "error";
		}
	}
	return valuestoreturn;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
parseRslt parse(vector<string> V)
{
  
	int ParenthesisCounter = 0;
	parseRslt ReturnVal;
	if (V.size()>0)
		ReturnVal.success = 1;
	else
		ReturnVal.success = 0;
	for (int i = 0; i<V.size();)
	{
		if ((V[0] == "T") || (V[0] == "F") || (V[0] == "(") || (V[0] == "~"))
		{
			if ((V[i] == "T") || (V[i] == "F"))
			{
				if ((i + 1)<(V.size()))
				{
					if ((V[(i + 1)] == "T") || (V[(i + 1)] == "F") || (V[(i + 1)] == "~") || (V[(i + 1)] == "("))
					{
						ReturnVal.success = 0;
						break;
					}
					else
						i++;
				}
				else
					i++;
			}
			else if ((V[i] == "^") || (V[i] == "v") || (V[i] == "=>") || (V[i] == "<=>"))
			{
				if ((i + 1)<(V.size()))
				{
					if ((V[(i + 1)] == "T") || (V[(i + 1)] == "F") || (V[(i + 1)] == "~") || (V[(i + 1)] == "("))
					{
						i++;
					}
					else
					{
						ReturnVal.success = 0;
						break;
					}
				}
				else
				{
					ReturnVal.success = 0;
					break;
				}
			}
			else if (V[i] == "~")
			{
				if ((i + 1)<(V.size()))
				{
					if ((V[(i + 1)] == "T") || (V[(i + 1)] == "F") || (V[(i + 1)] == "("))
						i++;
					else
					{
						ReturnVal.success = 0;
						break;
					}
				}
				else
				{
					ReturnVal.success = 0;
					break;
				}
			}
			else if (V[i] == "(")
			{
				ParenthesisCounter++;
				if ((i + 1)<(V.size()))
				{
					if ((V[i + 1] == "T") || (V[i + 1] == "F") || (V[i + 1] == "~") || (V[i + 1] == "("))
					{
						i++;
					}
					else
					{
						ReturnVal.success = 0;
						break;
					}
				}
				else
				{
					ReturnVal.success = 0;
					break;
				}
			}
			else if ((V[i] == ")"))
			{
				ParenthesisCounter--;
				if ((i + 1)<(V.size()))
				{
					if ((V[i + 1] == "T") || (V[i + 1] == "F") || (V[i + 1] == "~") || (V[i + 1] == "("))
					{
						ReturnVal.success = 0;
						break;
					}
					else
						i++;
				}
				else
					i++;
			}
		}
		else
		{
			ReturnVal.success = 0;
			break;
		}
	}
	if (ParenthesisCounter != 0)
		ReturnVal.success = 0;
	//tree converter   
	if (ReturnVal.success == 1) {
		V.push_back(string()); V.push_back(string());
	ParenthesisFunc(V);

		ReturnVal.ast = Tree[(Tree.size()-1)];
	}
	else
	{
		ReturnVal.ast = bad;
	}
	CurrentVectorPos = -1;

//	CurrentTreeNode = -1;
//	Tree.resize(0);
	return ReturnVal;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ParenthesisFunc(vector<string> V)
{

	int LocalVectorPos = CurrentVectorPos;
	int LocalEndParenthPos = 0;
	int x;
	for (int i = (LocalVectorPos + 1); i<(V.size() - 2);)
	{
		if (V[i] == "(")
		{
			CurrentVectorPos++;
			ParenthesisFunc(V);
			i = (CurrentVectorPos);
		}
		else if (V[i] == ")")
		{
			CurrentVectorPos = (i + 1);
			
			return;
		}
		else if (V[i] == "T")
		{
			
			Tree.push_back(*cons("T", (NULL), (NULL)));
			CurrentTreeNode++;
			i++; CurrentVectorPos = i;
		}
		else if (V[i] == "F")
		{
			
			Tree.push_back(*cons("F", NULL, NULL));
			CurrentTreeNode++;
			i++; CurrentVectorPos = i;
		}
		else if (V[i] == "~")
		{
			if (V[i + 1] == "T")
			{
			
			
				Tree.push_back(*cons("T", NULL, NULL));
					CurrentTreeNode++;
				Tree.push_back(*cons("~", &(Tree[Tree.size() - 1]), NULL));
					CurrentTreeNode++;
				i++; i++; CurrentVectorPos = i;
			}
			else if (V[i + 1] == "F")
			{
				
				Tree.push_back(*cons("F", NULL, NULL));
				CurrentTreeNode++;
				Tree.push_back(*cons("~", &(Tree[Tree.size() - 1]), NULL));
				 CurrentTreeNode++;
				i++; i++; CurrentVectorPos = i;
			}
			else if (V[i + 1] == "(")
			{
				CurrentVectorPos++;CurrentVectorPos++;
				ParenthesisFunc(V);
				i = (CurrentVectorPos);
				Tree.push_back(*cons("~", &(Tree[Tree.size() - 1]), NULL));
				CurrentTreeNode++;
			}
		}
		else if (V[i] == "^")
		{
			if (V[i + 1] == "T")
			{

				Tree.push_back(*cons("T", NULL, NULL));
					CurrentTreeNode++;
				Tree.push_back(*cons("^", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			 CurrentTreeNode++;
				i++; i++; CurrentVectorPos = i;
			}
			else if (V[i + 1] == "F")
			{
				Tree.push_back(*cons("F", NULL, NULL));
				 CurrentTreeNode++;
				Tree.push_back(*cons("^", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
				i++; i++; CurrentVectorPos = i;
			}
			else if (V[i + 1] == "~")
			{
				x = (CurrentTreeNode);
				TildeFunc(V, (i + 1));
				i = CurrentVectorPos;
				Tree.push_back(*cons("^", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 1] == "(")
			{
				x = (CurrentTreeNode);
				ParenthesisFunc(V);
				i = (CurrentVectorPos);
				Tree.push_back(*cons("^", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
		}
		//or starts here
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		else if (V[i] == "v")
		{
			if (V[i + 2] == "^")
			{
				x = CurrentTreeNode;
				if (V[i + 1] == "F")
				{
					
					Tree.push_back(*cons("F", NULL, NULL));
					CurrentTreeNode++;
					
				}
				else if (V[i + 1] == "T")
				{
					
					Tree.push_back(*cons("T", NULL, NULL));
					CurrentTreeNode++;
					
				}
				AndFunct(V, (i + 2));
				i = CurrentVectorPos;
				Tree.push_back(*cons("v", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 1] == "T")
			{
				Tree.push_back(*cons("T", NULL, NULL));
				 CurrentTreeNode++;
				Tree.push_back(*cons("v", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
				i++; i++; CurrentVectorPos = i;
			}
			else if (V[i + 1] == "F")
			{
				Tree.push_back(*cons("F", NULL, NULL));
				CurrentTreeNode++;
				Tree.push_back(*cons("v", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++; 
				i++;i++; CurrentVectorPos = i;
			}
			else if (V[i + 1] == "~")
			{
				x = (CurrentTreeNode);
				TildeFunc(V, (i + 1));

				if (V[i + 3] == "^")
				{
					AndFunct(V, (i + 3));
					i = CurrentVectorPos;
				}
				i = CurrentVectorPos;
				Tree.push_back(*cons("v", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 1] == "(")
			{
				x = (CurrentTreeNode);
				ParenthesisFunc(V);
				i = (CurrentVectorPos);
				Tree.push_back(*cons("v", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
		}
		else if (V[i] == "=>")
		{
			if (V[i + 2] == "^")
			{
				x = CurrentTreeNode;
				if (V[i + 1] == "F")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("F", NULL, NULL));
					
				}
				else if (V[i + 1] == "T")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("T", NULL, NULL));
					
				}
				AndFunct(V, (i + 2));
				i = CurrentVectorPos;
				Tree.push_back(*cons("=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 2] == "v")
			{
				x = CurrentTreeNode;
				if (V[i + 1] == "F")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("F", NULL, NULL));
					
				}
				else if (V[i + 1] == "T")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("T", NULL, NULL));
					
				}
				OrFunct(V, (i + 2));
				i = CurrentVectorPos;
				Tree.push_back(*cons("=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 1] == "T")
			{

				Tree.push_back(*cons("T", NULL, NULL));
				Tree.push_back(*cons("=>", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++; CurrentTreeNode++;
				i++; i++; CurrentVectorPos = i;
			}
			else if (V[i + 1] == "F")
			{
				Tree.push_back(*cons("F", NULL, NULL));
				Tree.push_back(*cons("=>", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++; CurrentTreeNode++;
				i++; i++; CurrentVectorPos = i;
			}
			else if (V[i + 1] == "~")
			{
				x = (CurrentTreeNode);
				TildeFunc(V, (i + 1));

				if (V[i + 3] == "^")
				{
					AndFunct(V, (i + 3));
					i = CurrentVectorPos;
				}
				else if (V[i + 3] == "v")
				{
					OrFunct(V, (i + 3));
					i = CurrentVectorPos;
				}
				i = CurrentVectorPos;
				Tree.push_back(*cons("=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 1] == "(")
			{
				x = (CurrentTreeNode);
				ParenthesisFunc(V);
				i = (CurrentVectorPos);
				Tree.push_back(*cons("=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
		}
		else if (V[i] == "<=>")
		{
			if (V[i + 2] == "^")
			{
				x = CurrentTreeNode;
				if (V[i + 1] == "F")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("F", NULL, NULL));
					
				}
				else if (V[i + 1] == "T")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("T", NULL, NULL));
					
				}
				AndFunct(V, (i + 2));
				i = CurrentVectorPos;
				Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 2] == "v")
			{
				x = CurrentTreeNode;
				if (V[i + 1] == "F")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("F", NULL, NULL));
					
				}
				else if (V[i + 1] == "T")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("T", NULL, NULL));
					
				}
				OrFunct(V, (i + 2));
				i = CurrentVectorPos;
				Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 2] == "=>")
			{
				x = CurrentTreeNode;
				if (V[i + 1] == "F")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("F", NULL, NULL));
					
				}
				else if (V[i + 1] == "T")
				{
					CurrentTreeNode++;
					Tree.push_back(*cons("T", NULL, NULL));
				
				}
				impliesFunct(V, (i + 2));
				i = CurrentVectorPos;
				Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 1] == "T")
			{

				Tree.push_back(*cons("T", NULL, NULL));
				Tree.push_back(*cons("<=>", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++; CurrentTreeNode++;
				i++; i++;
			}
			else if (V[i + 1] == "F")
			{
				Tree.push_back(*cons("F", NULL, NULL));
				Tree.push_back(*cons("<=>", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++; CurrentTreeNode++;
				i++; i++;
			}
			else if (V[i + 1] == "~")
			{
				x = (CurrentTreeNode);
				TildeFunc(V, (i + 1));

				if (V[i + 3] == "^")
				{
					AndFunct(V, (i + 3));
					i = CurrentVectorPos;
				}
				else if (V[i + 3] == "v")
				{
					OrFunct(V, (i + 3));
					i = CurrentVectorPos;
				}
				else if (V[i + 3] == "=>")
				{
					impliesFunct(V, (i + 3));
					i = CurrentVectorPos;
				}
				i = CurrentVectorPos;
				Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			}
			else if (V[i + 1] == "(")
			{
				x = (CurrentTreeNode);
				ParenthesisFunc(V);
				i = (CurrentVectorPos);
				Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
				CurrentTreeNode++;
			
			}
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TildeFunc(vector<string> V, int j)
{
	CurrentVectorPos = j;
	for (int i = (CurrentVectorPos); i<V.size();)
	{
		if (V[i + 1] == "T")
		{
			CurrentTreeNode++; CurrentTreeNode++;
			Tree.push_back(*cons("T", NULL, NULL));
			Tree.push_back(*cons("~", &(Tree[Tree.size() - 1]), NULL));
			CurrentVectorPos++; CurrentVectorPos++;
			break;
		}
		else if (V[i + 1] == "F")
		{
			CurrentTreeNode++; CurrentTreeNode++;
			Tree.push_back(*cons("F", NULL, NULL));
			Tree.push_back(*cons("~", &(Tree[Tree.size() - 1]), NULL));
			CurrentVectorPos++; CurrentVectorPos++;
			break;
		}
		else if (V[i + 1] == "(")
		{
			ParenthesisFunc(V);
			i = (CurrentVectorPos);
			Tree.push_back(*cons("~", &(Tree[Tree.size() - 1]), NULL));
			CurrentTreeNode++;
			CurrentVectorPos++;
			break;
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void AndFunct(vector<string> V, int j)
{
	CurrentVectorPos = j ;
	int x;
	for (int i = (CurrentVectorPos); i<(V.size() - 2);)
	{
		if (V[i + 1] == "T")
		{

			Tree.push_back(*cons("T", NULL, NULL));
			Tree.push_back(*cons("^", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++; CurrentTreeNode++;
			i++; i++; CurrentVectorPos = i;
			break;
		}
		else if (V[i + 1] == "F")
		{
			Tree.push_back(*cons("F", NULL, NULL));
			Tree.push_back(*cons("^", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++; CurrentTreeNode++;
			i++; i++; CurrentVectorPos = i;
			break;
		}
		else if (V[i + 1] == "~")
		{
			x = (CurrentTreeNode);
			TildeFunc(V, (i + 1));
			i = CurrentVectorPos;
			Tree.push_back(*cons("^", &(Tree[x]), &(Tree[Tree.size() - 1])));
			break;
		}
		else if (V[i + 1] == "(")
		{
			x = (CurrentTreeNode);
			ParenthesisFunc(V);
			i = (CurrentVectorPos);
			Tree.push_back(*cons("^", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			i++; i++; CurrentVectorPos = i;
			break;
		}
	}

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void OrFunct(vector<string> V, int j)
{
	CurrentVectorPos = j ;
	int x;
	for (int i = (CurrentVectorPos); i<(V.size() - 2);)
	{
		if (V[i + 2] == "^")
		{
			x = CurrentTreeNode;
			if (V[i + 1] == "F")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("F", NULL, NULL));
				
			}
			else if (V[i + 1] == "T")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("T", NULL, NULL));
				
			}
			AndFunct(V, (i + 2));
			i = CurrentVectorPos;
			Tree.push_back(*cons("v", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 1] == "T")
		{

			Tree.push_back(*cons("T", NULL, NULL));
			Tree.push_back(*cons("v", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++; CurrentTreeNode++;
			i++; i++; CurrentVectorPos = i;
			break;
		}
		else if (V[i + 1] == "F")
		{
			Tree.push_back(*cons("F", NULL, NULL));
			Tree.push_back(*cons("v", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++; CurrentTreeNode++;
			i++; i++; CurrentVectorPos = i;
			break;
		}
		else if (V[i + 1] == "~")
		{
			x = (CurrentTreeNode);
			TildeFunc(V, (i + 1));

			if (V[i + 3] == "^")
			{
				AndFunct(V, (i + 3));
				i = CurrentVectorPos;
			}
			i = CurrentVectorPos;
			Tree.push_back(*cons("v", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 1] == "(")
		{
			x = (CurrentTreeNode);
			ParenthesisFunc(V);
			i = (CurrentVectorPos);
			Tree.push_back(*cons("v", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			i = CurrentVectorPos;
			break;
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void impliesFunct(vector<string> V, int j)
{
	CurrentVectorPos = (j );
	int x;
	for (int i = (CurrentVectorPos); i<(V.size() - 2);)
	{
		if (V[i + 2] == "^")
		{
			x = CurrentTreeNode;
			if (V[i + 1] == "F")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("F", NULL, NULL));
		
			}
			else if (V[i + 1] == "T")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("T", NULL, NULL));
				
			}
			AndFunct(V, (i + 2));
			i = CurrentVectorPos;
			Tree.push_back(*cons("=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 2] == "v")
		{
			x = CurrentTreeNode;
			if (V[i + 1] == "F")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("F", NULL, NULL));
				
			}
			else if (V[i + 1] == "T")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("T", NULL, NULL));
				
			}
			OrFunct(V, (i + 2));
			i = CurrentVectorPos;
			Tree.push_back(*cons("=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 1] == "T")
		{

			Tree.push_back(*cons("T", NULL, NULL));
			Tree.push_back(*cons("=>", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++; CurrentTreeNode++;
			i++; i++; CurrentVectorPos = i;
			break;
		}
		else if (V[i + 1] == "F")
		{
			Tree.push_back(*cons("F", NULL, NULL));
			Tree.push_back(*cons("=>", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++; CurrentTreeNode++;
			i++; i++; CurrentVectorPos = i;
			break;
		}
		else if (V[i + 1] == "~")
		{
			x = (CurrentTreeNode);
			TildeFunc(V, (i + 1));

			if (V[i + 3] == "^")
			{
				AndFunct(V, (i + 3));
				i = CurrentVectorPos;
			}
			else if (V[i + 3] == "v")
			{
				OrFunct(V, (i + 3));
				i = CurrentVectorPos;
			}
			i = CurrentVectorPos;
			Tree.push_back(*cons("=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 1] == "(")
		{
			x = (CurrentTreeNode);
			ParenthesisFunc(V);
			i = (CurrentVectorPos);
			Tree.push_back(*cons("=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			i = CurrentVectorPos;
			break;
		}
	}


}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ifonlyfunct(vector<string> V, int j)
{
	CurrentVectorPos = j;
	int x;
	for (int i = (CurrentVectorPos); i<(V.size() - 2);)
	{
		if (V[i + 2] == "^")
		{
			x = CurrentTreeNode;
			if (V[i + 1] == "F")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("F", NULL, NULL));
				
			}
			else if (V[i + 1] == "T")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("T", NULL, NULL));
				
			}
			AndFunct(V, (i + 2));
			i = CurrentVectorPos;
			Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 2] == "v")
		{
			x = CurrentTreeNode;
			if (V[i + 1] == "F")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("F", NULL, NULL));
				
			}
			else if (V[i + 1] == "T")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("T", NULL, NULL));
				
			}
			OrFunct(V, (i + 2));
			i = CurrentVectorPos;
			Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 2] == "=>")
		{
			x = CurrentTreeNode;
			if (V[i + 1] == "F")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("F", NULL, NULL));
				
			}
			else if (V[i + 1] == "T")
			{
				CurrentTreeNode++;
				Tree.push_back(*cons("T", NULL, NULL));
				
			}
			impliesFunct(V, (i + 2));
			i = CurrentVectorPos;
			Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 1] == "T")
		{

			Tree.push_back(*cons("T", NULL, NULL));
			Tree.push_back(*cons("<=>", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++; CurrentTreeNode++;
			i++; i++;
			break;
		}
		else if (V[i + 1] == "F")
		{
			Tree.push_back(*cons("F", NULL, NULL));
			Tree.push_back(*cons("<=>", &(Tree[Tree.size() - 2]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++; CurrentTreeNode++;
			i++; i++;
			break;
		}
		else if (V[i + 1] == "~")
		{
			x = (CurrentTreeNode);
			TildeFunc(V, (i + 1));

			if (V[i + 3] == "^")
			{
				AndFunct(V, (i + 3));
				i = CurrentVectorPos;
			}
			else if (V[i + 3] == "v")
			{
				OrFunct(V, (i + 3));
				i = CurrentVectorPos;
			}
			else if (V[i + 3] == "=>")
			{
				impliesFunct(V, (i + 3));
				i = CurrentVectorPos;
			}
			i = CurrentVectorPos;
			Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			break;
		}
		else if (V[i + 1] == "(")
		{
			x = (CurrentTreeNode);
			ParenthesisFunc(V);
			i = (CurrentVectorPos);
			CurrentTreeNode++;
			Tree.push_back(*cons("<=>", &(Tree[x]), &(Tree[Tree.size() - 1])));
			CurrentTreeNode++;
			i = CurrentVectorPos;
			break;
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pNODE cons(string s, pNODE c1, pNODE c2) {
	pNODE ret = new AST;
	ret->info = s;  // same as (*ret).info = s
	ret->children[0] = c1;
	ret->children[1] = c2;
	return ret;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void prinTree(AST T) {
	// If both children are NULL, just print the symbol
	if (T.children[0] == NULL) {
		cout << T.info;
		return;
	}

	// print an opening paren, followed by the symbol of T, followed
	// by a space, and then the first child.
	cout << "(" << T.info << " ";
	prinTree(*(T.children[0]));
	cout << " ";

	// print the second child if there is one, and then a right paren.
	if (T.children[1] != NULL)
		prinTree(*(T.children[1]));
	cout << ")";
}

void ReadVector(vector<string> Vin)
{
	for (int i = 0; i<Vin.size(); i++)
		cout << Vin[i];
}
string ASTtoString(AST T) //converts an AST to String
{
	string s;
	// If both children are NULL, just print the symbol
	if (T.children[0] == NULL) {
		s = s + T.info;
		return s;
	}

	// print an opening paren, followed by the symbol of T, followed
	// by a space, and then the first child.
	s = s + "(";
	s = s + T.info;
	s = s + " ";
	s += ASTtoString(*(T.children[0]));
	s = s + " ";

	// print the second child if there is one, and then a right paren.
	if (T.children[1] != NULL)
		s += ASTtoString(*(T.children[1]));
	s = s + ")";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool eval(AST T)
{
	bool a;
	bool b;
	string y;
	vector<AST> Evaluator;
	//evaluation rules
	//~T =F, ~F=T
	//T^T =T, else is F
	//TvT;TvF;FvT =T, FvF is F
	//T=>F = F, else is T
	//T<=>T;F<=>F = T, else is F
	if (T.info == "T")
	{
		return 1;
	}
	else if (T.info == "F")
	{
		return 0;
	}
	else if (T.info == "~")
	{
		a = eval(*(T.children[0]));
		if (a)
		{
			return 0;
		}
		else if (!a);
		{
			return 1;
		}
	}
	else if (T.info == "^")
	{
		a = eval(*(T.children[0]));
		b = eval(*(T.children[1]));
		if (a&&b)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (T.info == "v")
	{
		a = eval(*(T.children[0]));
		b = eval(*(T.children[1]));
		if (a || b)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (T.info == "=>")
	{
		a = eval(*(T.children[0]));
		b = eval(*(T.children[1]));
		if (((a) && (!b)))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else if (T.info == "<=>")
	{
		a = eval(*(T.children[0]));
		b = eval(*(T.children[1]));
		if ((a&&b) || ((!a) && (!b)))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

TPERslt TPE(string s)
{
	TPERslt ReturnVal;
	if (tokenize(s).success)
	{
		if (parse(tokenize(s).syms).success)
		{
			ReturnVal.val = (eval(parse(tokenize(s).syms).ast));
			ReturnVal.msg = "success";
		}
		else
		{
			ReturnVal.msg = "grammar error";
			ReturnVal.val = 0;
		}
	}
	else
	{
		ReturnVal.msg = "symbol error";
		ReturnVal.val = 0;
	}
	return ReturnVal;
}

string TPEOut(string s)
{
	string reply;
	if ((TPE(s).msg) == "success")
	{
		if (TPE(s).val)
			reply = "true";
		else
			reply = "false";
	}
	else if ((TPE(s).msg) == "grammar error")
		reply = "grammar error";
	else if ((TPE(s).msg) == "symbol error")
		reply = "symbol error";

	return reply;
}

