#include "thriar.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <functional>

using namespace std;

/*
 Конструктор, который требует только функцию распределания элементов
 */
template <typename T>
thriar<T>::thriar(int (*_allocation_function)(T,T)) {
    allocation_function = _allocation_function;
}

/*
 Конструктор, который требует функцию распределания элементов, а также закодированное дерево (формат 213К)
 Данный конструктор также требует функцию-расшифровщик (строка -> тип T)
 */
template <typename T>
thriar<T>::thriar(int (*_allocation_function)(T,T), string s, T (*from_str_function)(string)) {
    allocation_function = _allocation_function;
    
    if (s != "{}") {
        thriar_node<T>* head_node = new thriar_node<T>();
        head = head_node;
        
        parse_tree(s, head, from_str_function);
    }
}

/*
 Конструктор, который требует только функцию распределания элементов
 */
template <typename T>
thriar<T>::~thriar() {
    traversal(head, [&](thriar_node<T>* node) {
        remove_node(node);
    });
}

/*
 Вспомогательная функция для поиска финальной закрывающейся скобки }
 Принимается, что s[0] = '{'
 
 То есть ищем первый цельный фрагмент {...}
 */
template <typename T>
long int thriar<T>::find_last_closing_index(string s) {
    int opened_count = 0;
    int closed_count = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '{') {
            opened_count++;
        }
        if (s[i] == '}') {
            closed_count++;
        }
        
        if (opened_count == closed_count) {
            return i;
        }
    }
    
    return -1;
}

/*
 Рекурсивный парсинг дерева из строки
 Формат записи для считывания: {2}{1}{3}{K}
 
 По сути находим поочерёдно три фигурных скобки (если их меньше - это ошибка), и если там внутри не пустота, запускаем их рекрусию
 Если в первых трёх пустота - это указатели на null
 Четвёртый блок - это корень (значение)
 */
template <typename T>
void thriar<T>::parse_tree(string s, thriar_node<T>* current_node, T (*from_str_function)(string)) {
    long int middle=0, left=0, right=0, node=0;
    bool has_error = false;
    
    // находим индексы
    long int middle_i = find_last_closing_index(s);
    if (middle_i != -1) {
        middle = find_last_closing_index(s);
        long int left_i = find_last_closing_index(s.substr(middle+1, s.length()-middle));
        if (left_i != -1) {
            left = middle + 1 + find_last_closing_index(s.substr(left+1, s.length()-left));
            long int right_i = find_last_closing_index(s.substr(middle+1, s.length()-middle));
            if (right_i != -1) {
                right = left + 1 + find_last_closing_index(s.substr(left+1, s.length()-left));
                long int node_i = find_last_closing_index(s.substr(right+1, s.length()-right));
                if (node_i != -1) {
                    node = right + 1 + find_last_closing_index(s.substr(right+1, s.length()-right));
                } else {
                    has_error = true;
                }
            } else {
                has_error = true;
            }
        } else {
            has_error = true;
        }
    } else {
        has_error = true;
    }
    
    if (has_error == true) {
        throw runtime_error("Input format error");
    }
    
    // создаём соответсвующий строки
    string s_middle = s.substr(1, middle-1);
    string s_left = s.substr(middle+2, left-middle-2);
    string s_right = s.substr(left+2, right-left-2);
    string s_node = s.substr(right+2, node-right-2);
    
    /*
     Поочерёдно проверяем середину-лево-право
     Если не пустота, продолжаем рекурсию
    */
    
    if (s_middle == "") {
        current_node->middle = NULL;
    } else {
        thriar_node<T>* new_node = new thriar_node<T>();
        current_node->middle = new_node;
        current_node->middle->parent = current_node;
        parse_tree(s_middle, current_node->middle, from_str_function);
    }
    
    if (s_left == "") {
        current_node->left = NULL;
    } else {
        thriar_node<T>* new_node = new thriar_node<T>();
        current_node->left = new_node;
        current_node->left->parent = current_node;
        parse_tree(s_left, current_node->left, from_str_function);
    }
    
    if (s_right == "") {
        current_node->right = NULL;
    } else {
        thriar_node<T>* new_node = new thriar_node<T>();
        current_node->right = new_node;
        current_node->right->parent = current_node;
        parse_tree(s_right, current_node->right, from_str_function);
    }
    
    // для самого узла проставляем значение корня
    current_node->data = from_str_function(s_node);
}

/*
 Добавление нового узла
 */
template <typename T>
void thriar<T>::add_node(thriar_node<T>* current_head, thriar_node<T>* current_node) {
    if (!current_node) {
        return;
    }
    
    if (!head) {
        head = current_node;
        return;
    }
    
    int allocation_result = allocation_function(current_head->data, current_node->data);
    if (allocation_result == 1) {
        if (!current_head->left) {
            current_head->left = current_node;
            current_head->left->parent = current_head;
        } else {
            add_node(current_head->left, current_node);
        }
    } else if (allocation_result == 2) {
        if (!current_head->middle) {
            current_head->middle = current_node;
            current_head->middle->parent = current_head;
        } else {
            add_node(current_head->middle, current_node);
        }
    } else if (allocation_result == 3) {
        if (!current_head->right) {
            current_head->right = current_node;
            current_head->right->parent = current_head;
        } else {
            add_node(current_head->right, current_node);
        }
    }
}

/*
 Добавление нового элемента
 */
template <typename T>
void thriar<T>::add_element(T data) {
    thriar_node<T>* new_node = new thriar_node<T>();
    new_node->data = data;
    
    if (!head) {
        head = new_node;
        head->parent = head;
    } else {
        add_node(head, new_node);
    }
}

/*
 Находим узел в current_head со значением data
 Или NULL, если такого узла не нашлось
 */
template <typename T>
thriar_node<T>* thriar<T>::find_node(thriar_node<T>* current_head, T data) {
    if (!current_head) {
        return NULL;
    }
    
    int allocation_result = allocation_function(current_head->data, data);
    if (allocation_result == 0) {
        return current_head;
    } else if (allocation_result == 1) {
        return find_node(current_head->left, data);
    } else if (allocation_result == 2) {
        return find_node(current_head->middle, data);
    } else if (allocation_result == 3) {
        return find_node(current_head->right, data);
    } else {
        return NULL;
    }
}

/*
 Удаление корня
 
 Идея: запонимаем родителя корня и его детей, удаляем сам корень, а далее добавляем к родителя поочерёдно середину, левый и правый узел
 */
template <typename T>
void thriar<T>::remove_node(thriar_node<T>* current_head) {
    thriar_node<T>* current_head_left = current_head->left;
    thriar_node<T>* current_head_middle = current_head->middle;
    thriar_node<T>* current_head_right = current_head->right;
    
    // отдельный случай для head
    if (current_head == head) {
        delete current_head;
        head = current_head_middle;
        add_node(head, current_head_left);
        add_node(head, current_head_right);
        
        return;
    }
    
    thriar_node<T>* current_head_parent = current_head->parent;
    int allocation_result = allocation_function(current_head->parent->data, current_head->data);
    
    if (allocation_result == 1) {
        current_head_parent->left = NULL;
    } else if (allocation_result == 2) {
        current_head_parent->middle = NULL;
    } else if (allocation_result == 3) {
        current_head_parent->right = NULL;
    }
    delete current_head;
    
    add_node(current_head_parent, current_head_middle);
    add_node(current_head_parent, current_head_left);
    add_node(current_head_parent, current_head_right);
}

/*
 Удаление элемент со значением data (если такой есть)
 
 Идея: запонимаем родителя корня и его детей, удаляем сам корень, а далее добавляем к родителя поочерёдно середину, левый и правый узел
 */
template <typename T>
void thriar<T>::remove_element(T data) {
    thriar_node<T>* found_node = find_node(head, data);
    if (!found_node) {
        return;
    } else {
        remove_node(found_node);
    }
}

/*
    Обход дерева (213К)
 */
template <typename T>
void thriar<T>::traversal(thriar_node<T>* current_head, function<void(thriar_node<T>*)>process_function) {
    if (!current_head) {
        return;
    }
    
    traversal(current_head->middle, process_function);
    traversal(current_head->left, process_function);
    traversal(current_head->right, process_function);
    
    process_function(current_head);
}

/*
 Обход дерева (213К) c функциями, которые вызываются перед и после обработки текущего узла
 */
template <typename T>
void thriar<T>::traversal(thriar_node<T>* current_head, function<void(thriar_node<T>*)>process_function, function<void(thriar_node<T>*)>preprocess_function, function<void(thriar_node<T>*)>postprocess_function){
    if (!current_head) {
        process_function(current_head);
        return;
    }
    
    if (current_head != head){
        preprocess_function(current_head);
    }
    traversal(current_head->middle, process_function, preprocess_function, postprocess_function);
    traversal(current_head->left, process_function, preprocess_function, postprocess_function);
    traversal(current_head->right, process_function, preprocess_function, postprocess_function);
    
    process_function(current_head);
    if (current_head != head){
        postprocess_function(current_head);
    }
}

/*
 Конвертируем дерево в строку согласно условию обходу {2}{1}{3}{К}
 */
template <typename T>
string thriar<T>::convert_to_string(string (*to_str_function)(T)) {
    stringstream ss;
    
    traversal(head, [&ss, to_str_function](thriar_node<T>* node){
        if (!node) {
            ss << "{}";
        } else {
            ss << "{" << to_str_function(node->data) << "}";
        }
    },[&ss](thriar_node<T>* node){
        ss << "{";
    },[&ss](thriar_node<T>* node){
        ss << "}";
    });
    
    string s = ss.str();
    return s;
}

/*
 Проверка на вхождение элемента
 */
template <typename T>
bool thriar<T>::has_element(T data) {
    thriar_node<T>* found_node = find_node(head, data);
    
    return !!found_node;
}

/*
 Проверка на совпадение у некоторого узла current_head узла arg_head (и всех их потомков)
 */
template <typename T>
bool thriar<T>::has_subnodes(thriar_node<T>* current_head, thriar_node<T>* arg_head) {
    if ((!current_head) && (!arg_head)) {
        return true;
    } else if ((!current_head) || (!arg_head)) {
        return false;
    }
    
    bool check_child_nodes = has_subnodes(current_head->left, arg_head->left) && has_subnodes(current_head->middle, arg_head->middle) && has_subnodes(current_head->right, arg_head->right);
    
    if ((current_head->data == arg_head->data) && (check_child_nodes == true)) {
        return true;
    } else {
        return false;
    }
}

/*
 Проверка на наличие поддерва
 
 По сути находм head требуемого поддера, дальше проверям уже их узлы
 */
template <typename T>
bool thriar<T>::has_subtree(thriar<T> subtree) {
    // нам дали путое дерево, пустое дерево - поддерево любого дерева
    if (!subtree.head) {
        return true;
    }
    
    thriar_node<T>* found_node = find_node(head, subtree.head->data);
    if (!!found_node) {
        return has_subnodes(found_node, subtree.head);
    } else {
        return false;
    }
}

/*
 Рекурсивное клонирование узла (именно по указателям, а не по новой всё заполняем)
 */
template <typename T>
thriar_node<T>* thriar<T>::clone_node(thriar_node<T>* node_to_clone) {
    if (!node_to_clone) {
        return node_to_clone;
    }
        
    thriar_node<T>* temp_node = new thriar_node<T>();
    temp_node->data = node_to_clone->data;
    
    temp_node->left = clone_node(node_to_clone->left);
    temp_node->middle = clone_node(node_to_clone->middle);
    temp_node->right = clone_node(node_to_clone->right);
    
    if (temp_node->left) {
        temp_node->left->parent = temp_node;
    }
    if (temp_node->middle) {
        temp_node->middle->parent = temp_node;
    }
    if (temp_node->right) {
        temp_node->right->parent = temp_node;
    }
    
    return temp_node;
}

/*
 Клонируем всё дерево
 */
template <typename T>
thriar<T> thriar<T>::copy_tree() {
    thriar<T> cloned_thriar = thriar<T>(allocation_function);
    cloned_thriar.head = clone_node(head);
    
    return cloned_thriar;
}

/*
 Применяем на дереве метод where по функции where_function()
 */
template <typename T>
thriar<T> thriar<T>::where(function<bool(T)>where_function) {
    thriar<T> cloned_thriar = copy_tree();
    
    cloned_thriar.traversal(cloned_thriar.head, [where_function, &cloned_thriar](thriar_node<T>* node) {
        bool where_result = where_function(node->data);
        
        if (where_result == false) {
            cloned_thriar.remove_node(node);
        }
    });
    
    return cloned_thriar;
}

template <typename T>
thriar<T> thriar<T>::create_subtree(T data) {
    thriar_node<T>* found_node = find_node(head, data);
    
    thriar<T> cloned_thriar = thriar<T>(allocation_function);
    cloned_thriar.head = clone_node(found_node);
    
    return cloned_thriar;
}

template <typename T>
template <typename U> thriar<U> thriar<T>::map(int (*_allocation_function)(U,U), function<U(T)>map_function) {
    thriar<U> cloned_thriar(_allocation_function);
    traversal(head, [map_function, &cloned_thriar](thriar_node<T>* node){
        U new_data = map_function(node->data);
        cloned_thriar.add_element(new_data);
    });
    
    return cloned_thriar;
}

template <typename T>
thriar<T> thriar<T>::merge(thriar<T> tree) {
    thriar<T> cloned_thriar = copy_tree();
    
    tree.traversal(tree.head, [&cloned_thriar](thriar_node<T>* node){
        cloned_thriar.add_element(node->data);
    });
    
    return cloned_thriar;
}

template <typename T>
thriar<T>::thriar(const thriar<T> & rhs) {
    allocation_function = rhs.allocation_function;
    head = clone_node(rhs.head);
}

template <typename T>
thriar<T> thriar<T>::operator=(const thriar<T> & rhs)
{
    if(this == &rhs)
        return *this;
    allocation_function = rhs.allocation_function;
    head = clone_node(rhs.head);
    return *this;
}


