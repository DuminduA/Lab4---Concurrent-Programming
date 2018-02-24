#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "time.h"

using namespace std;

int main() {
    srand((unsigned int) time(NULL)); // set a different seed for each test
    int a =100;
    std::cout << "hello" << std::endl;
    std::cout << printf("%d\n", a) << std::endl;
    std::cout << "hello" << std::endl;
    return 0;
}

