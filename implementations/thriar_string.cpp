#include "thriar_string.hpp"

using namespace std;

int thriar_string_cli_compare_function(string cur_elem, string new_elem) {
    if (cur_elem == new_elem) {
        return 0;
    }
    if (new_elem < cur_elem) {
        return 1;
    }
    if (new_elem > cur_elem) {
        return 3;
    }
    
    return -1;
}

string thriar_string_cli_function_to_string(string a) {
    stringstream stream;
    stream << fixed << setprecision(1) << a;
    string s = stream.str();
    return s;
}

void thriar_string_cli_print_help() {
    cout << "'add': adds new element" << endl;
    cout << "'fromstr': creates new tree from encoded string" << endl;
    cout << "'remove': removes element if exists" << endl;
    cout << "'subtree': creates subtree from element" << endl;
    cout << "'check': check if element exists" << endl;
    cout << "'print': prints list" << endl;
    cout << "'help': prints help" << endl;
    cout << "'quit': quits" << endl;
    cout << endl;
}

void thriar_string_cli_add(thriar<string> &thriar_of_strings) {
    cout << "Enter string: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    string new_string;
    cin >> new_string;
    if ((new_string.find("{") > -1) || (new_string.find("}") > -1)) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_strings.add_element(new_string);
    cout << "Command succeeded." << endl << endl;
}

void thriar_string_cli_remove(thriar<string> &thriar_of_strings) {
    cout << "Enter string: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    string string_to_remove;
    cin >> string_to_remove;
    if ((string_to_remove.find("{") > -1) || (string_to_remove.find("}") > -1)) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_strings.remove_element(string_to_remove);
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_string_cli_subtree(thriar<string> &thriar_of_strings) {
    cout << "Enter string: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    string string_to_subtree;
    cin >> string_to_subtree;
    if ((string_to_subtree.find("{") > -1) || (string_to_subtree.find("}") > -1)) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_strings = thriar_of_strings.create_subtree(string_to_subtree);
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_string_cli_check(thriar<string> &thriar_of_strings) {
    cout << "Enter string to check: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    string string_to_check;
    cin >> string_to_check;
    if (!cin) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    bool check_result = thriar_of_strings.has_element(string_to_check);
    if (check_result == true) {
        cout << "Element '" << string_to_check << "' exists in thriar." << endl;
    } else {
        cout << "Element '" << string_to_check << "' doesn't exist in thriar." << endl;
    }
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_string_cli_print(thriar<string> &thriar_of_strings) {
    cout << "Printing (converted to string) thriar:" << endl;
    cout << thriar_of_strings.convert_to_string(thriar_string_cli_function_to_string) << endl;
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_string_cli_fromstr(thriar<string> &thriar_of_strings) {
    cout << "Enter encoded thriar string:" << endl;
    string encoded_s;
    cin.ignore();
    getline(cin, encoded_s);
    
    try {
        thriar_of_strings = thriar<string>(thriar_string_cli_compare_function, encoded_s, [](string s){return (string)s;});
    } catch (invalid_argument e) {
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_string_cli() {
    thriar<string> thriar_of_strings(thriar_string_cli_compare_function);
    
    cout << "Welcome to Thriar \"string\" implementation." << endl;
    
    while (true) {
        cout << "Enter command: ";
        
        string command;
        cin >> command;
        
        if (command == "add") {
            thriar_string_cli_add(thriar_of_strings);
        } else if (command == "fromstr") {
            thriar_string_cli_fromstr(thriar_of_strings);
        } else if (command == "remove") {
            thriar_string_cli_remove(thriar_of_strings);
        } else if (command == "subtree") {
            thriar_string_cli_subtree(thriar_of_strings);
        } else if (command == "check") {
            thriar_string_cli_check(thriar_of_strings);
        } else if (command == "print") {
            thriar_string_cli_print(thriar_of_strings);
        } else if (command == "help") {
            thriar_string_cli_print_help();
        } else if (command == "quit") {
            break;
        } else {
            cout << "Command not found: '" << command << "'." << endl;
        }
    }
}
