#include <iostream>
#include "thriar.hpp"

using namespace std;

int compare(int a, int b) {
    int e = a*0.5;
    int el = a - e;
    int er = a + e;
    
    if (b < el) {
        return 1;
    } else if ((el <= b) && (b <= er)) {
        if (a == b) {
            return 0;
        } else {
            return 2;
        }
    } else if (b > el) {
        return 3;
    }
    
    return 4;
}

int main() {
    thriar<int> t(compare);
    t.add_element(300);
    t.add_element(100);
    t.add_element(20);
    t.add_element(50);
    t.add_element(200);
    t.add_element(230);
    t.add_element(160);
    t.add_element(10);
    
    thriar<int> t2 = t.map<int>(compare, [](int a){return a+50;});
    cout << t2.convert_to_string() << endl;
}
