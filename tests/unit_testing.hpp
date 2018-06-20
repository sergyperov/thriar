#ifndef unit_testing_hpp
#define unit_testing_hpp

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "thriar.hpp"

#include "tests_unit_1.hpp"
#include "tests_unit_2.hpp"
#include "tests_unit_3.hpp"
#include "tests_unit_4.hpp"
#include "tests_unit_5.hpp"
#include "tests_unit_6.hpp"
#include "tests_unit_7.hpp"

using namespace std;

template <typename form_data>
struct test_group {
    string group_name;
    
    bool (*test_function)(form_data);
    vector<form_data> data_set;
};


/*
 Own class to perform unit testing
 
 A new class object should be inited for each unit of tests
 Constructor works like: unit_testing (UNIT_NUMBER)
 
 Testing will start right afer object creation
 
 Call run_single_test() to run a test case for a particular function
 Call run_test_group() to run a group of test data for one particular function
 After the last test call finish_testing()
 */
class unit_testing {
private:
    int unit_number;
    int current_test_id = 0;
    
    bool is_aborted = false;
    string aborted_group_name;
    int aborted_group_data_id;
    
    int test_output_padding = 3;
    
    void start_testing();
    void abort_testing(string group_name, int group_data_id);
public:
    unit_testing(int _unit_number) {
        unit_number = _unit_number;
        start_testing();
    }
    
    template <typename form_data> void run_test_group(test_group<form_data> current_test_group);
    void run_single_test(bool (*test_function)(), string group_name);
    void finish_testing();
};

template <typename form_data>
void unit_testing::run_test_group(test_group<form_data> current_test_group) {
    if (is_aborted) {
        return;
    }
    
    for (int i = 0; i < current_test_group.data_set.size(); i++) {
        current_test_id++;
        
        cout << "[UNIT TESTING] TEST #" << current_test_id << ":";
        int spaces_count = test_output_padding - (int)to_string(current_test_id).length();
        for (int i = 0; i < spaces_count; i++) {
            cout << " ";
        }
        
        bool test_result = current_test_group.test_function(current_test_group.data_set[i]);
        if (test_result == true) {
            cout << "OK." << endl;
        } else {
            cout << "FAILED." << endl;
            abort_testing(current_test_group.group_name, i+1);
            break;
        }
    }
}

void run_tests();
int compare_function(int cur_elem, int new_elem);
int compare_function_double(double cur_elem, double new_elem);
int compare_function_string(string cur_elem, string new_elem);

string int_to_string(int a);
string double_to_string(double a);
string str_to_string(string a);

#endif /* unit_testing_hpp */
