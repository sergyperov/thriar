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
    thriar_node<T>* head_node = new thriar_node<T>();
    head = head_node;
    
    parse_tree(s, head, from_str_function);
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
        return find_node(current_head->left, data);
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
string thriar<T>::convert_to_string() {
    stringstream ss;
    
    traversal(head, [&ss](thriar_node<T>* node){
        if (!node) {
            ss << "{}";
        } else {
            ss << "{" << node->data << "}";
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
    thriar<T> cloned_thriar(allocation_function);
    cloned_thriar.head = clone_node(head);
    
    return cloned_thriar;
}

/*
 Применяем на дереве метод where по функции where_function()
 */
template <typename T>
thriar<T> thriar<T>::where(bool (*where_function)(T)) {
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
    
    thriar<T> cloned_thriar(allocation_function);
    cloned_thriar.head = clone_node(found_node);
    
    return cloned_thriar;
}

template <typename T>
template <typename U> thriar<U> thriar<T>::map(int (*_allocation_function)(U,U), U (*map_function)(T)) {
    thriar<U> cloned_thriar(_allocation_function);
    traversal(head, [map_function, &cloned_thriar](thriar_node<T>* node){
        U new_data = map_function(node->data);
        cloned_thriar.add_element(new_data);
    });
    
    return cloned_thriar;
}


