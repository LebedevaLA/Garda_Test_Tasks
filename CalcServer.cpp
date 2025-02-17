#include <iostream>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include<stack>
#include<map>
#include<set>

using namespace std;
class Calculate
{
    private:
        std::string polish;
        std::stack<float> stack;
        float result;


        void Calc()
        {
            std::set<char> signs
            {
                '*','/','+','-'
            };
            int i = 0;
            while (i < polish.length())
            {
                if (!signs.count(polish[i]) && polish[i] != ' ')
                {
                    std::string num = "";
                    while (i < polish.length() && polish[i] != ' ')
                    {
                        num += polish[i];
                        i++;
                    }
                    std::string correctnum = "";
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
        Calculate(std::string polish)
        {
            this->polish = polish;
        }

        float CalcandGetResult()
        {
            Calc();
            return this->result;
        }
};


class Parse
{
    private:
        std::string expression;
        std::string polish;
        std::stack<char> stack;

        bool IsNumber(char ch)
        {
            if ((int)ch <= 47 || (int)ch >= 58) return false;
            return true;
        }


        std::string RealizeUnaryMinus()
        {
            std::string str = "";
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


        std::string RealizeMultiplication(std::string s)
        {
            std::string str = "";
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
            std::string str_with_minus = RealizeUnaryMinus();
            std::string correct_str = RealizeMultiplication(str_with_minus);
            std::map<char, int> signs
            {
                {'+', 0 }, {'-', 0}, {'*',1}, {'/', 1}, {'(', -1}
            };

            std::string polish = "";
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
                    std::string number = "";
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
        Parse(std::string exception)
        {
            this->expression = exception;
        }

        std::string ConvertandGet_polish()
        {
            PolishString();
            return this->polish;
        }

};


class Checker
{
    private:
        std::string expression;
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
            std::set<char> signs
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
        Checker(std::string str)
        {
            this->expression = str;
        }
        bool IsCorrect()
        {
            if (!CheckBrackets() || !CheckSymbols()) return false;
            return true;
        }
};



void* clientHandler (void* lpParam)
{
    intptr_t clientSock = (intptr_t)lpParam;
    char buffer[1024];
    int DataLength;
    std::string data;
    std::string message;
    for(;;)
    {
        DataLength = recv(clientSock, buffer, 1024, 0);
        if (DataLength == 0 || DataLength == -1) {
            cout << "Client disconnected." << endl;
            close(clientSock);
            return 0; 
        }
        std::string data = std::string(buffer, DataLength);
        std::string message;
        Checker check(data);
        if (check.IsCorrect())
        {
            Parse parse(data);
            std::string polish = parse.ConvertandGet_polish();
            Calculate calc_expr(polish);
            message = to_string(calc_expr.CalcandGetResult());
        }
        else
        {
            message = "Uncorrected expression  ";
            message+=data;
        }
        send(clientSock, message.c_str(), message.length(), 0);
    }
    return 0; 
}


int main() {
    int listensocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listensocket == -1) {
        cout << "Can't create a socket" << endl;
        return 1;
    }
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(81);

    bind(listensocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(listensocket, 10);

    cout<<"Server had started"<<endl;

    pthread_t clientThread;
    for(;;){
        struct sockaddr clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int socketforclient = accept(listensocket,&clientAddr, &clientLen);
        if (socketforclient == -1)
        {
            cout<<"Can't accept a client connection"<<endl;
        }
        pthread_create(&clientThread, NULL, clientHandler, (void*)socketforclient); 
    }
    return 0;
}


