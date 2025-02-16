#include <iostream>
#include <string>
#include <stack>
#include<map>
#include <set>
using namespace std;

class Parse
{
    private:
        string expression;
        string polish;
        stack<char> stack;

        bool IsNumber(char ch)
        {
            if ((int)ch <= 47 || (int)ch >= 58) return false;
            return true;
        }


        string RealizeUnaryMinus()
        {
            string str = "";
            for (int i = 0; i < expression.length(); i++)
            {
                if ((i == 0 || expression[i - 1] == '(') && expression[i] == '-')
                {
                    str += '0';
                    str += expression[i];
                }
                else
                {
                    str += expression[i];
                }
            }
            return (str);
        }


        string RealizeMultiplication(string s)
        {
            string str = "";
            int fl;
            for (int i = 0; i < s.length(); i++)
            {
                fl = 0;
                if (i != 0)
                {
                    if ((IsNumber(s[i]) && s[i - 1] == ')' )|| (s[i]=='(' && s[i-1]==')'))
                    {
                        str += '*';
                        str += s[i];
                        fl = 1;
                    }
                }
                if (i!= s.length() - 1)
                {
                    if(IsNumber(s[i]) && s[i + 1] == '(')
                    {
                        str += s[i];
                        str += '*';
                        fl = 1;
                    }
                }
                if(fl==0) str += s[i];
            }
            return (str);
        }

        void PolishString()
        {
            string str_with_minus = RealizeUnaryMinus();
            string correct_str = RealizeMultiplication(str_with_minus);
            map<char, int> signs
            {
                {'+', 0 }, {'-', 0}, {'*',1}, {'/', 1}, {'(', -1}
            };

            string polish = "";
            int i = 0;
            while (i < correct_str.length())
            {
                if (correct_str[i] == ' ') i++;
                if (signs.count(correct_str[i]) && correct_str[i] != '(')
                {
                    if (stack.empty()) stack.push(correct_str[i]);
                    else
                    {
                        while (stack.size() > 0 && signs[stack.top()] >= signs[correct_str[i]])
                        {
                            polish += stack.top();
                            polish += ' ';
                            stack.pop();
                        }
                        stack.push(correct_str[i]);
                        polish += ' ';
                    }
                    i++;
                }
                else if (correct_str[i] == '(')
                {
                    stack.push('(');
                    i++;
                }
                else if (correct_str[i] == ')')
                {
                    while (stack.size() > 0 && stack.top() != '(')
                    {
                        polish += stack.top();
                        polish += ' ';
                        stack.pop();
                    }
                    if (stack.top() == '(') stack.pop();
                    polish += ' ';
                    i++;
                }
                else
                {
                    string number = "";
                    while (i < correct_str.length())
                    {
                        if (correct_str[i] == '(' || correct_str[i] == ')' || signs.count(correct_str[i]) || correct_str[i] == ' ') break;
                        number += correct_str[i];
                        i++;
                    }
                    polish += number;
                    polish += ' ';
                }


            }
            while (stack.size() > 0)
            {
                polish += stack.top();
                stack.pop();
            }
            this->polish = polish;

        }
    
    public:
        Parse(string exception)
        {
            this->expression = exception;
        }

        string ConvertandGet_polish()
        {
            PolishString();
            return this->polish;
        }

};

class Checker
{
    private:
        string expression;
        int balanse = 0;
        bool CheckBrackets()
        {
            for (int i = 0; i < expression.length(); i++)
            {
                if (balanse < 0) return false;
                if (expression[i] == '(') balanse++;
                else if (expression[i] == ')') balanse--;
            }
            if (balanse == 0) return true;
            return false;
        }

        bool IsNumber(char ch)
        {
            if ((int)ch <= 47 || (int)ch >= 58) return false;
            return true;
        }

        bool CheckSymbols()
        {
            char last = expression[0];
            set<char> signs
            {
                    '*','/','+','-'
            };
            if (last != '-' && last != '(' && !IsNumber(last)) return false;
            for (int i = 1; i < expression.length(); i++)
            {
                if (last == '(' && expression[i] == ')') return false;
                if (expression[i] == ' ') continue;
                if (signs.count(last) && signs.count(expression[i])) return false;
                if (signs.count(last) && expression[i] == ')') return false;
                if (last == '/' && expression[i] == '0')
                {
                    if (i == expression.length() - 1 || (i != expression.length() - 1 && expression[i + 1] != '.')) return false;
                }
                if (expression[i] == '.' && (i == expression.length() - 1 ||
                    !IsNumber(expression[i - 1]) || !IsNumber(expression[i + 1]))) return false;
                if (!signs.count(expression[i]) && expression[i] != '(' && expression[i] != ')' && expression[i] != '.')
                {
                    if (!IsNumber(expression[i])) return false;
                }
                if (i == expression.length() - 1 && signs.count(expression[i])) return false;
                last = expression[i];
            }
            return true;
        }

    public:
        Checker(string str)
        {
            this->expression = str;
        }
        bool IsCorrect()
        {
            if (!CheckBrackets() || !CheckSymbols()) return false;
            return true;
        }
};

class Calculate
{
    private:
        string polish;
        stack<float> stack;
        float result;


        void Calc()
        {
            set<char> signs
            {
                '*','/','+','-'
            };
            int i = 0;
            while (i < polish.length())
            {
                if (!signs.count(polish[i]) && polish[i] != ' ')
                {
                    string num = "";
                    while (i < polish.length() && polish[i] != ' ')
                    {
                        num += polish[i];
                        i++;
                    }
                    string correctnum = "";
                    for (int i=0; i<num.length(); i++){
                        if (num[i] != ' ') correctnum += num[i];
                    }
                    float number = stof(correctnum.c_str());
                    stack.push(number);
                }
                else if (polish[i] != ' ')
                {
                    float first = stack.top();
                    stack.pop();
                    float second = stack.top();
                    stack.pop();
                    if (polish[i] == '+')
                    {
                        stack.push(first + second);
                    }
                    else if (polish[i] == '-')
                    {
                        stack.push(second - first);
                    }
                    else if (polish[i] == '*')
                    {
                        stack.push(first * second);
                    }
                    else
                    {
                        stack.push(second / first);
                    }
                    i++;
                }
                else i++;
            }
            this->result = stack.top();
        }
    public:
        Calculate(string polish)
        {
            this->polish = polish;
        }

        float CalcandGetResult()
        {
            Calc();
            return this->result;
        }
};

int main()
{
    int ch = -1;
    while (ch != 0)
    {
        cout<<"Enter 1 to calculate the expression, and 0 to finish the calculation."<<endl;
        cin >> ch;
        if (ch==1){
            cout<<"Enter the expression"<<endl ;
            string expression;
            cin >> expression; 
            Checker check(expression);
            if (check.IsCorrect())
            {
                Parse parse(expression);
                string polish = parse.ConvertandGet_polish();
                Calculate calc_expr(polish);
                cout<<calc_expr.CalcandGetResult()<<endl;
            }
            else
            {
                cout<<"Uncorrected expression"<<endl;
            }
        }
        else break;
    }
}