#ifndef thriar_hpp
#define thriar_hpp

#include <stdio.h>

using namespace std;

template <typename T>
struct thriar_node {
    T data;
    thriar_node<T>* left;
    thriar_node<T>* middle;
    thriar_node<T>* right;
    
    thriar_node<T>* parent;
};

template <typename T>
class thriar {
private:
    int (*allocation_function)(T,T);
    thriar_node<T>* head = NULL;
    
    void add_node(thriar_node<T>* current_head, thriar_node<T>* current_node);
    void remove_node(thriar_node<T>* current_head);
    
    void traversal(thriar_node<T>* current_head, function<void(thriar_node<T>*)>process_function);
    void traversal(thriar_node<T>* current_head, function<void(thriar_node<T>*)>process_function, function<void(thriar_node<T>*)>preprocess_function, function<void(thriar_node<T>*)>postprocess_function);
    
    bool has_subnodes(thriar_node<T>* current_head, thriar_node<T>* arg_head);
    thriar_node<T>* find_node(thriar_node<T>* current_head, T data);
    
    thriar_node<T>* clone_node(thriar_node<T>* node_to_clone);
    
public:
    thriar(int (*_allocation_function)(T,T));
    thriar(int (*_allocation_function)(T,T), string s, T (*from_str_function)(string));
    
    void add_element(T data);
    void remove_element(T data);
    
    bool has_element(T data);
    bool has_subtree(thriar<T> subtree);
    
    string convert_to_string();
    
    thriar<T> copy_tree();
    thriar<T> create_subtree(T data);
    thriar<T> where(bool (*where_function)(T));
    template <typename U> thriar<U> map(int (*_allocation_function)(U,U), U (*map_function)(T));
};

#include "thriar.cpp"

#endif /* thriar_hpp */
