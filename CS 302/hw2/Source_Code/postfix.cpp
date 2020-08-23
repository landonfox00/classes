
#include <iostream>

#include "StackLinked.cpp"

StackLinked<char> stack;
std::string inFixExpr;
std::string postFixExpr;

// returns mathematical expression from user input
std::string getInputExpression()
{
	std::string expr;
	std::cout << "Please enter a mathematical expression: ";
	std::getline(std::cin, expr);
	return expr;
}

// returns precendence of operators: '+', '-', '*', '/', '^'
// defaults to -1 precendence
int getPrecedence( char op )
{
	switch( op )
	{
		case '+':
		case '-':
			return 0;
		case '*':
		case '/':
			return 1;
		case '^':
			return 2;
		default:
			return -1;
	}
}

// returns true if c is a digit from 0 to 9
bool isOperand( char c )
{ // characters 0-9
	return c >= 48 && c <= 57;
}

// returns true if c is either '+', '-', '*', '/', '^'
bool isOperator( char c )
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// returns post fix expression given in fix expression
std::string getPostfix( std::string expr, StackLinked<char> stack )
{
	std::string pExpr;
	stack.clear();
	int len = expr.length();
	// incr by 2 to ignore whitespace
	for ( int i = 0; i < len; i += 2 )
	{
		char c = expr[ i ];
		// if operand, place in post fix
		if ( isOperand( c ) )
			pExpr += c;
		// if opening parentheses, push onto stack
		else if ( c == '(' )
			stack.push( c );
		else if ( isOperator( c ) )
		{
			int currPrec = getPrecedence( c );
			while ( true )
			{
				if ( stack.isEmpty() )
					break;
				char op = stack.pop();
				if ( getPrecedence( op ) < currPrec )
				{
					stack.push( op );
					break;
				}
				pExpr += op;
			}
			stack.push( c );
		}
		else if ( c == ')' )
		{
			while ( true )
			{
				char op = stack.pop();
				if ( op == '(' )
					break;
				pExpr += op;
			}
		}
		else
			return "malformed expression";
	}
	while ( !stack.isEmpty() )
		pExpr += stack.pop();
	return pExpr;
}

// test expr: 1+2-3*4/5^6 -> 12+34*56^/-
bool test1()
{
	std::string iExpr = "1 + 2 - 3 * 4 / 5 ^ 6";
	std::string pExpr = getPostfix( iExpr, stack );
	std::cout << "In Fix: " << iExpr << std::endl;
	std::cout << "Post Fix: " << pExpr << std::endl;
	return pExpr == "12+34*56^/-";
}

// test expr: 3-1-2+4*9/0^0+(4-5)*2 -> 31-2-49*00^/+45-2*+
bool test2()
{
	std::string iExpr = "3 - 1 - 2 + 4 * 9 / 0 ^ 0 + ( 4 - 5 ) * 2";
	std::string pExpr = getPostfix( iExpr, stack );
	std::cout << "In Fix: " << iExpr << std::endl;
	std::cout << "Post Fix: " << pExpr << std::endl;
	return pExpr == "31-2-49*00^/+45-2*+";
}

// test expr: (4/5)^2-(6+2) -> 45/2^62+-
bool test3()
{
	std::string iExpr = "( 4 / 5 ) ^ 2 - ( 6 + 2 )";
	std::string pExpr = getPostfix( iExpr, stack );
	std::cout << "In Fix: " << iExpr << std::endl;
	std::cout << "Post Fix: " << pExpr << std::endl;
	return pExpr == "45/2^62+-";
}

// test expr: 8*3/(1+4^4*(2-3)) -> 83*144^23-*+/
bool test4()
{
	std::string iExpr = "8 * 3 / ( 1 + 4 ^ 4 * ( 2 - 3 ) )";
	std::string pExpr = getPostfix( iExpr, stack );
	std::cout << "In Fix: " << iExpr << std::endl;
	std::cout << "Post Fix: " << pExpr << std::endl;
	return pExpr == "83*144^23-*+/";
}

// test expr: (2+5*(1/3)*(6)^(0-4))^9 -> 2513/*604-^*+9^
bool test5()
{
	std::string iExpr = "( 2 + 5 * ( 1 / 3 ) * ( 6 ) ^ ( 0 - 4 ) ) ^ 9";
	std::string pExpr = getPostfix( iExpr, stack );
	std::cout << "In Fix: " << iExpr << std::endl;
	std::cout << "Post Fix: " << pExpr << std::endl;
	return pExpr == "2513/*604-^*+9^";
}

int main()
{
	std::cout << "test1: " << test1() << std::endl << std::endl;
	std::cout << "test2: " << test2() << std::endl << std::endl;
	std::cout << "test3: " << test3() << std::endl << std::endl;
	std::cout << "test4: " << test4() << std::endl << std::endl;
	std::cout << "test5: " << test5() << std::endl << std::endl;

	inFixExpr = getInputExpression();
	postFixExpr = getPostfix( inFixExpr, stack );
	std::cout << postFixExpr << std::endl;
	return 0;
}
