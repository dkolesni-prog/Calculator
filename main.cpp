#include <iostream>
#include <vector>
#include <cctype>
#include <cassert>
#include <algorithm>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

bool is_number(string letter) {
    if (isdigit(letter[0]))
        return true;
    else
        return false;
}

bool is_op(string letter) {
    if (letter == "+" or letter == "-" or letter == "*" or letter == "/")
        return true;
    else
        return false;
}

int prior_op(string letter) {
    if (letter == "+" or letter == "-")
        return 1;
    else if (letter == "*" or letter == "/") {
        return 2;
    }
}

bool is_float(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !(std::isdigit(c) || c == '.');  }) == s.end();
}

string do_op(string op_a, string op_b, string op) {
    double operand_a = stod(op_a);
    double operand_b = stod(op_b);
    if (op == "+") {
        return std::to_string(operand_a + operand_b);
    }
    else if (op == "-"){
        return std::to_string(operand_a - operand_b);
    }
    if (op == "*"){
        return std::to_string(operand_a * operand_b);
    }
    if (op == "/"){
        return std::to_string(operand_a / operand_b);
    }
}

int main() {
    vector<string> q;
    vector<string> stack;
    string expression;
    cin >> expression;
    bool last_number = false;
    for (int i = 0; i < expression.length(); ++i) {
        string curr = "";
        curr += expression[i];
        if (is_number(curr)) {
            if (last_number) {
                string tmp = q.back() + curr;
                q.pop_back();
                q.push_back((tmp));
            }
            else q.push_back(curr);
            last_number = true;
        }
        else if (curr == ".") {
            assert(last_number);
            string tmp = q.back() + curr;
            q.pop_back();
            q.push_back((tmp));
            last_number = true;
        }
        else if(is_op(curr)) {
            if (stack.empty() or stack.back() == "(") stack.push_back(curr);
            else if (prior_op(stack.back()) < prior_op(curr)) stack.push_back(curr);
            else if (prior_op(stack.back()) >= prior_op(curr)) {
                while (prior_op(stack.back()) > prior_op(curr) and stack.back() != "(") {
                    q.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(curr);
            }

            last_number = false;
        }
        else if (curr == "(") {
            stack.push_back(curr);
            last_number = false;
        }
        else if (curr == ")") {
            while (stack.back() != "(" and !stack.empty()) {
                q.push_back(stack.back());
                stack.pop_back();
            }
            if (stack.back() == "(") stack.pop_back();
            last_number = false;
        }
    }

    while (!stack.empty()) {
        q.push_back(stack.back());
        stack.pop_back();
    }

    std::reverse(q.begin(), q.end());

    //start calculate

    while (!q.empty()) {
        if (q.back() == "(") {
            q.pop_back();
            continue;
        }
        if (is_float(q.back())) {
            stack.push_back(q.back());
            q.pop_back();
        }
        else if (is_op(q.back())) {
            string operand_a = stack.back();
            stack.pop_back();
            string operand_b = stack.back();
            stack.pop_back();
            stack.push_back(do_op(operand_b, operand_a, q.back()));
            q.pop_back();
        }

    }

    cout << stack.back();
//    52.3*61.12+(2-9)*4
//    5*8*(2+9)+(7*5+8-9*(5*5)+5)

    return 0;
}

