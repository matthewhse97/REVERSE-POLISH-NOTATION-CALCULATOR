
#include<iostream>
#include<stack>

using namespace std;
float EvaluatePostfix(string expression);
float PerformOperation(char operation, float operand1, float operand2);
bool IsOperator(char C);
bool IsNumericDigit(char C);
int operation_count=0;
int number_count=0;
int invalid_input=0;
int main()
{
    string expression;
    while (expression!="exit") {
        expression.clear();
        operation_count=0;
        number_count=0;
        invalid_input=0;
        cout << "Enter Postfix Expression \n";
        getline(cin, expression);
        if (expression=="exit") break;
        float result = EvaluatePostfix(expression);
        if (operation_count>number_count){
            cout<<"input was invalid please retry"<<endl;
        }
        else if (invalid_input==1){
            cout<<"invalid character entry please retry"<<endl;
        }
        else{
            cout << "Output = " << result << "\n";
        }
    }
}
float EvaluatePostfix(string expression)
{
    stack<float> S;

    for(int i = 0;i< expression.length();i++) {
        if(expression[i] == ' ' || expression[i] == ',') continue;
        else if(IsOperator(expression[i])) {
            if(operation_count>number_count){
                cout<<"Invalid postfix expression used"<<endl;
                operation_count=operation_count+1;
            }
            else {
                float operand2 = S.top();
                S.pop();
                float operand1 = S.top();
                S.pop();
                float result = PerformOperation(expression[i], operand1, operand2);
                S.push(result);
                operation_count=operation_count+1;
            }
        }
        else if(IsNumericDigit(expression[i])){
            int operand = 0;
            while(i<expression.length() && IsNumericDigit(expression[i])) {
                operand = (operand*10) + (expression[i] - '0');
                i++;
            }
            i--;
            S.push(operand);
            number_count=number_count+1;
        }
        else{
            cout<<expression[i]<<" is an invalid input"<<endl;
            invalid_input=1;
            return invalid_input;
        }
    }
    return S.top();
}

bool IsNumericDigit(char C)
{
    if(C >= '0' && C <= '9') return true;
    return false;
}

bool IsOperator(char C)
{
    if(C == '+' || C == '-' || C == '*' || C == '/')
        return true;

    return false;
}

float PerformOperation(char operation, float operand1, float operand2)
{
    if(operation == '+') return operand1 +operand2;
    else if(operation == '-')
        return operand1 - operand2;
    else if(operation == '*')
        return operand1 * operand2;
    else if(operation == '/')
        return operand1 / operand2;
    else cout<<"Unexpected Error \n";
    return -1;
}