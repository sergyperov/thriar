#include "unit_testing.hpp"

using namespace std;

/*
 Модуль 1: Тестирование создания дерева
 Модуль 2: Тестирование добавления элемента, копирования объектов, а также вывод дерева в строку
 Модуль 3: Тестирование удаления элемента
 Модуль 4: Тестирование работы с поддервьями
 Модуль 5: Тестирование слияние поддеревьев
 Модуль 6: Тестирование метода where()
 Модуль 7: Тестирование метода map()
 */
void run_tests() {
    run_tests_unit_1();
    run_tests_unit_2();
    run_tests_unit_3();
    run_tests_unit_4();
    run_tests_unit_5();
    run_tests_unit_6();
    run_tests_unit_7();
}

void unit_testing::run_single_test(bool (*test_function)(), string group_name) {
    if (is_aborted) {
        return;
    }
    
    current_test_id++;
    
    cout << "[UNIT TESTING] TEST #" << current_test_id << ":";
    int spaces_count = test_output_padding - (int)to_string(current_test_id).length();
    for (int i = 0; i < spaces_count; i++) {
        cout << " ";
    }
    
    bool test_result = test_function();
    if (test_result == true) {
        cout << "OK." << endl;
    } else {
        cout << "FAILED." << endl;
        abort_testing(group_name, 0);
    }
}

void unit_testing::abort_testing(string group_name, int group_data_id) {
    is_aborted = true;
    
    cout << "[UNIT TESTING] Testing failed on group \"" << group_name << "\", test " << group_data_id << endl;
    cout << "[UNIT TESTING] Aborting..." << endl << endl;
}

void unit_testing::start_testing() {
    cout << "[UNIT TESTING] Starting UNIT " << unit_number << " testing." << endl;
}

void unit_testing::finish_testing() {
    if (!is_aborted) {
        cout << "[UNIT TESTING] Testing UNIT " << unit_number << " passed." << endl << endl;
    }
}

int compare_function(int cur_elem, int new_elem) {
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

int compare_function_double(double cur_elem, double new_elem) {
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

int compare_function_string(string cur_elem, string new_elem) {
    if (cur_elem == new_elem) {
        return 0;
    }
    if (new_elem > cur_elem) {
        return 3;
    }
    if (new_elem < cur_elem) {
        return 1;
    }
    
    return -1;
}

string int_to_string(int a) {
    return to_string(a);
}

string double_to_string(double a) {
    stringstream stream;
    stream << fixed << setprecision(1) << a;
    string s = stream.str();
    return s;
}

string str_to_string(string a) {
    return a;
}
