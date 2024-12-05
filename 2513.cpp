#include <iostream>
#include <stack>
#include <string>

using namespace std;

int youxianji(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string infixToPostfix(const string &infix)
{
    stack<char> operators;
    string postfix = "";
    for (int i = 0; i < infix.length(); ++i)
    {
        if (isdigit(infix[i]))
        {
            while (isdigit(infix[i]) || infix[i] == '.')
            {
                postfix += infix[i++];
            }
            --i;
        }
        else if (infix[i] == '(')
        {
            operators.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
        {
            while (!operators.empty() && (youxianji(operators.top()) >= youxianji(infix[i])))
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(infix[i]);
        }
        else if (infix[i] == '@')
        {
            break;
        }
    }
    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }
    postfix += '@';
    return postfix;
}

int main()
{
    string infix;
    cin >> infix;
    string postfix = infixToPostfix(infix);
    cout << postfix << endl;
    return 0;
}