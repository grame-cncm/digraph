//
//  main.cpp
//  graphlib
//
//  Created by Yann Orlarey on 31/01/2017.
//  Copyright © 2017-2021 GRAME. All rights reserved.
//

#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include "dglib/arrow.hh"
#include "dglib/digraph.hh"
#include "dglib/digraphop.hh"
#include "dglib/stdprinting.hh"
#include "mtests.hh"
#include "tests.hh"

void newtest()
{
    digraph<char, multidep> g;
    g.add('A', 'B', {{{"M", 2}, {"N", 0}}, 0});
    std::cout << "g = " << g << std::endl;
    dotfile(std::cout, g);
}

int main(int, const char**)
{
    std::cout << "Tests digraph library\n";
    // newtest();

    bool r = true;
    r &= mcheck0();
    r &= mcheck1();
    r &= mcheck2();
    r &= mcheck3();
    r &= mcheck4();
    r &= mcheck5();
    r &= check1();
    // r &= check2();
    // r &= check3();
    r &= check4();
    r &= check5();
    // r &= check7();
    r &= check8();
    r &= check9();
    r &= check10();
    r &= check11();
    r &= check12();
    r &= check13();
    // r &= check14();
    // r &= check15();

    return (r) ? 0 : 1;
}
