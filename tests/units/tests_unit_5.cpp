#include "tests_unit_5.hpp"

/*
 Модуль 5: Тестирование слияние поддеревьев
 Тестируемые методы: merge()
 
 Тест 1: слияние двух пустых деревьев
 Тест 2: слияние непустого дерева с пустым деревом
 Тест 3: слияние пустого дерева с непустым деревом
 Тест 4: слияние двух одинаковых деревьев
 Тест 5: слияние деревьев, расположенных только по середине
 Тест 6: слияние деревьев, расположенных только по левому краю
 Тест 7: слияние деревьев, расположенных только по правому краю
 Тест 8: слияние с сбалансированным деревом
 Тест 9: слияние с большим сбалансированным деревом
 */

struct unit_5_testing_struct {
    vector<int> vec_1;
    vector<int> vec_2;
    string converted_string;
    
    unit_5_testing_struct(initializer_list<int> list_1, initializer_list<int> list_2, string _converted_string) {
        vec_1.insert(vec_1.begin(), list_1.begin(), list_1.end());
        vec_2.insert(vec_2.begin(), list_2.begin(), list_2.end());
        converted_string = _converted_string;
    }
};

bool unit_5_testing_function(unit_5_testing_struct testing_struct) {
    thriar<int> tree_1(compare_function);
    thriar<int> tree_2(compare_function);
    for (int i = 0; i < testing_struct.vec_1.size(); i++) {
        tree_1.add_element(testing_struct.vec_1[i]);
    }
    for (int i = 0; i < testing_struct.vec_2.size(); i++) {
        tree_2.add_element(testing_struct.vec_2[i]);
    }
    thriar<int> tree_res = tree_1.merge(tree_2);
    
    if (tree_res.convert_to_string(int_to_string) != testing_struct.converted_string) {
        return false;
    }
    return true;
}

void run_tests_unit_5() {
    unit_testing unit_t(5);
    
    test_group<unit_5_testing_struct> unit_5_test_group;
    unit_5_test_group.group_name = "group test 1";
    unit_5_test_group.test_function = unit_5_testing_function;
    vector<unit_5_testing_struct> unit_5_test_vector;
    
    // Тест 1
    unit_5_test_vector.push_back(unit_5_testing_struct({}, {}, "{}"));
    // Тест 2
    unit_5_test_vector.push_back(unit_5_testing_struct({42}, {}, "{}{}{}{42}"));
    // Тест 3
    unit_5_test_vector.push_back(unit_5_testing_struct({}, {42}, "{}{}{}{42}"));
    // Тест 4
    unit_5_test_vector.push_back(unit_5_testing_struct({42}, {42}, "{}{}{}{42}"));
    // Тест 5
    unit_5_test_vector.push_back(unit_5_testing_struct({100, 90, 80, 70}, {60, 50}, "{{{{{{}{}{}{60}}{}{}{50}}{}{}{70}}{}{}{80}}{}{}{90}}{}{}{100}"));
    // Тест 6
    unit_5_test_vector.push_back(unit_5_testing_struct({100, 49, 23, 11}, {4, 1}, "{}{{}{{}{{}{{}{}{{}{}{}{4}}{1}}{}{11}}{}{23}}{}{49}}{}{100}"));
    // Тест 7
    unit_5_test_vector.push_back(unit_5_testing_struct({42, 100, 300, 500}, {1000, 2000}, "{}{}{{}{}{{}{}{{}{}{{{}{}{}{1000}}{}{}{2000}}{500}}{300}}{100}}{42}"));
    // Тест 8
    unit_5_test_vector.push_back(unit_5_testing_struct({500, 100, 600, 2000}, {650}, "{{{}{}{}{650}}{}{}{600}}{{}{}{}{100}}{{}{}{}{2000}}{500}"));
    // Тест 9
    unit_5_test_vector.push_back(unit_5_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, {120, 620, 2600}, "{{{{}{}{}{620}}{}{}{610}}{{}{}{}{255}}{}{600}}{{{{}{}{}{120}}{}{}{110}}{{}{}{}{45}}{{}{}{}{200}}{100}}{{{{}{}{}{2600}}{}{}{2500}}{{}{}{}{800}}{{}{}{}{10000}}{2000}}{500}"));
    
    unit_5_test_group.data_set = unit_5_test_vector;
    unit_t.run_test_group(unit_5_test_group);
    
    unit_t.finish_testing();
}
