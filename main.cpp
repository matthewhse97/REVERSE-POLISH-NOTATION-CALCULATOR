/** @file Reverse-Polish-Notation-Calculator.cpp
 *  This program takes the user input for a postfix expression and calculates it for them.
 *  It is capable of both single and multiple digit calculations.
 *  @author Matthew Reed
 *  @date Oct 2017
 */

#include<iostream>
#include<stack>

using namespace std;
float PostfixCalculator(string expression);                                 //This function evaluates the input and returns its output
float PerformOperation(char operation, float operand1, float operand2);     //This function completes an operation for the calculations
bool IsOperator(char A);                                                    //Checks for if the next character is an operator
bool IsNumericDigit(char A);                                                //Checks if the next character is a digit
int operation_count=0;                                                      //Count for making sure there are less operations than input numbers
int number_count=0;                                                         //Number tracker to counter the operator count
int invalid_char=0;                                                         //For in case an invalid character is input
int main()
{
    string expression;
    while (expression!="exit") {
        expression.clear();                                                 //Clears up expression for next calculation
        operation_count=0;                                                  //Resets the variable
        number_count=0;
        invalid_char=0;
        cout << "Enter Postfix Expression \n";                              //User prompt
        getline(cin, expression);                                           //Stores user input
        if (expression=="exit") break;                                      //If user inputs break will stop program
        float result = PostfixCalculator(expression);                       //Calls the function with the user input
        if (operation_count>number_count){                                  //If there are more operators there are more operators than input numbers
            cout<<"input was invalid please retry"<<endl;
        }
        else if (invalid_char==1){                                          //If an invalid character was input
            cout<<"invalid character entry please retry"<<endl;
        }
        else{                                                               //Else was valid input and outputs the answer
            cout << "Output = " << result << "\n";
        }
    }
}
float PostfixCalculator(string expression)                                  //Function for calculating user input
{
    stack<float> S;                                                         //Declaring stack from standard STL library

    for(int i = 0;i< expression.length();i++) {
        if(expression[i] == ' ' || expression[i] == ',') continue;          //Checks the expression for spaces and commas
        else if(IsOperator(expression[i])) {
            if(operation_count>number_count){                               //Checks that there aren't more operators than numbers
                cout<<"Invalid postfix expression used"<<endl;
                operation_count=operation_count+1;
            }
            else {
                float second_operator = S.top();                            //Pops two elements from the stack, performs the operation, and pushes the results back
                S.pop();
                float first_operator = S.top();
                S.pop();
                float result = PerformOperation(expression[i], first_operator, second_operator);   //performs operation
                S.push(result);                                             //Push results back on stack
                operation_count=operation_count+1;
            }
        }
        else if(IsNumericDigit(expression[i])){
            int operation = 0;                                                //variable for extracting the numeric characters
            while(i<expression.length() && IsNumericDigit(expression[i])) {   //for in case the number is multiple digits
                operation = (operation*10) + (expression[i] - '0');
                i++;
            }
            i--;
            S.push(operation);                                                //Pushes operation on stack
            number_count=number_count+1;
        }
        else{                                                                 //Is in case of the user entering a invalid character
            cout<<expression[i]<<" is an invalid input"<<endl;
            invalid_char=1;
            return invalid_char;
        }
    }
    return S.top();
}

bool IsNumericDigit(char A)                                                    //Checks the character for being a digit returns true/false
{
    if(A >= '0' && A <= '9') return true;
    return false;
}

bool IsOperator(char A)                                                        //Checks the character for being a operator returns true/false
{
    if(A == '+' || A == '-' || A == '*' || A == '/')
        return true;

    return false;
}

float PerformOperation(char operation, float first_operator, float second_operator)       //Function that completes each operation given by user
{
    if(operation == '+') return first_operator +second_operator;
    else if(operation == '-')
        return first_operator - second_operator;
    else if(operation == '*')
        return first_operator * second_operator;
    else if(operation == '/')
    return -1;
}