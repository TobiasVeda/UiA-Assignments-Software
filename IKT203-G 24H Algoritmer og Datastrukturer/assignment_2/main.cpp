#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

class Convert {
private:
//    static inline std::stack<std::string> stack;
//    static inline std::stack<std::string> stack_reserve; // used to temporarily store the main stack, so that convert can be used
    static inline std::map<std::string, int> operators = {
          //{operator, priority}
            {"+", 1},
            {"-", 1},
            {"*", 2},
            {"/", 2},
            {"%", 2},
            {"^", 3}
        // add another level of priority instead of
        // bothering with determining left and right leaning operators
    };
    static inline std::vector<std::string> functions = {"sin", "cos", "tan", "log", "ln"};

    // used to correctly parse parenthesis after a function
    static inline bool func_mode = false;
    static inline std::string func_string; // temporarily stores content of the function
    static inline std::vector<std::string> func_storage; // used for nested functions

    // used correctly parse function to the power of.: sin^2(x)
    static inline bool func_infix_power_mode = false; // syntax was used
    static inline std::string func_infix_power_string; // temporarily stores content of power


    static bool is_operator(std::string &s) {
        return operators.find(s) != operators.end();
    }

    static bool is_function(std::string &s){
        // tries to find a match among the function list
        return std::find(functions.begin(), functions.end(), s) != functions.end();
    }

    static bool is_operand(std::string &s){
        // if a character is neither an operator nor a function, it must be an operand
        return !is_operator(s) && !is_function(s) && s != "(" && s != ")";
    }

    static int get_op_priority(std::string &op){
        return operators[op];
    }



    static std::vector<std::string> to_vector(std::string &infix){
        // takes the infix as a string and returns it as a vector of strings
        // needed to allow multi char conversion such as log, tan and decimals
        //
        // currently needs spacing between operator/operand.
        // could be changed, but must support sin and decimal

        std::vector<std::string> result;
        std::stringstream ss(infix);
        std::string temp;

        // use stringstream to split string by space
        while (ss >> temp) {
            result.push_back(temp);
        }

        return result;
    }


    static void operand_action(std::string &postfix, std::string &s){
        postfix += s;
        postfix += " ";
    }
    static void open_action(std::string &s, std::stack<std::string> &stack){
        stack.push(s);
    }
    static void close_action(std::string &postfix, std::stack<std::string> &stack){
        while (stack.top() != "("){
            // Stack is popped and printed until "(" is encountered,
            // then both "(" and ")" is discarded
            postfix += stack.top();
            postfix += " ";
            stack.pop();
        }
        stack.pop();

    }
    static void operator_action(std::string &postfix, std::string &s, std::stack<std::string> &stack){

        if (stack.empty() || stack.top() == "("){
            stack.push(s);

        } else if (is_operand(stack.top())){
            postfix += s;
            postfix += " ";

        } else if(get_op_priority(s) > get_op_priority(stack.top())){
            // If the current operator has higher priority than the top of the stack,
            // it's pushed to the top of the stack.
            stack.push(s);

        } else if(get_op_priority(s) <= get_op_priority(stack.top())){
            // If the current operator has lower or equal priority than the top of the stack,
            // the top is popped and printed until that is no longer the case
            postfix += stack.top();
            postfix += " ";
            stack.pop();
            operator_action(postfix, s, stack);
        }
    }

    static int char_occurrence(std::string &s, char c){
        int count = 0;
        for (auto i : s) {
            if (i == c){
                count++;
            }
        }
        return count;
    }

    static std::string solve_inner_func(std::string &s, std::stack<std::string> &stack){
        // Enters the parentheses of a function until there are no more functions inside,
        // will then evaluate up until the outermost function.
        // Nested functions will not be displayed as nested in the postfix output,
        // but postfix was used for calculating.
        // Example: cos(sin(45+45)) ↓ sin(45+45) ↓ 45+45 -> 45 45 + -> 90 ↑ sin(90) -> 1 ↑ cos(1)
        // cos(1) will then be printed as postfix.

        auto inner_of_current = to_vector(s);

        // index 0 is func, 1 is (, and last is ).
        // Stores so only inner string is left. Added back later. (ex: sin(x))
        func_storage.push_back(inner_of_current[0]); // stores sin
        inner_of_current.erase(inner_of_current.begin() + 0); // removes sin
        inner_of_current.erase(inner_of_current.begin() + 0); // removes (
        inner_of_current.erase(inner_of_current.begin() + (int(inner_of_current.size()) - 1)); // removes )

        if (is_function(inner_of_current[0])){
            // x contains a function
            std::string temp;
            for (auto i : inner_of_current) { // turns inner_of_current into string
                temp += i;
                temp += " ";
            }
            inner_of_current = {};
            inner_of_current.push_back(solve_inner_func(temp, stack));
        }

        // evaluates inner (x)
        std::string inner = convert(inner_of_current); // turns inner to postfix
        inner = std::to_string(evaluatePostfix(inner)); // calculate the postfix


        std::string parsed;

            parsed += func_storage[func_storage.size()-1]; // adds the last removed function back
            func_storage.pop_back(); // then removes it
            parsed += " ( ";

        // All functions added back at start.
        // For each function added, add a ) at end
        parsed += inner;
        parsed += " ";
        parsed += ") ";


        return parsed;
    }

    static void function_action(std::string &postfix, std::string &s, std::stack<std::string> &stack){

        if (!func_mode){
            func_string += s; // adds sin
            func_string += " ";
            func_mode = true;

        } else if (func_mode){

            if (s == "^"){
                func_infix_power_mode = true;
                function_power_action(postfix, s, stack);
                func_infix_power_string += "( "; // encapsulates everything in parentheses
                return;
            }

            func_string += s;
            func_string += " ";

            if (char_occurrence(func_string, '(') > 0 && char_occurrence(func_string, '(') == char_occurrence(func_string, ')')){

                func_mode = false;
                postfix += solve_inner_func(func_string, stack);
                func_storage = {}; // done using
                postfix += " ";
                func_string = ""; // clears func_string for future use

                if (!func_infix_power_string.empty()){
                    // all function states should be false (func_mode, func_infix_power_mode)

                    auto temp = to_vector(func_infix_power_string);
                    postfix += convert(temp);
                    func_infix_power_string = ""; // clears func_string for future use

                }
            }

        }
    }

    static void function_power_action(std::string &postfix, std::string &s, std::stack<std::string> &stack){

        if (s == "("){
            func_infix_power_string += ")"; // encapsulates everything in parentheses
            func_infix_power_mode = false;
            function_action(postfix, s, stack);
            return;
        } else{
            func_infix_power_string += s;
            func_infix_power_string += " ";
        }

    }

    static std::string convert(std::vector<std::string> &infix) {
        // Convert infix expression to postfix.
        // Main loop. Moves on to other functions depending on if the character
        // is an operator, operand or a function
        std::stack<std::string> stack;
        std::string postfix;

        for (auto s : infix) {

            if (func_infix_power_mode){
                // (ex: sin^2(x)) takes ^2 and add it to string.
                // Converted to postfix and added to postfix string after function's ")"
                function_power_action(postfix, s, stack);

            } else if (func_mode){
                // everything in parentheses belongs to the most recent function
                function_action(postfix, s, stack);

            } else if (is_operand(s)) {
                operand_action(postfix, s);

            } else if (s == "("){
                open_action(s, stack);

            } else if (s == ")"){
                close_action(postfix, stack);

            } else if(is_operator(s)){
                operator_action(postfix, s, stack);

            } else if(is_function(s)){
                function_action(postfix, s, stack);
            }

        }

        // empty the stack
        while (!stack.empty()){
//            if (stack.top() != "(" && stack.top() != ")"){
                postfix += stack.top();
                postfix += " ";
//            }
            stack.pop();
        }

        return postfix;
    }


    static bool isNumber(const std::string& s) { // isdigit() dont work on strings unfortunately, so we had to make our own function
        std::stringstream ss(s);
        double temp;
        return (ss >> temp) && ss.eof(); // eof is short for end-of
    }

    static double processParenthesis (std::stringstream& ss) {
        std::string token;
        ss >> token;

        if (is_function(token)) {
            return evaluateExpression(token, ss);
        }
        else {
            return stod(token);
        }
    }

    // This is a recursive function to evaluate the insides of sin, cos or log
    static double evaluateExpression (std::string& func, std::stringstream& ss) {
        std::string token;
        double pi = 3.14159265359;

        while (ss >> token) {
//            std::cout << "Token: " << token << std::endl;
            if (token == "(") {
                double val = processParenthesis(ss);
//                std::cout << "VALUE: " << func << "(" << val << ")" << std::endl;

                if (func == "sin") {
                    ss >> token;
                    return sin(val * pi / 180.0);
                } else if (func == "cos") {
                    ss >> token;
                    return cos(val * pi / 180.0);
                } else if (func == "tan") {
                    ss >> token;
                    return tan(val * pi / 180.0);
                } else if (func == "log") {
                    ss >> token;
                    return log10(val);
                } else if (func == "ln") {
                    ss >> token;
                    return log(val);
                }
            }
            // Removes ) if it doesn't recognize any of the functions
            ss >> token;
        }
        return 0;
    }
    static bool has_consecutive_operators(std::string &expr) {
        std::vector<std::string> tokens = to_vector(expr);
        for (size_t i = 0; i < tokens.size() - 1; ++i) {
            if (is_operator(tokens[i]) && is_operator(tokens[i + 1])) {
                return true;
            }
        }
        return false;
    }


public:

    static double evaluatePostfix(const std::string& expression) {

        // We are aware that there is a lack of validation-checking in this section, but to be able to get to this point
        // the infix and postfix already have to be validated

        std::stack<double> evalStack;
        std::stringstream ss(expression);
        std::string token;

        // We are going through the postfix token by token. Each token is separated by a " "
        while (ss >> token) {
            if (isNumber(token)) {
                // If the token is a number, push it to the stack
                evalStack.push(stod(token));
            }
            else if (token == "+") {
                // Add the top 2 numbers in the stack
                double val2 = evalStack.top(); evalStack.pop();
                double val1 = evalStack.top(); evalStack.pop();
                evalStack.push(val1 + val2);
            }
            else if (token == "-") {
                // Subtract the top 2 numbers in the stack
                double val2 = evalStack.top(); evalStack.pop();
                double val1 = evalStack.top(); evalStack.pop();
                evalStack.push(val1 - val2);
            }
            else if (token == "*") {
                // Multiply the top 2 numbers in the stack
                double val2 = evalStack.top(); evalStack.pop();
                double val1 = evalStack.top(); evalStack.pop();
                evalStack.push(val1 * val2);
            }
            else if (token == "/") {
                // Divide the top 2 numbers in the stack
                double val2 = evalStack.top(); evalStack.pop();
                double val1 = evalStack.top(); evalStack.pop();
                evalStack.push(val1 / val2);
            }
            else if (token == "^") {
                // val1^val2
                double val2 = evalStack.top(); evalStack.pop();
                double val1 = evalStack.top(); evalStack.pop();
                evalStack.push(pow(val1, val2));
            }
            else if (token == "%") {
                // val1%val2
                double val2 = evalStack.top(); evalStack.pop();
                double val1 = evalStack.top(); evalStack.pop();
                evalStack.push(int(val1) % int(val2));
            }
            else if (is_function(token)) {
                // Sine function
                double result = evaluateExpression(token, ss);
                evalStack.push(result);
            }
            else {
                std::cerr << "Unknown token encountered: " << token << std::endl;
            }
        }

        // The last element in stack will be the result. If the stack is empty then GG, something went wrong
        if (!evalStack.empty()) {
            return evalStack.top();
        } else {
            std::cerr << "Error: Empty stack" << std::endl;
            return 0;
        }
    }


    static std::string to_postfix(std::string &infix){
        std::vector<std::string> temp = to_vector(infix);
        return convert(temp);
    }

    static bool syntax_error(std::string &expr){
        //TODO: prevent ++, ** etc. Ensure spacing, or remove need for spacing
        // word are allowed but will be treated as a single variable/operand.
        // sin( would be considered an operand, probably shouldn't be allowed. sin ( is correct, not case sensitive

        if (has_consecutive_operators(expr)) {
            std::cerr << "Syntax Error: Consecutive operators detected." << std::endl;
            return true;
        }
        // Additional syntax checks can be added here.
        return false;
// 2 ++ 2 går fortsatt
// sin( bør ikke være lov, må være sin (
// tall uten operator mellom hverandre bør ikke være lov, "2 2"
//miks av tall og operator kan ikke være lov, "a(", "2+", "2^"
    }

    static void print_rules(){

        std::cout <<"[]====================Rules======================" <<std::endl;
        std::cout <<"|| Expression operator/operand should be seperated by space" <<std::endl;
        std::cout <<"|| Example: 2 + 3.2 ^ ( 5 ) * cos ( log ( 150 - 50 ) )" <<std::endl;
        // If nested functions, must only be nested, can't be ex: sin(cos(90)+1) or sin(cos^2(2)),
        // sin(cos(90)) allowed.
        // could probably be done, but would be more of a state machine then a converter that utilizes a stack
        std::cout <<"|| " <<std::endl;
        std::cout <<"|| Both sin^2(x) and sin(x)^2 is allowed." <<std::endl;
        std::cout <<"|| For sin^y(x) syntax, parenthesis is not allowed (ex: sin^(2+2)(90))," <<std::endl;
        std::cout <<"|| however, sin^2+2(90) is allowed. If the power of a function requires parenthesis," <<std::endl;
        std::cout <<"|| use sin(x)^y syntax instead (ex: sin(90)^(2+2)." <<std::endl;
        std::cout <<"|| " <<std::endl;
        std::cout <<"|| Legal operators are: ";
        for (auto &i : operators) {
            std::cout <<i.first <<", ";
        }
        std::cout <<std::endl;
        std::cout <<"|| Modulus assumes int as input, will cast input to int before calculating." <<std::endl;
        std::cout <<"|| Legal functions are: ";
        for (auto &i : functions) {
            std::cout <<i <<", ";
        }
        std::cout <<std::endl;
        std::cout <<"|| Functions are case sensitive." <<std::endl;
        std::cout <<"[]====================Rules======================" <<std::endl;
        std::cout <<std::endl;
    }

};

int main() {
// TODO: tan

    Convert::print_rules();

    while (true){

        std::string infix;
        std::cout <<"Type \"exit\" to exit" <<std::endl;
        std::cout <<"Input: " <<std::endl;
        std::getline (std::cin, infix);

        if (infix == "exit"){
            return 0;
        }
        if (Convert::syntax_error(infix)){
            std::cout <<"Syntax error" <<std::endl;
            continue;
        }

        std::string postfix = Convert::to_postfix(infix);

        std::cout <<"Postfix expression: "<< postfix <<std::endl;

        std::cout << std::fixed << std::setprecision(4);
        std::cout <<"Result of expression: " << Convert::evaluatePostfix(postfix) << std::endl <<std::endl;
    }

}