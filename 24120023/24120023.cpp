#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
//24120023.cpp -o 24120023
//24120023 tests.txt output_24120023.txt
using namespace std;

// BigInt 
string removeZeros(string num);
string addBigIntegers(string a, string b);
string subtractBigIntegers(string a, string b);
string multiplyBigIntegers(string a, string b);
string divideBigIntegers(string a, string b);

// Operator
int precedence(char op);
bool isOperator(char c);
bool isValidExpression(const string& expr);
bool isAbsGreaterOrEqual(string a, string b);

//InfixToPostfix
vector<string> infixToPostfix(string expr);
string evaluatePostfix(vector<string>& postfix);
bool ConsecutiveNumbers(const string& expr);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./" << argv[0] << " <tests.txt> <output_24120023.txt>" << endl;
        return 1; 
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);
    if (!input.is_open() || !output.is_open()) {
        cerr << "Error opening files" << endl;
        return 1;
    }

    string line;
    while (getline(input, line)) {

        if (ConsecutiveNumbers(line)) {
            cout << "Error" << endl;
            output << "Error" << endl;
            continue;
        }
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty() || !isValidExpression(line)) {
            cout << "Error" << endl;
            output << "Error" << endl;
            continue;
        }
        vector<string> postfix = infixToPostfix(line);
        string result = evaluatePostfix(postfix);
        if (result == "Error") cout << result << endl; 
        output << result << endl;
    }

    input.close();
    output.close();
    return 0;
}

bool isAbsGreaterOrEqual(string a, string b) {
    if (a[0] == '-') a = a.substr(1);
    if (b[0] == '-') b = b.substr(1);
    if (a.length() != b.length()) return a.length() > b.length();
    return a >= b;
}

string removeZeros(string num) {
    if (num == "0" || num == "-0") return "0"; 
    if (num[0] == '-') {
        string temp = num.substr(1);
        temp.erase(0, temp.find_first_not_of('0')); 
        if(temp.empty()==true) return "0";
        return "-" + temp; 
    }
    num.erase(0, num.find_first_not_of('0'));
    if (num.empty()) return "0";
    return num;
}

string addBigIntegers(string a, string b) {
    bool negA = a[0] == '-';
    bool negB = b[0] == '-';
    if (negA && negB) return "-" + addBigIntegers(a.substr(1), b.substr(1));
    if (negA) return subtractBigIntegers(b, a.substr(1));
    if (negB) return subtractBigIntegers(a, b.substr(1));

    string ans;
    int temp = 0;
    int i = a.length() - 1, j = b.length() - 1;

    while (i >= 0 || j >= 0 || temp) {
        int sum = temp;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        temp = sum / 10;
        ans.push_back((sum % 10) + '0');
    }
    reverse(ans.begin(), ans.end());
    return removeZeros(ans);
}

string subtractBigIntegers(string a, string b) {
    bool negA = a[0] == '-';
    bool negB = b[0] == '-';
    if (negA && negB) return subtractBigIntegers(b.substr(1), a.substr(1));
    if (negA) return "-" + addBigIntegers(a.substr(1), b);
    if (negB) return addBigIntegers(a, b.substr(1));

    if (!isAbsGreaterOrEqual(a, b)) {
        string ans = subtractBigIntegers(b, a);
        if(ans == "0") return "0";
        else return "-" + ans;
    }

    string ans;
    int temp = 0;
    int i = a.length() - 1, j = b.length() - 1;

    while (i >= 0 || j >= 0) {
        int digitA = i >= 0 ? a[i--] - '0' : 0;
        int digitB = j >= 0 ? b[j--] - '0' : 0;
        digitA -= temp;
        if (digitA < digitB) {
            digitA += 10;
            temp = 1;
        } else {
            temp = 0;
        }
        ans.push_back((digitA - digitB) + '0');
    }
    reverse(ans.begin(), ans.end());
    return removeZeros(ans);
}

string multiplyBigIntegers(string a, string b) {
    bool neg = (a[0] == '-' && b[0] != '-') || (a[0] != '-' && b[0] == '-'); 
    if (a[0] == '-') a = a.substr(1);
    if (b[0] == '-') b = b.substr(1);

    int len1 = a.length(), len2 = b.length();
    vector<int> ans(len1 + len2, 0);

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int sum = mul + ans[i + j + 1];
            ans[i + j + 1] = sum % 10;
            ans[i + j] += sum / 10;
        }
    }

    string res;
    for (int x : ans) {
        if (!(res.empty() && x == 0)) res.push_back(x + '0');
    }
    if (res.empty()) res = "0";
    if (neg && res != "0") return "-" + res;
    return res;
}

string divideBigIntegers(string a, string b) {
    if (b == "0") return "Error";
    bool neg = (a[0] == '-' && b[0] != '-') || (a[0] != '-' && b[0] == '-');
    if (a[0] == '-') a = a.substr(1);
    if (b[0] == '-') b = b.substr(1);

    a = removeZeros(a);
    b = removeZeros(b);
    if (a == "0") return "0";
    if (!isAbsGreaterOrEqual(a, b)) return "0";

    string quotient;
    string cur;
    int idx = 0;

    while (idx < a.length()) {
        cur += a[idx++];
        cur = removeZeros(cur);
        if (cur == "0") {
            quotient += "0";
            continue;
        }

        int q = 0;
        string temp = cur;
        while (isAbsGreaterOrEqual(temp, b)) {
            temp = subtractBigIntegers(temp, b);
            q++;
        }
        cur = temp;
        quotient += to_string(q);
    }

    quotient = removeZeros(quotient);
    if(neg && quotient != "0") return "-" + quotient;
    else return quotient;
}

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isValidExpression(const string& expr) {
    int parenCount = 0;
    bool expectNumber = true; 
    bool lastTokenWasNumber = false; 

    for (int i = 0; i < expr.length(); ++i) {
        char c = expr[i];

        if (c == '(') {
            parenCount++;
            expectNumber = true;
            lastTokenWasNumber = false;
        } else if (c == ')') {
            if (expectNumber) return false; 
            parenCount--;
            lastTokenWasNumber = false;
        } else if (isdigit(c)) {
            if (lastTokenWasNumber) return false; 
            lastTokenWasNumber = true;
            expectNumber = false;
            while (i + 1 < expr.length() && isdigit(expr[i + 1])) i++;
        } else if (c == '-' && (i == 0 || expr[i - 1] == '(' || isOperator(expr[i - 1]))) {
            expectNumber = true;
            lastTokenWasNumber = false;
        } else if (isOperator(c)) {
            if (expectNumber) return false;
            expectNumber = true;
            lastTokenWasNumber = false;
        } else {
            return false; 
        }

        if (parenCount < 0) return false; 
    }

    return parenCount == 0 && !expectNumber;
}

vector<string> infixToPostfix(string expr) {
    vector<string> postfix;
    stack<char> ops;
    string num;

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '-' && (i == 0 || expr[i-1] == '(' || isOperator(expr[i-1]))) {
            num += expr[i]; 
            if (i + 1 < expr.length() && expr[i + 1] == '(') {
                i++;
                int parenCount = 1;
                string nested;
                while (i + 1 < expr.length() && parenCount > 0) {
                    i++;
                    if (expr[i] == '(') parenCount++;
                    else if (expr[i] == ')') parenCount--;
                    if (parenCount > 0) nested += expr[i];
                }
                num += nested;
            } else {
                while (i + 1 < expr.length() && isdigit(expr[i + 1])) {
                    num += expr[++i];
                }
            }
        } else if (isdigit(expr[i])) {
            num += expr[i];
            while (i + 1 < expr.length() && isdigit(expr[i + 1])) {
                num += expr[++i];
            }
        } else if (isOperator(expr[i]) || expr[i] == '(' || expr[i] == ')') {
            if (!num.empty()) {
                postfix.push_back(num);
                num.clear();
            }
            if (expr[i] == '(') {
                ops.push(expr[i]);
            } else if (expr[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    postfix.push_back(string(1, ops.top()));
                    ops.pop();
                }
                if (!ops.empty()) ops.pop(); // Remove '('
            } else if (isOperator(expr[i])) {
                while (!ops.empty() && ops.top() != '(' &&
                       precedence(ops.top()) >= precedence(expr[i])) {
                    postfix.push_back(string(1, ops.top()));
                    ops.pop();
                }
                ops.push(expr[i]);
            }
        }
    }
    if (!num.empty()) postfix.push_back(num);
    while (!ops.empty()) {
        if (ops.top() != '(') postfix.push_back(string(1, ops.top()));
        ops.pop();
    }
    return postfix;
}

string evaluatePostfix(vector<string>& postfix) {
    stack<string> operands;

    for (const string& token : postfix) {
        if (!isOperator(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
            operands.push(token);
        } else if (isOperator(token[0])) {
            if (operands.size() < 2) return "Error";
            string b = operands.top(); operands.pop();
            string a = operands.top(); operands.pop();
            string result;
            if (token == "+") result = addBigIntegers(a, b);
            else if (token == "-") result = subtractBigIntegers(a, b);
            else if (token == "*") result = multiplyBigIntegers(a, b);
            else if (token == "/") result = divideBigIntegers(a, b);
            if (result == "Error") return result;
            operands.push(result);
        }
    }
    if(operands.size()==1) return removeZeros(operands.top());
    else return "Error";
}

bool ConsecutiveNumbers(const string& expr) {
    bool lastWasNumber = false;
    string token;

    for (int i = 0; i < expr.length(); ++i) {
        char c = expr[i];
        if (isdigit(c)) {
            if (!lastWasNumber) {
                if (!token.empty() && token.back() == 'N') {
                    return true;
                }
                token += 'N'; 
            }
            lastWasNumber = true;
        } else if (isspace(c)) {
            lastWasNumber = false;
            continue;
        } else if (isOperator(c) || c == '(' || c == ')') {
            token.clear(); 
            lastWasNumber = false;
        } else {
            lastWasNumber = false;
            token.clear();
        }
    }

    return false;
}