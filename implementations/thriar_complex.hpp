#ifndef thriar_complex_hpp
#define thriar_complex_hpp

#include "thriar.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <string>

void thriar_complex_cli();

struct complex {
    int a;
    int b;
    
    complex() {};
    complex(int _a, int _b) {
        a = _a;
        b = _b;
    }
    
    double length() {
        return sqrt(a*a + b*b);
    }
};

#endif /* thriar_complex_hpp */
