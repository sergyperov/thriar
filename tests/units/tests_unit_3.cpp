#include "tests_unit_3.hpp"

/*
 Модуль 3: Тестирование удаления элемента
 Тестируемые методы: remove_element()
 
 Тест 1: не удаляем элементы вообще
 Тест 2: удаляем элемент в пустом дереве
 Тест 3: удаляем элемент в дереве с одним элементом
 Тест 4: удаляем элемент, когда все элементы в середине
 Тест 5: удаляем элемент, когда все элементы слева
 Тест 6: удаляем элемент, когда все элементы справа
 Тест 7: ещё один тест на удаление (теперь элементов больше)
 Тест 8: удаление несуществующего элемента
 */

struct unit_3_testing_struct {
    vector<int> vec_to_add;
    vector<int> vec_to_remove;
    string converted_string;
    
    unit_3_testing_struct(initializer_list<int> list_to_add, initializer_list<int> list_to_remove, string _converted_string) {
        vec_to_add.insert(vec_to_add.begin(), list_to_add.begin(), list_to_add.end());
        vec_to_remove.insert(vec_to_remove.begin(), list_to_remove.begin(), list_to_remove.end());
        converted_string = _converted_string;
    }
};

bool unit_3_testing_function(unit_3_testing_struct testing_struct) {
    thriar<int> tree(compare_function);
    for (int i = 0; i < testing_struct.vec_to_add.size(); i++) {
        tree.add_element(testing_struct.vec_to_add[i]);
    }
    for (int i = 0; i < testing_struct.vec_to_remove.size(); i++) {
        tree.remove_element(testing_struct.vec_to_remove[i]);
    }
    
    if (tree.convert_to_string(int_to_string) != testing_struct.converted_string) {
        return false;
    }
    
    return true;
}

void run_tests_unit_3() {
    unit_testing unit_t(3);
    
    test_group<unit_3_testing_struct> unit_3_test_group;
    unit_3_test_group.group_name = "group test 1";
    unit_3_test_group.test_function = unit_3_testing_function;
    vector<unit_3_testing_struct> unit_3_test_vector;
    
    // Тест 1
    unit_3_test_vector.push_back(unit_3_testing_struct({42}, {}, "{}{}{}{42}"));
    // Тест 2
    unit_3_test_vector.push_back(unit_3_testing_struct({}, {42}, "{}"));
    // Тест 3
    unit_3_test_vector.push_back(unit_3_testing_struct({42}, {42}, "{}"));
    // Тест 4
    unit_3_test_vector.push_back(unit_3_testing_struct({100, 90, 80, 70}, {100}, "{{{}{}{}{70}}{}{}{80}}{}{}{90}"));
    // Тест 5
    unit_3_test_vector.push_back(unit_3_testing_struct({42, 10, 4, 1}, {42}, "{}{{}{{}{}{}{1}}{}{4}}{}{10}"));
    // Тест 6
    unit_3_test_vector.push_back(unit_3_testing_struct({42, 100, 300, 500}, {42}, "{}{}{{}{}{{}{}{}{500}}{300}}{100}"));
    // Тест 7
    unit_3_test_vector.push_back(unit_3_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, {100}, "{{{}{}{}{610}}{{}{}{}{255}}{}{600}}{{}{{}{}{}{45}}{{}{}{}{200}}{110}}{{{}{}{}{2500}}{{}{}{}{800}}{{}{}{}{10000}}{2000}}{500}"));
    // Тест 8
    unit_3_test_vector.push_back(unit_3_testing_struct({500, 100, 600, 2000}, {42, 4242, 424242}, "{{}{}{}{600}}{{}{}{}{100}}{{}{}{}{2000}}{500}"));
    
    unit_3_test_group.data_set = unit_3_test_vector;
    unit_t.run_test_group(unit_3_test_group);
    
    unit_t.finish_testing();
}
