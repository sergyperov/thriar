#include "thriar_double.hpp"

using namespace std;

int thriar_double_cli_compare_function(double cur_elem, double new_elem) {
    int border = abs(cur_elem/2);
    
    if (cur_elem == new_elem) {
        return 0;
    }
    if ((new_elem >= (cur_elem - border)) && (new_elem <= (cur_elem + border))) {
        return 2;
    }
    if (new_elem < (cur_elem - border)) {
        return 1;
    }
    if (new_elem > (cur_elem - border)) {
        return 3;
    }
    
    return -1;
}

string thriar_double_cli_function_to_string(double a) {
    stringstream stream;
    stream << fixed << setprecision(1) << a;
    string s = stream.str();
    return s;
}

void thriar_double_cli_print_help() {
    cout << "'add': adds new element" << endl;
    cout << "'fromstr': creates new tree from encoded string" << endl;
    cout << "'remove': removes element if exists" << endl;
    cout << "'multiply': multiplies all element by N" << endl;
    cout << "'select': select only element greater then N" << endl;
    cout << "'subtree': creates subtree from element" << endl;
    cout << "'check': check if element exists" << endl;
    cout << "'print': prints list" << endl;
    cout << "'help': prints help" << endl;
    cout << "'quit': quits" << endl;
    cout << endl;
}

void thriar_double_cli_add(thriar<double> &thriar_of_doubles) {
    cout << "Enter double: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    double new_double;
    cin >> new_double;
    if (!cin) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_doubles.add_element(new_double);
    cout << "Command succeeded." << endl << endl;
}

void thriar_double_cli_remove(thriar<double> &thriar_of_doubles) {
    cout << "Enter double: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    double double_to_remove;
    cin >> double_to_remove;
    if (!cin) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_doubles.remove_element(double_to_remove);
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_double_cli_subtree(thriar<double> &thriar_of_doubles) {
    cout << "Enter double: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    double double_to_subtree;
    cin >> double_to_subtree;
    if (!cin) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_doubles = thriar_of_doubles.create_subtree(double_to_subtree);
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_double_cli_multiply(thriar<double> &thriar_of_doubles) {
    cout << "Enter double multiplyer N: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    double double_multiplyer;
    cin >> double_multiplyer;
    if (!cin) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_doubles = thriar_of_doubles.map<double>(thriar_double_cli_compare_function, [&double_multiplyer](double a){return (a*double_multiplyer);});
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_double_cli_selection(thriar<double> &thriar_of_doubles) {
    cout << "Enter double lower bound: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    double double_lower_bound;
    cin >> double_lower_bound;
    if (!cin) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_doubles = thriar_of_doubles.where([&double_lower_bound](double a){return (a>=double_lower_bound);});
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_double_cli_check(thriar<double> &thriar_of_doubles) {
    cout << "Enter double to check: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    double double_to_check;
    cin >> double_to_check;
    if (!cin) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    bool check_result = thriar_of_doubles.has_element(double_to_check);
    if (check_result == true) {
        cout << "Element '" << double_to_check << "' exists in thriar." << endl;
    } else {
        cout << "Element '" << double_to_check << "' doesn't exist in thriar." << endl;
    }
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_double_cli_print(thriar<double> &thriar_of_doubles) {
    cout << "Printing (converted to string) thriar:" << endl;
    cout << thriar_of_doubles.convert_to_string(thriar_double_cli_function_to_string) << endl;
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_double_cli_fromstr(thriar<double> &thriar_of_doubles) {
    cout << "Enter encoded thriar string:" << endl;
    string encoded_s;
    cin.ignore();
    getline(cin, encoded_s);
    try {
        thriar_of_doubles = thriar<double>(thriar_double_cli_compare_function, encoded_s, [](string s){return stod(s);});
    } catch (invalid_argument e) {
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_double_cli() {
    thriar<double> thriar_of_doubles(thriar_double_cli_compare_function);
    
    cout << "Welcome to Thriar \"double\" implementation." << endl;
    
    while (true) {
        cout << "Enter command: ";
        
        string command;
        cin >> command;
        
        if (command == "add") {
            thriar_double_cli_add(thriar_of_doubles);
        } else if (command == "fromstr") {
            thriar_double_cli_fromstr(thriar_of_doubles);
        } else if (command == "remove") {
            thriar_double_cli_remove(thriar_of_doubles);
        } else if (command == "multiply") {
            thriar_double_cli_multiply(thriar_of_doubles);
        } else if (command == "select") {
            thriar_double_cli_selection(thriar_of_doubles);
        } else if (command == "subtree") {
            thriar_double_cli_subtree(thriar_of_doubles);
        } else if (command == "check") {
            thriar_double_cli_check(thriar_of_doubles);
        } else if (command == "print") {
            thriar_double_cli_print(thriar_of_doubles);
        } else if (command == "help") {
            thriar_double_cli_print_help();
        } else if (command == "quit") {
            break;
        } else {
            cout << "Command not found: '" << command << "'." << endl;
        }
    }
}
