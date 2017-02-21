//
//  main.cpp
//  graphlib
//
//  Created by Yann Orlarey on 31/01/2017.
//  Copyright © 2017 Yann Orlarey. All rights reserved.
//

#include <iostream>
#include <list>
#include "tests.hpp"

using namespace std;


int main(int argc, const char* argv[])
{
    cout << "Tests digraph library\n";

    bool r = true;
    r &= check0();
    r &= check1();
    r &= check2();
    //r &= check3();

    return (r) ? 0 : -1;
}
