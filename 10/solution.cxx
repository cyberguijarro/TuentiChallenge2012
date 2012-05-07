#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef stack<int> evaluation_stack;
enum token_type {
    token_unknown,
    token_value,
    token_negate, // mirror
    token_multiply, // #
    token_duplicate, // breadandfish
    token_pop, // fire
    token_substract, //$
    token_swap, // dance
    token_mod, // conquer
    token_divide, // &
    token_add, // @
    token_eol // .
};

token_type get_token_type(const string& token) {
    token_type result = token_unknown;

    if (all_of(token.begin(), token.end(), [](const char& c) { return isdigit(c); }))
        result = token_value;
    else if (token == "mirror")
        result = token_negate;
    else if (token == "#")
        result = token_multiply;
    else if (token == "breadandfish")
        result = token_duplicate;
    else if (token == "fire")
        result = token_pop;
    else if (token == "$")
        result = token_substract;
    else if (token == "dance")
        result = token_swap;
    else if (token == "conquer")
        result = token_mod;
    else if (token == "&")
        result = token_divide;
    else if (token == "@")
        result = token_add;
    else if (token == ".")
        result = token_eol;

    return result;
}


int main() {
    string line, token;
    ofstream logger("log.txt"); 

    while (cin.good()) {
        evaluation_stack evaluator;

        getline(cin, line);
        logger << line << endl;

        istringstream stream(line);

        while (stream.good()) {
            stream >> token;

            switch (get_token_type(token)) {
                case token_value:
                    evaluator.push(atoi(token.c_str()));
                    break;
                case token_negate:
                    {
                        int a = evaluator.top();

                        evaluator.pop();
                        evaluator.push(-a);
                        break;
                    }
                case token_duplicate:
                    evaluator.push(evaluator.top());
                    break;
                case token_multiply:
                    {
                        int a = evaluator.top(), b;

                        evaluator.pop();
                        b = evaluator.top();
                        evaluator.pop();
                        evaluator.push(a * b);
                        break;
                    }
                case token_pop:
                    evaluator.pop();
                    break;
                case token_substract:
                    {
                        int a = evaluator.top(), b;

                        evaluator.pop();
                        b = evaluator.top();
                        evaluator.pop();
                        evaluator.push(b - a);
                        break;
                    }
                case token_swap:
                    {
                        int a = evaluator.top(), b;

                        evaluator.pop();
                        b = evaluator.top();
                        evaluator.pop();
                        evaluator.push(a);
                        evaluator.push(b);
                        break;
                    }
                case token_mod:
                    {
                        int a = evaluator.top(), b;

                        evaluator.pop();
                        b = evaluator.top();
                        evaluator.pop();
                        evaluator.push(b % a);
                        break;
                    }
                case token_divide:
                    {
                        int a = evaluator.top(), b;

                        evaluator.pop();
                        b = evaluator.top();
                        evaluator.pop();
                        evaluator.push(b / a);
                        break;
                    }
                case token_add:
                    {
                        int a = evaluator.top(), b;

                        evaluator.pop();
                        b = evaluator.top();
                        evaluator.pop();
                        evaluator.push(b + a);
                        break;
                    }
                case token_eol:
                    if (evaluator.size() >= 1)
                        cout << evaluator.top() << endl;
                    else {
                        logger << "unbalanced stack (" << evaluator.size() << ")" << endl;
                    }
                default:
                    break;
            }
        }
    }

    return 0;
}
