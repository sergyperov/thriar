#include "tests_unit_7.hpp"

/*
 Модуль 7: Тестирование метода map()
 Тестируемые методы: map()
 
 Тест 1: применение метода на пустом дереве
 Тест 2: применение метода с заведомо ложным условием
 Тест 3: применение метода с заведомо истинным условием
 Тест 4: оставляем только один элемент
 Тест 5: применение метода с условием сравнения
 Тест 6: оставляем только центральную ветви
 Тест 7: оставляем только левую ветвь
 Тест 8: оставляем только правую ветвь
 */

struct unit_7_testing_struct {
    vector<int> vec;
    int (*map_function)(int);
    string converted_string;
    
    unit_7_testing_struct(initializer_list<int> list, int (*_map_function)(int), string _converted_string) {
        vec.insert(vec.begin(), list.begin(), list.end());
        map_function = _map_function;
        converted_string = _converted_string;
    }
};

bool unit_7_testing_function(unit_7_testing_struct testing_struct) {
    thriar<int> tree(compare_function);
    for (int i = 0; i < testing_struct.vec.size(); i++) {
        tree.add_element(testing_struct.vec[i]);
    }
    thriar<int> new_tree = tree.map<int>(compare_function, testing_struct.map_function);
    
    if (new_tree.convert_to_string(int_to_string) != testing_struct.converted_string) {
        return false;
    }
    return true;
}

void run_tests_unit_7() {
    unit_testing unit_t(7);
    
    test_group<unit_7_testing_struct> unit_7_test_group;
    unit_7_test_group.group_name = "group test 1";
    unit_7_test_group.test_function = unit_7_testing_function;
    vector<unit_7_testing_struct> unit_7_test_vector;
    
    // Тест 1
    unit_7_test_vector.push_back(unit_7_testing_struct({}, [](int a){return a;},  "{}"));
    // Тест 2
    unit_7_test_vector.push_back(unit_7_testing_struct({500, 100, 600, 2000}, [](int a){return a;}, "{{}{}{}{500}}{{}{}{}{100}}{{}{}{}{2000}}{600}"));
    // Тест 3
    unit_7_test_vector.push_back(unit_7_testing_struct({500, 100, 600, 2000}, [](int a){return a*2;}, "{{}{}{}{1000}}{{}{}{}{200}}{{}{}{}{4000}}{1200}"));
    // Тест 4
    unit_7_test_vector.push_back(unit_7_testing_struct({500, 100, 600, 2000}, [](int a){return 0;}, "{}{}{}{0}"));
    
    unit_7_test_group.data_set = unit_7_test_vector;
    unit_t.run_test_group(unit_7_test_group);
    
    // Тест 5
    unit_t.run_single_test([]() {
        thriar<int> tree(compare_function);
        tree.add_element(1);
        tree.add_element(3);
        tree.add_element(5);
        tree.add_element(7);
        tree.add_element(9);
        
        thriar<double> tree_new = tree.map<double>(compare_function_double, [](int a){double res = a; res/=2; return res;});
        if (tree_new.convert_to_string(double_to_string) != "{{{}{}{}{2.5}}{}{}{4.5}}{{}{{}{}{}{0.5}}{}{1.5}}{}{3.5}") {
            return false;
        }
        return true;
    }, "single test 1");
    
    unit_t.finish_testing();
}
