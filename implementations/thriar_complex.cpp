#include "thriar_complex.hpp"

using namespace std;

complex complex_from_string(string str) {
    long int i_index = str.find("i");
    int a = 0, b = 0;
    
    if (i_index > -1) {
        a = stoi(str.substr(0, i_index));
        if ((str.length()-1) != i_index) {
            b = stoi(str.substr(i_index+1, str.length()-i_index-1));
        }
    } else {
        b = stoi(str);
    }
    
    complex result(a, b);
    return result;
}

string get_complex_formatted(complex k) {
    string res = "";
    if (k.a != 0) {
        res += (to_string(k.a) + "i");
    }
    
    if (k.b > 0) {
        if (k.a != 0) {
            res += "+";
        }
        res += to_string(k.b);
    } else if (k.b < 0) {
        res += "-" + to_string(k.b*(-1));
    }
    
    if (res == "") {
        res = "0";
    }
    
    return res;
}

int thriar_complex_cli_compare_function(complex cur_elem, complex new_elem) {
    if ((cur_elem.a == new_elem.a) && (cur_elem.b == new_elem.b)) {
        return 0;
    }
    
    int a_delta = abs(cur_elem.a/2);
    int b_delta = abs(cur_elem.b/2);
    
    int a_bottom = cur_elem.a - a_delta;
    int a_top = cur_elem.a + a_delta;
    int b_left = cur_elem.b - b_delta;
    int b_right = cur_elem.b + b_delta;
    
    if ((new_elem.a >= a_bottom) && (new_elem.a <= a_top) && (new_elem.b >= b_left) && (new_elem.b <= b_right)) {
        return 2;
    }
    
    if ((new_elem.a > a_top) || (new_elem.b > b_right)) {
        return 3;
    } else {
        return 1;
    }
    
    return -1;
}

void thriar_complex_cli_print_help() {
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

void thriar_complex_cli_add(thriar<complex> &thriar_of_complexes) {
    cout << "Enter complex: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    complex new_complex;
    try {
        string s;
        cin >> s;
        new_complex = complex_from_string(s);
    } catch (invalid_argument e) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_complexes.add_element(new_complex);
    cout << "Command succeeded." << endl << endl;
}

void thriar_complex_cli_remove(thriar<complex> &thriar_of_complexes) {
    cout << "Enter complex: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    complex complex_to_remove;
    try {
        string s;
        cin >> s;
        complex_to_remove = complex_from_string(s);
    } catch (invalid_argument e) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_complexes.remove_element(complex_to_remove);
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_complex_cli_subtree(thriar<complex> &thriar_of_complexes) {
    cout << "Enter complex: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    complex complex_to_subtree;
    try {
        string s;
        cin >> s;
        complex_to_subtree = complex_from_string(s);
    } catch (invalid_argument e) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
   // thriar_of_complexes = thriar_of_complexes.create_subtree(complex_to_subtree);
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_complex_cli_multiply(thriar<complex> &thriar_of_complexes) {
    cout << "Enter complex multiplyer N: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    int complex_multiplyer;
    cin >> complex_multiplyer;
    if (!cin) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_complexes = thriar_of_complexes.map<complex>(thriar_complex_cli_compare_function, [&complex_multiplyer](complex c){complex new_complex(c.a*complex_multiplyer, c.b*complex_multiplyer); return new_complex;});
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_complex_cli_selection(thriar<complex> &thriar_of_complexes) {
    cout << "Enter complex lower bound: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    complex complex_lower_bound;
    try {
        string s;
        cin >> s;
        complex_lower_bound = complex_from_string(s);
    } catch (invalid_argument e) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    thriar_of_complexes = thriar_of_complexes.where([&complex_lower_bound](complex c){return ((c.a >= complex_lower_bound.a) && (c.b >= complex_lower_bound.b));});
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_complex_cli_check(thriar<complex> &thriar_of_complexes) {
    cout << "Enter complex to check: ";
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    complex complex_to_check;
    try {
        string s;
        cin >> s;
        complex_to_check = complex_from_string(s);
    } catch (invalid_argument e) {
        cin.clear();
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    bool check_result = thriar_of_complexes.has_element(complex_to_check);
    if (check_result == true) {
        cout << "Element '" << get_complex_formatted(complex_to_check) << "' exists in thriar." << endl;
    } else {
        cout << "Element '" << get_complex_formatted(complex_to_check) << "' doesn't exist in thriar." << endl;
    }
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_complex_cli_print(thriar<complex> &thriar_of_complexes) {
    cout << "Printing (converted to string) thriar:" << endl;
    cout << thriar_of_complexes.convert_to_string(get_complex_formatted) << endl;
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_complex_cli_fromstr(thriar<complex> &thriar_of_complexes) {
    cout << "Enter encoded thriar string:" << endl;
    string encoded_s;
    cin.ignore();
    getline(cin, encoded_s);
    
    try {
        thriar_of_complexes = thriar<complex>(thriar_complex_cli_compare_function, encoded_s, complex_from_string);
    } catch (invalid_argument e) {
        cout << "Command failed: 'wrong input'." << endl << endl;
        return;
    }
    
    cout << "Command succeeded." << endl << endl;
}

void thriar_complex_cli() {
    thriar<complex> thriar_of_complexes(thriar_complex_cli_compare_function);
    
    cout << "Welcome to Thriar \"complex\" implementation." << endl;
    
    while (true) {
        cout << "Enter command: ";
        
        string command;
        cin >> command;
        
        if (command == "add") {
            thriar_complex_cli_add(thriar_of_complexes);
        } else if (command == "fromstr") {
            thriar_complex_cli_fromstr(thriar_of_complexes);
        } else if (command == "remove") {
            thriar_complex_cli_remove(thriar_of_complexes);
        } else if (command == "multiply") {
            thriar_complex_cli_multiply(thriar_of_complexes);
        } else if (command == "select") {
            thriar_complex_cli_selection(thriar_of_complexes);
        } else if (command == "subtree") {
            thriar_complex_cli_subtree(thriar_of_complexes);
        } else if (command == "check") {
            thriar_complex_cli_check(thriar_of_complexes);
        } else if (command == "print") {
            thriar_complex_cli_print(thriar_of_complexes);
        } else if (command == "help") {
            thriar_complex_cli_print_help();
        } else if (command == "quit") {
            break;
        } else {
            cout << "Command not found: '" << command << "'." << endl;
        }
    }
}
