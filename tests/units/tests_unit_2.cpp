#include "tests_unit_2.hpp"

/*
 Модуль 2: Тестирование добавления элемента, копирования объектов, а также вывод дерева в строку
 Тестируемые методы: add_element(), has_element(), convert_to_string()
 
 Тест 1: просто добавляем один элемент
 Тест 2: добавляем все элементы в середину
 Тест 3: добавляем все элементы влево
 Тест 4: добавляем все элементы вправо
 Тест 5: добавляем по одному элементу в каждый узел
 Тест 6: добавляем много элементов
 Тест 7: добавляем кучу одинаковых элементов
 Тест 8: не добавляем элементов
 Тест 9: проверяем добавление переменных
 Тест 10: проверяем копирование объекта
 */

struct unit_2_testing_struct {
    vector<int> vec;
    string converted_string;
    
    unit_2_testing_struct(initializer_list<int> list, string _converted_string) {
        vec.insert(vec.begin(), list.begin(), list.end());
        converted_string = _converted_string;
    }
};

bool unit_2_testing_function(unit_2_testing_struct testing_struct) {
    thriar<int> tree(compare_function);
    for (int i = 0; i < testing_struct.vec.size(); i++) {
        tree.add_element(testing_struct.vec[i]);
    }
    
    for (int i = 0; i < testing_struct.vec.size(); i++) {
        if (tree.has_element(testing_struct.vec[i]) == false) {
            return false;
        }
    }
    
    if (tree.convert_to_string(int_to_string) != testing_struct.converted_string) {
        return false;
    }
    
    return true;
}

void run_tests_unit_2() {
    unit_testing unit_t(2);

    test_group<unit_2_testing_struct> unit_2_test_group;
    unit_2_test_group.group_name = "group test 1";
    unit_2_test_group.test_function = unit_2_testing_function;
    vector<unit_2_testing_struct> unit_2_test_vector;
    
    // Тест 1
    unit_2_test_vector.push_back(unit_2_testing_struct({42}, "{}{}{}{42}"));
    // Тест 2
    unit_2_test_vector.push_back(unit_2_testing_struct({100, 90, 80, 70}, "{{{{}{}{}{70}}{}{}{80}}{}{}{90}}{}{}{100}"));
    // Тест 3
    unit_2_test_vector.push_back(unit_2_testing_struct({42, 10, 4, 1}, "{}{{}{{}{{}{}{}{1}}{}{4}}{}{10}}{}{42}"));
    // Тест 4
    unit_2_test_vector.push_back(unit_2_testing_struct({42, 100, 300, 500}, "{}{}{{}{}{{}{}{{}{}{}{500}}{300}}{100}}{42}"));
    // Тест 5
    unit_2_test_vector.push_back(unit_2_testing_struct({500, 100, 600, 2000}, "{{}{}{}{600}}{{}{}{}{100}}{{}{}{}{2000}}{500}"));
    // Тест 6
    unit_2_test_vector.push_back(unit_2_testing_struct({500, 100, 45, 110, 200, 600, 255, 610, 2000, 800, 2500, 10000}, "{{{}{}{}{610}}{{}{}{}{255}}{}{600}}{{{}{}{}{110}}{{}{}{}{45}}{{}{}{}{200}}{100}}{{{}{}{}{2500}}{{}{}{}{800}}{{}{}{}{10000}}{2000}}{500}"));
    // Тест 7
    unit_2_test_vector.push_back(unit_2_testing_struct({50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50}, "{}{}{}{50}"));
    // Тест 8
    unit_2_test_vector.push_back(unit_2_testing_struct({}, "{}"));
    
    unit_2_test_group.data_set = unit_2_test_vector;
    unit_t.run_test_group(unit_2_test_group);
    
    // Тест 9
    unit_t.run_single_test([]() {
        thriar<int> tree(compare_function);
        int elem = 40;
        tree.add_element(elem);
        elem *= 100;
        if ((tree.has_element(40) == true)) {
            return true;
        } else {
            return false;
        }
        return false;
    }, "single test 1");
    
    // Тест 10
    unit_t.run_single_test([]() {
        thriar<int> tree(compare_function);
        tree.add_element(500);
        tree.add_element(100);
        tree.add_element(600);
        tree.add_element(2000);
        
        thriar<int> copied_tree = tree.copy_tree();
        if (copied_tree.convert_to_string(int_to_string) != "{{}{}{}{600}}{{}{}{}{100}}{{}{}{}{2000}}{500}") {
            return false;
        }
        return true;
    }, "single test 2");
    
    unit_t.finish_testing();
}
