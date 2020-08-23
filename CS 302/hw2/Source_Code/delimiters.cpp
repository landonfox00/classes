//--------------------------------------------------------------------
//
//   delimiters.cpp
//
//--------------------------------------------------------------------

#include <iostream>

#include "config.h"

#if LAB6_TEST1
#   include "StackLinked.cpp"
#else
#   include "StackArray.cpp"
#endif

//--------------------------------------------------------------------

bool delimitersOk ( const string &expression );

//--------------------------------------------------------------------

// test expr: ()() -> true
bool test1()
{
    std::string expr = "()()";
    bool isValid = delimitersOk( expr );
    std::cout << "delimitersOk: " << expr << ", " << isValid << std::endl;
}

// test expr: (()())() -> true
bool test2()
{
    std::string expr = "(()())()";
    bool isValid = delimitersOk( expr );
    std::cout << "delimitersOk: " << expr << ", " << isValid << std::endl;
}

// test expr: (()(()))) -> false
bool test3()
{
    std::string expr = "(()(())))";
    bool isValid = delimitersOk( expr );
    std::cout << "delimitersOk: " << expr << ", " << isValid << std::endl;
}

// test expr: )())(()) -> false
bool test4()
{
    std::string expr = ")())(())";
    bool isValid = delimitersOk( expr );
    std::cout << "delimitersOk: " << expr << ", " << isValid << std::endl;
}

// test expr: ()(()((()))())()(()(())) -> true
bool test5()
{
    std::string expr = "()(()((()))())()(()(()))";
    bool isValid = delimitersOk( expr );
    std::cout << "delimitersOk: " << expr << ", " << isValid << std::endl;
}

int main()
{
    std::cout << "test1: " <<  test1() << std::endl << std::endl;
    std::cout << "test2: " <<  test2() << std::endl << std::endl;
    std::cout << "test3: " << !test3() << std::endl << std::endl;
    std::cout << "test4: " << !test4() << std::endl << std::endl;
    std::cout << "test5: " <<  test5() << std::endl << std::endl;

    string inputLine;            // Input line
    char   ch;                   // Holding pen for input chars

    cout << "This program checks for properly matched delimiters."
         << endl;

    while( cin )
    {
        cout << "Enter delimited expression (<EOF> to quit) : "
             << endl;

        // Read in one line
        inputLine = "";
        cin.get(ch);
        while( cin && ch != '\n' )
        {
            inputLine = inputLine + ch;
            cin.get(ch);
        }

        if( ! cin )              // Reached EOF: stop processing
            break;
    
        if ( delimitersOk (inputLine) )
            cout << "Valid" << endl;
        else
            cout << "Invalid" << endl;
    }

    return 0;
}

//--------------------------------------------------------------------
// delimitersOk: the function that students must implement for 
//    Programming Exercise 3.
// Note: we used the term "braces" to describe '[' and ']'. It would
//    have been better to use the term "brackets". The program can be
//    easily modified to process any set of matching delimiters.
//--------------------------------------------------------------------

// Insert your delimitersOk function below

bool delimitersOk( const string &expression )
{
    // create linked stack
    StackLinked<char> stack;
    int len = expression.length();
    for ( int i = 0; i < len; i++ )
    {
        char c = expression[ i ];
        // if opening parentheses, push it onto stack
        if ( c == '(' )
            stack.push( c );
        // if closing parentheses, pop corresponding pair
        else if ( c == ')' )
        {
            // if stack is empty while searching for pair, 
            // malformed expression
            if ( stack.isEmpty() )
                return false;
            stack.pop();
        }
    }
    return stack.isEmpty();
}
