//
//  main.cpp
//  graphlib
//
//  Created by Yann Orlarey on 31/01/2017.
//  Copyright © 2017-2019 GRAME. All rights reserved.
//

#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include "tests.hh"

void newtest()
{
    digraph<char, multidep> g;
    g.add('A', 'B', {{"VecA", 2}, {"VecB", 0}});
    std::cout << "g = " << g << std::endl;
}

int main(int, const char**)
{
    std::cout << "Tests digraph library\n";
    newtest();

    bool r = true;
    r &= check0();
    r &= check1();
    r &= check2();
    r &= check3();
    r &= check4();
    r &= check5();
    r &= check7();
    r &= check8();
    r &= check9();
    r &= check10();
    r &= check11();
    r &= check12();
    r &= check13();
    r &= check14();
    r &= check15();

    return (r) ? 0 : 1;
}
