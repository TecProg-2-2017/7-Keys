/*
 * File: main.cpp
 *
 * Description: Elementary testing of library functionalities.
 */

#include "7keys.h"
#include <iostream>

using namespace std;

// Method that runs the aplication
int main(int, char *[]) {

    try {

        srand(time(NULL));
        SevenKeys keys;
        keys.init("7 Keys", 1280, 720, 1, true);
        keys.run();
    }
    catch (Exception ex) {

        cerr << ex.message() << endl;
        return -1;
    }
    return 0;
}
