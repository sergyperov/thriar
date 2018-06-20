#include "tests_unit_6.hpp"

/*
 Модуль 6: Тестирование метода where()
 Тестируемые методы: where()
 
 Тест 1: применение метода на пустом дереве
 Тест 2: применение метода с заведомо ложным условием
 Тест 3: применение метода с заведомо истинным условием
 Тест 4: оставляем только один элемент
 Тест 5: применение метода с условием сравнения
 Тест 6: оставляем только центральную ветви
 Тест 7: оставляем только левую ветвь
 Тест 8: оставляем только правую ветвь
 */

struct unit_6_testing_struct {
    vector<int> vec;
    bool (*where_function)(int);
    string converted_string;
    
    unit_6_testing_struct(initializer_list<int> list, bool (*_where_function)(int), string _converted_string) {
        vec.insert(vec.begin(), list.begin(), list.end());
        where_function = _where_function;
        converted_string = _converted_string;
    }
};

bool unit_6_testing_function(unit_6_testing_struct testing_struct) {
    thriar<int> tree(compare_function);
    for (int i = 0; i < testing_struct.vec.size(); i++) {
        tree.add_element(testing_struct.vec[i]);
    }
    thriar<int> new_tree = tree.where(testing_struct.where_function);
    
    if (new_tree.convert_to_string(int_to_string) != testing_struct.converted_string) {
        return false;
    }
    return true;
}

void run_tests_unit_6() {
    unit_testing unit_t(6);
    
    test_group<unit_6_testing_struct> unit_6_test_group;
    unit_6_test_group.group_name = "group test 1";
    unit_6_test_group.test_function = unit_6_testing_function;
    vector<unit_6_testing_struct> unit_6_test_vector;
    
    // Тест 1
    unit_6_test_vector.push_back(unit_6_testing_struct({}, [](int a){return (a>50);},  "{}"));
    // Тест 2
    unit_6_test_vector.push_back(unit_6_testing_struct({1, 2, 4, 8, 16, 32}, [](int a){return false;},  "{}"));
    // Тест 3
    unit_6_test_vector.push_back(unit_6_testing_struct({100, 90, 80, 70}, [](int a){return true;},  "{{{{}{}{}{70}}{}{}{80}}{}{}{90}}{}{}{100}"));
    // Тест 4
    unit_6_test_vector.push_back(unit_6_testing_struct({100, 90, 80, 70}, [](int a){return (a==100);},  "{}{}{}{100}"));
    // Тест 5
    unit_6_test_vector.push_back(unit_6_testing_struct({42, 100, 300, 500}, [](int a){return (a>=300);},  "{}{}{{}{}{}{500}}{300}"));
    // Тест 6
    unit_6_test_vector.push_back(unit_6_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, [](int a){return ((a>=255)&&(a<=610));},  "{{{}{}{}{610}}{{}{}{}{255}}{}{600}}{}{}{500}"));
    // Тест 7
    unit_6_test_vector.push_back(unit_6_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, [](int a){return (a<=200);},  "{{}{}{}{110}}{{}{}{}{45}}{{}{}{}{200}}{100}"));
    // Тест 8
    unit_6_test_vector.push_back(unit_6_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, [](int a){return (a>=800);},  "{{}{}{}{2500}}{{}{}{}{800}}{{}{}{}{10000}}{2000}"));
    
    unit_6_test_group.data_set = unit_6_test_vector;
    unit_t.run_test_group(unit_6_test_group);
    
    unit_t.finish_testing();
}
