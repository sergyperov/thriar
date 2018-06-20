#include "tests_unit_1.hpp"

/*
 Модуль 1: Тестирование создания дерева
 
 Тест 1: тестируем создание дерева
 Тест 2: тестируем создание дерева из строки (с пустой строкой)
 Тест 3: тестируем создание дерева из строки (с непустой строкой)
 Тест 4: тестируем создание дерева из строки (с целым числом)
 Тест 5: тестируем создание дерева из строки (с ошибкой в строке)
 */

void run_tests_unit_1() {
    unit_testing unit_t(1);
    
    // Тест 1
    unit_t.run_single_test([]() {
        thriar<int> tree(compare_function);
        if (tree.has_element(0) == false) {
            return true;
        } else {
            return false;
        }
        return false;
    }, "single test 1");
    
    // Тест 2
    unit_t.run_single_test([]() {
        thriar<string> tree(compare_function_string, "{}{}{}{}", [](string s){return s;});
        if ((tree.convert_to_string(str_to_string) == "{}{}{}{}") && (tree.has_element("") == true)) {
            return true;
        } else {
            return false;
        }
    }, "single test 2");
    
    // Тест 3
    unit_t.run_single_test([]() {
        thriar<string> tree(compare_function_string, "{}{}{}{hello, world}", [](string s){return s;});
        if ((tree.convert_to_string(str_to_string) == "{}{}{}{hello, world}") && (tree.has_element("hello, world") == true)) {
            return true;
        } else {
            return false;
        }
    }, "single test 3");
    
    // Тест 4
    unit_t.run_single_test([]() {
        thriar<int> tree(compare_function, "{}{}{}{42}", [](string s){return stoi(s);});
        if ((tree.has_element(42) == true) && (tree.convert_to_string(int_to_string) == "{}{}{}{42}")) {
            return true;
        } else {
            return false;
        }
        return false;
    }, "single test 4");
    
    // Тест 5
    unit_t.run_single_test([]() {
        try {
           thriar<int> tree(compare_function, "{}{}{}", [](string s){return stoi(s);});
        } catch(runtime_error e) {
            return true;
        }
        
        return false;
    }, "single test 5");
    
    unit_t.finish_testing();
}
