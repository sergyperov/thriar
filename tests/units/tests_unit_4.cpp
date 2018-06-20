#include "tests_unit_4.hpp"

/*
 Модуль 4: Тестирование работы с поддервьями
 Тестируемые методы: has_subtree(), create_subtree()

 Тест 1: найти поддерево у пустого дерева
 Тест 2: найти пустое поддерево у непустого дерева
 Тест 3: найти пустое поддерево у пустого дерева
 Тест 4: найти поддерево, составленное только по середине
 Тест 5: найти поддерево, составленное только по левому боку
 Тест 6: найти поддерево, составленное только по правому боку
 Тест 7: поддерво, не совпадающего по одному узлу
 Тест 8: поиск поддерева в большом дереве
 Тест 9: поиск поддерева в большом дереве (безуспешная)
 Тест 10: поиск поддерва в идентичном дереве
 Тест 11: создание поддерева по несуществующему элементу
 Тест 12: создание поддерева из пустого дерева
 Тест 13: создание полного поддерева
 Тест 14: создание поддерева из созданного только по середине дерева
 Тест 15: создание поддерева из созданного только по левому боку дерева
 Тест 16: создание поддерева из созданного только по правому боку дерева
 Тест 17: создание поддерева из сбалансированного дерева
 Тест 18: создание поддерева из большого сбалансированного дерева
 */

struct unit_4_1_testing_struct {
    vector<int> vec_1;
    vector<int> vec_2;
    bool comparison_result;
    
    unit_4_1_testing_struct(initializer_list<int> list_1, initializer_list<int> list_2, bool _comparison_result) {
        vec_1.insert(vec_1.begin(), list_1.begin(), list_1.end());
        vec_2.insert(vec_2.begin(), list_2.begin(), list_2.end());
        comparison_result = _comparison_result;
    }
};
bool unit_4_1_testing_function(unit_4_1_testing_struct testing_struct) {
    thriar<int> tree(compare_function);
    thriar<int> subtree(compare_function);
    for (int i = 0; i < testing_struct.vec_1.size(); i++) {
        tree.add_element(testing_struct.vec_1[i]);
    }
    for (int i = 0; i < testing_struct.vec_2.size(); i++) {
        subtree.add_element(testing_struct.vec_2[i]);
    }
    
    if (tree.has_subtree(subtree) != testing_struct.comparison_result) {
        return false;
    }
    
    return true;
}

struct unit_4_2_testing_struct {
    vector<int> vec;
    int subtree_head;
    string converted_string;
    
    unit_4_2_testing_struct(initializer_list<int> list, int _subtree_head, string _converted_string) {
        vec.insert(vec.begin(), list.begin(), list.end());
        subtree_head = _subtree_head;
        converted_string = _converted_string;
    }
};
bool unit_4_2_testing_function(unit_4_2_testing_struct testing_struct) {
    thriar<int> tree(compare_function);
    for (int i = 0; i < testing_struct.vec.size(); i++) {
        tree.add_element(testing_struct.vec[i]);
    }
    thriar<int> subtree = tree.create_subtree(testing_struct.subtree_head);
    
    if (subtree.convert_to_string(int_to_string) != testing_struct.converted_string) {
        return false;
    }
    
    return true;
}

void run_tests_unit_4() {
    unit_testing unit_t(4);
    
    test_group<unit_4_1_testing_struct> unit_4_1_test_group;
    unit_4_1_test_group.group_name = "group test 1";
    unit_4_1_test_group.test_function = unit_4_1_testing_function;
    vector<unit_4_1_testing_struct> unit_4_1_test_vector;
    
    // Тест 1
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({}, {42}, false));
    // Тест 2
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({42}, {}, true));
    // Тест 3
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({}, {}, true));
    // Тест 4_1
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({100, 90, 80, 70}, {80, 70}, true));
    // Тест 5
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({42, 10, 4, 1}, {10, 4, 1}, true));
    // Тест 6
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({42, 100, 300, 500}, {100, 300, 500}, true));
    // Тест 7
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({42, 100, 300, 500}, {42, 100, 300}, false));
    // Тест 8
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, {2000, 800, 2500, 10000}, true));
    // Тест 9
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, {2000, 800, 10000}, false));
    // Тест 10
    unit_4_1_test_vector.push_back(unit_4_1_testing_struct({42, 100, 300, 500}, {42, 100, 300, 500}, true));
    
    unit_4_1_test_group.data_set = unit_4_1_test_vector;
    unit_t.run_test_group(unit_4_1_test_group);
    
    test_group<unit_4_2_testing_struct> unit_4_2_test_group;
    unit_4_2_test_group.group_name = "group test 2";
    unit_4_2_test_group.test_function = unit_4_2_testing_function;
    vector<unit_4_2_testing_struct> unit_4_2_test_vector;
    
    // Тест 11
    unit_4_2_test_vector.push_back(unit_4_2_testing_struct({42}, 0, "{}"));
    // Тест 12
    unit_4_2_test_vector.push_back(unit_4_2_testing_struct({}, 42, "{}"));
    // Тест 13
    unit_4_2_test_vector.push_back(unit_4_2_testing_struct({100, 90, 80, 70}, 100, "{{{{}{}{}{70}}{}{}{80}}{}{}{90}}{}{}{100}"));
    // Тест 14
    unit_4_2_test_vector.push_back(unit_4_2_testing_struct({100, 90, 80, 70}, 80, "{{}{}{}{70}}{}{}{80}"));
    // Тест 15
    unit_4_2_test_vector.push_back(unit_4_2_testing_struct({42, 10, 4, 1}, 10, "{}{{}{{}{}{}{1}}{}{4}}{}{10}"));
    // Тест 16
    unit_4_2_test_vector.push_back(unit_4_2_testing_struct({42, 100, 300, 500}, 100, "{}{}{{}{}{{}{}{}{500}}{300}}{100}"));
    // Тест 17
    unit_4_2_test_vector.push_back(unit_4_2_testing_struct({500, 100, 600, 2000}, 100, "{}{}{}{100}"));
    // Тест 18
    unit_4_2_test_vector.push_back(unit_4_2_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, 2000, "{{}{}{}{2500}}{{}{}{}{800}}{{}{}{}{10000}}{2000}"));
    
    unit_4_2_test_group.data_set = unit_4_2_test_vector;
    unit_t.run_test_group(unit_4_2_test_group);
    
    unit_t.finish_testing();
}
