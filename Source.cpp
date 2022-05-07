// FILE: parens.cxx
// A small demonstration program for a stack.
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <iostream>    // Provides cin, cout
#include <stack>       // Provides stack
#include <string>      // Provides string
#include <fstream>

using namespace std;

// PROTOTYPE for a function used by this demonstration program
bool is_balanced(const string& expression);
// Postcondition: A true return value indicates that the parentheses in the
// given expression are balanced. Otherwise, the return value is false.

int main()
{
    string filename;

    cout << "Enter File Name: ";
    cin >> filename;
    cout << "\n";

    // When object is created, it'll get the filename
    ifstream inputFile(filename);

    //object will either be a successful file or a nullptr
    if (inputFile)
    {
        string fileData;
        while (!inputFile.eof())
        {
            //info coming from inputFile and going into fileData
            getline(inputFile, fileData);

            if (is_balanced(fileData))
            {
                cout << "Those braces are balanced.\n";
            }
            else
            {
                cout << "Those braces are not balanced.\n";
            }
        }
        inputFile.close();
    }
    else
    {
        cout << "Error: File Nonexistent" << endl;
    }

    cout << "That ends this balancing act.\n";
    return EXIT_SUCCESS;
}

bool is_balanced(const string& expression)
// Library facilities used: stack, string
{
    // Meaningful names for constants
    const char LEFT_PARENTHESIS = '(';
    const char RIGHT_PARENTHESIS = ')';
    const char LEFT_CURLY_BRACES = '{';
    const char RIGHT_CURLY_BRACES = '}';
    const char LEFT_SQUARE_BRACKETS = '[';
    const char RIGHT_SQUARE_BRACKETS = ']';

    stack<char> store;    // Stack to store the left parentheses as they occur
    string::size_type i;  // An index into the string
    char next;            // The next character from the string
    bool failed = false;  // Becomes true if a needed parenthesis is not found
    //not initialized since there is nothing in the stack
    char aboveStack;

    for (i = 0; (i < expression.length()); ++i)
    {
        next = expression[i];
        if (next == LEFT_PARENTHESIS || next == LEFT_CURLY_BRACES || next == LEFT_SQUARE_BRACKETS)
        {
            store.push(next);
        }

        else if (!store.empty())
        {
            aboveStack = store.top();
            if (
                (next == RIGHT_PARENTHESIS && aboveStack == LEFT_PARENTHESIS) ||
                (next == RIGHT_CURLY_BRACES && aboveStack == LEFT_CURLY_BRACES) ||
                (next == RIGHT_SQUARE_BRACKETS && aboveStack == LEFT_SQUARE_BRACKETS)
                )
            {
                store.pop(); // Pops the corresponding left parenthesis.
                failed = false;
            }
            else
            {
                failed = true;
            }

        }
        //else
        //{
        //    failed = true;
        //}
    }
    return (store.empty() && !failed);
}

/*
This comment is the test file contents of what will be attached in HW zip. Output will be in next multiline comment.
name of file: braces.txt
file content:
{balancedSample;}
{imbalancedSample;
(balancedSample;)
(imbalancedSample;
[imbalancedSample;
[balancedSample];
*/

/*
Enter File Name: braces.txt 

Those braces are balanced.
Those braces are not balanced.
Those braces are balanced.
Those braces are not balanced.
Those braces are not balanced.
Those braces are balanced.
That ends this balancing act.

*/